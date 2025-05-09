#include "Vbitty_core.h"
#include "verilated.h"
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdint> // For uint16_t
#include <bitset>


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


uint16_t immediate_golden_model(uint16_t rx, uint16_t immediate, uint16_t alu_sel) {
    switch (alu_sel) {
        case 0: return rx + immediate;                  // add
        case 1: return rx - immediate;                  // sub
        case 2: return rx & immediate;                  // and
        case 3: return rx | immediate;                  // or
        case 4: return rx ^ immediate;                  // xor
        case 5: return rx << (immediate % 16);
        case 6: return rx >> (immediate % 16);
        case 7: // compare
            if (rx == immediate) return 0;
            else if (rx < immediate) return 2;
            else return 1;
        default: return 0;
    }
}

// Reference model for expected output
uint16_t regular_golden_module(uint16_t in_a, uint16_t in_b, uint16_t sel) {
    switch (sel) {
        case 0: return in_a + in_b;
        case 1: return in_a - in_b;
        case 2: return in_a & in_b;
        case 3: return in_a | in_b;
        case 4: return in_a ^ in_b;
        case 5: return in_a << (in_b % 16);
        case 6: return in_a >> (in_b % 16);
        case 7:
            if (in_a == in_b) return 0;
            else if (in_a > in_b) return 1;
            else return 2;
        default: return 0;
    }
}


void fibonacci_tb(Vbitty_core* top, int n) {
    std::vector<uint16_t> result_values;

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


    // Test 1: Execute Fibonacci code

    // assign r1 and r2 to 1
    // rx = 1; immediate = 1; alu_sel = 0; res = 01
    uint16_t init_r1 = 0b0010000000100001;
    result_values = execute_instruction(top, init_r1);

    // rx = 2; immediate = 1; alu_sel = 0; res = 01
    uint16_t init_r2 = 0b0100000000100001;
    result_values = execute_instruction(top, init_r2);


    // save Fibonacci sequence
    uint16_t sub_r3_r3 = (3 << 13) | (3 << 10) | (0 << 5) | (1 << 2) | (0 << 0);
    uint16_t add_r3_r2 = (3 << 13) | (2 << 10) | (0 << 5) | (0 << 2) | (0 << 0);
    uint16_t add_r2_r1 = (2 << 13) | (1 << 10) | (0 << 5) | (0 << 2) | (0 << 0);
    uint16_t sub_r1_r1 = (1 << 13) | (1 << 10) | (0 << 5) | (1 << 2) | (0 << 0);
    uint16_t add_r1_r3 = (1 << 13) | (3 << 10) | (0 << 5) | (0 << 2) | (0 << 0);

    std::vector<uint16_t> fib_seq = {
        sub_r3_r3,
        add_r3_r2,
        add_r2_r1,
        sub_r1_r1,
        add_r1_r3,
    };

    // execute Fibonacci code for first 10 values
    std::cout << "Test #1: Fibonacci values" << std::endl;
    int r1 = 1;
    int r2 = 1;
    int r3 = 0;
    for (int i = 0; i < 10; i++) {
        // emulate
        for (int inst = 0; inst < fib_seq.size(); inst++) {
            result_values = execute_instruction(top, fib_seq[inst]);
        }

        // gold model
        r3 = r2;
        r2 += r1;
        r1 = r3;

        if (r3 != result_values[3]) {
            std::cout << "MISMATCH" << std::endl;
        }
        std::cout << "Expected: " << r3 << "\t Got: " << result_values[3] << std::endl;

    }
}


// void random_instructions_tb(Vbitty_core* top) {
//     uint16_t min_val = 0;  // Example minimum value
//     uint16_t max_val = 65535; // Example maximum value

//     // init core
//     top->clk = 0;
//     top->reset = 1;
//     top->run = 0;
//     top->instruction = 0;
//     top->eval();
//     top->clk = 1;
//     top->eval();
//     top->clk = 0;
//     top->reset = 0;
//     top->eval();

//     for (int i = 0; i < 1000; i++) {
//         // generate random instruction
//         uint16_t mode = generateRandomUInt16()
//     }

//     // uint16_t sub_r3_r3 = (3 << 13) | (3 << 10) | (0 << 5) | (1 << 2) | (0 << 0);
    

// }

void random_instructions_tb(Vbitty_core* top, int tests) {
    uint16_t min_val = 0;  // Example minimum value
    uint16_t max_val = 65535; // Example maximum value
    std::vector<uint16_t> registers = {0, 0, 0, 0, 0, 0, 0, 0};

    int counter = 0;

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

    for (int i = 0; i < tests; i++) {
        // generate random instruction
        uint16_t rx = generateRandomUInt16(0, 7);
        uint16_t ry = generateRandomUInt16(0, 7);
        uint16_t imm = generateRandomUInt16(0, 255);
        uint16_t sel = generateRandomUInt16(0, 7);
        uint16_t mode = generateRandomUInt16(0, 1);

        std::vector<uint16_t> sim_regs;

        if (mode) {
            uint16_t inst = (rx << 13) | (imm << 5) | (sel << 2) | (1 << 0);
            std::cout << std::bitset<16>(inst) << std::endl;
            sim_regs = execute_instruction(top, inst);
            uint16_t model_res = immediate_golden_model(registers[rx], imm, sel);
            registers[rx] = model_res;  
        } else {
            uint16_t inst = (rx << 13) | (ry << 10) | (0 << 5) | (sel << 2) | (0 << 0);
            std::cout << std::bitset<16>(inst) << std::endl;
            sim_regs = execute_instruction(top, inst);
            uint16_t model_res = regular_golden_module(registers[rx], registers[ry], sel);
            registers[rx] = model_res;    
        }

        if (sim_regs == registers) {
            std::cout << "SUCCESS" << std::endl;
            std::cout << "Expected: \t"; 
            for (int i = 0; i < registers.size(); i++) {
                std::cout << registers[i] << " ";
            }
            std::cout << std::endl;
    
            std::cout << "Got: \t\t";
            for (int i = 0; i < sim_regs.size(); i++) {
                std::cout << sim_regs[i] << " ";
            }
            std::cout << std::endl;
            std::cout << "rx: " << rx << "\try: " << ry << "\tsel" << sel << "\timm: " << imm << "\tmode: " << mode << std::endl << std::endl;

            counter++;
        } else {
            std::cout << "FAIL" << std::endl;
            std::cout << "Expected: \t"; 
            for (int i = 0; i < registers.size(); i++) {
                std::cout << registers[i] << " ";
            }
            std::cout << std::endl;
    
            std::cout << "Got: \t\t";
            for (int i = 0; i < sim_regs.size(); i++) {
                std::cout << sim_regs[i] << " ";
            }
            std::cout << std::endl;
            std::cout << "rx: " << rx << "\try: " << ry << "\tsel" << sel << "\timm: " << imm << "\tmode: " << mode << std::endl << std::endl;
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

    std::cout << "Out of " << tests << " tests " << counter << " had passed." << std::endl;
}


int main(int argc, char** argv) {
    Vbitty_core* top = new Vbitty_core();

    // Test 1: Fibonacci calculator for first 10 values
    fibonacci_tb(top, 10);


    // Test 2: Random instructions generator
    random_instructions_tb(top, 10000);


    return 0;
}