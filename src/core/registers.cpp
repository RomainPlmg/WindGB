#include "registers.h"

void Registers::SetFlag(FlagBits flag, bool value) {
    if (value) {
        F |= static_cast<uint8_t>(flag);
    } else {
        F &= ~static_cast<uint8_t>(flag);
    }
}

bool Registers::GetFlag(FlagBits flag) { return (F & static_cast<uint8_t>(flag)) != 0; }

void Registers::ClearFlags() { F = 0; }
