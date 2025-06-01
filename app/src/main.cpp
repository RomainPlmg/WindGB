#include <argparse/argparse.hpp>
#include <string>

#include "core/emu.h"
#include "gfx/tile.h"
#include "ui.h"
#include "utils/exit_codes.h"

int main(int argc, char const* argv[]) {
    std::string romPath;
    bool verbose;
    bool header;
    argparse::ArgumentParser parser("WindGB", "0.1.0");
    parser.add_argument("rom_path").help("Path to the ROM to load into the emulator.").store_into(romPath);
    parser.add_argument("--verbose").default_value(false).implicit_value(true).help("Enable standard logging").store_into(verbose);
    parser.add_argument("--header").default_value(false).implicit_value(true).help("Only print the header of the ROM").store_into(header);
    try {
        parser.parse_args(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        exit(EXIT_INVALID_ARGS);
    }

    Gameboy::InitLog();

    Cartridge cartridge;
    cartridge.Load(romPath);

    if (header) exit(EXIT_OK);

    Gameboy gameboy(cartridge);
    gameboy.VerboseLog(verbose);
    UI ui(gameboy);

    gameboy.Init();
    ui.Init();

    while (gameboy.IsRunning() && ui.IsOpen()) {
        // Emulator
        gameboy.Step();

        if (gameboy.GetPPU()->IsFramebufferReady()) {
            ui.ProcessEvents();
            ui.Clear();
            ui.Update();
            ui.Display();
        }
    }

    return 0;
}
