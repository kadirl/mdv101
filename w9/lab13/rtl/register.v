module register (
    input wire [15:0] d_in,  // Data input
    input wire reset,        // Asynchronous reset
    input wire clk,          // Clock input
    input wire en,           // Enable input
    output reg [15:0] d_out  // Data output
);

    reg [15:0] storage; // Internal storage register

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            storage <= 16'b0; // Reset to 0
        end else if (en) begin
            storage <= d_in; // Load data when enabled
        end
    end

    assign d_out = storage; // Assign internal storage to output

endmodule
