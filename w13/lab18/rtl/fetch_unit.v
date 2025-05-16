module fetch_unit #(
    INSTRUCTION_WIDTH = 16,              // Width of the instructions
    ADDR_WIDTH        = 8,               // Width of the address bus (determines depth)
    MEM_DEPTH         = 1 << ADDR_WIDTH  // Calculate depth (e.g., 16 bits -> 65536 locations)
) (
    // Inputs
    input wire clk,
    input wire en_pc,  // Increments PC when enabled
    input wire reset,
    input wire [15:0] last_alu_result,

    // Outputs
    output wire [INSTRUCTION_WIDTH-1:0] instruction_out
);

    // init wires
    reg [ADDR_WIDTH-1:0] current_inst, next_inst;

    // init PC
    // resets on its own
    register pc (
        .d_in(next_inst),
        .reset(reset),
        .clk(clk),
        .en(en_pc),
        .d_out(current_inst)
    );

    // init memory
    reg [INSTRUCTION_WIDTH-1:0] memory[MEM_DEPTH];
    assign instruction_out = memory[current_inst];

    always @(*) begin
        next_inst = current_inst + 1'b1;  // Default action: fetch next sequential instruction

        // Instruction format assumed for branch:
        // inst[1:0]   : Opcode (2'b10 for branch)
        // inst[3:2]   : Condition code
        // inst[15:4]  : 12-bit immediate address/offset

        // Check if the instruction is a branch type (lowest 2 bits are 2'b10)
        if (instruction_out[1:0] == 2'b10) begin
            // Extract condition bits and immediate value directly from instruction_out.

            // The immediate value from instruction_out[15:4] is 12 bits.
            // next_inst is ADDR_WIDTH bits.
            // Assigning the 12-bit immediate to the 16-bit next_inst will
            // result in zero-extension (e.g., next_inst = {4'b0, instruction_out[15:4]}),
            // which is typical for absolute branch targets.

            // Branch condition evaluation
            if (instruction_out[3:2] == 2'b00 && last_alu_result == 16'd0) begin // Condition: last_alu_result is 0
                next_inst = instruction_out[11:4];
            end
            else if (instruction_out[3:2] == 2'b01 && last_alu_result == 16'd1) begin // Condition: last_alu_result is 1
                next_inst = instruction_out[11:4];
            end
            else if (instruction_out[3:2] == 2'b10 && last_alu_result == 16'd2) begin // Condition: last_alu_result is 2
                next_inst = instruction_out[11:4];
            end
            // Note: If instruction_out[3:2] is 2'b11, or if none of the above conditions are met
            // (e.g., last_alu_result does not match for the given cond),
            // then next_inst remains current_inst + 1 (branch not taken). This is correct.
        end
    end

    // Dump signals for WAVES=1
    initial begin
        integer i;
        for (i = 0; i < MEM_DEPTH; i = i + 1) memory[i] = 1;

        $dumpfile("dump.vcd");
        $dumpvars(1, fetch_unit);
    end

endmodule
