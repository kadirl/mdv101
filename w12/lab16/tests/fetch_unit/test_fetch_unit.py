import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer, ClockCycles, ReadOnly, NextTimeStep


# Helper functions

async def init_placeholder_memory(dut):
    """Initialize memory with some values."""
    for i in range(1 << 16 - 1):
        dut.memory[i].value = i + 1


async def reset_dut(dut):
    """Reset the DUT."""
    dut.reset.value = 1
    dut.en_pc.value = 0
    await RisingEdge(dut.clk)
    dut.reset.value = 0
    await RisingEdge(dut.clk)


@cocotb.test()
async def test_reset(dut):
    """Test the reset functionality of the DUT."""
    # Start clock
    clock = Clock(dut.clk, 1, units="ns")
    cocotb.start_soon(clock.start())

    # Let clock run for a bit
    await ClockCycles(dut.clk, 5)

    # Reset DUT
    await reset_dut(dut)

    # Check that the instruction output is zero after reset
    assert dut.instruction_out.value == 0, "Instruction output should be zero after reset"
    assert dut.current_inst.value == 0, "PC output output should be zero after reset"


@cocotb.test()
async def test_en_pc(dut):
    """Test the PC counter functionality."""

    # Preload memory with some values
    await init_placeholder_memory(dut)

    # Start clock
    clock = Clock(dut.clk, 1, units="ns")
    cocotb.start_soon(clock.start())

    # Reset DUT
    await reset_dut(dut)

    # Let clock run for a bit
    await ClockCycles(dut.clk, 5)
    assert dut.current_inst.value == 0, "PC output should be zero after reset"

    # Enable en_pc and let clock run for a bit for PC to increment
    dut.en_pc.value = 1
    await ClockCycles(dut.clk, 5)
    dut.en_pc.value = 0
    await ClockCycles(dut.clk, 1)
    assert dut.current_inst.value == 5, "PC output should be 5 after 5 clock cycles with en_pc enabled"


@cocotb.test()
async def test_sim_fetch_cycle(dut):
    """Test the fetch cycle of the DUT."""

    # Preload memory with placeholder intructions
    await init_placeholder_memory(dut)

    # Start clock
    clock = Clock(dut.clk, 1, units="ns")
    cocotb.start_soon(clock.start())

    # Reset DUT
    await reset_dut(dut)

    # STATE 0: Read insturction and write in current instruction register
    assert dut.instruction_out.value == 1, "First instruction must be 1"
    await ClockCycles(dut.clk, 1)

    # STATE 1: Decode instruction
    await ClockCycles(dut.clk, 1)

    # STATE 2: Execute
    await ClockCycles(dut.clk, 1)

    # STATE 3: Writeback
    dut.en_pc.value = 1
    await ClockCycles(dut.clk, 1)

    # STATE 0: Read insturction
    # await Timer(1, "ps")
    await ReadOnly()
    assert dut.instruction_out.value == 2, "Second instruction must be 2"
    await ClockCycles(dut.clk, 1)


@cocotb.test()
async def test_full_sim(dut):
    """Full test with 256 intruction reading"""
    # Preload memory with placeholder intructions
    await init_placeholder_memory(dut)

    # Start clock
    clock = Clock(dut.clk, 1, units="ns")
    cocotb.start_soon(clock.start())

    # Reset DUT
    await reset_dut(dut)

    for i in range(256):
        # STATE 0: Read insturction and write in current instruction register
        await ReadOnly()
        await NextTimeStep()
        dut.en_pc.value = 0
        assert dut.current_inst.value == i, f"PC must be {i}"
        assert dut.instruction_out.value == i + 1, f"Instruction must be {i + 1}"
        await ClockCycles(dut.clk, 1)

        # STATE 1: Decode instruction
        await ClockCycles(dut.clk, 1)

        # STATE 2: Execute
        await ClockCycles(dut.clk, 1)

        # STATE 3: Writeback
        dut.en_pc.value = 1
        await ClockCycles(dut.clk, 1)


@cocotb.test()
async def test_mid_execution_reset(dut):
    """Reset PC in the middle of fetch cycle"""
    await init_placeholder_memory(dut)
    clock = Clock(dut.clk, 1, units="ns")
    cocotb.start_soon(clock.start())
    await reset_dut(dut)

    dut.en_pc.value = 1
    await ClockCycles(dut.clk, 10)

    assert dut.current_inst.value == 9, "PC should be 10 before reset"

    dut.reset.value = 1
    await ClockCycles(dut.clk, 1)
    dut.reset.value = 0
    await ClockCycles(dut.clk, 1)

    assert dut.current_inst.value == 0, "PC should reset to 0"
    assert dut.instruction_out.value == 1, "Instruction should reset to instruction[0]"


@cocotb.test()
async def test_pc_hold(dut):
    """PC should hold if en_pc is not asserted"""
    await init_placeholder_memory(dut)
    clock = Clock(dut.clk, 1, units="ns")
    cocotb.start_soon(clock.start())
    await reset_dut(dut)

    dut.en_pc.value = 0
    await ClockCycles(dut.clk, 5)
    assert dut.current_inst.value == 0, "PC should not increment if en_pc is low"


@cocotb.test()
async def test_instruction_output_stability(dut):
    """Instruction output should remain same if PC doesn't change"""
    await init_placeholder_memory(dut)
    clock = Clock(dut.clk, 1, units="ns")
    cocotb.start_soon(clock.start())
    await reset_dut(dut)

    inst_val = dut.instruction_out.value.integer
    dut.en_pc.value = 0
    await ClockCycles(dut.clk, 10)
    assert dut.instruction_out.value.integer == inst_val, "instruction_out should not change if PC doesn't"



