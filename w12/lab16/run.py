import argparse
import glob
import os
import sys
from pathlib import Path
from cocotb.runner import get_runner
import shutil

TEST_MODULE_FORMAT = "tests.%s.test_%s"  # Adjust if your structure differs


def get_rtl_modules(rtl_dir):
    rtl_dir_path = Path(rtl_dir)
    verilog_files = list(rtl_dir_path.glob("*.v"))
    modules = [f.stem for f in verilog_files]
    sources = [f.resolve() for f in verilog_files]
    return modules, sources


def has_testbench(mod_name, test_module_format):
    if test_module_format.count("%s") == 2:
        module_path = test_module_format % (mod_name, mod_name)
    elif test_module_format.count("%s") == 1:
        module_path = test_module_format % mod_name
    else:
        return False
    path = Path(*module_path.split("."))  # e.g., tests/my_module/test_my_module
    return (path.with_suffix(".py")).exists()


def run_with_runner(mod_name, sources, test_module, sim, memory_file):
    runner = get_runner(sim)
    runner.build(sources=sources, hdl_toplevel=mod_name, timescale=("1ns", "1ps"))
    
    extra_env = {}
    if memory_file is not None:
        extra_env["MEMORY_FILE"] = str(memory_file)

    runner.test(
        hdl_toplevel=mod_name, 
        test_module=test_module, 
        waves=True, 
        timescale=("1ns", "1ps"),
        extra_env=extra_env
    )


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("module_name", nargs="?", default="all")
    parser.add_argument("--test_module_format", default=TEST_MODULE_FORMAT)
    parser.add_argument("--rtl_dir", default="rtl")
    parser.add_argument("-mf", "--memory_file", default=None)
    args = parser.parse_args()

    sim = os.getenv("SIM", "icarus")
    all_modules, sources = get_rtl_modules(args.rtl_dir)
    
    memory_file = args.memory_file
    if args.memory_file is not None:
        memory_file = Path(memory_file).resolve()

    if memory_file is not None and not memory_file.exists():
        print(f"Error: {memory_file} not found.")
        sys.exit(1)

    if args.module_name == "all":
        modules_to_run = [m for m in all_modules if has_testbench(m, args.test_module_format)]
    else:
        if args.module_name not in all_modules:
            print(f"Error: {args.module_name} not found in {args.rtl_dir}.")
            sys.exit(1)
        if not has_testbench(args.module_name, args.test_module_format):
            print(f"No testbench found for {args.module_name}.")
            sys.exit(1)
        modules_to_run = [args.module_name]

    if not modules_to_run:
        print("No modules with testbenches found.")
        sys.exit(0)

    for mod in modules_to_run:
        if args.test_module_format.count("%s") == 2:
            test_module = args.test_module_format % (mod, mod)
        else:
            test_module = args.test_module_format % mod

        print(f"Running test for module: {mod}")
        try:
            run_with_runner(mod, sources, test_module, sim, memory_file)
            print(f"Test for {mod} PASSED\n")
        except Exception as e:
            print(f"Test for {mod} FAILED: {e}")
            sys.exit(1)

    print("All tests completed.")
    sys.exit(0)

if __name__ == "__main__":
    build_dir = "sim_build"
    try:
        main()
    finally:
        pass
        # Remove build directory after test
        # if Path(build_dir).exists():
        #     shutil.rmtree(build_dir)
