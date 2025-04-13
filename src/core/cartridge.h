#ifndef __CARTRIDGE_H__
#define __CARTRIDGE_H__

#include <string>
#include <vector>

class Cartridge {
   public:
    Cartridge(const std::string& path);

    const std::vector<uint8_t>& GetROM() const { return m_ROMData; }

   private:
    std::vector<uint8_t> m_ROMData;

    void LoadROM(const std::string path);
};

#endif  //__CARTRIDGE_H__