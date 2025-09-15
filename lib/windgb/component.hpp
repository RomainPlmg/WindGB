#pragma once

#include <cstdint>

namespace WindGB {

class Component {
   public:
    virtual ~Component() = default;

    [[nodiscard]] virtual uint8_t read(uint16_t addr) const = 0;
    virtual void write(uint16_t addr, uint8_t data) = 0;
};

}  // namespace WindGB