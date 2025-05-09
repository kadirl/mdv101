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
    generator = BittyInstructionGenerator()
    for _ in range(10):
        print(f"{generator.generate():016b}")