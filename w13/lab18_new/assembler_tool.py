import argparse
import os


class BittyISA:
    MNEMONICS = {
        'add': 0b000, 'sub': 0b001, 'and': 0b010, 'or': 0b011,
        'xor': 0b100, 'shl': 0b101, 'shr': 0b110, 'cmp': 0b111,
    }
    REGISTERS = {f'r{i}': i for i in range(8)}
    BRANCHES = {'bie': 0b00, 'big': 0b01, 'bil': 0b10}
    NOP_ENCODING = 0x0001  # 0b0000_0000_0000_0001

    @classmethod
    def encode(cls, mnemonic: str, rx: str = None, operand: str = None) -> int:
        mnem = mnemonic.lower()
        if mnem == 'nop':
            return cls.NOP_ENCODING
        if mnem in cls.MNEMONICS:
            alu = cls.MNEMONICS[mnem]
            x = cls.REGISTERS[rx]
            if operand in cls.REGISTERS:
                y = cls.REGISTERS[operand]
                mode = 0b00
                return (x << 13) | (y << 10) | (alu << 2) | mode
            else:
                imm = int(operand) & 0xFF
                mode = 0b01
                return (x << 13) | (imm << 5) | (alu << 2) | mode
        elif mnem in cls.BRANCHES:
            imm = int(rx) & 0xFFF
            cond = cls.BRANCHES[mnem]
            fmt = 0b10
            return (imm << 4) | (cond << 2) | fmt
        else:
            raise ValueError(f"Unknown instruction: {mnemonic}")

    @classmethod
    def decode(cls, instr: int) -> str:
        fmt = instr & 0b11
        if fmt == 0b10:
            imm = (instr >> 4) & 0xFFF
            cond = (instr >> 2) & 0b11
            for k, v in cls.BRANCHES.items():
                if v == cond:
                    return f"{k} {imm}"
            raise ValueError(f"Unknown branch condition: {cond}")
        else:
            rx = (instr >> 13) & 0b111
            ry = (instr >> 10) & 0b111
            imm = (instr >> 5) & 0xFF
            alu = (instr >> 2) & 0b111
            mnem = next(k for k, v in cls.MNEMONICS.items() if v == alu)
            return f"{mnem} r{rx}, r{ry}" if fmt == 0 else f"{mnem} r{rx}, {imm}"



class Assembler:
    def __init__(self, input_path: str, output_path: str = None):
        self.input = input_path
        self.output = output_path

    def assemble(self):
        # Read lines from the input file
        lines = self._read_lines()
        # Initialize an empty list to store the generated machine code
        machine_code = []
        # Iterate through each line in the input
        for line in lines:
            # Skip empty lines or comment lines
            if not line or line.startswith('#'):
                continue

            # Remove comments from the line
            line = line.split('#')[0].strip()

            # Skip empty lines after comment removal
            if not line:
                continue

            # Split the line into instruction and operands
            parts = line.strip().split()
            # Extract the instruction and convert it to lowercase
            instr = parts[0].lower()
            # Extract the operands, remove any spaces, and split them into a list
            operands = ''.join(parts[1:]).split(',')
            # For BIE 100 → operands = ['100']
            # If there is only one operand
            if len(operands) == 1:
                # Encode the instruction with one operand
                word = BittyISA.encode(instr, operands[0])
            # If there are two operands
            else:
                # Encode the instruction with two operands
                word = BittyISA.encode(instr, operands[0], operands[1])
            # Append the machine code instruction (formatted as a 4-digit hexadecimal string) to the list
            machine_code.append(f"{word:04x}")
        # Write the machine code to the output file or print it to the console
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
