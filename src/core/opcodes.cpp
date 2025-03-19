#include "opcodes.h"

#include "cpu.h"
#include "ram.h"
#include "registers.h"

// TODO: Implement decode function
void Op_Nop(CPU& cpu) { return; }  // Nop

void Op_LD_BC_n16(CPU& cpu) {
    uint16_t value = cpu.Fetch16();
    cpu.GetRegisters()->BC = value;
}  // LD BC, n16

void Op_LD_DE_n16(CPU& cpu) {
    uint16_t value = cpu.Fetch16();
    cpu.GetRegisters()->DE = value;
}  // LD DE, n16

void Op_LD_HL_n16(CPU& cpu) {
    uint16_t value = cpu.Fetch16();
    cpu.GetRegisters()->HL = value;
}  // LD HL, n16

void Op_LD_SP_n16(CPU& cpu) {
    uint16_t value = cpu.Fetch16();
    cpu.GetRegisters()->SP = value;
}  // LD SP, n16

void Op_LD_BC_A(CPU& cpu) {
    uint8_t data = cpu.GetRegisters()->A;
    uint16_t addr = cpu.GetRegisters()->BC;
    cpu.GetRAM().Write(addr, data);
}  // LD [BC], A

void Op_LD_DE_A(CPU& cpu) {
    uint8_t data = cpu.GetRegisters()->A;
    uint16_t addr = cpu.GetRegisters()->DE;
    cpu.GetRAM().Write(addr, data);
}  // LD [DE], A

void Op_LD_HL_plus_A(CPU& cpu) {
    uint8_t data = cpu.GetRegisters()->A;
    uint16_t addr = cpu.GetRegisters()->HL++;
    cpu.GetRAM().Write(addr, data);
}  // LD [HL+], A

void Op_LD_HL_minus_A(CPU& cpu) {
    uint8_t data = cpu.GetRegisters()->A;
    uint16_t addr = cpu.GetRegisters()->HL--;
    cpu.GetRAM().Write(addr, data);
}  // LD [HL-], A

// Opcode table initialisation
std::array<Opcode, 256> opcodeTable = {
    Opcode{"Nop", 1, 1, Op_Nop},                    // 0x00: No operation
    Opcode{"LD BC, n16", 3, 3, Op_LD_BC_n16},       // 0x01: Copy the value n16 into register BC.
    Opcode{"LD [BC], A", 1, 2, Op_LD_BC_A},         // 0x02: Copy the value in register A into the byte pointed to by BC.
    Opcode{"LD DE, n16", 3, 3, Op_LD_DE_n16},       // 0x11: Copy the value n16 into register DE.
    Opcode{"LD [DE], A", 1, 2, Op_LD_DE_A},         // 0x12: Copy the value in register A into the byte pointed to by DE.
    Opcode{"LD HL, n16", 3, 3, Op_LD_HL_n16},       // 0x21: Copy the value n16 into register HL.
    Opcode{"LD [HL+], A", 1, 2, Op_LD_HL_plus_A},   // 0x22: Copy the value in register A into the byte pointed to by HL+.
    Opcode{"LD HL, n16", 3, 3, Op_LD_SP_n16},       // 0x31: Copy the value n16 into register SP.
    Opcode{"LD [HL-], A", 1, 2, Op_LD_HL_minus_A},  // 0x32: Copy the value in register A into the byte pointed to by HL-.
    // TODO: Add missing instructions
};