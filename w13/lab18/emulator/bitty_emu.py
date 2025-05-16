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

    MODE_ALU_RTYPE = 0b00
    MODE_ALU_ITYPE = 0b01
    MODE_JTYPE = 0b10

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
        self.last_alu_result = 0

    def _load_instructions(self, file_path: str) -> list[int]:
        with open(file_path, "r") as f:
            lines = f.readlines()
        return [int(line.strip(), 16) for line in lines if line.strip()]

    def decode(self, instruction: int) -> dict[str, int]:
        return {
            "rx": (instruction >> 13) & 0b111,
            "ry": (instruction >> 10) & 0b111,
            "reserved": (instruction >> 5) & 0b11111,
            "alu_select": (instruction >> 2) & 0b111,
            "mode": instruction & 0b11,
            "i_type_immediate": (instruction >> 5) & 0xFF,
            "j_type_immediate": (instruction >> 4) & 0b111111111111,
            "j_type_cond": (instruction >> 2) & 0b11,
        }

    def execute_rtype(self, decoded: dict[str, int]) -> None:
        rx = self.get_register_value(decoded["rx"])
        ry = self.get_register_value(decoded["ry"])
        op = self.alu_functions[decoded["alu_select"]]
        val = op(rx, ry)
        self.set_register_value(decoded["rx"], val)
        self.last_alu_result = val
        self.instruction_pointer += 1

    def execute_itype(self, decoded: dict[str, int]) -> None:
        rx = self.get_register_value(decoded["rx"])
        immediate = decoded["i_type_immediate"]
        op = self.alu_functions[decoded["alu_select"]]
        val = op(rx, immediate)
        self.set_register_value(decoded["rx"], val)
        self.last_alu_result = val
        self.instruction_pointer += 1

    def execute_jtype(self, decoded: dict[str, int]) -> None:
        immediate = decoded["j_type_immediate"]
        cond = decoded["j_type_cond"]
        last_alu_result = self.last_alu_result

        # if cond == 0b00 and last_alu_result == 0:
        #     self.instruction_pointer = immediate
        # elif cond == 0b01 and last_alu_result == 1:
        #     self.instruction_pointer = immediate
        # elif cond == 0b10 and last_alu_result == 2:
        #     self.instruction_pointer = immediate
        # else:
        #     self.instruction_pointer += 1

        if cond == last_alu_result:
            self.instruction_pointer = immediate
            print("Jumped to", immediate)
        else:
            self.instruction_pointer += 1

    def evaluate(self) -> None:
        if self.instruction_pointer >= len(self.instructions):
            raise StopIteration("No more instructions to execute.")
        instruction = self.instructions[self.instruction_pointer]
        decoded = self.decode(instruction)

        if decoded["mode"] == self.MODE_ALU_RTYPE:
            self.execute_rtype(decoded)
        elif decoded["mode"] == self.MODE_ALU_ITYPE:
            self.execute_itype(decoded)
        elif decoded["mode"] == self.MODE_JTYPE:
            self.execute_jtype(decoded)
        else:
            raise ValueError(f"Invalid mode: {decoded['mode']}")

        return self.instruction_pointer

    def get_register_value(self, reg_num: int) -> int:
        return self.registers[reg_num]

    def set_register_value(self, reg_num: int, value: int) -> None:
        self.registers[reg_num] = value

    def get_pc(self):
        return self.instruction_pointer

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
