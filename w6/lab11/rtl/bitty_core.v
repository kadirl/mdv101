module bitty_core(
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
    wire en_i, en_s, en_c, en_0, en_1, en_2, en_3, en_4, en_5, en_6, en_7, mode, cmp, cout;
    wire [3:0] alu_sel;
    wire [2:0] mux_sel;

    control_unit control_inst(
        .d_in(reg_instr_out),

        .clk(clk),
        .reset(reset),
        .run(run),

        .alu_sel(alu_sel),
        .alu_mode(mode),
        .mux_sel(mux_sel),

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

    register reg_instr_inst(
        .clk(clk),
        .reset(reset), 
        .d_in(instruction), 
        .en(en_i),
        .d_out(reg_instr_out)
    );

    register reg_s_inst(
        .clk(clk),
        .reset(reset),
        .d_in(mux_out),
        .en(en_s),
        .d_out(reg_s_out)
    );

    register reg_c_inst(
        .clk(clk),
        .reset(reset),
        .d_in(alu_out),
        .en(en_c),
        .d_out(reg_c_out)
    );

    // assign all general registers
    register reg0_inst(
        .clk(clk),
        .reset(reset),
        .d_in(reg_c_out),
        .en(en_0),
        .d_out(reg0_out)
    );
    register reg1_inst(
        .clk(clk),
        .reset(reset),
        .d_in(reg_c_out),
        .en(en_1),
        .d_out(reg1_out)
    );
    register reg2_inst(
        .clk(clk),
        .reset(reset),
        .d_in(reg_c_out),
        .en(en_2),
        .d_out(reg2_out)
    );
    register reg3_inst(
        .clk(clk),
        .reset(reset),
        .d_in(reg_c_out),
        .en(en_3),
        .d_out(reg3_out)
    );
    register reg4_inst(
        .clk(clk),
        .reset(reset),
        .d_in(reg_c_out),
        .en(en_4),
        .d_out(reg4_out)
    );
    register reg5_inst(
        .clk(clk),
        .reset(reset),
        .d_in(reg_c_out),
        .en(en_5),
        .d_out(reg5_out)
    );
    register reg6_inst(
        .clk(clk),
        .reset(reset),
        .d_in(reg_c_out),
        .en(en_6),
        .d_out(reg6_out)
    );
    register reg7_inst(
        .clk(clk),
        .reset(reset),
        .d_in(reg_c_out),
        .en(en_7),
        .d_out(reg7_out)
    );

    wire [15:0] mux_in_array [0:7]; // Create an array wire

    assign mux_in_array[0] = reg0_out;
    assign mux_in_array[1] = reg1_out;
    assign mux_in_array[2] = reg2_out;
    assign mux_in_array[3] = reg3_out;
    assign mux_in_array[4] = reg4_out;
    assign mux_in_array[5] = reg5_out;
    assign mux_in_array[6] = reg6_out;
    assign mux_in_array[7] = reg7_out;

    mux mux_inst(
        .sel(mux_sel),
        .in(mux_in_array), // Use the array wire
        .out(mux_out)
    );

    alu alu_inst(
        .carry_in(1'b0),
        .in_a(reg_s_out),
        .in_b(mux_out),
        .select(alu_sel),
        .mode(mode),
        .carry_out(cout),
        .compare(cmp),
        .alu_out(alu_out)
    );

endmodule
