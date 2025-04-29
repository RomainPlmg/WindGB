#pragma once

#include <array>
#include <cstdint>

#include "common.h"

//
//       +---------------------------+
//       |         CPU CORE          |
//       +---------------------------+
//       |                           |
//       |  +---------------------+  |
//       |  |         PC          |  |    -> Program counter: contains the next program instruction to fetch & decode
//       |  |---------------------|  |
//       |  |         SP          |  |    -> Stack pointer: Point on the memory stack to use, follow POP & PUSH instructions
//       |  |---------------------|  |
//       |  |     A    |    F     |  |
//       |  |---------------------|  |
//       |  |     B    |    C     |  |
//       |  |---------------------|  |
//       |  |     D    |    E     |  |
//       |  |---------------------|  |
//       |  |     H    |    L     |  |
//       |  +---------------------+  |
//       |                           |
//       +---------------------------+
//
//          ^                     ^
//          |   8-BIT  |   8-BIT  |
//          |---------------------|
//          |       16-BIT        |
//

struct Registers {
    union {
        struct {
            union {
                struct {
                    u8 F;  // Flags (Z: Zero | N: Negative | C: Carry | H: Half-carry)
                    u8 A;  // General purpose | Accumulator
                };
                u16 AF;
            };
            union {
                struct {
                    u8 C;  // General purpose
                    u8 B;  // General purpose
                };
                u16 BC;
            };
            union {
                struct {
                    u8 E;  // General purpose
                    u8 D;  // General purpose
                };
                u16 DE;
            };
            union {
                struct {
                    u8 L;  // General purpose
                    u8 H;  // General purpose
                };
                u16 HL;
            };
        };
    };

    u16 SP = 0;  // Stack pointer
    u16 PC = 0;  // Program counter

    enum class Flag {
        Z = 0b10000000,  // Zero flag
        N = 0b01000000,
        H = 0b00100000,
        C = 0b00010000
    };

    void SetFlag(Flag flag, bool value);
    bool GetFlag(Flag flag);
};