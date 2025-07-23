from abc import ABC, abstractmethod
import argparse
import os
import traceback

class Operand(ABC):
    @abstractmethod
    def encode(self) -> int:
        pass


class RegisterOperand(Operand):
    REGISTERS = {f'r{i}': i for i in range(8)}

    def __init__(self, name: str):
        if name not in self.REGISTERS:
            raise ValueError(f"Invalid register: {name}")
        self.name = name
        self.index = self.REGISTERS[name]

    def encode(self) -> int:
        return self.index

    def __str__(self):
        return self.name


class ImmediateOperand(Operand):
    def __init__(self, value: int, bits: int = 8):
        self.value = value & ((1 << bits) - 1)
        self.bits = bits

    def encode(self) -> int:
        return self.value

    def __str__(self):
        return str(self.value)


class Instruction(ABC):
    @abstractmethod
    def encode(self) -> int:
        pass

    @staticmethod
    @abstractmethod
    def decode(word: int):
        pass


class NOPInstruction(Instruction):
    ENCODING = 0x0001

    def encode(self):
        return self.ENCODING

    @staticmethod
    def decode(word: int):
        if word != NOPInstruction.ENCODING:
            raise ValueError("Invalid NOP encoding")
        return NOPInstruction()

    def __str__(self):
        return "nop"


class ALUInstruction(Instruction):
    MNEMONICS = {
        'add': 0b000, 'sub': 0b001, 'and': 0b010, 'or': 0b011,
        'xor': 0b100, 'shl': 0b101, 'shr': 0b110, 'cmp': 0b111,
    }

    def __init__(self, mnemonic: str, rx: RegisterOperand, operand: Operand):
        self.mnemonic = mnemonic
        self.rx = rx
        self.operand = operand

    def encode(self):
        op = self.MNEMONICS[self.mnemonic]
        x = self.rx.encode()
        if isinstance(self.operand, RegisterOperand):
            y = self.operand.encode()
            mode = 0b00
            return (x << 13) | (y << 10) | (op << 2) | mode
        elif isinstance(self.operand, ImmediateOperand):
            imm = self.operand.encode()
            mode = 0b01
            return (x << 13) | (imm << 5) | (op << 2) | mode
        else:
            raise ValueError("Invalid operand type")

    @staticmethod
    def decode(word: int):
        fmt = word & 0b11
        x = (word >> 13) & 0b111
        op = (word >> 2) & 0b111
        mnemonic = next(k for k, v in ALUInstruction.MNEMONICS.items() if v == op)
        rx = RegisterOperand(f"r{x}")
        if fmt == 0b00:
            y = (word >> 10) & 0b111
            return ALUInstruction(mnemonic, rx, RegisterOperand(f"r{y}"))
        elif fmt == 0b01:
            imm = (word >> 5) & 0xFF
            return ALUInstruction(mnemonic, rx, ImmediateOperand(imm))
        else:
            raise ValueError("Invalid ALU instruction format")

    def __str__(self):
        return f"{self.mnemonic} {self.rx}, {self.operand}"


class BranchInstruction(Instruction):
    CONDITIONS = {'bie': 0b00, 'big': 0b01, 'bil': 0b10}

    def __init__(self, mnemonic: str, offset: ImmediateOperand):
        self.mnemonic = mnemonic
        self.offset = offset

    def encode(self):
        imm = self.offset.encode()
        cond = self.CONDITIONS[self.mnemonic]
        return (imm << 4) | (cond << 2) | 0b10

    @staticmethod
    def decode(word: int):
        fmt = word & 0b11
        if fmt != 0b10:
            raise ValueError("Invalid branch format")
        imm = (word >> 4) & 0xFFF
        cond = (word >> 2) & 0b11
        mnemonic = next(k for k, v in BranchInstruction.CONDITIONS.items() if v == cond)
        return BranchInstruction(mnemonic, ImmediateOperand(imm, 12))

    def __str__(self):
        return f"{self.mnemonic} {self.offset}"


class LDSTInstruction(Instruction):
    TYPES = {'ld': 0b0, 'st': 0b1}

    def __init__(self, mnemonic: str, rx: RegisterOperand, ry: RegisterOperand):
        self.mnemonic = mnemonic
        self.rx = rx
        self.ry = ry

    def encode(self):
        x = self.rx.encode()
        y = self.ry.encode()
        typ = self.TYPES[self.mnemonic]
        return (x << 13) | (y << 10) | (typ << 2) | 0b11

    @staticmethod
    def decode(word: int):
        fmt = word & 0b11
        if fmt != 0b11:
            raise ValueError("Invalid LD/ST format")
        x = (word >> 13) & 0b111
        y = (word >> 10) & 0b111
        typ = (word >> 2) & 0b1
        mnemonic = next(k for k, v in LDSTInstruction.TYPES.items() if v == typ)
        return LDSTInstruction(mnemonic, RegisterOperand(f"r{x}"), RegisterOperand(f"r{y}"))

    def __str__(self):
        return f"{self.mnemonic} {self.rx}, {self.ry}"

# Include previously defined classes: Operand, RegisterOperand, ImmediateOperand,
# Instruction, ALUInstruction, BranchInstruction, LDSTInstruction, NOPInstruction

class InstructionFactory:
    @staticmethod
    def decode(word: int) -> Instruction:
        fmt = word & 0b11
        if word == NOPInstruction.ENCODING:
            return NOPInstruction.decode(word)
        elif fmt in (0b00, 0b01):
            return ALUInstruction.decode(word)
        elif fmt == 0b10:
            return BranchInstruction.decode(word)
        elif fmt == 0b11:
            return LDSTInstruction.decode(word)
        else:
            raise ValueError("Unknown instruction format")


class Assembler:
    def __init__(self, input_path: str, output_path: str = None):
        self.input_path = input_path
        self.output_path = output_path
        self.label_to_address = {}
        self.instructions = []

    def assemble(self):
        with open(self.input_path, 'r') as f:
            lines = [line.strip().split(';')[0].strip() for line in f
                if line.strip() and not line.strip().startswith('#')]

        # First pass: identify labels
        address = 0
        for line in lines:
            if line.endswith(":"):
                label = line[:-1]
                self.label_to_address[label] = address
            else:
                self.instructions.append(line)
                address += 1

        # Second pass: encode instructions
        output = []
        for idx, line in enumerate(self.instructions):
            try:
                word = self.assemble_line(line)
                if word is not None:
                    output.append(f"{word:016b}")
            except Exception as e:
                print(f"Error in line {idx}: {line.strip()} -> {e}")
                traceback.print_exception(e)

        if self.output_path:
            with open(self.output_path, 'w') as f:
                f.write("\n".join(output))
        else:
            print("\n".join(output))

    # @staticmethod
    def assemble_line(self, line: str) -> int:
        tokens = line.replace(',', '').split()
        if not tokens or line[0].startswith("#"):
            return None

        mnemonic = tokens[0]

        if mnemonic == "nop":
            return NOPInstruction().encode()

        if mnemonic in ALUInstruction.MNEMONICS:
            rx = RegisterOperand(tokens[1])
            operand = RegisterOperand(tokens[2]) if tokens[2].startswith("r") else ImmediateOperand(int(tokens[2]))
            return ALUInstruction(mnemonic, rx, operand).encode()

        if mnemonic in BranchInstruction.CONDITIONS:
            target = tokens[1]
            imm = None
            if target.isdigit():
                imm = int(target)
            elif target in self.label_to_address:
                imm = self.label_to_address[target]
            else:
                raise ValueError(f"Unknown label or invalid branch target: {target}")
            return BranchInstruction(mnemonic, ImmediateOperand(imm, bits=12)).encode()

        if mnemonic in LDSTInstruction.TYPES:
            rx = RegisterOperand(tokens[1])
            ry = RegisterOperand(tokens[2])
            return LDSTInstruction(mnemonic, rx, ry).encode()

        raise ValueError(f"Unknown mnemonic: {mnemonic}")


class Disassembler:
    def __init__(self, input_path: str, output_path: str = None):
        self.input_path = input_path
        self.output_path = output_path

    def disassemble(self):
        with open(self.input_path, 'r') as f:
            lines = f.readlines()

        output = []
        for line in lines:
            try:
                word = int(line.strip(), 2)
                asm = Disassembler.disassemble_word(word)
                output.append(asm)
            except Exception as e:
                print(f"Error in line: {line.strip()} -> {e}")
                traceback.print_exception(e)

        if self.output_path:
            with open(self.output_path, 'w') as f:
                f.write("\n".join(output))
        else:
            print("\n".join(output))

    @staticmethod
    def disassemble_word(word: int) -> str:
        instr = InstructionFactory.decode(word)
        return str(instr)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", required=True, help="Input file")
    parser.add_argument("-o", help="Output file")
    parser.add_argument("-a", action='store_true', help="Assemble")
    parser.add_argument("-d", action='store_true', help="Disassemble")
    args = parser.parse_args()

    if not os.path.exists(args.i):
        print("Error: Input file does not exist.")
        return

    if args.a:
        Assembler(args.i, args.o).assemble()
    elif args.d:
        Disassembler(args.i, args.o).disassemble()
    else:
        print("Error: Must specify -a or -d")

if __name__ == "__main__":
    main()
