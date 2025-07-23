from enum import Enum

BIT_COUNT = 16
BIT_MASK = (1 << BIT_COUNT) - 1
PC_BIT = 8
REGISTER_COUNT = 8


class Mode(Enum):
    R_TYPE = 0b00
    I_TYPE = 0b01
    J_TYPE = 0b10
    LD_ST = 0b11


class ALU:
    def compute(self, op: int, x: int, y: int) -> int:
        match op:
            case 0b000: return (x + y) & BIT_MASK
            case 0b001: return (x - y) & BIT_MASK
            case 0b010: return x & y
            case 0b011: return x | y
            case 0b100: return x ^ y
            case 0b101: return (x << (y % BIT_COUNT)) & BIT_MASK
            case 0b110: return (x >> (y % BIT_COUNT)) & BIT_MASK
            case 0b111: return ((x < y) << 1) | (x > y)
            case _: raise ValueError(f"Unknown ALU op: {op}")


class Memory:
    def __init__(self, size=1 << BIT_COUNT):
        self.data = [0] * size

    def load_from_file(self, path):
        with open(path) as f:
            for i, line in enumerate(f):
                if i >= len(self.data): break
                line = line.strip()
                if line: self.data[i] = int(line, 2)

    def __getitem__(self, addr):
        return self.data[addr]

    def __setitem__(self, addr, value):
        self.data[addr] = value


class Instruction:
    def __init__(self, raw: int):
        self.raw = raw

    def decode_fields(self):
        return {
            "rx": (self.raw >> 13) & 0b111,
            "ry": (self.raw >> 10) & 0b111,
            "alu_select": (self.raw >> 2) & 0b111,
            "mode": Mode(self.raw & 0b11),
            "i_imm": (self.raw >> 5) & 0xFF,
            "j_imm": (self.raw >> 4) & 0xFF,
            "j_cond": (self.raw >> 2) & 0b11,
            "ls": (self.raw >> 2) & 0b1
        }

    def execute(self, emulator):
        raise NotImplementedError()


class RTypeInstruction(Instruction):
    def execute(self, emulator):
        f = self.decode_fields()
        val = emulator.alu.compute(f["alu_select"], emulator.get_reg(f["rx"]), emulator.get_reg(f["ry"]))
        emulator.set_reg(f["rx"], val)
        emulator.last_result = val
        emulator.pc += 1


class ITypeInstruction(Instruction):
    def execute(self, emulator):
        f = self.decode_fields()
        val = emulator.alu.compute(f["alu_select"], emulator.get_reg(f["rx"]), f["i_imm"])
        emulator.set_reg(f["rx"], val)
        emulator.last_result = val
        emulator.pc += 1


class JTypeInstruction(Instruction):
    def execute(self, emulator):
        f = self.decode_fields()
        if f["j_cond"] == emulator.last_result:
            emulator.pc = f["j_imm"]
        else:
            emulator.pc += 1


class LDSTInstruction(Instruction):
    def execute(self, emulator):
        f = self.decode_fields()
        if f["ls"] == 0:
            emulator.set_reg(f["rx"], emulator.memory[emulator.get_reg(f["ry"] & 0b11111111)])
        else:
            emulator.memory[emulator.get_reg(f["ry"]) & 0b11111111] = emulator.get_reg(f["rx"])
        emulator.pc += 1


class BittyEmulator:
    def __init__(self, instruction_path):
        self.memory = Memory()
        self.alu = ALU()
        self.registers = [0] * REGISTER_COUNT
        self.instructions = []
        self.pc = 0
        self.last_result = 0
        self._load_instructions(instruction_path)

    def _load_instructions(self, path):
        inst_limit = 1 << PC_BIT
        with open(path) as f:
            lines = f.readlines()
            if len(lines) > inst_limit:
                print(f"Instruction file contains more than {inst_limit} instruction. Using only first {inst_limit}")
            for line in lines[:inst_limit]:
                line = line.strip()
                if line: self.instructions.append(int(line, 2))

    def step(self):
        if self.pc >= len(self.instructions):
            raise StopIteration("No more instructions")
        raw = self.instructions[self.pc]
        instr = self._decode(raw)
        instr.execute(self)

    def _decode(self, raw):
        mode = Mode(raw & 0b11)
        if mode == Mode.R_TYPE: return RTypeInstruction(raw)
        if mode == Mode.I_TYPE: return ITypeInstruction(raw)
        if mode == Mode.J_TYPE: return JTypeInstruction(raw)
        if mode == Mode.LD_ST: return LDSTInstruction(raw)
        raise ValueError(f"Unknown mode: {mode}")

    def get_reg(self, idx):
        return self.registers[idx]

    def set_reg(self, idx, value):
        self.registers[idx] = value

    def get_pc(self):
        return self.pc

    def __str__(self):
        return " | ".join(f"r{i}: {val}" for i, val in enumerate(self.registers))
