#pragma once

#include <memory>

#include "cartridge.h"
#include "gfx/oam.h"
#include "ram.h"
#include "utils/common.h"

//      +------------+------------+-------------+--------------------------------+
//      |  Start     | End        | Size        | Description                   |
//      +------------+------------+-------------+--------------------------------+
//      | 0x0000     | 0x3FFF     | 16 KB       | ROM Bank 0 (Game code)        |
//      | 0x4000     | 0x7FFF     | 16 KB       | Switchable ROM Bank           |
//      | 0x8000     | 0x9FFF     | 8 KB        | VRAM (Video memory)           |
//      | 0xA000     | 0xBFFF     | 8 KB        | External RAM (Cartridge)      |
//      | 0xC000     | 0xDFFF     | 8 KB        | WRAM (Work RAM)               |
//      | 0xE000     | 0xFDFF     | 8 KB        | WRAM echo (Not used)          |
//      | 0xFE00     | 0xFE9F     | 160 B       | OAM (Sprite Attributes)       |
//      | 0xFEA0     | 0xFEFF     | 96 B        | Prohibited                    |
//      | 0xFF00     | 0xFF7F     | 128 B       | IO Registers                  |
//      | 0xFF80     | 0xFFFE     | 127 B       | HRAM (Quick memory)           |
//      | 0xFFFF     | 0xFFFF     | 1 B         | IE (Interrupt Enable)         |
//      +------------+------------+-------------+--------------------------------+

constexpr u16 INTERRUPT_ENABLE_ADDR = 0xFFFF;

class IO;

class Bus {
   public:
    Bus();
    u8 Read(u16 addr) const;
    const u8* GetPointerTo(u16 addr);
    void Write(u16 addr, u8 data);

    /* Attach methods */
    void Attach(IO* io) { m_IO = io; }
    void Attach(Cartridge* cartridge) { m_Cartridge = cartridge; }

   private:
    std::unique_ptr<VRAM> m_VRAM;
    std::unique_ptr<WRAM> m_WRAM;
    std::unique_ptr<HRAM> m_HRAM;
    std::unique_ptr<OAM> m_OAM;
    IO* m_IO;
    Cartridge* m_Cartridge;

    u8 m_IE;
};