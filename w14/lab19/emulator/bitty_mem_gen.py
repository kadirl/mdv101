import argparse
import random


class BittyMemoryGenerator:
    def generate(self, number=1 << 16):
        """Generates a single memory cell value"""
        return random.randint(0, 1 << 16)

    def generate_memory(self, number):
        """Loads all memory with random data"""
        return [self.generate() for _ in range(number)]


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Process file and instruction count.")
    parser.add_argument('-f', '--file', required=True, help='Path to .hex file')
    parser.add_argument('-n', '--number', type=int, required=True, help='Number of instructions')

    args = parser.parse_args()

    with open(args.file, 'w') as f:
        for _ in range(args.number):
            instruction_gen = BittyMemoryGenerator()
            instruction = instruction_gen.generate(args.number)
            f.write(f"{instruction:04x}\n")
