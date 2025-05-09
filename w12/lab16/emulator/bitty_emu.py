import argparse


class BittyEmulator:
    BIT_COUNT = 16
    BIT_MASK = (1 << BIT_COUNT) - 1

    alu_functions = {
        0b000: lambda x, y: (x + y) & BittyEmulator.BIT_MASK,
        0b001: lambda x, y: (x - y) & BittyEmulator.BIT_MASK,
        0b010: lambda x, y: x & y,
        0b011: lambda x, y: x | y,
        0b100: lambda x, y: x ^ y,
        0b101: lambda x, y: (x << (y % BittyEmulator.BIT_COUNT)) & BittyEmulator.BIT_MASK,
        0b110: lambda x, y: (x >> (y % BittyEmulator.BIT_COUNT)) & BittyEmulator.BIT_MASK,
        0b111: lambda x, y: ((x < y) << 1) | (x > y)
    }

    ALU_MODE_RTYPE = 0b00
    ALU_MODE_ITYPE = 0b01

    def __init__(self, instructions: list[int] = None, file_path: str = None) -> None:
        self.registers = [0 for _ in range(8)]
        if instructions is not None:
            self.instructions = instructions
        elif file_path is not None:
            self.instructions = self._load_instructions(file_path)
        else:
            pass
            # raise ValueError("Must provide either 'instructions' or 'file_path'.")
        self.instruction_pointer = 0

    def _load_instructions(self, file_path: str) -> list[int]:
        with open(file_path, "r") as f:
            lines = f.readlines()
        return [int(line.strip(), 16) for line in lines if line.strip()]

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

    def evaluate(self) -> None:
        if self.instruction_pointer >= len(self.instructions):
            raise StopIteration("No more instructions to execute.")
        instruction = self.instructions[self.instruction_pointer]
        decoded = self.decode(instruction)

        if decoded["mode"] == self.ALU_MODE_RTYPE:
            self.execute_rtype(decoded)
        elif decoded["mode"] == self.ALU_MODE_ITYPE:
            self.execute_itype(decoded)
        else:
            raise ValueError(f"Invalid mode: {decoded['mode']}")
        

        self.instruction_pointer += 1

    def append_instruction(self, instruction: int) -> None:
        self.instructions.append(instruction)

    def get_register_value(self, reg_num: int) -> int:
        return self.registers[reg_num]

    def set_register_value(self, reg_num: int, value: int) -> None:
        self.registers[reg_num] = value

    def __str__(self) -> str:
        return " | ".join([f"r{i}: {reg}" for i, reg in enumerate(self.registers)])
    

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("instructions_file", nargs="?")
    args = parser.parse_args()

    if not args.instructions_file:
        raise ValueError(f"No instructions file provided.")
    
    emulator = BittyEmulator(file_path=args.instructions_file)
    print(f"Loaded instructions from {args.instructions_file}:")
    for instruction in emulator.instructions:
        print(f"Instruction: {instruction:016b}")
    print(f"Emulator state before execution:\n{emulator}")
    print("Starting execution...")
    while True:
        try:
            emulator.evaluate()
            print(f"Emulator state after execution:\n{emulator}")
        except StopIteration:
            print("No more instructions to execute.")
            break
