import pytest
import traceback
from emulator.bitty_emu import BittyEmulator
from assembler_tool import Assembler, Disassembler


DIRECTORY_PATH_PREFIX = "tests/bitty_emu/"


# Tests for st instruction:
# Must write asm to upload a memory on every even address
# Then check emulators internal memory to see if everything is in place
def test_store_inst():
    return
    TEST_FILE_ASM = DIRECTORY_PATH_PREFIX + "test_store.asm"
    TEST_FILE_BIN = DIRECTORY_PATH_PREFIX + "test_store.bin"
    # 0: assemble .asm to .bin
    assembler = Assembler(
        TEST_FILE_ASM,
        TEST_FILE_BIN
    )
    assembler.assemble()

    # 1: init emulator & upload instructions
    emulator = BittyEmulator(instruction_path=TEST_FILE_BIN)

    # 2: execute instrutcions
    inst_counter = 0
    while True:
        try:
            emulator.step()
            inst_counter += 1
            # pytest.
            print(f"Executed instruction #{inst_counter} with PC={emulator.pc - 1}: {Disassembler.disassemble_word(emulator.instructions[emulator.pc - 1])}")
            print(f"Emulator state: {emulator}")
        except StopIteration:
            print("No more instructions to execute")
            break
        except Exception as e:
            print(f"An unexpected error: {e}")
            traceback.print_exc(e)
    else:
        pytest.fail("Emulator ran too long without halting — possible infinite loop.")

    # 3: check memory
    memory = emulator.memory
    for i, val in enumerate(memory[:201]):
        print(i, val)
        if i % 2 == 0:
            assert val == i // 2 , \
                f"Expected {i // 2} on address {i} but got {val}"
        else:
            assert val == 0, \
                f"Expected 0 on address {i} but got {val}"

    # 4: done
    print("Tested st instructions successfully.")

# Tests for ld instruction:
# Must preload memory with a numbers on certain points in memory
# Then, must compare to ensure everything is in place
def test_load_inst():
    # 0: assemble .asm to .bin
    TEST_FILE_ASM = DIRECTORY_PATH_PREFIX + "test_load.asm"
    TEST_FILE_BIN = DIRECTORY_PATH_PREFIX + "test_load.bin"
    assembler = Assembler(
        TEST_FILE_ASM,
        TEST_FILE_BIN
    )
    assembler.assemble()

    # 1: init emulator & upload instructions
    emulator = BittyEmulator(instruction_path=TEST_FILE_BIN)

    # 2: upload memory with numbers from 0 to 100 on even addresses
    memory_pointers = [0, 10, 35, 40, 60, 90, 125, 130]
    for i in memory_pointers:
        emulator.memory[i] = i

    # 3: execute asm script
    while True:
        try:
            emulator.step()
        except StopIteration:
            print("No more instructions to execute")
            break
        except Exception as e:
            print(f"An unexpected error: {e}")
            traceback.print_exc(e)

    # 4: compare values
    for i, val in enumerate(memory_pointers):
        i = (i + 1) % 8
        assert val == emulator.get_reg(i), \
            f"Expected {val} in reg_{i}, got {emulator.get_reg(i)}"

# Test for ld & sd instructions:
# Manually setup memory with st and then read with ld
