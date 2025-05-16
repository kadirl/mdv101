import argparse
import os


class BittyISA:
    MNEMONICS = {
        'add': 0b000, 'sub': 0b001, 'and': 0b010, 'or': 0b011,
        'xor': 0b100, 'shl': 0b101, 'shr': 0b110, 'slt': 0b111
    }
    REGISTERS = {f'r{i}': i for i in range(8)}

    @classmethod
    def encode(cls, mnemonic: str, rx: str, operand: str) -> int:
        alu = cls.MNEMONICS[mnemonic]
        x = cls.REGISTERS[rx]
        if operand in cls.REGISTERS:
            y = cls.REGISTERS[operand]
            mode = 0b00
            return (x << 13) | (y << 10) | (alu << 2) | mode
        else:
            imm = int(operand) & 0xFF
            mode = 0b01
            return (x << 13) | (imm << 5) | (alu << 2) | mode

    @classmethod
    def decode(cls, instr: int) -> str:
        rx = (instr >> 13) & 0b111
        ry = (instr >> 10) & 0b111
        imm = (instr >> 5) & 0xFF
        alu = (instr >> 2) & 0b111
        mode = instr & 0b11
        mnem = next(k for k, v in cls.MNEMONICS.items() if v == alu)
        return f"{mnem} r{rx}, r{ry}" if mode == 0 else f"{mnem} r{rx}, {imm}"


class Assembler:
    def __init__(self, input_path: str, output_path: str = None):
        self.input = input_path
        self.output = output_path

    def assemble(self):
        lines = self._read_lines()
        machine_code = []
        for line in lines:
            if not line: continue
            parts = line.strip().split()
            instr, operands = parts[0].lower(), ''.join(parts[1:]).split(',')
            word = BittyISA.encode(instr, operands[0], operands[1])
            machine_code.append(f"{word:04x}")
        self._write_or_print(machine_code)

    def _read_lines(self):
        with open(self.input) as f:
            return [line.strip() for line in f if line.strip()]

    def _write_or_print(self, lines):
        if self.output:
            with open(self.output, 'w') as f: f.write('\n'.join(lines))
        else:
            print('\n'.join(lines))


class Disassembler:
    def __init__(self, input_path: str, output_path: str = None):
        self.input = input_path
        self.output = output_path

    def disassemble(self):
        with open(self.input) as f:
            instructions = [int(line.strip(), 16) for line in f if line.strip()]
        asm_lines = [BittyISA.decode(instr) for instr in instructions]
        if self.output:
            with open(self.output, 'w') as f: f.write('\n'.join(asm_lines))
        else:
            print('\n'.join(asm_lines))


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
