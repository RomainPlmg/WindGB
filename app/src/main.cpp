#include "core/emu.h"
#include "gfx/tile.h"
#include "ui.h"

int main(int argc, char const *argv[]) {
    Gameboy gameboy(argc, argv);
    UI ui;

    gameboy.Init();
    ui.Init(std::string(gameboy.GetLoadedGame()));

    int i = 0;
    while (gameboy.IsRunning() && ui.IsOpen()) {
        // Emulator
        gameboy.Step();

        // UI
        if (i >= 500) {
            ui.ProcessEvents();
            ui.Clear();
            ui.Update(gameboy);
            ui.Display();

            i = 0;
        }

        i++;
    }

    return 0;
}
