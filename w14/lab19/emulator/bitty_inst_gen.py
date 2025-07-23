import argparse
import random


class BittyInstructionGenerator:
    def generate(self, number=1<<8):
        instruction = 0

        # R-type parameters
        rx = random.randint(0, 7)
        ry = random.randint(0, 7)

        # I-type parameters
        i_type_immediate = random.randint(0, 255)

        # R and I-type common parameters
        alu_select = random.randint(0, 7)

        # J-type parameters
        j_type_immediate = random.randint(0, min(1 << 8 - 1, number))
        cond = random.randint(0, 2)

        # Load & Store parameters
        ls = random.randint(0, 1)

        # Common parameter
        mode = random.randint(0, 3)

        if mode == 0:
            # R-type instruction
            instruction = (rx << 13) | (ry << 10) | (0 << 5) | (alu_select << 2) | mode
        elif mode == 1:
            # I-type instruction
            instruction = (rx << 13) | (i_type_immediate << 5) | (alu_select << 2) | mode
        elif mode == 2:
            # J-type instruction
            instruction = (j_type_immediate << 4) | (cond << 2) | mode
        elif mode == 3:
            # Load & store instruction
            instruction = (rx << 13) | (ry << 10) | (ls << 2) | mode

        return instruction


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Process HEX file and instruction count.")
    parser.add_argument('-f', '--file', required=True, help='Path to .hex file')
    parser.add_argument('-n', '--number', type=int, required=True, help='Number of instructions')

    args = parser.parse_args()

    with open(args.file, 'w') as f:
        for _ in range(args.number):
            instruction_gen = BittyInstructionGenerator()
            instruction = instruction_gen.generate(args.number)
            f.write(f"{instruction:016b}\n")
