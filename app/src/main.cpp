#include "emu.h"

int main(int argc, char const *argv[]) {
    Gameboy gameboy(argc, argv);
    gameboy.Run();
    return 0;
}
