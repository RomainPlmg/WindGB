#include "core/emu.h"
#include "ui.h"

int main(int argc, char const *argv[]) {
    Gameboy gameboy(argc, argv);
    UI ui;

    gameboy.Init();
    ui.Init(std::string(gameboy.GetLoadedGame()));

    while (gameboy.IsRunning() && ui.IsOpen()) {
        // Emulator
        gameboy.Step();

        // UI
        ui.ProcessEvents();
        ui.Clear();
        ui.Update();
        ui.Display();
    }

    return 0;
}
