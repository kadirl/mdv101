module alu(
    input   wire [15:0] in_a,
    input   wire [15:0] in_b,
    input   wire [2:0]  select,

    output  reg  [15:0] alu_out
);  
    always @(*) begin
        case (select)
            3'b000: alu_out = in_a + in_b;
            3'b001: alu_out = in_a - in_b;
            3'b010: alu_out = in_a & in_b;
            3'b011: alu_out = in_a | in_b;
            3'b100: alu_out = in_a ^ in_b;
            3'b101: alu_out = in_a << in_b[3:0];
            3'b110: alu_out = in_a >> in_b[3:0];
            3'b111: begin
                if (in_a == in_b) begin
                    alu_out = 16'b00; // 0 if equal
                end else if (in_a > in_b) begin
                    alu_out = 16'b01; // 1 if in_a > in_b
                end else begin
                    alu_out = 16'b10; // 2 if in_a < in_b
                end
            end
            default: alu_out = 16'b0;
        endcase
    end

    // Dump signals for WAVES=1
    initial begin
        $dumpfile("alu.fst");
        $dumpvars(0, alu);
    end
endmodule
