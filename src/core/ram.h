#ifndef __RAM_H__
#define __RAM_H__

#include <array>
#include <cstdint>

//
//      +------------+------------+-------------+--------------------------------+
//      |  Start     | End        | Size        | Description                   |
//      +------------+------------+-------------+--------------------------------+
//      | 0x0000     | 0x3FFF     | 16 KB       | ROM Bank 0 (Game code)        |
//      | 0x4000     | 0x7FFF     | 16 KB       | Switchable ROM Bank           |
//      | 0x8000     | 0x9FFF     | 8 KB        | VRAM (Video memory)           |
//      | 0xA000     | 0xBFFF     | 8 KB        | External RAM (Cartridge)      |
//      | 0xC000     | 0xCFFF     | 4 KB        | WRAM (Work RAM)               |
//      | 0xD000     | 0xDFFF     | 4 KB        | WRAM Bank 1 (CGB)             |
//      | 0xE000     | 0xFDFF     | 8 KB        | WRAM echo (Not used)          |
//      | 0xFE00     | 0xFE9F     | 160 B       | OAM (Sprite Attributes)       |
//      | 0xFEA0     | 0xFEFF     | 96 B        | Prohibited                    |
//      | 0xFF00     | 0xFF7F     | 128 B       | IO Registers                  |
//      | 0xFF80     | 0xFFFE     | 127 B       | HRAM (Quick memory)           |
//      | 0xFFFF     | 0xFFFF     | 1 B         | IE (Interrupt Enable)         |
//      +------------+------------+-------------+--------------------------------+
//

class RAM {
   public:
    RAM();
    uint8_t Read(uint16_t addr) const;
    void Write(uint16_t addr, uint8_t data);

   private:
    std::array<uint8_t, 655336> m_Memory;
};

#endif  // __RAM_H__