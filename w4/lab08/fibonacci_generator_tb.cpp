// #include "Vfibonacci_generator.h"
// #include "verilated.h"
// #include <iostream>

// #include "verilated_vcd_c.h"

// int main(int argc, char **argv) {
//     // Initialize Verilator
//     Verilated::commandArgs(argc, argv);

//     // Instantiate the Verilog module
//     Vfibonacci_generator *tb = new Vfibonacci_generator;

//     // Enable waveform tracing. 
//     Verilated::traceEverOn(true); 
//     VerilatedVcdC* vcd_trace = new VerilatedVcdC; 
//     tb->trace(vcd_trace, 99); // Trace 99 levels of hierarchy. 
//     vcd_trace->open("and_gate_trace.vcd"); // Open the VCD file.

//     // Simulation setup
//     vluint64_t sim_time = 0;  // Simulation time
//     const vluint64_t max_sim_time = 1000;  // Maximum simulation time
//     bool enable = true;  // Enable signal

//     // Initialize the clock and reset
//     tb->clk = 0;
//     tb->rst = 1;  // Assert reset

//     // Start the simulation loop
//     while (sim_time < max_sim_time) {
//         // Toggle the clock
//         tb->clk = !tb->clk;

//         // Deassert reset after a few clock cycles
//         if (sim_time == 10) {
//             tb->rst = 0;  // Deassert reset
//         }

//         // Apply the enable signal
//         tb->enable = enable;

//         // Evaluate the model (tick the clock)
//         tb->eval();

//         // Dump to VCD
//         vcd_trace->dump(sim_time);

//         // Print Fibonacci number output on the rising edge of the clock
//         if (tb->clk && !tb->rst) {
//             std::cout << "Cycle " << sim_time / 2 << ": Fibonacci number = " << tb->fib_out << std::endl;
//         }

//         // Increment simulation time
//         sim_time++;

        
//     }

//     // Final cleanup
//     tb->final();
//     delete tb;
    
//     vcd_trace->close();

//     return 0;
// }