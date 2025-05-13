import argparse
import concurrent.futures
import subprocess
import pathlib
import sys

THIS_DIR = pathlib.Path(__file__).parent.resolve()
PROJECT_ROOT = THIS_DIR.parent
EMULATOR_PATH = PROJECT_ROOT / "build" / "Debug" / "app" / "emuapp.exe"
ROMS_DIR = PROJECT_ROOT / "roms" / "gb-test-roms" / "cpu_instrs" / "individual"
DOCTOR_PATH = PROJECT_ROOT / "tests" / "tools" / "gameboy-doctor" / "gameboy-doctor"


def extract_test_number(filename: str) -> int:
    return int(filename.split("-")[0])


def run_test_on_rom(rom_path) -> tuple[str, bool]:
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

        return name, doctor_proc.returncode == 0

    except Exception as e:
        return name, False


def main():
    parser = argparse.ArgumentParser(description="Run Blargg CPU tests through Gameboy Doctor.")
    parser.add_argument("--only", nargs="+", help="Run specific test(s) by number (e.g. 03 07 11)")
    args = parser.parse_args()

    rom_files = sorted(ROMS_DIR.glob("*.gb"))

    max_name_length = max(len(rom.name) for rom in rom_files)

    
    if args.only:
        rom_files = [f for f in rom_files if any(f.name.startswith(f"{nb}-") for nb in args.only)]
        if not rom_files:
            print(f"⚠️ No ROM found for test {args.only}")
            return

    results = []
    with concurrent.futures.ThreadPoolExecutor() as executor:
        future_to_rom = {
            executor.submit(run_test_on_rom, rom): rom for rom in rom_files
        }
        for future in concurrent.futures.as_completed(future_to_rom):
            name, success = future.result()
            print(f"{name.ljust(max_name_length)} --> {"✅ ​Pass" if success else "❌ ​Fail"}")
            results.append(success)

    passed = sum(results)
    total = len(results)
    print(f"\n🧪 Test summary: {passed} / {total} passed.")

    if passed != total:
        sys.exit(1)


if __name__ == "__main__":
    main()
