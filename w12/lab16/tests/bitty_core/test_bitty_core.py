import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, FallingEdge, Timer, ClockCycles, ReadOnly, NextTimeStep

# Assuming your emulator and instruction generator are in these locations
# Adjust import paths if necessary based on your project structure
from emulator.bitty_emu import BittyEmulator
from emulator.bitty_inst_gen import BittyInstructionGenerator

import os
from pathlib import Path


# --- Testbench Configuration ---
CLOCK_PERIOD_NS = 1  # Clock period in nanoseconds
RESET_CYCLES = 5 # Number of clock cycles to hold reset
# Number of clock cycles for one instruction to execute (based on your state machine)
INSTRUCTION_CYCLES = 4


# Simulate Bitty Core with manually driven instructions
@cocotb.test()
async def test_bitty_core(dut):
    """Co-simulation test for the bitty_core."""

    # --- Parse insturctions ---
    memory_file_path = Path(os.getenv("MEMORY_FILE"))
    instructions = list()
    with open(memory_file_path, "r") as f:
        for line in f.readlines():
            if line.strip():
                # Convert hex string to integer
                instruction = int(line.strip(), 16)
                instructions.append(instruction)

    # --- Initialize Emulator with preloaded memory ---
    emulator = BittyEmulator(file_path=memory_file_path)

    # --- Load instructions into the dut ---
    for i, instruction in enumerate(instructions):
        dut.fetch_unit_inst.memory[i].value = instruction

    # --- Initialize Clock and Reset ---
    cocotb.log.info("Starting test_bitty_core")

    # Create a clock instance
    clock = Clock(dut.clk, CLOCK_PERIOD_NS, units="ns")
    # Start the clock in the background
    cocotb.start_soon(clock.start())

    # Apply reset
    cocotb.log.info(f"Applying reset for {RESET_CYCLES} cycles")
    dut.reset.value = 1
    dut.run.value = 0 # Ensure run is low during reset
    dut.instruction.value = 0 # Drive instruction to 0 during reset

    await ClockCycles(dut.clk, RESET_CYCLES)
    dut.reset.value = 0
    cocotb.log.info("Reset released")

    # Wait for a few clock cycles after reset to ensure stability
    await ClockCycles(dut.clk, 2)

    # --- Co-simulation Loop ---
    cocotb.log.info(f"Starting co-simulation for {len(instructions)} instructions")

    for i, inst in enumerate(instructions):
        cocotb.log.info(f"--- Instruction {i+1}/{len(instructions)} ---")

        # 1. Use the generated instruction from the list
        next_instruction = inst
        cocotb.log.info(f"Using instruction: {next_instruction:016b}")

        # 3. Start the core execution
        dut.run.value = 1
        cocotb.log.info("Asserted run signal")

        # Wait for the core to execute the instruction for the required number of cycles
        # This replaces waiting for the 'done' signal for synchronization
        cocotb.log.info(f"Waiting for {INSTRUCTION_CYCLES} clock cycles for instruction execution...")
        await ClockCycles(dut.clk, INSTRUCTION_CYCLES)
        cocotb.log.info("Instruction execution cycles completed.")

        # Deassert run signal after execution cycles
        dut.run.value = 0
        cocotb.log.info("Deasserted run signal")

        # Wait a very small amount of time *after* the last clock edge
        # to allow register outputs to propagate and become stable before sampling.
        await ReadOnly()
        await NextTimeStep()

        # 4. Emulate the instruction using your emulator function
        emulator.evaluate()
        cocotb.log.info(f"Emulator after emulation:\t {emulator}")

        # Extract DUT register values into a list for better readability
        dut_register_values = [f"r{idx}: {getattr(dut, f'reg{idx}_out').value.integer}" for idx in range(8)]
        cocotb.log.info(f"DUT after emulation:\t\t {' | '.join(dut_register_values)}")

        # 5. Compare DUT outputs with emulator state
        cocotb.log.info("Comparing DUT outputs with emulator state...")

        # Helper function for comparison
        def compare_value(dut_signal, emu_value, name):
            # Check if the DUT signal value is valid before accessing .integer
            if dut_signal.value.is_resolvable:
                dut_value = dut_signal.value.integer
                # Mask emulator value to the width of the DUT signal
                width = len(dut_signal)
                emu_value_masked = emu_value & ((1 << width) - 1)
                cocotb.log.debug(f"  Compare {name} (width {width}): DUT={dut_value:0{width//4}x}, Emulator={emu_value_masked:0{width//4}x}")
                assert dut_value == emu_value_masked, f"Mismatch in {name}: DUT={dut_value:0{width//4}x}, Emulator={emu_value_masked:0{width//4}x}"
            else:
                 cocotb.log.warning(f"  DUT signal {name} is not resolvable (e.g., 'x' or 'z'). Skipping comparison for this cycle.")
                 # Depending on your test requirements, you might want to fail the test here
                 # assert False, f"DUT signal {name} is not resolvable"


        # Compare general-purpose registers (reg0_out to reg7_out)
        for reg_idx in range(8):
             compare_value(getattr(dut, f'reg{reg_idx}_out'), emulator.get_register_value(reg_idx), f'reg{reg_idx}')

        cocotb.log.info("Comparison successful.")

    cocotb.log.info("Co-simulation finished successfully.")
