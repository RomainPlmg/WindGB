#pragma once

#include <array>
#include <cstdint>
#include <memory>

#include "component.hpp"
#include "joypad.hpp"

namespace WindGB {

class IO final : public Component {
   public:
    IO();
    [[nodiscard]] uint8_t read(uint16_t addr) const override;
    void write(uint16_t addr, uint8_t data) override;
    uint8_t* get_data() { return data_.data(); }

    Joypad* get_joypad() { return joypad_.get(); }

   private:
    std::unique_ptr<Joypad> joypad_;
    std::array<uint8_t, 0x80> data_ = {0};
};

}  // namespace WindGB