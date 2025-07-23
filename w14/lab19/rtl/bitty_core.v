module bitty_core #(
    INSTRUCTION_WIDTH = 16,              // Width of the instructions
    ADDR_WIDTH        = 16,              // Width of the address bus (determines depth)
    MEM_DEPTH         = 1 << ADDR_WIDTH  // Calculate depth (e.g., 16 bits -> 65536 locations)
) (
    input clk,
    input reset,
    input [15:0] instruction,
    input run,

    output done,

    output [15:0] reg_instr_out,
    output [15:0] reg_s_out,
    output [15:0] reg_c_out,
    output [15:0] reg0_out,
    output [15:0] reg1_out,
    output [15:0] reg2_out,
    output [15:0] reg3_out,
    output [15:0] reg4_out,
    output [15:0] reg5_out,
    output [15:0] reg6_out,
    output [15:0] reg7_out,

    output [15:0] mux_out,
    output [15:0] alu_out
);
    wire en_i, en_s, en_c, en_0, en_1, en_2, en_3, en_4, en_5, en_6, en_7;
    wire [ 2:0] alu_sel;
    wire [ 3:0] mux_sel;
    wire [15:0] immediate_wire;

    wire [ 1:0] lsu_sel;
    wire [15:0] lsu_out;
    wire [15:0] to_store_to_reg;

    fetch_unit fetch_unit_inst (
        .clk(clk),
        .en_pc(done),
        .reset(reset),
        .instruction_out(instruction),
        .last_alu_result(reg_c_out)
    );

    lsu lsu (
        .clk(clk),
        .reset(!reset),
        .en_ls(lsu_sel),
        .address(mux_out[7:0]),
        .data_to_store(reg_s_out),
        .data_to_load(lsu_out)
    );

    control_unit control_inst (
        .d_in(reg_instr_out),

        .clk  (clk),
        .reset(reset),
        .run  (run),

        .alu_sel(alu_sel),
        .mux_sel(mux_sel),
        .i_out  (immediate_wire),

        .en_ls(lsu_sel),

        .en_i(en_i),
        .en_s(en_s),
        .en_c(en_c),
        .en_0(en_0),
        .en_1(en_1),
        .en_2(en_2),
        .en_3(en_3),
        .en_4(en_4),
        .en_5(en_5),
        .en_6(en_6),
        .en_7(en_7),

        .done(done)
    );

    register reg_instr_inst (
        .clk(clk),
        .reset(reset),
        .d_in(instruction),
        .en(en_i),
        .d_out(reg_instr_out)
    );

    register reg_s_inst (
        .clk(clk),
        .reset(reset),
        .d_in(mux_out),
        .en(en_s),
        .d_out(reg_s_out)
    );

    register reg_c_inst (
        .clk(clk),
        .reset(reset),
        .d_in(alu_out),
        .en(en_c),
        .d_out(reg_c_out)
    );

    // assign all general registers
    register reg0_inst (
        .clk(clk),
        .reset(reset),
        .d_in(to_store_to_reg),
        .en(en_0),
        .d_out(reg0_out)
    );
    register reg1_inst (
        .clk(clk),
        .reset(reset),
        .d_in(to_store_to_reg),
        .en(en_1),
        .d_out(reg1_out)
    );
    register reg2_inst (
        .clk(clk),
        .reset(reset),
        .d_in(to_store_to_reg),
        .en(en_2),
        .d_out(reg2_out)
    );
    register reg3_inst (
        .clk(clk),
        .reset(reset),
        .d_in(to_store_to_reg),
        .en(en_3),
        .d_out(reg3_out)
    );
    register reg4_inst (
        .clk(clk),
        .reset(reset),
        .d_in(to_store_to_reg),
        .en(en_4),
        .d_out(reg4_out)
    );
    register reg5_inst (
        .clk(clk),
        .reset(reset),
        .d_in(to_store_to_reg),
        .en(en_5),
        .d_out(reg5_out)
    );
    register reg6_inst (
        .clk(clk),
        .reset(reset),
        .d_in(to_store_to_reg),
        .en(en_6),
        .d_out(reg6_out)
    );
    register reg7_inst (
        .clk(clk),
        .reset(reset),
        .d_in(to_store_to_reg),
        .en(en_7),
        .d_out(reg7_out)
    );

    wire [15:0] mux_in_array[0:8];  // Create an array wire

    assign mux_in_array[0] = reg0_out;
    assign mux_in_array[1] = reg1_out;
    assign mux_in_array[2] = reg2_out;
    assign mux_in_array[3] = reg3_out;
    assign mux_in_array[4] = reg4_out;
    assign mux_in_array[5] = reg5_out;
    assign mux_in_array[6] = reg6_out;
    assign mux_in_array[7] = reg7_out;
    assign mux_in_array[8] = immediate_wire;

    mux mux_inst (
        .sel(mux_sel),
        .in (mux_in_array),  // Use the array wire
        .out(mux_out)
    );

    alu alu_inst (
        .in_a(reg_s_out),
        .in_b(mux_out),
        .select(alu_sel),
        .alu_out(alu_out)
    );

    assign to_store_to_reg = (lsu_sel == 2'b10) ? lsu_out : reg_c_out;

    // Dump signals for WAVES=1
    initial begin
        $dumpfile("bitty_core.fst");
        $dumpvars(0, bitty_core);
    end
endmodule
