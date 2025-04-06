#include <verilated.h>
#include "Vregister.h" // Include the generated header file

#include <iostream>
#include <cassert>

int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
    Vregister* top = new Vregister;

    top->clk = 0;
    top->reset = 1;
    top->en = 0;
    top->d_in = 16; // Initial value, not used during reset
    top->eval();

    top->clk = 1;
    top->eval();
    top->clk = 0;
    top->reset = 0;
    top->eval(); // Release reset

    std::cout << "Reset Test: " << std::endl;
    std::cout << "  clk = 0, reset = 1" << std::endl;
    std::cout << "  clk = 1, reset = 1" << std::endl;
    std::cout << "  clk = 0, reset = 0" << std::endl;
    std::cout << "  d_out = " << (int)top->d_out << std::endl;
    assert(top->d_out == 0); // Check reset value
    std::cout << "  Reset test passed." << std::endl;

    // Test enable functionality
    top->en = 1;
    top->d_in = 42;
    top->clk = 1;
    top->eval();
    top->clk = 0;
    top->eval();

    std::cout << "\nEnable Test: " << std::endl;
    std::cout << "  en = 1, d_in = 42" << std::endl;
    std::cout << "  clk = 1" << std::endl;
    std::cout << "  clk = 0" << std::endl;
    std::cout << "  d_out = " << (int)top->d_out << std::endl;
    assert(top->d_out == 42); // Check data load
    std::cout << "  Enable test passed." << std::endl;

    // Test disable functionality
    top->en = 0;
    top->d_in = 99; // New data, should be ignored
    top->clk = 1;
    top->eval();
    top->clk = 0;
    top->eval();

    std::cout << "\nDisable Test: " << std::endl;
    std::cout << "  en = 0, d_in = 99" << std::endl;
    std::cout << "  clk = 1" << std::endl;
    std::cout << "  clk = 0" << std::endl;
    std::cout << "  d_out = " << (int)top->d_out << std::endl;
    assert(top->d_out == 42); // Check data remains unchanged
    std::cout << "  Disable test passed." << std::endl;

    // Test reset during operation
    top->reset = 1;
    top->eval();
    top->clk = 1;
    top->eval();
    top->clk = 0;
    top->reset = 0;
    top->eval();

    std::cout << "\nReset During Operation Test: " << std::endl;
    std::cout << "  reset = 1" << std::endl;
    std::cout << "  clk = 1" << std::endl;
    std::cout << "  clk = 0, reset = 0" << std::endl;
    std::cout << "  d_out = " << (int)top->d_out << std::endl;
    assert(top->d_out == 0); // Check reset value
    std::cout << "  Reset during operation test passed." << std::endl;

    top->final();
    delete top;
    return 0;
}