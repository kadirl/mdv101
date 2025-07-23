# import cocotb
# from cocotb.triggers import RisingEdge, FallingEdge
# from cocotb.clock import Clock



import cocotb
from cocotb.triggers import RisingEdge
from cocotb.clock import Clock
import random


@cocotb.test()
async def test_lsu_basic_store_and_load(dut):
    """Test basic store and load operations."""
    clock = Clock(dut.clk, 10, units="ns")
    cocotb.start_soon(clock.start())

    dut.reset.value = 0  # Active-low reset asserted
    await RisingEdge(dut.clk)
    dut.reset.value = 1  # Deassert reset
    await RisingEdge(dut.clk)

    # Store 0xABCD to address 0x10
    dut.en_ls.value = 0b01
    dut.address.value = 0x10
    dut.data_to_store.value = 0xABCD
    await RisingEdge(dut.clk)
    dut.en_ls.value = 0b00
    await RisingEdge(dut.clk)

    # Load from address 0x10
    for i in range(256):
        print(dut.memory[i])
    #
    dut.address.value = 0x10
    dut.en_ls.value = 0b10
    await RisingEdge(dut.clk)
    await RisingEdge(dut.clk)
    assert dut.data_to_load.value == 0xABCD, f"Load mismatch: expected 0xABCD, got {dut.data_to_load.value}"

@cocotb.test()
async def test_lsu_reset_behavior(dut):
    """Test memory reset behavior does not erase memory contents."""
    clock = Clock(dut.clk, 10, units="ns")
    cocotb.start_soon(clock.start())

    # First reset
    dut.reset.value = 0
    await RisingEdge(dut.clk)
    dut.reset.value = 1
    await RisingEdge(dut.clk)

    # Store a value
    dut.en_ls.value = 0b01
    dut.address.value = 0x20
    dut.data_to_store.value = 0x1234
    await RisingEdge(dut.clk)

    # Second reset
    dut.reset.value = 0
    await RisingEdge(dut.clk)
    dut.reset.value = 1
    await RisingEdge(dut.clk)

    # Try loading again
    dut.en_ls.value = 0b10
    await RisingEdge(dut.clk)
    assert dut.data_to_load.value == 0x1234, f"Data lost after reset: expected 0x1234, got {dut.data_to_load.value}"

@cocotb.test()
async def test_lsu_read_after_write(dut):
    """Test reading immediately after writing."""
    clock = Clock(dut.clk, 10, units="ns")
    cocotb.start_soon(clock.start())

    dut.reset.value = 0
    await RisingEdge(dut.clk)
    dut.reset.value = 1
    await RisingEdge(dut.clk)

    addr = 0x30
    val = 0xDEAD

    # Write
    dut.en_ls.value = 0b01
    dut.address.value = addr
    dut.data_to_store.value = val
    await RisingEdge(dut.clk)

    # Read
    dut.en_ls.value = 0b10
    dut.address.value = addr
    await RisingEdge(dut.clk)
    assert dut.data_to_load.value == val, f"Read-after-write failed: expected {val:X}, got {dut.data_to_load.value}"

@cocotb.test()
async def test_lsu_randomized_access(dut):
    """Test multiple random store/load accesses."""
    clock = Clock(dut.clk, 10, units="ns")
    cocotb.start_soon(clock.start())

    dut.reset.value = 0
    await RisingEdge(dut.clk)
    dut.reset.value = 1
    await RisingEdge(dut.clk)

    ref_mem = {}

    for _ in range(10):
        addr = random.randint(0, 255)
        val = random.randint(0, 0xFFFF)

        # Store
        dut.en_ls.value = 0b01
        dut.address.value = addr
        dut.data_to_store.value = val
        ref_mem[addr] = val
        await RisingEdge(dut.clk)

    for addr, val in ref_mem.items():
        # Load
        dut.en_ls.value = 0b10
        dut.address.value = addr
        await RisingEdge(dut.clk)
        assert dut.data_to_load.value == val, f"Mismatch at addr {addr:X}: expected {val:X}, got {dut.data_to_load.value:X}"

@cocotb.test()
async def test_lsu_no_op(dut):
    """Test no operation (en_ls = 00) results in no change."""
    clock = Clock(dut.clk, 10, units="ns")
    cocotb.start_soon(clock.start())

    dut.reset.value = 0
    await RisingEdge(dut.clk)
    dut.reset.value = 1
    await RisingEdge(dut.clk)

    # Store known value
    dut.en_ls.value = 0b01
    dut.address.value = 0x40
    dut.data_to_store.value = 0xFFFF
    await RisingEdge(dut.clk)

    # Idle
    dut.en_ls.value = 0b00
    await RisingEdge(dut.clk)

    # Load
    dut.en_ls.value = 0b10
    dut.address.value = 0x40
    await RisingEdge(dut.clk)
    assert dut.data_to_load.value == 0xFFFF, f"Idle altered memory: expected 0xFFFF, got {dut.data_to_load.value:X}"
