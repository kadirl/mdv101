module key_lock_fsm (
    input wire clk,
    input wire rst,
    input wire [3:0] key_in, // 4-bit input for single digit
    output reg [2:0] state_debug,
    output reg locked // 1 = locked, 0 = unlocked
);

    parameter LOCKED   = 3'd0;
    parameter STATE1   = 3'd1;
    parameter STATE2   = 3'd2;
    parameter STATE3   = 3'd3;
    parameter STATE4   = 3'd4;
    parameter STATE5   = 3'd5;
    parameter UNLOCKED = 3'd6;

    reg [2:0] current_state, next_state;

    always @(posedge clk or posedge rst) begin
        if (rst)
            current_state <= LOCKED;
        else
            current_state <= next_state;
    end

    always @(*) begin
        next_state = LOCKED; // Default state
        case (current_state)
            LOCKED:   next_state = (key_in == 4'd3) ? STATE1 : LOCKED;
            STATE1:   next_state = (key_in == 4'd3) ? STATE2 : LOCKED;
            STATE2:   next_state = (key_in == 4'd5) ? STATE3 : LOCKED;
            STATE3:   next_state = (key_in == 4'd2) ? STATE4 : LOCKED;
            STATE4:   next_state = (key_in == 4'd5) ? STATE5 : LOCKED;
            STATE5:   next_state = (key_in == 4'd6) ? UNLOCKED : LOCKED;
            UNLOCKED: next_state = UNLOCKED; // Stays unlocked
            default:  next_state = LOCKED;
        endcase
    end

    always @(*) begin
        case (current_state) 
            UNLOCKED:   locked = 1'b0;
            default:    locked = 1'b1;
        endcase
    end

    assign state_debug = current_state;
endmodule
