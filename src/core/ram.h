#ifndef __RAM_H__
#define __RAM_H__

#include <array>
#include <cstdint>

constexpr int MEMORY_BUS_WIDTH = 16;
constexpr size_t MEMORY_SIZE = static_cast<size_t>(1) << MEMORY_BUS_WIDTH;

class RAM {
   public:
    RAM();
    uint8_t Read(uint16_t addr) const;
    void Write(uint16_t addr, uint8_t data);

   private:
    std::array<uint8_t, MEMORY_SIZE> m_Memory;
};

#endif  // __RAM_H__