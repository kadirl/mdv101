#include <verilated.h>
#include "Vkey_lock_fsm.h"
#include <iostream>

#define SIM_CYCLES 50

int main() {
    Verilated::traceEverOn(true);
    Vkey_lock_fsm* dut = new Vkey_lock_fsm;

    dut->clk = 0;
    dut->rst = 1;
    dut->key_in = 0;
    dut->eval();

    dut->clk = 1;
    dut->eval();
    dut->clk = 0;
    dut->rst = 0;
    dut->eval(); // Release reset

    std::vector<uint8_t> unlock_sequence = {3, 3, 5, 2, 5, 6};

    // TEST 1:
    // check if correct sequence works
    for (uint8_t key : unlock_sequence) {
        dut->key_in = key;
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }

    if (dut->locked == 0) {
        std::cout << "Unlock sequence successful!\n";
    } else {
        std::cout << "Unlock sequence failed!\n";
    }

    // TEST 2:
    // check if incorrect sequence works

    std::vector<uint8_t> incorrect_sequence = {1, 2, 3, 4, 5, 6};
    for (uint8_t key : incorrect_sequence) {
        dut->key_in = key;
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }

    if (dut->locked == 0) {
        std::cout << "Incorrect sequence test successful!\n";
    } else {
        std::cout << "Incorrect sequence test failed!\n\n";
    }


    // TEST 3:
    // check all transitions

    // test all 6 digits
    for (int correct = 0; correct <= unlock_sequence.size(); correct++) {
        // reset
        dut->clk = 0;
        dut->rst = 1;
        dut->key_in = 0;
        dut->eval();

        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->rst = 0;
        dut->eval(); // Release reset
        
        for (int i = 0; i < correct; i++) {
            dut->key_in = unlock_sequence[i];
            dut->clk = 1;
            dut->eval();
            dut->clk = 0;
            dut->eval();
        }

        std::cout << "state after inputting " << correct << " correct numbers: " << (int)dut->state_debug << std::endl;
        std::cout << "locked? " << (int)dut->locked << std::endl;

        dut->key_in = 9;
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        std::cout << "state after inputting incorrect number: " << (int)dut->state_debug << std::endl;
        std::cout << "resetting\n\n";
    }

    dut->final();
    delete dut;
    return 0;
}
