#include "WindGB.h"

int main(void) {
    Logger::Init();
    auto cartridge = new Cartridge(TEST_DIR "cpu_instrs/cpu_instrs.gb");
    auto console = new GB();
    console->LoadCartridge(std::shared_ptr<Cartridge>(cartridge));
    console->Run();
    delete console;
}