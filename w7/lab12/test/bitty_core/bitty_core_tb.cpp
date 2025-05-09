#include "Vbitty_core.h"
#include "verilated.h"
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdint> // For uint16_t


uint16_t generateRandomUInt16(uint16_t min, uint16_t max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint16_t> distrib(min, max);
    return distrib(gen);
}


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


uint16_t regular_golden_module(uint16_t rx, uint16_t ry, uint16_t alu_sel) {
    switch (alu_sel) {
        case 0: // ADD
            return rx + ry;
        case 1: // SUB
            return rx - ry;
        case 2: // AND
            return rx & ry;
        case 3: // OR
            return rx | ry;
        case 4: // XOR
            return rx ^ ry;
        case 5: // SHL (shift left by ry bits)
            return rx << (ry & 0xF); // Mask to avoid undefined behavior
        case 6: // SHR (shift right by ry bits)
            return rx >> (ry & 0xF);
        case 7: // CMP
            if (rx == ry)
                return 0;
            else if (rx > ry)
                return 1;
            else
                return 2;
        default:
            return 0; // default case (can assert or handle invalid op)
    }
}


void random_instructions_tb(Vbitty_core* top) {
    uint16_t min_val = 0;  // Example minimum value
    uint16_t max_val = 65535; // Example maximum value
    std::vector<uint16_t> registers = {10, 10, 10, 10, 10, 10, 10, 10};

    // init core
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

    for (int i = 0; i < 1000; i++) {
        // generate random instruction
        uint16_t rx = generateRandomUInt16(0, 7);
        uint16_t ry = generateRandomUInt16(0, 7);
        uint16_t sel = generateRandomUInt16(0, 7);

        uint16_t inst = (rx << 13) | (ry << 10) | (0 << 5) | (sel << 2) | (0 << 0);
        std::vector<uint16_t> sim_regs = execute_instruction(top, inst);

        uint16_t model_res = regular_golden_module(registers[rx], registers[ry], sel);
        registers[rx] = model_res;

        if (sim_regs == registers) {
            // std::cout << "SUCCESS" << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
                    // std::cout << "Expected: "; 
        // for (int i = 0; i < registers.size(); i++) {
        //     std::cout << registers[i] << " ";
        // }
        // std::cout << std::endl;

        // std::cout << "Got: ";
        // for (int i = 0; i < sim_regs.size(); i++) {
        //     std::cout << sim_regs[i] << " ";
        // }
        // std::cout << std::endl;
        // std::cout << "rx: " << rx << "\try: " << ry << "\tsel" << sel << std::endl << std::endl;
        }

        // std::cout << "Expected: "; 
        // for (int i = 0; i < registers.size(); i++) {
        //     std::cout << registers[i] << " ";
        // }
        // std::cout << std::endl;

        // std::cout << "Got: ";
        // for (int i = 0; i < sim_regs.size(); i++) {
        //     std::cout << sim_regs[i] << " ";
        // }
        // std::cout << std::endl;
        // std::cout << "rx: " << rx << "\try: " << ry << "\tsel" << sel << std::endl << std::endl;
        // std::cout << "Expected: " << "asdf" << "\tOutput: " << "asdf" << std::endl;
    }


}


int main(int argc, char** argv) {
    Vbitty_core* top = new Vbitty_core();

    // Test 2: Random instructions generator
    random_instructions_tb(top);


    return 0;
}