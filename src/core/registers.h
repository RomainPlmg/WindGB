#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#include <array>
#include <cstdint>

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

class Registers {
   public:
    union {
        struct {
            union {
                struct {
                    uint8_t F;  // Flags (Z: Zero | N: Negative | C: Carry | H: Half-carry)
                    uint8_t A;  // General purpose | Accumulator
                };
                uint16_t AF;
            };
            union {
                struct {
                    uint8_t C;  // General purpose
                    uint8_t B;  // General purpose
                };
                uint16_t BC;
            };
            union {
                struct {
                    uint8_t E;  // General purpose
                    uint8_t D;  // General purpose
                };
                uint16_t DE;
            };
            union {
                struct {
                    uint8_t L;  // General purpose
                    uint8_t H;  // General purpose
                };
                uint16_t HL;
            };
        };
    };

    uint16_t SP = 0;  // Stack pointer
    uint16_t PC = 0;  // Program counter

    enum class FlagBits {
        Z = 0b10000000,  // Zero flag
        N = 0b01000000,
        H = 0b00100000,
        C = 0b00010000
    };
};

#endif  // __REGISTERS_H__