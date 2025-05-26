import argparse
import concurrent.futures
import subprocess
import pathlib
import sys

THIS_DIR = pathlib.Path(__file__).parent.resolve()
PROJECT_ROOT = THIS_DIR.parent
EMULATOR_PATH = PROJECT_ROOT / "build" / "Debug" / "app" / "emuapp"
if sys.platform.startswith("win"):
    EMULATOR_PATH = EMULATOR_PATH.with_suffix(".exe")
ROMS_DIR = PROJECT_ROOT / "libs" / "gb-test-roms" / "cpu_instrs" / "individual"
DOCTOR_PATH = PROJECT_ROOT / "libs" / "gameboy-doctor" / "gameboy-doctor"


def extract_test_number(filename: str) -> int:
    return int(filename.split("-")[0])


def run_test_on_rom(rom_path: pathlib.Path, verbose: bool):
    test_num = extract_test_number(rom_path.name)
    name = rom_path.name
    try:
        windgb_proc = subprocess.Popen(
            [str(EMULATOR_PATH), str(rom_path), "--gameboy_doctor"],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )

        doctor_proc = subprocess.run(
            [sys.executable, str(DOCTOR_PATH), "-", "cpu_instrs", str(test_num)],
            stdin=windgb_proc.stdout,
            capture_output=True,
            text=True,
        )

        windgb_proc.stdout.close()
        try:
            windgb_proc.wait(timeout=1.0)
        except subprocess.TimeoutExpired:
            windgb_proc.kill()

        if doctor_proc.returncode == 0:
            return rom_path.name, True, None
        else:
            log = ""
            if verbose:
                log += f"\n---- {rom_path.name} stdout ----\n{doctor_proc.stdout}"
                if doctor_proc.stderr:
                    log += f"\n---- {rom_path.name} stderr ----\n{doctor_proc.stderr}"
            return rom_path.name, False, log

    except Exception as e:
        return rom_path.name, False, f"⚠️ Error running {rom_path.name}: {e}"


def main():
    parser = argparse.ArgumentParser(
        description="Run Blargg CPU tests through Gameboy Doctor."
    )
    parser.add_argument(
        "--only", nargs="+", help="Run specific test(s) by number (e.g. 03 07 11)"
    )
    parser.add_argument(
        "--verbose", action="store_true", help="Show gameboy_doctor output on failure"
    )
    args = parser.parse_args()

    rom_files = sorted(ROMS_DIR.glob("*.gb"))

    max_name_length = max(len(rom.name) for rom in rom_files)

    if args.only:
        rom_files = [
            f for f in rom_files if any(f.name.startswith(f"{nb}-") for nb in args.only)
        ]
        if not rom_files:
            print(f"⚠️ No ROM found for test {args.only}")
            return

    results = []
    logs = []
    with concurrent.futures.ThreadPoolExecutor() as executor:
        future_to_rom = {
            executor.submit(run_test_on_rom, rom, args.verbose): rom
            for rom in rom_files
        }

        for future in concurrent.futures.as_completed(future_to_rom):
            name, success, log = future.result()
            print(
                f"{name.ljust(max_name_length)} --> {'PASS' if success else 'FAIL'}"
            )
            results.append(success)
            if log:
                logs.append(log)

    if logs:
        print("\nDetailed error output:\n")
        for log in logs:
            print(log)

    passed = sum(results)
    total = len(results)
    print(f"\nTest summary: {passed} / {total} passed.")

    if passed != total:
        sys.exit(1)


if __name__ == "__main__":
    main()
