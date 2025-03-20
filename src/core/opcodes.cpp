#include "opcodes.h"

#include "cpu.h"
#include "ram.h"
#include "registers.h"

// TODO: Implement decode function
void Op_Nop(CPU& cpu) { return; }  // Nop

/** LD r16,n16 *******************************************************************************************************/
void Op_LD_BC_n16(CPU& cpu) {  // LD BC, n16
    uint16_t value = cpu.Fetch16();
    cpu.GetRegisters()->BC = value;
}
void Op_LD_DE_n16(CPU& cpu) {  // LD DE, n16
    uint16_t value = cpu.Fetch16();
    cpu.GetRegisters()->DE = value;
}
void Op_LD_HL_n16(CPU& cpu) {  // LD HL, n16
    uint16_t value = cpu.Fetch16();
    cpu.GetRegisters()->HL = value;
}
void Op_LD_SP_n16(CPU& cpu) {  // LD SP, n16
    uint16_t value = cpu.Fetch16();
    cpu.GetRegisters()->SP = value;
}

/** LD [r16],A *******************************************************************************************************/
void Op_LD_pBC_A(CPU& cpu) {  // LD [BC], A
    uint8_t data = cpu.GetRegisters()->A;
    uint16_t addr = cpu.GetRegisters()->BC;
    cpu.GetRAM().Write(addr, data);
}
void Op_LD_pDE_A(CPU& cpu) {  // LD [DE], A
    uint8_t data = cpu.GetRegisters()->A;
    uint16_t addr = cpu.GetRegisters()->DE;
    cpu.GetRAM().Write(addr, data);
}
void Op_LD_pHL_plus_A(CPU& cpu) {  // LD [HL+], A
    uint8_t data = cpu.GetRegisters()->A;
    uint16_t addr = cpu.GetRegisters()->HL++;
    cpu.GetRAM().Write(addr, data);
}
void Op_LD_pHL_minus_A(CPU& cpu) {  // LD [HL-], A
    uint8_t data = cpu.GetRegisters()->A;
    uint16_t addr = cpu.GetRegisters()->HL--;
    cpu.GetRAM().Write(addr, data);
}

/** INC r16 **********************************************************************************************************/
void Op_INC_BC(CPU& cpu) { cpu.GetRegisters()->BC++; }  // INC BC
void Op_INC_DE(CPU& cpu) { cpu.GetRegisters()->DE++; }  // INC DE
void Op_INC_HL(CPU& cpu) { cpu.GetRegisters()->HL++; }  // INC HL
void Op_INC_SP(CPU& cpu) { cpu.GetRegisters()->SP++; }  // INC SP

/** INC r8 ***********************************************************************************************************/
void Op_INC_A(CPU& cpu) {  // INC A
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->A + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->A & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->A = result;
}
void Op_INC_B(CPU& cpu) {  // INC B
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->B + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->B & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->B = result;
}
void Op_INC_C(CPU& cpu) {  // INC C
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->C + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->C & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->C = result;
}
void Op_INC_D(CPU& cpu) {  // INC D
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->D + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->D & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->D = result;
}
void Op_INC_E(CPU& cpu) {  // INC E
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->E + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->E & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->E = result;
}
void Op_INC_H(CPU& cpu) {  // INC H
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->H + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->H & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->H = result;
}
void Op_INC_L(CPU& cpu) {  // INC L
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->L + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->L & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->L = result;
}
void Op_INC_pHL(CPU& cpu) {  // INC [HL]
    // Read the value in memory at address HL
    uint16_t addr = cpu.GetRegisters()->HL;
    uint8_t value = cpu.GetRAM().Read(addr);

    // Calculate the new value
    uint8_t newValue = value + 1;

    // Write the new value to RAM
    cpu.GetRAM().Write(addr, newValue);

    // Update flags
    Registers* reg = cpu.GetRegisters();
    reg->SetFlag(Registers::FlagBits::Z, newValue == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                      // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (value & 0x0F) + 1 > 0x0F);  // H: Activated if a bit overflow 3->4
}

/** DEC r8 ***********************************************************************************************************/
void Op_DEC_A(CPU& cpu) {  // DEC A
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->A - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->A & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->A = result;
}
void Op_DEC_B(CPU& cpu) {  // DEC B
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->B - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->B & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->B = result;
}
void Op_DEC_C(CPU& cpu) {  // DEC C
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->C - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->C & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->C = result;
}
void Op_DEC_D(CPU& cpu) {  // DEC D
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->D - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->D & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->D = result;
}
void Op_DEC_E(CPU& cpu) {  // DEC E
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->E - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->E & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->E = result;
}
void Op_DEC_H(CPU& cpu) {  // DEC H
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->H - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->H & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->H = result;
}
void Op_DEC_L(CPU& cpu) {  // DEC L
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->L - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->L & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->L = result;
}
void Op_DEC_pHL(CPU& cpu) {  // DEC [HL]
    uint8_t addr = cpu.GetRegisters()->HL;
    uint8_t value = cpu.GetRAM().Read(addr);

    uint8_t newValue = value + 1;

    cpu.GetRAM().Write(addr, newValue);

    // Update flags
    Registers* reg = cpu.GetRegisters();
    reg->SetFlag(Registers::FlagBits::Z, newValue == 0);           // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                    // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (value & 0x0F) == 0x00);  // H: Set if borrow from bit 4
}

/** LD r8,n8 *********************************************************************************************************/
void Op_LD_A_n8(CPU& cpu) {}
void Op_LD_B_n8(CPU& cpu) {}
void Op_LD_C_n8(CPU& cpu) {}
void Op_LD_D_n8(CPU& cpu) {}
void Op_LD_E_n8(CPU& cpu) {}
void Op_LD_H_n8(CPU& cpu) {}
void Op_LD_L_n8(CPU& cpu) {}
void Op_LD_pHL_n8(CPU& cpu) {}

/** RLCA *************************************************************************************************************/
void Op_RLCA(CPU& cpu) {}

/** LD [n16],SP ******************************************************************************************************/
void Op_LD_pn16_SP(CPU& cpu) {}

/** ADD HL,r16 *******************************************************************************************************/
void Op_ADD_HL_BC(CPU& cpu) {}
void Op_ADD_HL_DE(CPU& cpu) {}
void Op_ADD_HL_HL(CPU& cpu) {}
void Op_ADD_HL_SP(CPU& cpu) {}

/** LD A,[r16] *******************************************************************************************************/
void Op_LD_A_pBC(CPU& cpu) {}
void Op_LD_A_pDE(CPU& cpu) {}
void Op_LD_A_pHL_plus(CPU& cpu) {}
void Op_LD_A_pHL_minus(CPU& cpu) {}

/** DEC r16 **********************************************************************************************************/
void Op_DEC_BC(CPU& cpu) {}
void Op_DEC_DE(CPU& cpu) {}
void Op_DEC_HL(CPU& cpu) {}
void Op_DEC_SP(CPU& cpu) {}

/** RRCA *************************************************************************************************************/
void Op_RRCA(CPU& cpu) {}

/** STOP *************************************************************************************************************/
void Op_STOP(CPU& cpu) {}

/** RLA **************************************************************************************************************/
void Op_RLA(CPU& cpu) {}

/** JR n8 ************************************************************************************************************/
void Op_JR_n8(CPU& cpu) {}

/** RRA **************************************************************************************************************/
void Op_RRA(CPU& cpu) {}

/** JR cc,n8 *********************************************************************************************************/
void Op_JR_NZ_n8(CPU& cpu) {}
void Op_JR_Z_n8(CPU& cpu) {}
void Op_JR_NC_n8(CPU& cpu) {}
void Op_JR_C_n8(CPU& cpu) {}

/** DAA **************************************************************************************************************/
void Op_DAA(CPU& cpu) {}

/** CPL **************************************************************************************************************/
void Op_CPL(CPU& cpu) {}

/** SCF **************************************************************************************************************/
void Op_SCF(CPU& cpu) {}

/** CCF **************************************************************************************************************/
void Op_CCF(CPU& cpu) {}

/** LD r8,r8 *********************************************************************************************************/
void Op_LD_A_A(CPU& cpu) {}
void Op_LD_A_B(CPU& cpu) {}
void Op_LD_A_C(CPU& cpu) {}
void Op_LD_A_D(CPU& cpu) {}
void Op_LD_A_E(CPU& cpu) {}
void Op_LD_A_H(CPU& cpu) {}
void Op_LD_A_L(CPU& cpu) {}
void Op_LD_A_pHL(CPU& cpu) {}

void Op_LD_B_A(CPU& cpu) {}
void Op_LD_B_B(CPU& cpu) {}
void Op_LD_B_C(CPU& cpu) {}
void Op_LD_B_D(CPU& cpu) {}
void Op_LD_B_E(CPU& cpu) {}
void Op_LD_B_H(CPU& cpu) {}
void Op_LD_B_L(CPU& cpu) {}
void Op_LD_B_pHL(CPU& cpu) {}

void Op_LD_C_A(CPU& cpu) {}
void Op_LD_C_B(CPU& cpu) {}
void Op_LD_C_C(CPU& cpu) {}
void Op_LD_C_D(CPU& cpu) {}
void Op_LD_C_E(CPU& cpu) {}
void Op_LD_C_H(CPU& cpu) {}
void Op_LD_C_L(CPU& cpu) {}
void Op_LD_C_pHL(CPU& cpu) {}

void Op_LD_D_A(CPU& cpu) {}
void Op_LD_D_B(CPU& cpu) {}
void Op_LD_D_C(CPU& cpu) {}
void Op_LD_D_D(CPU& cpu) {}
void Op_LD_D_E(CPU& cpu) {}
void Op_LD_D_H(CPU& cpu) {}
void Op_LD_D_L(CPU& cpu) {}
void Op_LD_D_pHL(CPU& cpu) {}

void Op_LD_E_A(CPU& cpu) {}
void Op_LD_E_B(CPU& cpu) {}
void Op_LD_E_C(CPU& cpu) {}
void Op_LD_E_D(CPU& cpu) {}
void Op_LD_E_E(CPU& cpu) {}
void Op_LD_E_H(CPU& cpu) {}
void Op_LD_E_L(CPU& cpu) {}
void Op_LD_E_pHL(CPU& cpu) {}

void Op_LD_H_A(CPU& cpu) {}
void Op_LD_H_B(CPU& cpu) {}
void Op_LD_H_C(CPU& cpu) {}
void Op_LD_H_D(CPU& cpu) {}
void Op_LD_H_E(CPU& cpu) {}
void Op_LD_H_H(CPU& cpu) {}
void Op_LD_H_L(CPU& cpu) {}
void Op_LD_H_pHL(CPU& cpu) {}

void Op_LD_L_A(CPU& cpu) {}
void Op_LD_L_B(CPU& cpu) {}
void Op_LD_L_C(CPU& cpu) {}
void Op_LD_L_D(CPU& cpu) {}
void Op_LD_L_E(CPU& cpu) {}
void Op_LD_L_H(CPU& cpu) {}
void Op_LD_L_L(CPU& cpu) {}
void Op_LD_L_pHL(CPU& cpu) {}

void Op_LD_pHL_A(CPU& cpu) {}
void Op_LD_pHL_B(CPU& cpu) {}
void Op_LD_pHL_C(CPU& cpu) {}
void Op_LD_pHL_D(CPU& cpu) {}
void Op_LD_pHL_E(CPU& cpu) {}
void Op_LD_pHL_H(CPU& cpu) {}
void Op_LD_pHL_L(CPU& cpu) {}

/** HALT *************************************************************************************************************/
void Op_HALT(CPU& cpu) {}

// Opcode table initialisation
std::array<Opcode, 256> opcodeTable = {
    // Block 0
    Opcode{"Nop", 1, 1, 0, Op_Nop},                  // 0x00: No operation
    Opcode{"LD BC, n16", 3, 3, 0, Op_LD_BC_n16},     // 0x01: Copy the value n16 into register BC.
    Opcode{"LD [BC], A", 1, 2, 0, Op_LD_pBC_A},      // 0x02: Copy the value in register A into the byte pointed to by BC.
    Opcode{"INC BC", 1, 2, 0, Op_INC_BC},            // 0x03: Increment the value in register BC by 1.
    Opcode{"INC B", 1, 1, 0, Op_INC_B},              // 0x04: Increment the value in register B by 1.
    Opcode{"DEC B", 1, 1, 0, Op_DEC_B},              // 0x05: Decrement the value in register B by 1.
    Opcode{"LD B, n8", 2, 2, 0, Op_LD_B_n8},         // 0x06: Copy the value n8 into register B.
    Opcode{"RLCA", 1, 1, 0, Op_RLCA},                // 0x07: Rotate register A left.
    Opcode{"LD [n16], SP", 3, 5, 0, Op_LD_pn16_SP},  // 0x08: Copy SP & $FF at address n16 and SP >> 8 at address n16 + 1.
    Opcode{"ADD HL, BC", 1, 2, 0, Op_ADD_HL_BC},     // 0x09: Add the value in BC to HL.
    Opcode{"LD A, [BC]", 1, 2, 0, Op_LD_A_pBC},      // 0x0A: Copy the byte pointed to by BC into register A.
    Opcode{"DEC BC", 1, 2, 0, Op_DEC_BC},            // 0x0B: Decrement the value in register BC by 1.
    Opcode{"INC C", 1, 1, 0, Op_INC_C},              // 0x0C: Increment the value in register C by 1.
    Opcode{"DEC C", 1, 1, 0, Op_DEC_C},              // 0x0D: Decrement the value in register C by 1.
    Opcode{"LD C, n8", 2, 2, 0, Op_LD_C_n8},         // 0x0E: Copy the value n8 into register C.
    Opcode{"RRCA", 1, 1, 0, Op_RRCA},                // 0x0F: Rotate register A right.
    Opcode{"STOP", 2, 0, 0, Op_STOP},  // 0x10: Enter CPU very low power mode. Special case, refer to https://rgbds.gbdev.io/docs/v0.9.1/gbz80.7#STOP
    Opcode{"LD DE, n16", 3, 3, 0, Op_LD_DE_n16},        // 0x11: Copy the value n16 into register DE.
    Opcode{"LD [DE], A", 1, 2, 0, Op_LD_pDE_A},         // 0x12: Copy the value in register A into the byte pointed to by DE.
    Opcode{"INC DE", 1, 2, 0, Op_INC_DE},               // 0x13: Increment the value in register DE by 1.
    Opcode{"INC D", 1, 1, 0, Op_INC_D},                 // 0x14: Increment the value in register D by 1.
    Opcode{"DEC D", 1, 1, 0, Op_DEC_D},                 // 0x15: Decrement the value in register D by 1.
    Opcode{"LD D, n8", 2, 2, 0, Op_LD_D_n8},            // 0x16: Copy the value n8 into register D.
    Opcode{"RLA", 1, 1, 0, Op_RLA},                     // 0x17: Rotate register A left, through the carry flag.
    Opcode{"JR n8", 2, 3, 0, Op_JR_n8},                 // 0x18: Relative Jump with a signed offset n8.
    Opcode{"ADD HL, DE", 1, 2, 0, Op_ADD_HL_DE},        // 0x19: Add the value in DE to HL.
    Opcode{"LD A, [DE]", 1, 2, 0, Op_LD_A_pDE},         // 0x1A: Copy the byte pointed to by DE into register A.
    Opcode{"DEC DE", 1, 2, 0, Op_DEC_DE},               // 0x1B: Decrement the value in register DE by 1.
    Opcode{"INC E", 1, 1, 0, Op_INC_E},                 // 0x1C: Increment the value in register E by 1.
    Opcode{"DEC E", 1, 1, 0, Op_DEC_E},                 // 0x1D: Decrement the value in register E by 1.
    Opcode{"LD E, n8", 2, 2, 0, Op_LD_E_n8},            // 0x1E: Copy the value n8 into register E.
    Opcode{"RRA", 2, 2, 0, Op_RRA},                     // 0x1F: Rotate register A right, through the carry flag.
    Opcode{"JR NZ, n8", 2, 2, 1, Op_JR_NZ_n8},          // 0x20: Relative Jump with a signed offset n8 if condition NZ is met.
    Opcode{"LD HL, n16", 3, 3, 0, Op_LD_HL_n16},        // 0x21: Copy the value n16 into register HL.
    Opcode{"LD [HL+], A", 1, 2, 0, Op_LD_pHL_plus_A},   // 0x22: Copy the value in register A into the byte pointed by HL and increment HL afterwards.
    Opcode{"INC HL", 1, 2, 0, Op_INC_HL},               // 0x23: Increment the value in register HL by 1.
    Opcode{"INC H", 1, 1, 0, Op_INC_H},                 // 0x24: Increment the value in register H by 1.
    Opcode{"DEC H", 1, 1, 0, Op_DEC_H},                 // 0x25: Decrement the value in register H by 1.
    Opcode{"LD H, n8", 2, 2, 0, Op_LD_H_n8},            // 0x26: Copy the value n8 into register H.
    Opcode{"DAA", 1, 1, 0, Op_DAA},                     // 0x27: Decimal Adjust Accumulator.
    Opcode{"JR Z, n8", 2, 2, 1, Op_JR_Z_n8},            // 0x28: Relative Jump with a signed offset n8 if condition Z is met.
    Opcode{"ADD HL, HL", 1, 2, 0, Op_ADD_HL_HL},        // 0x29: Add the value in HL to HL.
    Opcode{"LD A, [HL+]", 1, 2, 0, Op_LD_A_pHL_plus},   // 0x2A: Copy the byte pointed to by HL into register A, and increment HL afterwards.
    Opcode{"DEC HL", 1, 2, 0, Op_DEC_HL},               // 0x2B: Decrement the value in register HL by 1.
    Opcode{"INC L", 1, 1, 0, Op_INC_L},                 // 0x2C: Increment the value in register L by 1.
    Opcode{"DEC L", 1, 1, 0, Op_DEC_L},                 // 0x2D: Decrement the value in register L by 1.
    Opcode{"LD L, n8", 2, 2, 0, Op_LD_L_n8},            // 0x2E: Copy the value n8 into register L.
    Opcode{"CPL", 1, 1, 0, Op_CPL},                     // 0x2F: ComPLement accumulator (A = ~A); also called bitwise NOT.
    Opcode{"JR NC, n8", 2, 2, 1, Op_JR_NC_n8},          // 0x30: Relative Jump with a signed offset n8 if condition NC is met.
    Opcode{"LD SP, n16", 3, 3, 0, Op_LD_SP_n16},        // 0x31: Copy the value n16 into register SP.
    Opcode{"LD [HL-], A", 1, 2, 0, Op_LD_pHL_minus_A},  // 0x32: Copy the value in register A into the byte pointed by HL and decrement HL afterwards.
    Opcode{"INC SP", 1, 2, 0, Op_INC_SP},               // 0x33: Increment the value in register SP by 1.
    Opcode{"INC [HL]", 1, 3, 0, Op_INC_pHL},            // 0x34: Increment the byte pointed to by HL by 1.
    Opcode{"DEC [HL]", 1, 3, 0, Op_DEC_pHL},            // 0x35: Decrement the byte pointed to by HL by 1.
    Opcode{"LD [HL], n8", 1, 2, 0, Op_LD_pHL_n8},       // 0x36: Copy the value n8 into the byte pointed to by HL.
    Opcode{"SCF", 1, 1, 0, Op_SCF},                     // 0x37: Set Carry Flag.
    Opcode{"JR C, n8", 2, 2, 1, Op_JR_C_n8},            // 0x38: Relative Jump with a signed offset n8 if condition C is met.
    Opcode{"ADD SP, BC", 1, 2, 0, Op_ADD_HL_SP},        // 0x39: Add the value in SP to HL.
    Opcode{"LD A, [HL+]", 1, 2, 0, Op_LD_A_pHL_minus},  // 0x3A: Copy the byte pointed to by HL into register A, and decrement HL afterwards.
    Opcode{"DEC SP", 1, 2, 0, Op_DEC_SP},               // 0x3B: Decrement the value in register SP by 1.
    Opcode{"INC A", 1, 1, 0, Op_INC_A},                 // 0x3C: Increment the value in register A by 1.
    Opcode{"DEC A", 1, 1, 0, Op_DEC_A},                 // 0x3D: Decrement the value in register A by 1.
    Opcode{"LD A, n8", 2, 2, 0, Op_LD_A_n8},            // 0x3E: Copy the value n8 into register A.
    Opcode{"CCF", 1, 1, 0, Op_CCF},                     // 0x3F: Complement Carry Flag.
    // Block 1: 8-bit register-to-register loads
    Opcode{"LD B, B", 1, 1, 0, Op_LD_B_B},       // 0x40: Copy (aka Load) the value in B into B. -> TODO: Check if HALT
    Opcode{"LD B, C", 1, 1, 0, Op_LD_B_C},       // 0x41: Copy (aka Load) the value in B into C.
    Opcode{"LD B, D", 1, 1, 0, Op_LD_B_D},       // 0x42: Copy (aka Load) the value in B into D.
    Opcode{"LD B, E", 1, 1, 0, Op_LD_B_E},       // 0x43: Copy (aka Load) the value in B into E.
    Opcode{"LD B, H", 1, 1, 0, Op_LD_B_H},       // 0x44: Copy (aka Load) the value in B into H.
    Opcode{"LD B, L", 1, 1, 0, Op_LD_B_L},       // 0x45: Copy (aka Load) the value in B into L.
    Opcode{"LD B, [HL]", 1, 1, 0, Op_LD_B_pHL},  // 0x46: Copy (aka Load) the value in B into the byte pointed by HL.
    Opcode{"LD B, A", 1, 1, 0, Op_LD_B_A},       // 0x47: Copy (aka Load) the value in B into A.
    Opcode{"LD C, B", 1, 1, 0, Op_LD_C_B},       // 0x48: Copy (aka Load) the value in C into B.
    Opcode{"LD C, C", 1, 1, 0, Op_LD_C_C},       // 0x49: Copy (aka Load) the value in C into C. -> TODO: Check if HALT
    Opcode{"LD C, D", 1, 1, 0, Op_LD_C_D},       // 0x4A: Copy (aka Load) the value in C into D.
    Opcode{"LD C, E", 1, 1, 0, Op_LD_C_E},       // 0x4B: Copy (aka Load) the value in C into E.
    Opcode{"LD C, H", 1, 1, 0, Op_LD_C_H},       // 0x4C: Copy (aka Load) the value in C into H.
    Opcode{"LD C, L", 1, 1, 0, Op_LD_C_L},       // 0x4D: Copy (aka Load) the value in C into L.
    Opcode{"LD C, [HL]", 1, 1, 0, Op_LD_C_pHL},  // 0x4E: Copy (aka Load) the value in C into the byte pointed by HL.
    Opcode{"LD C, A", 1, 1, 0, Op_LD_C_A},       // 0x4F: Copy (aka Load) the value in C into A.
    Opcode{"LD D, B", 1, 1, 0, Op_LD_D_B},       // 0x50: Copy (aka Load) the value in D into B.
    Opcode{"LD D, C", 1, 1, 0, Op_LD_D_C},       // 0x51: Copy (aka Load) the value in D into C.
    Opcode{"LD D, D", 1, 1, 0, Op_LD_D_D},       // 0x52: Copy (aka Load) the value in D into D. -> TODO: Check if HALT
    Opcode{"LD D, E", 1, 1, 0, Op_LD_D_E},       // 0x53: Copy (aka Load) the value in D into E.
    Opcode{"LD D, H", 1, 1, 0, Op_LD_D_H},       // 0x54: Copy (aka Load) the value in D into H.
    Opcode{"LD D, L", 1, 1, 0, Op_LD_D_L},       // 0x55: Copy (aka Load) the value in D into L.
    Opcode{"LD D, [HL]", 1, 1, 0, Op_LD_D_pHL},  // 0x56: Copy (aka Load) the value in D into the byte pointed by HL.
    Opcode{"LD D, A", 1, 1, 0, Op_LD_D_A},       // 0x57: Copy (aka Load) the value in D into A.
    Opcode{"LD E, B", 1, 1, 0, Op_LD_E_B},       // 0x58: Copy (aka Load) the value in E into B.
    Opcode{"LD E, C", 1, 1, 0, Op_LD_E_C},       // 0x59: Copy (aka Load) the value in E into C.
    Opcode{"LD E, D", 1, 1, 0, Op_LD_E_D},       // 0x5A: Copy (aka Load) the value in E into D.
    Opcode{"LD E, E", 1, 1, 0, Op_LD_E_E},       // 0x5B: Copy (aka Load) the value in E into E. -> TODO: Check if HALT
    Opcode{"LD E, H", 1, 1, 0, Op_LD_E_H},       // 0x5C: Copy (aka Load) the value in E into H.
    Opcode{"LD E, L", 1, 1, 0, Op_LD_E_L},       // 0x5D: Copy (aka Load) the value in E into L.
    Opcode{"LD E, [HL]", 1, 1, 0, Op_LD_E_pHL},  // 0x5E: Copy (aka Load) the value in E into the byte pointed by HL.
    Opcode{"LD E, A", 1, 1, 0, Op_LD_E_A},       // 0x5F: Copy (aka Load) the value in E into A.
    Opcode{"LD H, B", 1, 1, 0, Op_LD_H_B},       // 0x60: Copy (aka Load) the value in H into B.
    Opcode{"LD H, C", 1, 1, 0, Op_LD_H_C},       // 0x61: Copy (aka Load) the value in H into C.
    Opcode{"LD H, D", 1, 1, 0, Op_LD_H_D},       // 0x62: Copy (aka Load) the value in H into D.
    Opcode{"LD H, E", 1, 1, 0, Op_LD_H_E},       // 0x63: Copy (aka Load) the value in H into E.
    Opcode{"LD H, H", 1, 1, 0, Op_LD_H_H},       // 0x64: Copy (aka Load) the value in H into H. -> TODO: Check if HALT
    Opcode{"LD H, L", 1, 1, 0, Op_LD_H_L},       // 0x65: Copy (aka Load) the value in H into L.
    Opcode{"LD H, [HL]", 1, 1, 0, Op_LD_H_pHL},  // 0x66: Copy (aka Load) the value in H into the byte pointed by HL.
    Opcode{"LD H, A", 1, 1, 0, Op_LD_H_A},       // 0x67: Copy (aka Load) the value in H into A.
    Opcode{"LD L, B", 1, 1, 0, Op_LD_L_B},       // 0x68: Copy (aka Load) the value in L into B.
    Opcode{"LD L, C", 1, 1, 0, Op_LD_L_C},       // 0x69: Copy (aka Load) the value in L into C.
    Opcode{"LD L, D", 1, 1, 0, Op_LD_L_D},       // 0x6A: Copy (aka Load) the value in L into D.
    Opcode{"LD L, E", 1, 1, 0, Op_LD_L_E},       // 0x6B: Copy (aka Load) the value in L into E.
    Opcode{"LD L, H", 1, 1, 0, Op_LD_L_H},       // 0x6C: Copy (aka Load) the value in L into H.
    Opcode{"LD L, L", 1, 1, 0, Op_LD_L_L},       // 0x6D: Copy (aka Load) the value in L into L. -> TODO: Check if HALT
    Opcode{"LD L, [HL]", 1, 1, 0, Op_LD_L_pHL},  // 0x6E: Copy (aka Load) the value in L into the byte pointed by HL.
    Opcode{"LD L, A", 1, 1, 0, Op_LD_L_A},       // 0x6F: Copy (aka Load) the value in L into A.
    Opcode{"LD [HL], B", 1, 1, 0, Op_LD_pHL_B},  // 0x70: Copy (aka Load) the byte pointed by HL into B.
    Opcode{"LD [HL], C", 1, 1, 0, Op_LD_pHL_C},  // 0x71: Copy (aka Load) the byte pointed by HL into C.
    Opcode{"LD [HL], D", 1, 1, 0, Op_LD_pHL_D},  // 0x72: Copy (aka Load) the byte pointed by HL into D.
    Opcode{"LD [HL], E", 1, 1, 0, Op_LD_pHL_E},  // 0x73: Copy (aka Load) the byte pointed by HL into E.
    Opcode{"LD [HL], H", 1, 1, 0, Op_LD_pHL_H},  // 0x74: Copy (aka Load) the byte pointed by HL into H.
    Opcode{"LD [HL], L", 1, 1, 0, Op_LD_pHL_L},  // 0x75: Copy (aka Load) the byte pointed by HL into L.
    Opcode{"HALT", 1, 0, 0, Op_HALT},            // 0x76: Enter CPU low-power consumption mode until an interrupt occurs.
    Opcode{"LD [HL], A", 1, 1, 0, Op_LD_pHL_A},  // 0x77: Copy (aka Load) the byte pointed by HL into A.
    Opcode{"LD A B", 1, 1, 0, Op_LD_A_B},        // 0x78: Copy (aka Load) the value in A into B.
    Opcode{"LD A C", 1, 1, 0, Op_LD_A_C},        // 0x79: Copy (aka Load) the value in A into C.
    Opcode{"LD A D", 1, 1, 0, Op_LD_A_D},        // 0x7A: Copy (aka Load) the value in A into D.
    Opcode{"LD A E", 1, 1, 0, Op_LD_A_E},        // 0x7B: Copy (aka Load) the value in A into E.
    Opcode{"LD A H", 1, 1, 0, Op_LD_A_H},        // 0x7C: Copy (aka Load) the value in A into H.
    Opcode{"LD A L", 1, 1, 0, Op_LD_A_L},        // 0x7D: Copy (aka Load) the value in A into L.
    Opcode{"LD A [HL]", 1, 1, 0, Op_LD_A_pHL},   // 0x7E: Copy (aka Load) the value in A into the byte pointed by HL.
    Opcode{"LD A A", 1, 1, 0, Op_LD_A_A},        // 0x7F: Copy (aka Load) the value in A into A. -> TODO: Check if HALT
    // TODO: Add missing instructions
};