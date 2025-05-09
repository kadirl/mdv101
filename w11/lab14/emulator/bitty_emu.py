import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge
from cocotb.binary import BinaryValue


class BittyEmulator:
    BIT_COUNT = 16
    BIT_MASK = (1 << BIT_COUNT) - 1

    alu_functions = {
        0b000: lambda x, y: (x + y) & BittyEmulator.BIT_MASK,
        0b001: lambda x, y: (x - y) & BittyEmulator.BIT_MASK,
        0b010: lambda x, y: x & y,
        0b011: lambda x, y: x | y,
        0b100: lambda x, y: x ^ y,
        0b101: lambda x, y: (x << (y ^ BittyEmulator.BIT_COUNT)) & BittyEmulator.BIT_MASK,
        0b110: lambda x, y: (x >> (y ^ BittyEmulator.BIT_COUNT)) & BittyEmulator.BIT_MASK,
        0b111: lambda x, y: ((x < y) << 1) | (x > y)  # 0 if x == y, 1 if x > y, 2 if x < y
    }

    ALU_MODE_RTYPE = 0b00
    ALU_MODE_ITYPE = 0b01

    def __init__(self) -> None:
        # initialize 8 registers
        self.registers = [0 for _ in range(8)]  

    def decode(self, instruction: int) -> dict[str, int]:
        return {
            "rx": (instruction >> 13) & 0b111,
            "ry": (instruction >> 10) & 0b111,
            "reserved_1": (instruction >> 5) & 0b11111,
            "alu_select": (instruction >> 2) & 0b111,
            "mode": instruction & 0b11,
            "immediate": (instruction >> 5) & 0xFF
        }

    def execute_rtype(self, decoded: dict[str, int]) -> None:
        rx = self.get_register_value(decoded["rx"])
        ry = self.get_register_value(decoded["ry"])
        op = self.alu_functions[decoded["alu_select"]]

        self.set_register_value(decoded["rx"], op(rx, ry))

    def execute_itype(self, decoded: dict[str, int]) -> None:
        rx = self.get_register_value(decoded["rx"])
        immediate = decoded["immediate"]
        op = self.alu_functions[decoded["alu_select"]]

        self.set_register_value(decoded["rx"], op(rx, immediate))

    def evaluate(self, instruction: int) -> None:
        decoded = self.decode(instruction)
        print(f"Raw instruction: {instruction}\nDecoded instruction: {decoded}")

        if decoded["mode"] == self.ALU_MODE_RTYPE:
            self.execute_rtype(decoded)
        elif decoded["mode"] == self.ALU_MODE_ITYPE:
            self.execute_itype(decoded)
        else:
            raise ValueError(f"Invalid mode: {decoded['mode']}")

    def get_register_value(self, reg_num: int) -> int:
        return self.registers[reg_num]

    def set_register_value(self, reg_num: int, value: int) -> None:
        self.registers[reg_num] = value

    def __str__(self) -> str:
        return " | ".join([f"r{i}: {reg}" for i, reg in enumerate(self.registers)])


def test_fibonacci(emulator: BittyEmulator, n: int) -> bool:
    # prepare the emulator

    # assign r1 to 1
    # rx = 1; immediate = 1; alu_sel = 0; res = 01
    init_r1 = 0b0010000000100001  # load immediate 1 into r1
    emulator.evaluate(init_r1)
    assert emulator.get_register_value(1) == 1, \
              f"Expected 1 in r1, got {emulator.get_register_value(1)}"
    print(emulator)

    # assign r2 to 1
    # rx = 2; immediate = 1; alu_sel = 0; res = 01
    init_r2 = 0b0100000000100001  # load immediate 1 into r2
    emulator.evaluate(init_r2)
    assert emulator.get_register_value(2) == 1, \
              f"Expected 1 in r2, got {emulator.get_register_value(2)}"
    print(emulator)

    # instuction sequence to calculate next fibonacci value
    fib_seq = [
        (3 << 13) | (3 << 10) | (0 << 5) | (1 << 2) | (0 << 0),  # sub r3 r3
        (3 << 13) | (2 << 10) | (0 << 5) | (0 << 2) | (0 << 0),  # add r3 r2
        (2 << 13) | (1 << 10) | (0 << 5) | (0 << 2) | (0 << 0),  # add r2 r1
        (1 << 13) | (1 << 10) | (0 << 5) | (1 << 2) | (0 << 0),  # sub r1 r1
        (1 << 13) | (3 << 10) | (0 << 5) | (0 << 2) | (0 << 0),  # add r1 r3
    ]

    # set initial values for golden model
    r1 = 1
    r2 = 1
    r3 = 0
    
    # run the fibonacci sequence for n iterations
    for i in range(n):
        for inst in fib_seq:
            emulator.evaluate(inst)
            print(emulator)

        # gold model
        r3 = r2 & emulator.BIT_MASK
        r2 += r1
        r1 = r3
        
        assert r3 == emulator.get_register_value(3), \
            f"Expected {r3} in r3, got {emulator.get_register_value(3)}"
        
        print()

    return True


if __name__ == "__main__":
    emulator = BittyEmulator()

    # test the Fibonacci sequence
    result = test_fibonacci(emulator, 1000)
    if result:
        print("Fibonacci test passed.")
