import argparse
import random


class BittyInstructionGenerator:
    def generate(self):
        instruction = 0

        rx = random.randint(0, 7)
        ry = random.randint(0, 7)
        immediate = random.randint(0, 255)
        alu_select = random.randint(0, 7)
        mode = random.randint(0, 1)
        # mode = 0

        if mode == 0:
            # R-type instruction
            instruction = (rx << 13) | (ry << 10) | (0 << 5) | (alu_select << 2) | mode
        elif mode == 1:
            # I-type instruction
            instruction = (rx << 13) | (immediate << 5) | (alu_select << 2) | mode

        return instruction
    

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Process HEX file and instruction count.")
    parser.add_argument('-f', '--file', required=True, help='Path to .hex file')
    parser.add_argument('-n', '--number', type=int, required=True, help='Number of instructions')
    
    args = parser.parse_args()
    
    with open(args.file, 'w') as f:
        for _ in range(args.number):
            instruction_gen = BittyInstructionGenerator()
            instruction = instruction_gen.generate()
            f.write(f"{instruction:04x}\n")