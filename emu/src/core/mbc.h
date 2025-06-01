#pragma once

#include "utils/common.h"

class MBC {
   public:
    virtual ~MBC() = default;

    virtual u8 ReadROM(u16 addr) const = 0;
    virtual void WriteROM(u8 data, u16 addr) = 0;
    virtual u8 ReadRAM(u16 addr) const = 0;
    virtual void WriteRAM(u8 data, u16 addr) = 0;

   private:
};