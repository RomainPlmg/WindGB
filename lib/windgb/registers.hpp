#pragma once

#include <cstdint>

namespace WindGB {

struct Registers {
    union {
        struct {
            uint8_t F{}, A{};
        };
        uint16_t AF;
    };

    union {
        struct {
            uint8_t C{}, B{};
        };
        uint16_t BC;
    };

    union {
        struct {
            uint8_t E{}, D{};
        };
        uint16_t DE;
    };

    union {
        struct {
            uint8_t L{}, H{};
        };
        uint16_t HL;
    };

    uint16_t SP = 0;  // Stack pointer
    uint16_t PC = 0;  // Program counter

    enum class Flag {
        Z = 0b10000000,  // Zero flag
        N = 0b01000000,
        H = 0b00100000,
        C = 0b00010000
    };

    void set_flag(Flag flag, bool value) {
        if (value == true) {
            F |= static_cast<uint8_t>(flag);
        } else {
            F &= ~static_cast<uint8_t>(flag);
        }
    }

    [[nodiscard]] bool get_flag(Flag flag) const { return (F & static_cast<uint8_t>(flag)) != 0; }
};

}  // namespace WindGB