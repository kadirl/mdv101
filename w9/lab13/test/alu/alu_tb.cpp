#include <verilated.h>
#include "Valu.h"

#include <iostream>
#include <random>
#include <ctime>
#include <cstdint> // For uint16_t


uint16_t generateRandomUInt16(uint16_t min, uint16_t max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint16_t> distrib(min, max);
    return distrib(gen);
}


// comparator
bool test (
    Valu* dut,
    uint16_t in_a,
    uint16_t in_b,
    uint16_t sel,
    uint16_t expect
) {
    dut->in_a = in_a;
    dut->in_b = in_b;
    dut->select = sel;
    dut->eval();

    uint16_t res = dut->alu_out;
    bool test_output = false;

    if (res == expect) {
        std::cout << "SUCCESS" << std::endl;
        test_output = true;
    } else {
        std::cout << "FAIL" << std::endl;
    }

    std::cout << "in_a: " << in_a << "\t in_b: " << in_b << "\tsel: " << sel << std::endl;
    std::cout << "Expected: " << expect << "\tGot: " << res << std::endl << std::endl;

    return test_output;
}


// Reference model for expected output
uint16_t referenceModel(uint16_t in_a, uint16_t in_b, uint16_t sel) {
    switch (sel) {
        case 0: return in_a + in_b;
        case 1: return in_a - in_b;
        case 2: return in_a & in_b;
        case 3: return in_a | in_b;
        case 4: return in_a ^ in_b;
        case 5: return in_a << in_b;
        case 6: return in_a >> in_b;
        case 7:
            if (in_a == in_b) return 0;
            else if (in_a > in_b) return 1;
            else return 2;
        default: return 0;
    }
}


int main() {
    uint16_t min_val = 0;  // Example minimum value
    uint16_t max_val = 65535; // Example maximum value

    Valu* dut = new Valu();

    const int test_count = 1000;
    int passed = 0;

    for (int i = 0; i < test_count; ++i) {
        uint16_t in_a = generateRandomUInt16(0, 65535);
        uint16_t in_b = generateRandomUInt16(0, 15); // Shift operations reasonable range
        uint16_t sel = generateRandomUInt16(0, 7);

        uint16_t expect = referenceModel(in_a, in_b, sel);

        if (test(dut, in_a, in_b, sel, expect)) {
            ++passed;
        }
    }

    std::cout << "Test Summary: " << passed << "/" << test_count << " tests passed." << std::endl;

    delete dut;
    return 0;
}
