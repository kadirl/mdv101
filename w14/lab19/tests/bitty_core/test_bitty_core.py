import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, FallingEdge, Timer, ClockCycles, ReadOnly, NextTimeStep

from emulator.bitty_emu import BittyEmulator
from emulator.bitty_inst_gen import BittyInstructionGenerator

from assembler_tool import Disassembler

import os
import tempfile
import random
import argparse
from pathlib import Path


# --- Testbench Configuration ---
CLOCK_PERIOD_NS = 1
RESET_CYCLES = 5
INSTRUCTION_CYCLES = 4

# --- Graceful Stop Configuration ---
MAX_SIMULATION_ITERATIONS = (1 << 8) * 10
PC_STAGNATION_LIMIT = 10

# --- Stress Test Configuration ---
DEFAULT_STRESS_TEST_COUNT = 10
DEFAULT_INSTRUCTIONS_PER_TEST = 50
STRESS_TEST_MODE = False  # Set via environment variable

def compare_value(dut_signal, emu_value, name_prefix):
    signal_name = f"{name_prefix}"
    if hasattr(dut_signal, "name"):
        signal_name = dut_signal.name

    if dut_signal.value.is_resolvable:
        dut_value = dut_signal.value.integer
        width = len(dut_signal)

        try:
            emu_value_int = int(emu_value)
        except (ValueError, TypeError) as e:
            cocotb.log.error(f"Emulator value for {name_prefix} ('{emu_value}') is not a valid integer: {e}")
            assert False, f"Invalid emulator value for {name_prefix}"
            return

        mask = (1 << width) - 1
        emu_value_masked = emu_value_int & mask

        hex_width_chars = (width + 3) // 4

        cocotb.log.debug(f"  Compare {name_prefix} (width {width}, DUT signal: {signal_name}): "
                         f"DUT={dut_value:0{hex_width_chars}X} ({dut_value}), "
                         f"Emulator={emu_value_masked:0{hex_width_chars}X} ({emu_value_masked})")

        assert dut_value == emu_value_masked, \
            f"Mismatch in {name_prefix} (DUT signal: {signal_name}): " \
            f"DUT={dut_value:0{hex_width_chars}X} ({dut_value}), " \
            f"Emulator={emu_value_masked:0{hex_width_chars}X} ({emu_value_masked})"
    else:
        cocotb.log.warning(f"  DUT signal {name_prefix} ({signal_name}) is not resolvable (value: {dut_signal.value}). Skipping comparison.")


def generate_random_instructions(count):
    """Generate a list of random instructions."""
    instructions = []
    generator = BittyInstructionGenerator()
    for _ in range(count):
        instructions.append(generator.generate(count))
    return instructions

def write_instruction_file(instructions):
    """Write instructions to a temporary file and return the path."""
    temp_file = tempfile.NamedTemporaryFile(mode='w', delete=False, suffix='.bin')

    for instruction in instructions:
        temp_file.write(f"{instruction:016b}\n")

    temp_file.close()
    return temp_file.name

@cocotb.test()
async def test_bitty_core(dut):
    """Co-simulation test for the bitty_core.

    This test can operate in two modes:
    1. Normal mode: Uses a pre-defined instruction file (MEMORY_FILE)
    2. Stress test mode: Generates random instructions and tests multiple times
    """
    global STRESS_TEST_MODE

    # Check if we're in stress test mode
    stress_count = os.getenv("STRESS_TEST_COUNT")
    STRESS_TEST_MODE = stress_count is not None

    if STRESS_TEST_MODE:
        # Get stress test configuration
        stress_test_count = int(stress_count) if stress_count else DEFAULT_STRESS_TEST_COUNT
        inst_per_test = int(os.getenv("INSTRUCTIONS_PER_TEST", DEFAULT_INSTRUCTIONS_PER_TEST))

        cocotb.log.info(f"=== STRESS TEST MODE: Running {stress_test_count} tests with {inst_per_test} instructions each ===")

        for test_iteration in range(stress_test_count):
            cocotb.log.info(f"\n\n=== STRESS TEST {test_iteration+1}/{stress_test_count} ===\n")

            # Generate random instructions
            instructions = generate_random_instructions(inst_per_test)
            temp_file_path = write_instruction_file(instructions)

            try:
                # Run the test with these instructions
                await run_single_test(dut, Path(temp_file_path), instructions)
            finally:
                # Clean up the temporary file
                os.unlink(temp_file_path)

            cocotb.log.info(f"=== STRESS TEST {test_iteration+1}/{stress_test_count} PASSED ===")

        cocotb.log.info(f"=== ALL {stress_test_count} STRESS TESTS PASSED ===")
    else:
        # Normal mode - use the provided memory file
        memory_file_path = Path(os.getenv("MEMORY_FILE"))
        emulator = BittyEmulator(instruction_path=memory_file_path)
        instructions = emulator.instructions

        # Run a single test with the provided memory file
        await run_single_test(dut, memory_file_path, instructions)

async def run_single_test(dut, memory_file_path, instructions):
    """Run a single test with the given instructions."""

    # If instructions are provided directly, use them
    # Otherwise, load from the emulator
    if isinstance(instructions, list):
        # We have pre-generated instructions
        pass
    else:
        # Create an emulator and load instructions from the file
        emulator = BittyEmulator(instruction_path=memory_file_path)
        instructions = emulator.instructions

    # Create an emulator with the given memory file
    emulator = BittyEmulator(instruction_path=memory_file_path)

    # Reset all DUT memories to ensure clean state between tests
    # 1. Reset instruction memory
    if hasattr(dut.fetch_unit_inst, 'memory'):
        for i in range(256):  # Reset all possible instruction memory
            dut.fetch_unit_inst.memory[i].value = 0

    # 2. Reset LSU (data) memory
    if hasattr(dut, 'lsu') and hasattr(dut.lsu, 'memory'):
        for i in range(256):  # Reset all data memory locations
            dut.lsu.memory[i].value = 0

    # Upload instructions to the DUT
    for i, instruction in enumerate(instructions):
        cocotb.log.info(f"Uploading {instruction} = {Disassembler.disassemble_word(instruction)} at {i}")
        dut.fetch_unit_inst.memory[i].value = instruction

    # Initialize and reset
    cocotb.log.info(f"Starting test with {len(instructions)} instructions")
    clock = Clock(dut.clk, CLOCK_PERIOD_NS, units="ns")
    cocotb.start_soon(clock.start())

    cocotb.log.info(f"Applying reset for {RESET_CYCLES} cycles")
    dut.reset.value = 1
    dut.run.value = 0
    dut.instruction.value = 0
    await ClockCycles(dut.clk, RESET_CYCLES)
    dut.reset.value = 0
    cocotb.log.info("Reset released")
    await ClockCycles(dut.clk, 2)

    cocotb.log.info(f"Starting co-simulation for {len(instructions)} instructions")

    # Main simulation loop
    iteration_count = 0
    previous_pc = None
    stagnant_pc_counter = 0
    # verbosity = not STRESS_TEST_MODE  # Less verbose in stress test mode
    verbosity = True

    while iteration_count < MAX_SIMULATION_ITERATIONS:
        pc = emulator.get_pc()
        try:
            next_instruction = instructions[pc]
        except IndexError:
            if verbosity: cocotb.log.info("No more instructions")
            break

        if verbosity: cocotb.log.info(f"--- Instruction at PC={pc} ---")
        if verbosity: cocotb.log.info(f"Using instruction: {next_instruction:016b} at iteration {iteration_count}")

        dut.run.value = 1
        if verbosity: cocotb.log.info("Asserted run signal")

        await ClockCycles(dut.clk, INSTRUCTION_CYCLES)
        if verbosity: cocotb.log.info("Instruction execution cycles completed.")

        if verbosity:
            cocotb.log.info(f"Current DUT instruction: {dut.instruction}: {Disassembler.disassemble_word(dut.instruction.value)}")
            cocotb.log.info(f"Current DUT last_alu_result: {dut.reg_c_out.value}")
            cocotb.log.info(f"Current EMU instruction: {next_instruction:016b}: {Disassembler.disassemble_word(next_instruction)}")

        assert dut.instruction.value == next_instruction, \
            f"Instruction mismatch: DUT {dut.instruction.value} != EMU {next_instruction}"

        dut.run.value = 0
        if verbosity: cocotb.log.info("Deasserted run signal")

        await ReadOnly()
        await NextTimeStep()

        try:
            emulator.step()
            if verbosity: cocotb.log.info(f"Emulator after step:\t\t {emulator}")
        except StopIteration:
            if verbosity: cocotb.log.info("No more instructions to execute in the emulator.")
            break

        current_pc = emulator.get_pc()
        if current_pc == previous_pc:
            stagnant_pc_counter += 1
        else:
            stagnant_pc_counter = 0
            previous_pc = current_pc

        if stagnant_pc_counter >= PC_STAGNATION_LIMIT:
            cocotb.log.warning(f"PC did not change for {stagnant_pc_counter} cycles. Assuming infinite loop.")
            break

        iteration_count += 1

        # Collect register values for display
        dut_register_values = [f"r{idx}: {getattr(dut, f'reg{idx}_out').value.integer}" for idx in range(8)]
        if verbosity:
            cocotb.log.info(f"DUT after emulation:\t\t {' | '.join(dut_register_values)}")

            # Display memory
            dut_mem_str = " | ".join(f"m{i}: {int(dut.lsu.memory[i].value)}" for i in range(10))
            emu_mem_str = " | ".join(f"m{i}: {emulator.memory[i]}" for i in range(10))
            cocotb.log.info(f"Emulator memory:\t {emu_mem_str}")
            cocotb.log.info(f"DUT memory:     \t {dut_mem_str}")

        # Compare registers
        if verbosity: cocotb.log.info("Comparing DUT registers with emulator state...")
        for reg_idx in range(8):
            compare_value(getattr(dut, f'reg{reg_idx}_out'), emulator.get_reg(reg_idx), f'reg{reg_idx}')

        # Compare memory (check a reasonable subset in stress test mode)
        mem_check_range = 20 if STRESS_TEST_MODE else 256
        if verbosity: cocotb.log.info("Comparing DUT memory with emulator memory...")
        for mem_idx in range(mem_check_range):
            if mem_idx < 256:  # Stay within bounds
                dut_mem_value = dut.lsu.memory[mem_idx].value
                emu_mem_value = emulator.memory[mem_idx]
                assert int(dut_mem_value) == emu_mem_value, \
                    f"Memory mismatch at address {mem_idx}: DUT={int(dut_mem_value)}, Emulator={emu_mem_value}"

        if verbosity: cocotb.log.info("Comparison successful.")

    if iteration_count >= MAX_SIMULATION_ITERATIONS:
        cocotb.log.error(f"Simulation stopped after reaching MAX_SIMULATION_ITERATIONS={MAX_SIMULATION_ITERATIONS}")

    # Final memory check - do a more thorough check at the end
    mem_final_check = 20 if STRESS_TEST_MODE else 256
    for i in range(mem_final_check):
        if i < 256:  # Stay within bounds
            if verbosity:
                cocotb.log.info(f"Final memory check - Address {i}: DUT={int(dut.lsu.memory[i].value):d}, Emulator={emulator.memory[i]}")
            assert int(dut.lsu.memory[i].value) == emulator.memory[i], \
                f"Final memory mismatch at address {i}: DUT={int(dut.lsu.memory[i].value)}, Emulator={emulator.memory[i]}"

    cocotb.log.info("Co-simulation finished successfully")
