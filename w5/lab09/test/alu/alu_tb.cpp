// // #include "Valu.h"

// // #include <iostream>

// // int main()
// // {
// //     Valu* dut = new Valu();
// //     dut->carry_in = 0;
// //     dut->in_a = 33000;
// //     dut->in_b = 31000;
// //     dut->select = 9;
// //     dut->mode = 0;
// //     dut->eval();

// //     int expected_output = 3;
// //     int dut_output = (int)dut->alu_out;
    
// //     std::cout << dut_output << std::endl;
// //     std::cout << (int)dut->carry_out << std::endl;
// //     std::cout << dut->compare << std::endl;

// //     if (expected_output == dut_output)
// //     {
// //         std::cout << "OK" << std::endl;
// //     }
// //     else
// //     {   
// //         std::cout << "Fail!" << std::endl;
// //     }

// //     return 0;
// // }


// #include "Valu.h"
// #include <iostream>

// #include <cstdint>

// #define ALU(x) ((int16_t)(x))


// void test_case(Valu* dut, int carry_in, int in_a, int in_b, int select, int mode, int expected_output, bool verbose) {
//     dut->carry_in = carry_in;
//     dut->in_a = in_a;
//     dut->in_b = in_b;
//     dut->select = select;
//     dut->mode = mode;
//     dut->eval();

//     int dut_output = (int)dut->alu_out;

//     if (verbose) {
//         std::cout << "Inputs:\n"
//             << "A:" << in_a << "\tB: " << in_b << "\tCin: " << carry_in << std::endl 
//             << "Select: " << select << "\tMode: " << mode << std::endl
//             << "Outputs:\n"
//             << "Result: " << dut_output << "\tCout: " << dut->carry_out << "\tCompare: " << dut->compare 
//             << "Expected: " << expected_output
//             << std::endl;
//     }

//     if (expected_output == dut_output) {
//         // std::cout << "OK" << std::endl << std::endl;
//     } else {
//         std::cout << "Fail! Expected: " << expected_output << std::endl << std::endl;
//         if (true) {
//             std::cout << "Inputs:\n"
//                 << "A:" << in_a << "\tB: " << in_b << "\tCin: " << carry_in << std::endl 
//                 << "Select: " << select << "\tMode: " << mode << std::endl
//                 << "Outputs:\n"
//                 << "Result: " << dut_output << "\tCout: " << dut->carry_out << "\tCompare: " << dut->compare 
//                 << std::endl;
//         }
//     }
// }

// int main() {
//     Valu* dut = new Valu();
//     // Test all possible cases
//     for (unsigned short i = 0; i < 65535; i += 15) {
//         for (unsigned short j = 0; j < 65535; j += 15) {
//             // Logical unit: mode = 1
//             test_case(dut, 0, i, j, 0, 1, (unsigned short)~i, false);            // A'
//             test_case(dut, 0, i, j, 1, 1, (unsigned short)~(i | j), false);      // (A + B)'
//             test_case(dut, 0, i, j, 2, 1, (unsigned short)(~i & j), true);      // A'B

//             // 4'd3:   log_out = 16'b0;            // 0
//             // 4'd4:   log_out = ~(in_a & in_b);   // (AB)'
//             // 4'd5:   log_out = ~in_b;            // B'
//             // 4'd6:   log_out = in_a ^ in_b;      // A XOR B
//             // 4'd7:   log_out = in_a & ~in_b;     // AB'
//             // 4'd8:   log_out = ~in_a | in_b;     // A' + B
//             // 4'd9:   log_out = ~(in_a ^ in_b);   // (A XOR B)'
//             // 4'd10:  log_out = in_b;             // B
//             // 4'd11:  log_out = in_a & in_b;      // AB
//             // 4'd12:  log_out = 16'b1;            // 1
//             // 4'd13:  log_out = in_a | ~in_b ;    // A + B'
//             // 4'd14:  log_out = in_a | in_b ;     // A + B
//             // 4'd15:  log_out = in_a  ;           // A
//             // default:    log_out = 16'b0;        // 0 by default
//         }
//         if (i % 1000 == 0) 
//             std::cout << (int)(i) << std::endl;
//     }

//     return 0;
// }

#include "Valu.h"
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

std::mutex cout_mutex;

void test_case(
    Valu* dut, 
    int carry_in, 
    unsigned short in_a, 
    unsigned short in_b, 
    int select, 
    int mode, 
    unsigned short expected_output
) {
    dut->carry_in = carry_in;
    dut->in_a = in_a;
    dut->in_b = in_b;
    dut->select = select;
    dut->mode = mode;
    dut->eval();

    unsigned short dut_output = (unsigned short)dut->alu_out;
    
    if (in_a % 100 == 0 && in_b % 100 == 0 && 0) {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << in_a << " " << in_b << std::endl;

        std::cout << "Inputs:\n"
            << "A:" << in_a << "\tB: " << in_b << "\tCin: " << carry_in << std::endl 
            << "Select: " << select << "\tMode: " << mode << std::endl
            << "Outputs:\n"
            << "Result: " << dut_output << "\tCout: " << (int)dut->carry_out << "\tCompare: " << (int)dut->compare 
            << "\nExpected: " << expected_output
            << std::endl << std::endl;
    }

    if (dut_output != expected_output) {
        // error_count++;
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Fail!\nA: " << in_a << ", B: " << in_b 
                  << ", Select: " << select 
                  << ", Output: " << dut_output 
                  << ", Expected: " << expected_output 
                  << std::endl << std::endl;
    }
}

void run_tests_for_range(int start, int end) {
    Valu* dut = new Valu();

    std::cout << "Starting LU test." << std::endl;

    // test LU
    for (int i = start; i < end; i += 15) {
        for (int j = 0; j < 65535; j += 15) {
            test_case(dut, 0, i, j, 0, 1, ~i);          // A'
            test_case(dut, 0, i, j, 1, 1, ~(i | j));    // (A + B)'
            test_case(dut, 0, i, j, 2, 1, ~i & j);      // A'B
            test_case(dut, 0, i, j, 3, 1, 0);           // 0
            test_case(dut, 0, i, j, 4, 1, ~(i & j));    // (AB)'
            test_case(dut, 0, i, j, 5, 1, ~j);          // B'
            test_case(dut, 0, i, j, 6, 1, i ^ j);       // A XOR B
            test_case(dut, 0, i, j, 7, 1, i & ~j);      // AB'
            test_case(dut, 0, i, j, 8, 1, ~i | j);      // A' + B
            test_case(dut, 0, i, j, 9, 1, ~(i ^ j));    // (A XOR B)'
            test_case(dut, 0, i, j, 10, 1, j);          // B
            test_case(dut, 0, i, j, 11, 1, i & j);      // AB
            test_case(dut, 0, i, j, 12, 1, 1);          // 1
            test_case(dut, 0, i, j, 13, 1, i | ~j);     // A + B'
            test_case(dut, 0, i, j, 14, 1, i | j);      // A + B
            test_case(dut, 0, i, j, 15, 1, i);          // A
        }

        if (i % 1000 == 0) {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << i << std::endl;
        }
    }

    std::cout << "LU test done. Starting AU test." << std::endl;

    // test AU
    for (int i = start; i < end; i += 15) {
        for (int j = 0; j < 65535; j += 15) {
            test_case(dut, 0, i, j, 0, 0, i);
            test_case(dut, 1, i, j, 0, 0, i + 1);

            test_case(dut, 0, i, j, 1, 0, i | j);
            test_case(dut, 1, i, j, 1, 0, (i | j) + 1);

            test_case(dut, 0, i, j, 2, 0, i | ~j);
            test_case(dut, 1, i, j, 2, 0, (i | ~j) + 1);

            test_case(dut, 0, i, j, 3, 0, -1);
            test_case(dut, 1, i, j, 3, 0, -1 + 1);

            test_case(dut, 0, i, j, 4, 0, (i | (i & ~ j)));
            test_case(dut, 1, i, j, 4, 0, (i | (i & ~ j)) + 1);
            
            test_case(dut, 0, i, j, 5, 0, (i | j) | (i & ~ j));
            test_case(dut, 1, i, j, 5, 0, ((i | j) | (i & ~ j)) + 1);

            test_case(dut, 0, i, j, 6, 0, i - j - 1);
            test_case(dut, 1, i, j, 6, 0, i - j);

            test_case(dut, 0, i, j, 7, 0, (i & ~ j) - 1);
            test_case(dut, 1, i, j, 7, 0, (i & ~ j));

            test_case(dut, 0, i, j, 8, 0, i + (i & j));
            test_case(dut, 1, i, j, 8, 0, i + (i & j) + 1);

            test_case(dut, 0, i, j, 9, 0, i + j);
            test_case(dut, 1, i, j, 9, 0, i + j + 1);

            test_case(dut, 0, i, j, 10, 0, (i | ~j) + (i & j));
            test_case(dut, 1, i, j, 10, 0, (i | ~j) + (i & j) + 1);

            test_case(dut, 0, i, j, 11, 0, ((i & j) - 1));
            test_case(dut, 1, i, j, 11, 0, ((i & j) - 1) + 1);

            test_case(dut, 0, i, j, 12, 0, i + i);
            test_case(dut, 1, i, j, 12, 0, i + i + 1);

            test_case(dut, 0, i, j, 13, 0, (i | j) + i);
            test_case(dut, 1, i, j, 13, 0, (i | j) + i + 1);

            test_case(dut, 0, i, j, 14, 0, (i | ~j) + i);
            test_case(dut, 1, i, j, 14, 0, (i | ~j) + i + 1);

            test_case(dut, 0, i, j, 15, 0, i - 1);
            test_case(dut, 1, i, j, 15, 0, i - 1 + 1);

        }

        if (i % 1000 == 0) {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << i << std::endl;
        }
    }

    delete dut;
}

int main() {
    const int num_threads = 8;

    // Multi-threaded testing
    std::vector<std::thread> threads;
    int step = 65535 / num_threads;

    for (int t = 0; t < num_threads; t++) {
        int start = t * step;
        int end = (t == num_threads - 1) ? 65535 : (start + step);
        std::cout << "Thread #" << t + 1 << " start: " << start << " end: " << end << std::endl;
        threads.emplace_back(run_tests_for_range, start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
