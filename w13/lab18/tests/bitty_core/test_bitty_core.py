# import cocotb
# from cocotb.clock import Clock
# from cocotb.triggers import RisingEdge, FallingEdge, Timer, ClockCycles, ReadOnly, NextTimeStep

# # Assuming your emulator and instruction generator are in these locations
# # Adjust import paths if necessary based on your project structure
# from emulator.bitty_emu import BittyEmulator
# from emulator.bitty_inst_gen import BittyInstructionGenerator

# from assembler_tool import BittyISA

# import os
# from pathlib import Path


# # --- Testbench Configuration ---
# CLOCK_PERIOD_NS = 1  # Clock period in nanoseconds
# RESET_CYCLES = 5     # Number of clock cycles to hold reset
# # Number of clock cycles for one instruction to execute (based on your state machine)
# # If your DUT has a 'done' signal, using it would be more robust than a fixed cycle count.
# INSTRUCTION_CYCLES = 4

# # --- Graceful Stop Configuration ---
# # Max number of instructions to attempt to simulate (overall loop iterations)
# # Adjust based on expected program length and complexity. E.g., len(instructions) * 10 or a fixed large number.
# MAX_SIMULATION_ITERATIONS = 10000
# # Max number of consecutive times the Program Counter (from emulator) can be the same before declaring a loop/stall
# PC_STAGNATION_LIMIT = 10          # Adjust as needed; too low might give false positives on multi-cycle instructions
#                                   # if PC doesn't advance immediately in the emulator's view.


# # --- Helper function for comparison ---
# def compare_value(dut_signal, emu_value, name_prefix):
#     signal_name = f"{name_prefix}"
#     if hasattr(dut_signal, "name"): # Use full hierarchical name if available
#         signal_name = dut_signal.name

#     if dut_signal.value.is_resolvable:
#         dut_value = dut_signal.value.integer
#         width = len(dut_signal)

#         try:
#             emu_value_int = int(emu_value) # Ensure emulator value is an integer
#         except (ValueError, TypeError) as e:
#             cocotb.log.error(f"Emulator value for {name_prefix} ('{emu_value}') is not a valid integer: {e}")
#             assert False, f"Invalid emulator value for {name_prefix}"
#             return # Should be unreachable due to assert

#         mask = (1 << width) - 1
#         emu_value_masked = emu_value_int & mask

#         hex_width_chars = (width + 3) // 4

#         cocotb.log.debug(f"  Compare {name_prefix} (width {width}, DUT signal: {signal_name}): "
#                             f"DUT={dut_value:0{hex_width_chars}X} ({dut_value}), "
#                             f"Emulator={emu_value_masked:0{hex_width_chars}X} ({emu_value_masked})")

#         assert dut_value == emu_value_masked, \
#             f"Mismatch in {name_prefix} (DUT signal: {signal_name}): " \
#             f"DUT={dut_value:0{hex_width_chars}X} ({dut_value}), " \
#             f"Emulator={emu_value_masked:0{hex_width_chars}X} ({emu_value_masked})"
#     else:
#         cocotb.log.warning(f"  DUT signal {name_prefix} ({signal_name}) is not resolvable (value: {dut_signal.value}). "
#                             "Skipping comparison for this cycle.")
#         # Depending on your test requirements, you might want to fail the test here
#         # assert False, f"DUT signal {name_prefix} ({signal_name}) is not resolvable ({dut_signal.value})"


# # Simulate Bitty Core with manually driven instructions
# @cocotb.test()
# async def test_bitty_core(dut):
#     """Co-simulation test for the bitty_core."""

#     # --- Parse insturctions ---
#     memory_file_path = Path(os.getenv("MEMORY_FILE"))
#     instructions = list()
#     with open(memory_file_path, "r") as f:
#         for line in f.readlines():
#             if line.strip():
#                 # Convert hex string to integer
#                 instruction = int(line.strip(), 16)
#                 instructions.append(instruction)

#     # --- Initialize Emulator with preloaded memory ---
#     emulator = BittyEmulator(file_path=memory_file_path)

#     # --- Load instructions into the dut ---
#     for i, instruction in enumerate(instructions):
#         cocotb.log.info(f"uploading {BittyISA.decode(instruction)} at {i}")
#         dut.fetch_unit_inst.memory[i].value = instruction

#     # --- Initialize Clock and Reset ---
#     cocotb.log.info("Starting test_bitty_core")

#     # Create a clock instance
#     clock = Clock(dut.clk, CLOCK_PERIOD_NS, units="ns")
#     # Start the clock in the background
#     cocotb.start_soon(clock.start())

#     # Apply reset
#     cocotb.log.info(f"Applying reset for {RESET_CYCLES} cycles")
#     dut.reset.value = 1
#     dut.run.value = 0 # Ensure run is low during reset
#     dut.instruction.value = 0 # Drive instruction to 0 during reset

#     await ClockCycles(dut.clk, RESET_CYCLES)
#     dut.reset.value = 0
#     cocotb.log.info("Reset released")

#     # Wait for a few clock cycles after reset to ensure stability
#     await ClockCycles(dut.clk, 2)

#     # --- Co-simulation Loop ---
#     cocotb.log.info(f"Starting co-simulation for {len(instructions)} instructions")

#     i = 0
#     while True:
#         cocotb.log.info(f"--- Instruction {i}/{len(instructions) - 1} ---")

#         # 1. Use the instruction from the list
#         try:
#             next_instruction = instructions[i]
#             cocotb.log.info(f"Using instruction: {next_instruction:016b}")

#         except IndexError:
#             cocotb.log.info(f"No more instructions")
#             break

#         # 3. Start the core execution
#         dut.run.value = 1
#         cocotb.log.info("Asserted run signal")

#         # Wait for the core to execute the instruction for the required number of cycles
#         # This replaces waiting for the 'done' signal for synchronization
#         cocotb.log.info(f"Waiting for {INSTRUCTION_CYCLES} clock cycles for instruction execution...")
#         await ClockCycles(dut.clk, INSTRUCTION_CYCLES)
#         cocotb.log.info("Instruction execution cycles completed.")

#         cocotb.log.info(f"Current DUT instruction: {dut.instruction}: {BittyISA.decode(dut.instruction.value)}")
#         cocotb.log.info(f"Current DUT last_alu_result: {dut.reg_c_out.value}")
#         cocotb.log.info(f"Current EMU instruction: {next_instruction:016b}: {BittyISA.decode(next_instruction)}")

#         # Deassert run signal after execution cycles
#         dut.run.value = 0
#         cocotb.log.info("Deasserted run signal")

#         # Wait a very small amount of time *after* the last clock edge
#         # to allow register outputs to propagate and become stable before sampling.
#         await ReadOnly()
#         await NextTimeStep()

#         # 4. Emulate the instruction using your emulator function
#         try:
#             i = emulator.evaluate()
#             cocotb.log.info(f"Emulator after emulation:\t {emulator}")
#         except StopIteration:
#             cocotb.log.info("No more instructions to execute in the emulator.")
#             break

#         # Extract DUT register values into a list for better readability
#         dut_register_values = [f"r{idx}: {getattr(dut, f'reg{idx}_out').value.integer}" for idx in range(8)]
#         cocotb.log.info(f"DUT after emulation:\t\t {' | '.join(dut_register_values)}")

#         # 5. Compare DUT outputs with emulator state
#         cocotb.log.info("Comparing DUT outputs with emulator state...")

#         # Helper function for comparison
#         def compare_value(dut_signal, emu_value, name):
#             # Check if the DUT signal value is valid before accessing .integer
#             if dut_signal.value.is_resolvable:
#                 dut_value = dut_signal.value.integer
#                 # Mask emulator value to the width of the DUT signal
#                 width = len(dut_signal)
#                 emu_value_masked = emu_value & ((1 << width) - 1)
#                 cocotb.log.debug(f"  Compare {name} (width {width}): DUT={dut_value:0{width//4}x}, Emulator={emu_value_masked:0{width//4}x}")
#                 assert dut_value == emu_value_masked, f"Mismatch in {name}: DUT={dut_value:0{width//4}x}, Emulator={emu_value_masked:0{width//4}x}"
#             else:
#                  cocotb.log.warning(f"  DUT signal {name} is not resolvable (e.g., 'x' or 'z'). Skipping comparison for this cycle.")
#                  # Depending on your test requirements, you might want to fail the test here
#                  # assert False, f"DUT signal {name} is not resolvable"


#         # Compare general-purpose registers (reg0_out to reg7_out)
#         for reg_idx in range(8):
#              compare_value(getattr(dut, f'reg{reg_idx}_out'), emulator.get_register_value(reg_idx), f'reg{reg_idx}')

#         cocotb.log.info("Comparison successful.")

#     cocotb.log.info("Co-simulation finished successfully.")


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
MAX_SIMULATION_ITERATIONS = (1 << 12) * 10
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
    instructions = []
    with open(memory_file_path, "r") as f:
        for line in f.readlines():
            if line.strip():
                instruction = int(line.strip(), 16)
                instructions.append(instruction)

    emulator = BittyEmulator(file_path=memory_file_path)

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

    i = 0
    iteration_count = 0                              # --- ADDED
    previous_pc = None                               # --- ADDED
    stagnant_pc_counter = 0                          # --- ADDED

    while iteration_count < MAX_SIMULATION_ITERATIONS:  # --- MODIFIED
        cocotb.log.info(f"--- Instruction {i}/{len(instructions) - 1} ---")

        try:
            next_instruction = instructions[i]
            cocotb.log.info(f"Using instruction: {next_instruction:016b} at iteration {iteration_count}")
        except IndexError:
            cocotb.log.info(f"No more instructions")
            break

        dut.run.value = 1
        cocotb.log.info("Asserted run signal")

        cocotb.log.info(f"Waiting for {INSTRUCTION_CYCLES} clock cycles for instruction execution...")
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
            i = emulator.evaluate()
            cocotb.log.info(f"Emulator after emulation:\t {emulator}")
        except StopIteration:
            cocotb.log.info("No more instructions to execute in the emulator.")
            break

        # --- Infinite loop detection via PC stagnation ---
        current_pc = emulator.get_pc()                 # --- ADDED
        if current_pc == previous_pc:                  # --- ADDED
            stagnant_pc_counter += 1                   # --- ADDED
        else:
            stagnant_pc_counter = 0                    # --- ADDED
            previous_pc = current_pc                   # --- ADDED

        if stagnant_pc_counter >= PC_STAGNATION_LIMIT:  # --- ADDED
            cocotb.log.warning(f"PC did not change for {stagnant_pc_counter} cycles. Assuming infinite loop.")
            break

        iteration_count += 1                           # --- ADDED

        dut_register_values = [f"r{idx}: {getattr(dut, f'reg{idx}_out').value.integer}" for idx in range(8)]
        cocotb.log.info(f"DUT after emulation:\t\t {' | '.join(dut_register_values)}")

        cocotb.log.info("Comparing DUT outputs with emulator state...")

        for reg_idx in range(8):
            compare_value(getattr(dut, f'reg{reg_idx}_out'), emulator.get_register_value(reg_idx), f'reg{reg_idx}')

        cocotb.log.info("Comparison successful.")

    if iteration_count >= MAX_SIMULATION_ITERATIONS:
        cocotb.log.error(f"Simulation stopped after reaching MAX_SIMULATION_ITERATIONS={MAX_SIMULATION_ITERATIONS}")

    cocotb.log.info("Co-simulation finished.")
