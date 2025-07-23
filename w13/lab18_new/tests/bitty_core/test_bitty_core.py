# import cocotb
# from cocotb.clock import Clock
# from cocotb.triggers import RisingEdge, FallingEdge, Timer, ClockCycles, ReadOnly, NextTimeStep

# from emulator.bitty_emu import BittyEmulator
# from emulator.bitty_inst_gen import BittyInstructionGenerator

# from assembler_tool import BittyISA

# import os
# from pathlib import Path


# # --- Testbench Configuration ---
# CLOCK_PERIOD_NS = 1
# RESET_CYCLES = 5
# INSTRUCTION_CYCLES = 4

# # --- Graceful Stop Configuration ---
# MAX_SIMULATION_ITERATIONS = (1 << 8) * 10
# PC_STAGNATION_LIMIT = 10


# def compare_value(dut_signal, emu_value, name_prefix):
#     signal_name = f"{name_prefix}"
#     if hasattr(dut_signal, "name"):
#         signal_name = dut_signal.name

#     if dut_signal.value.is_resolvable:
#         dut_value = dut_signal.value.integer
#         width = len(dut_signal)

#         try:
#             emu_value_int = int(emu_value)
#         except (ValueError, TypeError) as e:
#             cocotb.log.error(f"Emulator value for {name_prefix} ('{emu_value}') is not a valid integer: {e}")
#             assert False, f"Invalid emulator value for {name_prefix}"
#             return

#         mask = (1 << width) - 1
#         emu_value_masked = emu_value_int & mask

#         hex_width_chars = (width + 3) // 4

#         cocotb.log.debug(f"  Compare {name_prefix} (width {width}, DUT signal: {signal_name}): "
#                          f"DUT={dut_value:0{hex_width_chars}X} ({dut_value}), "
#                          f"Emulator={emu_value_masked:0{hex_width_chars}X} ({emu_value_masked})")

#         assert dut_value == emu_value_masked, \
#             f"Mismatch in {name_prefix} (DUT signal: {signal_name}): " \
#             f"DUT={dut_value:0{hex_width_chars}X} ({dut_value}), " \
#             f"Emulator={emu_value_masked:0{hex_width_chars}X} ({emu_value_masked})"
#     else:
#         cocotb.log.warning(f"  DUT signal {name_prefix} ({signal_name}) is not resolvable (value: {dut_signal.value}). Skipping comparison.")


# @cocotb.test()
# async def test_bitty_core(dut):
#     """Co-simulation test for the bitty_core."""

#     memory_file_path = Path(os.getenv("MEMORY_FILE"))
#     instructions = []
#     with open(memory_file_path, "r") as f:
#         for line in f.readlines():
#             if line.strip():
#                 instruction = int(line.strip(), 16)
#                 instructions.append(instruction)

#     emulator = BittyEmulator(file_path=memory_file_path)

#     for i, instruction in enumerate(instructions):
#         cocotb.log.info(f"uploading {BittyISA.decode(instruction)} at {i}")
#         dut.fetch_unit_inst.memory[i].value = instruction

#     cocotb.log.info("Starting test_bitty_core")
#     clock = Clock(dut.clk, CLOCK_PERIOD_NS, units="ns")
#     cocotb.start_soon(clock.start())

#     cocotb.log.info(f"Applying reset for {RESET_CYCLES} cycles")
#     dut.reset.value = 1
#     dut.run.value = 0
#     dut.instruction.value = 0
#     await ClockCycles(dut.clk, RESET_CYCLES)
#     dut.reset.value = 0
#     cocotb.log.info("Reset released")
#     await ClockCycles(dut.clk, 2)

#     cocotb.log.info(f"Starting co-simulation for {len(instructions)} instructions")

#     i = 0
#     iteration_count = 0                              # --- ADDED
#     previous_pc = None                               # --- ADDED
#     stagnant_pc_counter = 0                          # --- ADDED

#     while iteration_count < MAX_SIMULATION_ITERATIONS:  # --- MODIFIED
#         cocotb.log.info(f"--- Instruction {i}/{len(instructions) - 1} ---")

#         try:
#             next_instruction = instructions[i]
#             cocotb.log.info(f"Using instruction: {next_instruction:016b} at iteration {iteration_count}")
#         except IndexError:
#             cocotb.log.info(f"No more instructions")
#             break

#         dut.run.value = 1
#         cocotb.log.info("Asserted run signal")

#         cocotb.log.info(f"Waiting for {INSTRUCTION_CYCLES} clock cycles for instruction execution...")
#         await ClockCycles(dut.clk, INSTRUCTION_CYCLES)
#         cocotb.log.info("Instruction execution cycles completed.")

#         cocotb.log.info(f"Current DUT instruction: {dut.instruction}: {BittyISA.decode(dut.instruction.value)}")
#         cocotb.log.info(f"Current DUT last_alu_result: {dut.reg_c_out.value}")
#         cocotb.log.info(f"Current EMU instruction: {next_instruction:016b}: {BittyISA.decode(next_instruction)}")

#         assert dut.instruction.value == next_instruction, \
#             f"Instruction mismatch: DUT {dut.instruction.value} != EMU {next_instruction}"

#         dut.run.value = 0
#         cocotb.log.info("Deasserted run signal")

#         await ReadOnly()
#         await NextTimeStep()

#         try:
#             i = emulator.evaluate()
#             cocotb.log.info(f"Emulator after emulation:\t {emulator}")
#         except StopIteration:
#             cocotb.log.info("No more instructions to execute in the emulator.")
#             break

#         # --- Infinite loop detection via PC stagnation ---
#         current_pc = emulator.get_pc()                 # --- ADDED
#         if current_pc == previous_pc:                  # --- ADDED
#             stagnant_pc_counter += 1                   # --- ADDED
#         else:
#             stagnant_pc_counter = 0                    # --- ADDED
#             previous_pc = current_pc                   # --- ADDED

#         if stagnant_pc_counter >= PC_STAGNATION_LIMIT:  # --- ADDED
#             cocotb.log.warning(f"PC did not change for {stagnant_pc_counter} cycles. Assuming infinite loop.")
#             break

#         iteration_count += 1                           # --- ADDED

#         dut_register_values = [f"r{idx}: {getattr(dut, f'reg{idx}_out').value.integer}" for idx in range(8)]
#         cocotb.log.info(f"DUT after emulation:\t\t {' | '.join(dut_register_values)}")

#         cocotb.log.info("Comparing DUT outputs with emulator state...")

#         for reg_idx in range(8):
#             compare_value(getattr(dut, f'reg{reg_idx}_out'), emulator.get_register_value(reg_idx), f'reg{reg_idx}')

#         cocotb.log.info("Comparison successful.")

#     if iteration_count >= MAX_SIMULATION_ITERATIONS:
#         cocotb.log.error(f"Simulation stopped after reaching MAX_SIMULATION_ITERATIONS={MAX_SIMULATION_ITERATIONS}")

#     cocotb.log.info("Co-simulation finished.")


import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, FallingEdge, Timer, ClockCycles, ReadOnly, NextTimeStep

from emulator.bitty_emu import BittyEmulator
from emulator.bitty_inst_gen import BittyInstructionGenerator

from assembler_tool import BittyISA

import os
from pathlib import Path


# --- Testbench Configuration ---
CLOCK_PERIOD_NS = 1
RESET_CYCLES = 5
INSTRUCTION_CYCLES = 4

# --- Graceful Stop Configuration ---
MAX_SIMULATION_ITERATIONS = (1 << 8) * 10
PC_STAGNATION_LIMIT = 10

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


@cocotb.test()
async def test_bitty_core(dut):
    """Co-simulation test for the bitty_core."""

    memory_file_path = Path(os.getenv("MEMORY_FILE"))
    emulator = BittyEmulator(instruction_path=memory_file_path)
    instructions = emulator.instructions

    for i, instruction in enumerate(instructions):
        cocotb.log.info(f"uploading {BittyISA.decode(instruction)} at {i}")
        dut.fetch_unit_inst.memory[i].value = instruction

    cocotb.log.info("Starting test_bitty_core")
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

    iteration_count = 0
    previous_pc = None
    stagnant_pc_counter = 0

    while iteration_count < MAX_SIMULATION_ITERATIONS:
        pc = emulator.get_pc()
        try:
            next_instruction = instructions[pc]
        except IndexError:
            cocotb.log.info("No more instructions")
            break

        cocotb.log.info(f"--- Instruction at PC={pc} ---")
        cocotb.log.info(f"Using instruction: {next_instruction:016b} at iteration {iteration_count}")

        dut.run.value = 1
        cocotb.log.info("Asserted run signal")

        await ClockCycles(dut.clk, INSTRUCTION_CYCLES)
        cocotb.log.info("Instruction execution cycles completed.")

        cocotb.log.info(f"Current DUT instruction: {dut.instruction}: {BittyISA.decode(dut.instruction.value)}")
        cocotb.log.info(f"Current DUT last_alu_result: {dut.reg_c_out.value}")
        cocotb.log.info(f"Current EMU instruction: {next_instruction:016b}: {BittyISA.decode(next_instruction)}")

        assert dut.instruction.value == next_instruction, \
            f"Instruction mismatch: DUT {dut.instruction.value} != EMU {next_instruction}"

        dut.run.value = 0
        cocotb.log.info("Deasserted run signal")

        await ReadOnly()
        await NextTimeStep()

        try:
            emulator.step()
            cocotb.log.info(f"Emulator after step:\t {emulator}")
        except StopIteration:
            cocotb.log.info("No more instructions to execute in the emulator.")
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

        dut_register_values = [f"r{idx}: {getattr(dut, f'reg{idx}_out').value.integer}" for idx in range(8)]
        cocotb.log.info(f"DUT after emulation:\t\t {' | '.join(dut_register_values)}")

        cocotb.log.info("Comparing DUT outputs with emulator state...")
        for reg_idx in range(8):
            compare_value(getattr(dut, f'reg{reg_idx}_out'), emulator.get_reg(reg_idx), f'reg{reg_idx}')

        cocotb.log.info("Comparison successful.")

    if iteration_count >= MAX_SIMULATION_ITERATIONS:
        cocotb.log.error(f"Simulation stopped after reaching MAX_SIMULATION_ITERATIONS={MAX_SIMULATION_ITERATIONS}")

    cocotb.log.info("Co-simulation finished.")
