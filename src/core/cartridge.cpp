#include "cartridge.h"

#include "pch.h"
#include "utils/Logger.h"
Cartridge::Cartridge(const std::string& path) { LoadROM(path); }

void Cartridge::LoadROM(const std::string path) {
    std::ifstream file(path, std::ios::binary | std::ios::in);
    if (!file) {
        LOG_ERROR("Error: Unable to open the ROM \'{}\'", path);
        return;
    }

    // Read file into the memory
    char byte;
    while (file.read(&byte, 1)) {
        m_ROMData.push_back(static_cast<uint8_t>(byte));
    }

    if (!file.eof()) {
        LOG_ERROR("Error: ROM read failed");
        m_ROMData.clear();
    }
}