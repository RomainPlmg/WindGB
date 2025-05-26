#include "core/emu.h"
#include "gfx/tile.h"
#include "ui.h"

int main(int argc, char const *argv[]) {
    Gameboy gameboy(argc, argv);

    gameboy.Init();

    int i = 0;
    while (gameboy.IsRunning()) {
        // Emulator
        gameboy.Step();
    }

    return 0;
}
