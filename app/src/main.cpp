#include "core/emu.h"
#include "gfx/tile.h"
#include "ui.h"

int main(int argc, char const *argv[]) {
    Gameboy gameboy(argc, argv);
    UI ui(gameboy);

    gameboy.Init();
    ui.Init();

    while (gameboy.IsRunning() && ui.IsOpen()) {
        // Emulator
        gameboy.Step();

        ui.ProcessEvents();

        if (gameboy.GetPPU()->IsFramebufferReady()) {
            ui.Clear();
            ui.Update();
            ui.Display();
        }
    }

    return 0;
}
