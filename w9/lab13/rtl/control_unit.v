module control_unit(
    input [15:0] d_in,

    input wire clk,
    input wire reset,
    input wire run,

    output reg [2:0] alu_sel,
    output reg [3:0] mux_sel,
    output reg [15:0] i_out,  // immediate out

    output reg en_s,
    output reg en_c,
    output reg en_0,
    output reg en_1,
    output reg en_2,
    output reg en_3,
    output reg en_4,
    output reg en_5,
    output reg en_6,
    output reg en_7,
    output reg en_i,

    output reg done

    // output reg state_debug
);
    // Define states
    parameter STATE0 = 2'b00;  // save the instruction
    parameter STATE1 = 2'b01;  // get register value 
    parameter STATE2 = 2'b10;  // use ALU
    parameter STATE3 = 2'b11;  // save result value  

    // Parse d_in instruction
    wire [3:0]  rx          = {1'b0, d_in[15:13]};  // zero extend to 4-bit for 4 bit mux selector
    wire [3:0]  ry          = {1'b0, d_in[12:10]};  // zero extend to 4-bit for 4 bit mux selector
    wire [4:0]  res1        = d_in[9:5];
    wire [2:0]  _alu_sel    = d_in[4:2];
    wire [1:0]  res2        = d_in[1:0];
    
    // immediate value
    wire [7:0]  immediate   = d_in[12:5];
    assign i_out = {8'b0, immediate};


    // Model state register
    reg [1:0]   state, next_state;
    // assign state_debug = state;
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            state <= STATE0;
        end
        else if (run) begin
            state <= next_state;
        end
    end


    // Model next state logic
    always @(*) begin
        case(state)
            STATE0: next_state = STATE1;
            STATE1: next_state = STATE2;
            STATE2: next_state = STATE3;
            STATE3: next_state = STATE0;
        endcase
    end


    // Model output logic
    always @(*) begin
        // default values
        en_s = 1'b0;
        done = 1'b0;
        en_i = 1'b0;
        en_c = 1'b0;
        en_0 = 1'b0;
        en_1 = 1'b0;
        en_2 = 1'b0;
        en_3 = 1'b0;
        en_4 = 1'b0;
        en_5 = 1'b0;
        en_6 = 1'b0;
        en_7 = 1'b0;
        mux_sel = 4'b0;
        alu_sel = 3'b0;
        i_out = 16'b0;

        case (state) 
            // enable instruction register
            STATE0: en_i = 1'b1;

            // save Rx to Rs
            STATE1: begin
                // insturction parsing for immediate values
                // put immediate values into Rs register
                // if (res2 == 2'b01) begin
                //     mux_sel = 4'd8;  // select for immediate value 
                // end
                // insturction parsing for regular instructions
                // else begin
                mux_sel = rx;
                // end
                
                // enable write to Reg S (Rs)
                en_s = 1'b1;
            end

            // use ALU and save to Rc
            STATE2: begin
                // insturction parsing for immediate values
                if (res2 == 2'b01) begin
                    mux_sel = 4'd8;
                    // mux_sel = rx;  // 
                end
                // insturction parsing for regular instructions
                else begin
                    mux_sel = ry;
                end

                alu_sel = _alu_sel;
                en_c = 1'b1;
            end

            // move from Rc to Rx
            STATE3: begin
                done = 1'b1;
                case (rx) 
                    4'b0000: en_0 = 1'b1;
                    4'b0001: en_1 = 1'b1;
                    4'b0010: en_2 = 1'b1;
                    4'b0011: en_3 = 1'b1;
                    4'b0100: en_4 = 1'b1;
                    4'b0101: en_5 = 1'b1;
                    4'b0110: en_6 = 1'b1;
                    4'b0111: en_7 = 1'b1;
                    default: ;
                endcase
            end
        endcase
    end

endmodule
