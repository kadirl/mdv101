#include <verilated.h>
#include "Vmux.h"

#include <iostream>
#include <vector>
#include <cassert>


int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
    Vmux* top = new Vmux;

    // Initialize inputs
    top->sel = 0;
    for (int i = 0; i < 8; ++i) {
        top->in[i] = i * 10; // Assign distinct values to inputs
    }

    // Function to apply a clock cycle and check output
    auto tick = [&]() {
        top->eval();
    };

    // Test each select value
    for (int i = 0; i < 8; ++i) {
        top->sel = i;
        tick();
        assert(top->out == i * 10); // Check if output matches selected input
        std::cout << "sel = " << i << ", out = " << top->out << " (passed)\n";
    }

    // Test an out-of-range select value (if you added a default case)
    top->sel = 8; // Out of range
    tick();
    assert(top->out == 0); // Check if default value is assigned
    std::cout << "sel = 8 (out of range), out = " << top->out << " (default passed)\n";

    top->final();
    delete top;
    return 0;
}