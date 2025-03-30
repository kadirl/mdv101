module traffic_light_fsm (
    input clk,
    input reset,
    output reg [2:0] light
);
    // State encoding
    parameter RED = 2'b00;
    parameter GREEN = 2'b01;
    parameter YELLOW = 2'b10;
    parameter TIMER = 8'd2;
   
    reg [1:0] current_state, next_state;
    reg [7:0] elapsed_time = 0;

    // Model state register 
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            current_state <= RED;
            elapsed_time <= 0;
        end else if (elapsed_time >= TIMER) begin
            current_state <= next_state;
            elapsed_time <= 0;
        end else begin
            elapsed_time = elapsed_time + 1;
            current_state <= current_state;
        end
    end 

    // Model next state decode logic (combinational)
    always @(*) begin
        case (current_state)
            RED:        next_state = GREEN;
            GREEN:      next_state = YELLOW;
            YELLOW:     next_state = RED;
            default:    next_staet = RED;
        endcase
    end

    // Model output logic
    always @(*) begin
        case (current_state)
            RED:        light = 3'b001;
            GREEN:      light = 3'b010;
            YELLOW:     light = 3'b100;
            default:    light = 3'b001;
        endcase
    end
endmodule