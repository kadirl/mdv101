module fetch_unit #(
    INSTRUCTION_WIDTH = 16,  // Width of the instructions
    ADDR_WIDTH = 16,        // Width of the address bus (determines depth)
    MEM_DEPTH  = 1 << ADDR_WIDTH // Calculate depth (e.g., 16 bits -> 65536 locations)
) (
    // Inputs
    input wire clk, 
    input wire en_pc,  // Increments PC when enabled
    input wire reset,

    // Outputs
    output wire [INSTRUCTION_WIDTH-1:0] instruction_out
);
    initial begin
        integer i;
        for (i = 0; i < MEM_DEPTH; i = i + 1)
            memory[i] = 0;
    end

    // init wires
    wire [ADDR_WIDTH-1:0] current_inst, next_inst;
    assign next_inst = current_inst + 1;

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
    reg [INSTRUCTION_WIDTH-1:0] memory [0:MEM_DEPTH-1];
    assign instruction_out = memory[current_inst];

    // process PC itself
    always @(posedge clk) begin
        if (reset) begin
            // current_inst <= 0;
            // next_inst <= 1;
        end
        // else if (en_pc) begin
        //     // current_inst <= next_inst;
        //     next_inst <= next_inst + 1;
        // end
    end

        // Dump signals for WAVES=1
    initial begin
        $dumpfile("fetch_unit.vcd");
        $dumpvars(1, fetch_unit);
    end

endmodule



