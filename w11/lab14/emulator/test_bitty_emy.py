import pytest
from bitty_emu import BittyEmulator, fibonacci
# Assuming the BittyEmulator class definition is available either 
# in the same file or imported e.g., from bitty_emu import BittyEmulator

# --- Test Fixture ---
@pytest.fixture
def emulator():
    """Provides a fresh BittyEmulator instance for each test."""
    return BittyEmulator()

# --- Initialization Tests ---
def test_initialization(emulator):
    """Verify emulator starts with 8 zeroed registers."""
    assert len(emulator.registers) == 8, "Emulator should have 8 registers"
    assert all(reg == 0 for reg in emulator.registers), "All registers should be initialized to 0"
    assert emulator.BIT_COUNT == 16
    assert emulator.BIT_MASK == 0xFFFF

# --- Register Access Tests ---
def test_register_set_get(emulator):
    """Test setting and getting values from registers."""
    emulator.set_register_value(0, 123)
    assert emulator.get_register_value(0) == 123

    emulator.set_register_value(7, 65535) # Max 16-bit unsigned
    assert emulator.get_register_value(7) == 65535

    emulator.set_register_value(3, 500)
    emulator.set_register_value(4, emulator.get_register_value(3)) # Read from one, write to another
    assert emulator.get_register_value(4) == 500

# --- Decoding Tests ---
def test_decode_rtype(emulator):
    """Verify decoding of a sample R-Type instruction."""
    # Example: SUB R1, R2 (rx=1, ry=2, alu_select=1 (sub), mode=0)
    # Binary: 001 010 00000 001 00 
    instruction = 0b001_010_00000_001_00
    decoded = emulator.decode(instruction)
    assert decoded["rx"] == 1
    assert decoded["ry"] == 2
    assert decoded["alu_select"] == 1  # sub
    assert decoded["mode"] == BittyEmulator.ALU_MODE_RTYPE
    # Immediate value might be decoded but isn't used for R-Type execution
    assert decoded["immediate"] == 64  # Based on bits 12-5 being 01000000

def test_decode_itype(emulator):
    """Verify decoding of a sample I-Type instruction."""
    # Example: ADD R3, 42 (rx=3, immediate=42, alu_select=0 (add), mode=1)
    # Immediate 42 = 0b00101010
    # Binary: 011 001 01010 000 01
    instruction = 0b011_00101010_000_01
    decoded = emulator.decode(instruction)
    assert decoded["rx"] == 3
    assert decoded["immediate"] == 42
    assert decoded["alu_select"] == 0 # add
    assert decoded["mode"] == BittyEmulator.ALU_MODE_ITYPE
    # ry value might be decoded but isn't used for I-Type execution
    assert decoded["ry"] == 1 # Based on bits 10-8 being 001

# --- ALU Function Tests (Direct) ---
# It's good practice to test the core logic units directly

@pytest.mark.parametrize("x, y, expected", [
    (0, 0, 0),
    (10, 20, 30),
    (0xFFFF, 1, 0),      # Unsigned overflow
    (0xFFFF, 10, 9),     # Unsigned overflow
    (1, 0xFFFF, 0),
])
def test_alu_add(x, y, expected):
    op = BittyEmulator.alu_functions[0b000] # add opcode
    assert op(x, y) == expected

@pytest.mark.parametrize("x, y, expected", [
    (0, 0, 0),
    (20, 10, 10),
    (10, 20, 0xFFF6),  # Unsigned underflow (10 - 20 = -10 = 65526)
    (0, 1, 0xFFFF),   # Unsigned underflow (0 - 1 = -1 = 65535)
    (0, 0xFFFF, 1),   # 0 - (-1) = 1
])
def test_alu_sub(x, y, expected):
    op = BittyEmulator.alu_functions[0b001] # sub opcode
    assert op(x, y) == expected

@pytest.mark.parametrize("x, y, expected", [
    (0, 0, 0),
    (0xFFFF, 0xAAAA, 0xAAAA),
    (0xF0F0, 0x0F0F, 0x0000),
    (0x1234, 0xFFFF, 0x1234),
    (0x1234, 0x0000, 0x0000),
])
def test_alu_and(x, y, expected):
    op = BittyEmulator.alu_functions[0b010] # and opcode
    assert op(x, y) == expected

@pytest.mark.parametrize("x, y, expected", [
    (0, 0, 0),
    (0xFFFF, 0xAAAA, 0xFFFF),
    (0xF0F0, 0x0F0F, 0xFFFF),
    (0x1234, 0xABCD, 0x1234 | 0xABCD),
    (0x1234, 0x0000, 0x1234),
])
def test_alu_or(x, y, expected):
    op = BittyEmulator.alu_functions[0b011] # or opcode
    assert op(x, y) == expected

@pytest.mark.parametrize("x, y, expected", [
    (0, 0, 0),
    (0xFFFF, 0xAAAA, 0x5555),
    (0xF0F0, 0x0F0F, 0xFFFF),
    (0x1234, 0xABCD, 0x1234 ^ 0xABCD),
    (0x1234, 0x1234, 0x0000),
])
def test_alu_xor(x, y, expected):
    op = BittyEmulator.alu_functions[0b100] # xor opcode
    assert op(x, y) == expected

# NOTE: Testing the SHIFT operations AS WRITTEN in the code (with y ^ BIT_COUNT)
# If the intent was standard shifts, these tests would fail and the lambdas need fixing.
@pytest.mark.parametrize("x, y, expected_shift_amount, expected_result", [
    # y=0 -> shift 0^16=16
    (0x0001, 0, 16, 0),
    (0xFFFF, 0, 16, 0),
    # y=1 -> shift 1^16=17
    (0x0001, 1, 17, 0),
    (0x0001, 17, 17^16, 0x0002), # shift amount 17 -> y=17^16=1
    # y=15 -> shift 15^16=31
    (0x0001, 15, 31, 0),
])
def test_alu_shl_as_written(x, y, expected_shift_amount, expected_result):
    """Tests the SHL operation with the current y^BIT_COUNT logic."""
    op = BittyEmulator.alu_functions[0b101] # shl opcode
    # For documentation/debugging: verify shift amount calculation
    assert (y ^ BittyEmulator.BIT_COUNT) == expected_shift_amount
    assert op(x, y) == expected_result

@pytest.mark.parametrize("x, y, expected_shift_amount, expected_result", [
    # y=0 -> shift 0^16=16
    (0xFFFF, 0, 16, 0),
    (0x8000, 0, 16, 0),
    # y=1 -> shift 1^16=17
    (0xFFFF, 1, 17, 0),
    (0x0002, 17, 17^16, 0x0001), # shift amount 17 -> y=17^16=1
    # y=15 -> shift 15^16=31
    (0xFFFF, 15, 31, 0),
])
def test_alu_shr_as_written(x, y, expected_shift_amount, expected_result):
    """Tests the SHR operation with the current y^BIT_COUNT logic."""
    op = BittyEmulator.alu_functions[0b110] # shr opcode
    # For documentation/debugging: verify shift amount calculation
    assert (y ^ BittyEmulator.BIT_COUNT) == expected_shift_amount
    assert op(x, y) == expected_result

@pytest.mark.parametrize("x, y, expected", [
    (5, 5, 0),          # Equal
    (6, 5, 1),          # x > y
    (5, 6, 2),          # x < y
    (0, 0, 0),
    (0xFFFF, 0xFFFF, 0),
    (0xFFFF, 0, 1),
    (0, 0xFFFF, 2),
])
def test_alu_cmp(x, y, expected):
    op = BittyEmulator.alu_functions[0b111] # cmp opcode
    assert op(x, y) == expected

# --- Execution Tests (Integration) ---

def test_execute_rtype_add(emulator):
    """Test R-Type ADD execution."""
    emulator.set_register_value(1, 100)
    emulator.set_register_value(2, 50)
    # ADD R1, R2: rx=1, ry=2, alu=0, mode=0
    instruction = 0b001_010_00000_000_00 # 0x2800
    emulator.evaluate(instruction)
    assert emulator.get_register_value(1) == 150
    assert emulator.get_register_value(2) == 50 # R2 should be unchanged

def test_execute_rtype_sub_self(emulator):
    """Test R-Type SUB R, R to zero a register."""
    emulator.set_register_value(3, 12345)
    # SUB R3, R3: rx=3, ry=3, alu=1, mode=0
    instruction = 0b011_011_00000_001_00 # 0x6C04
    emulator.evaluate(instruction)
    assert emulator.get_register_value(3) == 0

def test_execute_itype_add(emulator):
    """Test I-Type ADD execution."""
    emulator.set_register_value(5, 1000)
    # ADD R5, 234: rx=5, imm=234 (0xEA = 0b11101010), alu=0, mode=1
    instruction = 0b101_11101010_000_01 
    emulator.evaluate(instruction)
    assert emulator.get_register_value(5) == 1234

def test_execute_itype_sub(emulator):
    """Test I-Type SUB execution."""
    emulator.set_register_value(6, 100)
    # SUB R6, 30: rx=6, imm=30 (0x1E = 0b00011110), alu=1, mode=1
    instruction = 0b110_00011110_001_01 
    emulator.evaluate(instruction)
    assert emulator.get_register_value(6) == 70

def test_execute_itype_sub_underflow(emulator):
    """Test I-Type SUB execution causing underflow."""
    emulator.set_register_value(7, 10)
    # SUB R7, 42: rx=7, imm=42, alu=1, mode=1
    instruction = 0b111_00101010_001_01 # 0xE2A5
    emulator.evaluate(instruction)
    assert emulator.get_register_value(7) == 65504

# --- Error Handling Tests ---

def test_evaluate_invalid_mode(emulator):
    """Test that evaluate raises ValueError for invalid mode."""
    # Instruction with valid fields but mode = 2 (0b10)
    instruction = 0b001_010_00000_000_10 # RType ADD fields, mode=2
    with pytest.raises(ValueError, match="Invalid mode: 2"):
        emulator.evaluate(instruction)

    # Instruction with valid fields but mode = 3 (0b11)
    instruction = 0b001_010_00000_000_11 # RType ADD fields, mode=3
    with pytest.raises(ValueError, match="Invalid mode: 3"):
        emulator.evaluate(instruction)

# --- Fibonacci Test (as Integration Test) ---
# Keep the original Fibonacci test as a higher-level integration test
def test_fibonacci_integration(emulator):
    """Run the original Fibonacci sequence test."""
    # Optionally adjust n for speed if running frequently
    assert fibonacci(emulator, 20) == True