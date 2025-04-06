#include "Vbitty_core.h"
#include "verilated.h"
#include <iostream>
#include <vector>

std::vector<uint16_t> execute_instruction(Vbitty_core* top, uint16_t instruction) {
    top->instruction = instruction;
    top->clk = 1;
    top->eval();
    top->clk = 0;
    top->eval();

    top->run = 1;
    for (int i = 0; i < 4; ++i) {
        top->clk = 1;
        top->eval();
        top->clk = 0;
        top->eval();
    }
    top->run = 0;

    std::vector<uint16_t> register_values = {
        top->reg0_out, top->reg1_out, top->reg2_out, top->reg3_out,
        top->reg4_out, top->reg5_out, top->reg6_out, top->reg7_out
    };

    return register_values;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vbitty_core* top = new Vbitty_core;

    top->clk = 0;
    top->reset = 1;
    top->run = 0;
    top->instruction = 0;
    top->eval();

    top->clk = 1;
    top->eval();
    top->clk = 0;
    top->reset = 0;
    top->eval();

    // Example Usage: Add 1 to reg0
    uint16_t add_one_to_reg0 = 0b0000000000000000; // rx=0, ry=0, alu_sel=0, alu_mode=0

    // Initialize all registers with a value
    std::vector<uint16_t> initial_values = {10, 20, 30, 40, 50, 60, 70, 80};

    // set the initial values of the registers.
    for (int i = 0; i < 8; ++i){
        top->instruction = (i << 13) | (i << 10) | (0 << 7) | (15 << 3) | (0 << 2) | (0 << 0);
        execute_instruction(top, top->instruction);
    }

    std::vector<uint16_t> result_values = execute_instruction(top, add_one_to_reg0);


    // Print the results
    std::cout << "Register Values after add 1 to reg 0:" << std::endl;
    for (size_t i = 0; i < result_values.size(); ++i) {
        std::cout << "reg" << i << "_out = " << (int)result_values[i] << std::endl;
    }


    add_one_to_reg0 = 0b0000000000000000; // rx=0, ry=0, alu_sel=0, alu_mode=0

    // set the initial values of the registers.
    for (int i = 0; i < 8; ++i){
        top->instruction = (i << 13) | (i << 10) | (0 << 7) | (15 << 3) | (0 << 2) | (0 << 0);
        execute_instruction(top, top->instruction);
    }

    result_values = execute_instruction(top, add_one_to_reg0);



    // Print the results
    std::cout << "Register Values after add 1 to reg 0:" << std::endl;
    for (size_t i = 0; i < result_values.size(); ++i) {
        std::cout << "reg" << i << "_out = " << (int)result_values[i] << std::endl;
    }

    delete top;
    return 0;
}