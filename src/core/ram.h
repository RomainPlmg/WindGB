#ifndef __RAM_H__
#define __RAM_H__

#include <array>
#include <cstdint>

class RAM {
   public:
    RAM();
    uint8_t Read(uint16_t addr) const;
    void Write(uint16_t addr, uint8_t data);

   private:
    std::array<uint8_t, 655336> m_Memory;
};

#endif  // __RAM_H__