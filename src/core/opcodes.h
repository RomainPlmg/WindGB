#ifndef __OPCODES_H__
#define __OPCODES_H__

#include <array>
#include <string>

#include "cpu.h"

using OpcodeFunc = void (*)(CPU&);  // Callback, takes CPU reference and return void

struct Opcode {
    std::string name;
    uint8_t size;
    uint8_t cycles;
    uint8_t extraCycles;
    OpcodeFunc Execute;
};

// Declaration of the opcodes table
extern std::array<Opcode, 256> opcodeTable;

#endif  // __OPCODES_H__