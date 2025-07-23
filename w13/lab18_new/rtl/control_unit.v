module control_unit(
    input [15:0] d_in, // Input data bus

    input wire clk, // Clock signal
    input wire reset, // Reset signal
    input wire run, // Run signal

    output reg [2:0] alu_sel, // ALU selection signal
    output reg [3:0] mux_sel, // Mux selection signal
    output wire [15:0] i_out,  // Immediate output

    output reg en_s, // Enable signal for register S
    output reg en_c, // Enable signal for register C
    output reg en_0, // Enable signal for register 0
    output reg en_1, // Enable signal for register 1
    output reg en_2, // Enable signal for register 2
    output reg en_3, // Enable signal for register 3
    output reg en_4, // Enable signal for register 4
    output reg en_5, // Enable signal for register 5
    output reg en_6, // Enable signal for register 6
    output reg en_7, // Enable signal for register 7
    output reg en_i, // Enable signal for instruction register

    output reg done // Done signal

    // output reg state_debug
);
    // Define states
    parameter STATE0 = 2'b00;  // save the instruction
    parameter STATE1 = 2'b01;  // get register value 
    parameter STATE2 = 2'b10;  // use ALU
    parameter STATE3 = 2'b11;  // save result value  

    // Parse R-type instruction
    wire [3:0]  rx          = {1'b0, d_in[15:13]};  // zero extend to 4-bit for 4 bit mux selector
    wire [3:0]  ry          = {1'b0, d_in[12:10]};  // zero extend to 4-bit for 4 bit mux selector
    wire [4:0]  res1        = d_in[9:5];
    wire [2:0]  _alu_sel    = d_in[4:2];
    wire [1:0]  mode        = d_in[1:0]; // Responsible for J-type too
    
    // Parse I-type instruction
    wire [7:0]  immediate   = d_in[12:5];
    assign i_out = {8'b0, immediate};

    // Parse J-type instructions
    wire [11:0] pc_immediate = d_in[15:4];
    wire [1:0]  cond         = d_in[3:2]; // for branch type selection (eq, gt, lt)
    // d_in[1:0] for mode


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
        // i_out = 16'b0;

        case (state) 
            // enable instruction register
            STATE0: en_i = 1'b1;

            // save Rx to Rs
            STATE1: begin
                mux_sel = rx;
                
                // enable write to Reg S (Rs)
                en_s = 1'b1;
            end

            // use ALU and save to Rc
            STATE2: begin
                if (mode == 2'b01) begin
                    mux_sel = 4'd8;
                end

                else if (mode == 2'b00) begin
                    mux_sel = ry;
                end

                alu_sel = _alu_sel;
                if (mode != 2'b10) begin
                    en_c = 1'b1;
                end
            end

            // move from Rc to Rx
            STATE3: begin
                done = 1'b1;
                if (mode != 2'b10) begin
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
            end
        endcase
    end

    // Dump signals for WAVES=1
    initial begin
        $dumpfile("control_unit.fst");
        $dumpvars(0, control_unit);
    end

endmodule
