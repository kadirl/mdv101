# Microchip Design & Verification Labs  
**Course by Dr. Nursultan Kabylkas ([GitHub](https://github.com/kabylkas))**

## About This Repository

This repo is my work log and codebase for a 14-week extracurricular course at university, led by Dr. Nursultan Kabylkas. The course was all about learning how to design, build, and verify microchips using Verilog HDL, and it was a pretty hands-on, project-driven experience.

## Project Overview

The course was structured as a series of 19 lab works, each building on the last. I started with the basics—simple digital logic circuits and basic verification—and gradually worked my way up to designing and verifying a custom 16-bit, 4-cycle, non-pipelined general-purpose processor, complete with my own instruction set, assembler, and emulator.

### What’s Inside

- **w2–w14 folders:** Each week’s work, broken down by lab.  
  - Early labs (w2–w5): 
    - Simple circuits in Logisim, basic Verilog, and C++ testbenches.
  - Middle labs (w6–w11): 
    -Built more complex modules: ALUs, state machines, and the first pieces of my CPU.
    - Started writing more advanced testbenches and scripts to automate verification.
  - Later labs (w12–w14): 
    - Pulled everything together into a working CPU.
    - Designed my own assembly language and wrote a Python assembler.
    - Built an emulator to run and debug programs for my CPU.
    - Switched to cocotb (Python) for co-simulation and more powerful verification.


- **Lab folders:**  
  Each `labXX` folder contains the design files (Verilog, Logisim, etc.), testbenches, and scripts for that week’s assignment.

- **Verification:**  
  - Early on, I used Verilator and C++ for simulation and verification.
  - Later, I switched to Python and cocotb for more advanced, co-simulation-based verification.

- **Assembler & Emulator:**  
  - As the CPU design matured, I wrote my own assembler (in Python) to translate my custom assembly language into machine code.
  - I also built an emulator to run and test programs for my CPU, which was crucial for debugging and verification.

## Highlights & Milestones

- **Started from scratch:**  
  My first labs were simple multiplexers, encoders, and ALUs, designed in Logisim and then in Verilog.

- **Verification journey:**  
  I learned to write C++ testbenches for Verilog modules using Verilator, then moved to Python/cocotb for more flexible and powerful test automation.

- **CPU design:**  
  The big project was a homebrew 16-bit multi-cycle CPU with a custom instruction set, designed and verified from scratch I designed the architecture, wrote the Verilog, and built all the supporting modules (ALU, control unit, register file, etc.).

- **Custom assembly language:**  
  I created my own assembly language and wrote a Python assembler to convert it to machine code for my CPU.

- **Co-simulation:**  
  Used cocotb to run co-simulation between my Verilog CPU and the Python emulator, checking that both produced the same results for thousands of instructions.

- **Stress testing:**  
  Wrote stress tests that generated random instruction streams and compared the hardware and emulator outputs, catching subtle bugs and edge cases.

## How to Navigate

- **Each week’s folder (`w2`, `w3`, ...):**  
  Contains one or more labs, each with its own design and test files.

- **`rtl/` folders:**  
  Verilog source code for each module.

- **`test/` or `tests/` folders:**  
  Testbenches, either in C++ (for Verilator) or Python (for cocotb).

- **`run.py` scripts:**  
  Utility scripts to build, simulate, and test the designs.

- **Assembler and emulator:**  
  Python scripts for translating assembly and running programs on the CPU model.

## What I Learned

- The nuts and bolts of digital design, from gates to CPUs.
- How to write and verify Verilog code, both with C++ and Python.
- The importance of thorough verification—bugs always hide in the corners!
- How to design a CPU from the ground up, including the instruction set, assembler, and emulator.
- How to automate testing and catch subtle hardware/software mismatches.

## Acknowledgements

Big thanks to Dr. Nursultan Kabylkas for the course, guidance, and inspiration.  
Check out his [GitHub](https://github.com/kabylkas) for more cool projects and resources.

---

**If you’re a student or hobbyist interested in digital design, feel free to poke around! There’s a bit of everything here—from basic circuits to a full custom CPU, along with all the verification and tooling. Just a heads up: most of my code isn’t exactly cute or clean, so it might be a little tricky to navigate.**

---

Let me know if you want to add a section on how to run the tests or build the CPU, or if you want to highlight any specific lab or achievement!