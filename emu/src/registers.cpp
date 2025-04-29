#include "registers.h"

void Registers::SetFlag(Flag flag, bool value) {
    if (value == true) {
        F |= static_cast<u8>(flag);
    } else {
        F &= ~static_cast<u8>(flag);
    }
}

bool Registers::GetFlag(Flag flag) { return (F & static_cast<u8>(flag)) != 0; }
