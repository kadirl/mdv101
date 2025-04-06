#include "Vcontrol_unit.h"
#include "verilated.h"
#include <iostream>
#include <random>
#include <vector>

void print_outputs(Vcontrol_unit* dut, const std::vector<int>& expected_outputs) {
    std::cout << "  Outputs: ";
    std::cout << "alu_sel = " << (int)dut->alu_sel << ", ";
    std::cout << "alu_mode = " << (int)dut->alu_mode << ", ";
    std::cout << "mux_sel = " << (int)dut->mux_sel << ", ";
    std::cout << "en_s = " << (int)dut->en_s << ", ";
    std::cout << "en_c = " << (int)dut->en_c << ", ";
    std::cout << "en_0 = " << (int)dut->en_0 << ", ";
    std::cout << "en_1 = " << (int)dut->en_1 << ", ";
    std::cout << "en_2 = " << (int)dut->en_2 << ", ";
    std::cout << "en_3 = " << (int)dut->en_3 << ", ";
    std::cout << "en_4 = " << (int)dut->en_4 << ", ";
    std::cout << "en_5 = " << (int)dut->en_5 << ", ";
    std::cout << "en_6 = " << (int)dut->en_6 << ", ";
    std::cout << "en_7 = " << (int)dut->en_7 << ", ";
    std::cout << "en_i = " << (int)dut->en_i << ", ";
    std::cout << "done = " << (int)dut->done;

    std::vector<int> actual_outputs = {
        (int)dut->alu_sel, (int)dut->alu_mode, (int)dut->mux_sel, (int)dut->en_s, (int)dut->en_c,
        (int)dut->en_0, (int)dut->en_1, (int)dut->en_2, (int)dut->en_3, (int)dut->en_4,
        (int)dut->en_5, (int)dut->en_6, (int)dut->en_7, (int)dut->en_i, (int)dut->done
    };

    if (actual_outputs == expected_outputs) {
        std::cout << " (Correct)" << std::endl << std::endl;
    } else {
        std::cout << " (Incorrect)" << std::endl << std::endl;
    }
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vcontrol_unit* dut = new Vcontrol_unit;

    dut->reset = 1;
    dut->clk = 0;
    dut->run = 0;
    dut->eval();
    dut->clk = 1;
    dut->eval();
    std::cout << "Test case 1: Reset" << std::endl;
    print_outputs(dut, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0});

    dut->reset = 0;
    dut->run = 1;
    for (int i = 0; i < 4; ++i) {
        dut->clk = 0;
        dut->eval();
        dut->clk = 1;
        dut->eval();
        std::cout << "Test case 2." << i + 1 << ": Clock cycle " << i + 1 << std::endl;
        if (i == 0) print_outputs(dut, {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
        else if (i == 1) print_outputs(dut, {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
        else if (i == 2) print_outputs(dut, {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1});
        else if (i == 3) print_outputs(dut, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0});
    }

    dut->reset = 0;
    dut->run = 1;
    dut->d_in = 0b1110000000000000; // d_in[15:13] = 111
    dut->clk = 0;
    dut->eval();
    dut->clk = 1;
    dut->eval();
    std::cout << "Test case 3: STATE1" << std::endl;
    print_outputs(dut, {0, 0, 7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    dut->d_in = 0b0001110000000000;
    dut->clk = 0;
    dut->eval();
    dut->clk = 1;
    dut->eval();
    std::cout << "Test case 4: STATE2" << std::endl;
    print_outputs(dut, {0, 0, 7, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    dut->d_in = 0b1110000000000000; // d_in[15:13] = 111
    dut->clk = 0;
    dut->eval();
    dut->clk = 1;
    dut->eval();
    std::cout << "Test case 5: STATE3" << std::endl;
    print_outputs(dut, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1});

    dut->run = 0;
    dut->clk = 0;
    dut->eval();
    dut->clk = 1;
    dut->eval();
    std::cout << "Test case 6: run = 0" << std::endl;
    print_outputs(dut, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1});

    dut->run = 1;
    dut->clk = 0;
    dut->eval();
    dut->clk = 1;
    dut->eval();
    dut->reset = 1;
    dut->clk = 0;
    dut->eval();
    dut->clk = 1;
    dut->eval();
    std::cout << "Test case 7: Reset during operation" << std::endl;
    print_outputs(dut, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0});

    delete dut;
    return 0;
}