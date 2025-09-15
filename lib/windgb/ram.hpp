#pragma once

#include <array>

#include "component.hpp"

namespace WindGB {

class WRAM final : public Component {
   public:
    [[nodiscard]] uint8_t read(uint16_t addr) const override;
    void write(uint16_t addr, uint8_t data) override;

   private:
    std::array<uint8_t, 0x2000> data_ = {0};
};

class HRAM final : public Component {
   public:
    [[nodiscard]] uint8_t read(uint16_t addr) const override;
    void write(uint16_t addr, uint8_t data) override;

   private:
    std::array<uint8_t, 0x007F> data_ = {0};
};

class VRAM final : public Component {
   public:
    [[nodiscard]] uint8_t read(uint16_t addr) const override;
    void write(uint16_t addr, uint8_t data) override;

   private:
    std::array<uint8_t, 0x2000> data_ = {0};
};

class OAM final : public Component {
   public:
    [[nodiscard]] uint8_t read(uint16_t addr) const override;
    void write(uint16_t addr, uint8_t data) override;

   private:
    std::array<uint8_t, 0x00A0> data_ = {0};
};

}  // namespace WindGB