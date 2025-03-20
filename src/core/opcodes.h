#ifndef __OPCODES_H__
#define __OPCODES_H__

#include <array>
#include <string>

#include "cpu.h"
#include "ram.h"
#include "registers.h"

using OpcodeFunc = void (*)(CPU&);  // Callback, takes CPU reference and return static void

struct Opcode {
    std::string name;
    uint8_t size;
    uint8_t cycles;
    uint8_t extraCycles;
    OpcodeFunc Execute;
};

// Declaration of the opcodes table
extern std::array<Opcode, 256> opcodeTable;

// TODO: Implement decode function
static void Op_Nop(CPU& cpu) { return; }  // Nop

/** LD r16,n16 *******************************************************************************************************/
static void Op_LD_BC_n16(CPU& cpu) {  // LD BC, n16
    uint16_t value = cpu.Fetch16();
    cpu.GetRegisters()->BC = value;
}
static void Op_LD_DE_n16(CPU& cpu) {  // LD DE, n16
    uint16_t value = cpu.Fetch16();
    cpu.GetRegisters()->DE = value;
}
static void Op_LD_HL_n16(CPU& cpu) {  // LD HL, n16
    uint16_t value = cpu.Fetch16();
    cpu.GetRegisters()->HL = value;
}
static void Op_LD_SP_n16(CPU& cpu) {  // LD SP, n16
    uint16_t value = cpu.Fetch16();
    cpu.GetRegisters()->SP = value;
}

/** LD [r16],A *******************************************************************************************************/
static void Op_LD_pBC_A(CPU& cpu) {  // LD [BC], A
    uint8_t data = cpu.GetRegisters()->A;
    uint16_t addr = cpu.GetRegisters()->BC;
    cpu.GetRAM().Write(addr, data);
}
static void Op_LD_pDE_A(CPU& cpu) {  // LD [DE], A
    uint8_t data = cpu.GetRegisters()->A;
    uint16_t addr = cpu.GetRegisters()->DE;
    cpu.GetRAM().Write(addr, data);
}
static void Op_LD_pHL_plus_A(CPU& cpu) {  // LD [HL+], A
    uint8_t data = cpu.GetRegisters()->A;
    uint16_t addr = cpu.GetRegisters()->HL++;
    cpu.GetRAM().Write(addr, data);
}
static void Op_LD_pHL_minus_A(CPU& cpu) {  // LD [HL-], A
    uint8_t data = cpu.GetRegisters()->A;
    uint16_t addr = cpu.GetRegisters()->HL--;
    cpu.GetRAM().Write(addr, data);
}

/** INC r16 **********************************************************************************************************/
static void Op_INC_BC(CPU& cpu) { cpu.GetRegisters()->BC++; }  // INC BC
static void Op_INC_DE(CPU& cpu) { cpu.GetRegisters()->DE++; }  // INC DE
static void Op_INC_HL(CPU& cpu) { cpu.GetRegisters()->HL++; }  // INC HL
static void Op_INC_SP(CPU& cpu) { cpu.GetRegisters()->SP++; }  // INC SP

/** INC r8 ***********************************************************************************************************/
static void Op_INC_A(CPU& cpu) {  // INC A
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->A + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->A & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->A = result;
}
static void Op_INC_B(CPU& cpu) {  // INC B
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->B + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->B & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->B = result;
}
static void Op_INC_C(CPU& cpu) {  // INC C
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->C + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->C & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->C = result;
}
static void Op_INC_D(CPU& cpu) {  // INC D
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->D + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->D & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->D = result;
}
static void Op_INC_E(CPU& cpu) {  // INC E
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->E + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->E & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->E = result;
}
static void Op_INC_H(CPU& cpu) {  // INC H
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->H + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->H & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->H = result;
}
static void Op_INC_L(CPU& cpu) {  // INC L
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->L + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->L & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->L = result;
}
static void Op_INC_pHL(CPU& cpu) {  // INC [HL]
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
static void Op_DEC_A(CPU& cpu) {  // DEC A
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->A - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->A & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->A = result;
}
static void Op_DEC_B(CPU& cpu) {  // DEC B
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->B - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->B & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->B = result;
}
static void Op_DEC_C(CPU& cpu) {  // DEC C
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->C - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->C & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->C = result;
}
static void Op_DEC_D(CPU& cpu) {  // DEC D
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->D - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->D & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->D = result;
}
static void Op_DEC_E(CPU& cpu) {  // DEC E
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->E - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->E & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->E = result;
}
static void Op_DEC_H(CPU& cpu) {  // DEC H
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->H - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->H & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->H = result;
}
static void Op_DEC_L(CPU& cpu) {  // DEC L
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->L - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->L & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->L = result;
}
static void Op_DEC_pHL(CPU& cpu) {  // DEC [HL]
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
static void Op_LD_A_n8(CPU& cpu) {}
static void Op_LD_B_n8(CPU& cpu) {}
static void Op_LD_C_n8(CPU& cpu) {}
static void Op_LD_D_n8(CPU& cpu) {}
static void Op_LD_E_n8(CPU& cpu) {}
static void Op_LD_H_n8(CPU& cpu) {}
static void Op_LD_L_n8(CPU& cpu) {}
static void Op_LD_pHL_n8(CPU& cpu) {}

/** RLCA *************************************************************************************************************/
static void Op_RLCA(CPU& cpu) {}

/** LD [n16],SP ******************************************************************************************************/
static void Op_LD_pn16_SP(CPU& cpu) {}

/** ADD HL,r16 *******************************************************************************************************/
static void Op_ADD_HL_BC(CPU& cpu) {}
static void Op_ADD_HL_DE(CPU& cpu) {}
static void Op_ADD_HL_HL(CPU& cpu) {}
static void Op_ADD_HL_SP(CPU& cpu) {}

/** LD A,[r16] *******************************************************************************************************/
static void Op_LD_A_pBC(CPU& cpu) {}
static void Op_LD_A_pDE(CPU& cpu) {}
static void Op_LD_A_pHL_plus(CPU& cpu) {}
static void Op_LD_A_pHL_minus(CPU& cpu) {}

/** DEC r16 **********************************************************************************************************/
static void Op_DEC_BC(CPU& cpu) {}
static void Op_DEC_DE(CPU& cpu) {}
static void Op_DEC_HL(CPU& cpu) {}
static void Op_DEC_SP(CPU& cpu) {}

/** RRCA *************************************************************************************************************/
static void Op_RRCA(CPU& cpu) {}

/** STOP *************************************************************************************************************/
static void Op_STOP(CPU& cpu) {}

/** RLA **************************************************************************************************************/
static void Op_RLA(CPU& cpu) {}

/** JR n8 ************************************************************************************************************/
static void Op_JR_n8(CPU& cpu) {}

/** RRA **************************************************************************************************************/
static void Op_RRA(CPU& cpu) {}

/** JR cc,n8 *********************************************************************************************************/
static void Op_JR_NZ_n8(CPU& cpu) {}
static void Op_JR_Z_n8(CPU& cpu) {}
static void Op_JR_NC_n8(CPU& cpu) {}
static void Op_JR_C_n8(CPU& cpu) {}

/** DAA **************************************************************************************************************/
static void Op_DAA(CPU& cpu) {}

/** CPL **************************************************************************************************************/
static void Op_CPL(CPU& cpu) {}

/** SCF **************************************************************************************************************/
static void Op_SCF(CPU& cpu) {}

/** CCF **************************************************************************************************************/
static void Op_CCF(CPU& cpu) {}

/** LD r8,r8 *********************************************************************************************************/
static void Op_LD_A_A(CPU& cpu) {}
static void Op_LD_A_B(CPU& cpu) {}
static void Op_LD_A_C(CPU& cpu) {}
static void Op_LD_A_D(CPU& cpu) {}
static void Op_LD_A_E(CPU& cpu) {}
static void Op_LD_A_H(CPU& cpu) {}
static void Op_LD_A_L(CPU& cpu) {}
static void Op_LD_A_pHL(CPU& cpu) {}

static void Op_LD_B_A(CPU& cpu) {}
static void Op_LD_B_B(CPU& cpu) {}
static void Op_LD_B_C(CPU& cpu) {}
static void Op_LD_B_D(CPU& cpu) {}
static void Op_LD_B_E(CPU& cpu) {}
static void Op_LD_B_H(CPU& cpu) {}
static void Op_LD_B_L(CPU& cpu) {}
static void Op_LD_B_pHL(CPU& cpu) {}

static void Op_LD_C_A(CPU& cpu) {}
static void Op_LD_C_B(CPU& cpu) {}
static void Op_LD_C_C(CPU& cpu) {}
static void Op_LD_C_D(CPU& cpu) {}
static void Op_LD_C_E(CPU& cpu) {}
static void Op_LD_C_H(CPU& cpu) {}
static void Op_LD_C_L(CPU& cpu) {}
static void Op_LD_C_pHL(CPU& cpu) {}

static void Op_LD_D_A(CPU& cpu) {}
static void Op_LD_D_B(CPU& cpu) {}
static void Op_LD_D_C(CPU& cpu) {}
static void Op_LD_D_D(CPU& cpu) {}
static void Op_LD_D_E(CPU& cpu) {}
static void Op_LD_D_H(CPU& cpu) {}
static void Op_LD_D_L(CPU& cpu) {}
static void Op_LD_D_pHL(CPU& cpu) {}

static void Op_LD_E_A(CPU& cpu) {}
static void Op_LD_E_B(CPU& cpu) {}
static void Op_LD_E_C(CPU& cpu) {}
static void Op_LD_E_D(CPU& cpu) {}
static void Op_LD_E_E(CPU& cpu) {}
static void Op_LD_E_H(CPU& cpu) {}
static void Op_LD_E_L(CPU& cpu) {}
static void Op_LD_E_pHL(CPU& cpu) {}

static void Op_LD_H_A(CPU& cpu) {}
static void Op_LD_H_B(CPU& cpu) {}
static void Op_LD_H_C(CPU& cpu) {}
static void Op_LD_H_D(CPU& cpu) {}
static void Op_LD_H_E(CPU& cpu) {}
static void Op_LD_H_H(CPU& cpu) {}
static void Op_LD_H_L(CPU& cpu) {}
static void Op_LD_H_pHL(CPU& cpu) {}

static void Op_LD_L_A(CPU& cpu) {}
static void Op_LD_L_B(CPU& cpu) {}
static void Op_LD_L_C(CPU& cpu) {}
static void Op_LD_L_D(CPU& cpu) {}
static void Op_LD_L_E(CPU& cpu) {}
static void Op_LD_L_H(CPU& cpu) {}
static void Op_LD_L_L(CPU& cpu) {}
static void Op_LD_L_pHL(CPU& cpu) {}

static void Op_LD_pHL_A(CPU& cpu) {}
static void Op_LD_pHL_B(CPU& cpu) {}
static void Op_LD_pHL_C(CPU& cpu) {}
static void Op_LD_pHL_D(CPU& cpu) {}
static void Op_LD_pHL_E(CPU& cpu) {}
static void Op_LD_pHL_H(CPU& cpu) {}
static void Op_LD_pHL_L(CPU& cpu) {}

/** HALT *************************************************************************************************************/
static void Op_HALT(CPU& cpu) {}

/** ADD A,r8 ********************************************************************************************************/
static void Op_ADD_A_A(CPU& cpu) {}
static void Op_ADD_A_B(CPU& cpu) {}
static void Op_ADD_A_C(CPU& cpu) {}
static void Op_ADD_A_D(CPU& cpu) {}
static void Op_ADD_A_E(CPU& cpu) {}
static void Op_ADD_A_H(CPU& cpu) {}
static void Op_ADD_A_L(CPU& cpu) {}
static void Op_ADD_A_pHL(CPU& cpu) {}

/** ADC A,r8 ********************************************************************************************************/
static void Op_ADC_A_A(CPU& cpu) {}
static void Op_ADC_A_B(CPU& cpu) {}
static void Op_ADC_A_C(CPU& cpu) {}
static void Op_ADC_A_D(CPU& cpu) {}
static void Op_ADC_A_E(CPU& cpu) {}
static void Op_ADC_A_H(CPU& cpu) {}
static void Op_ADC_A_L(CPU& cpu) {}
static void Op_ADC_A_pHL(CPU& cpu) {}

/** SUB A,r8 ********************************************************************************************************/
static void Op_SUB_A_A(CPU& cpu) {}
static void Op_SUB_A_B(CPU& cpu) {}
static void Op_SUB_A_C(CPU& cpu) {}
static void Op_SUB_A_D(CPU& cpu) {}
static void Op_SUB_A_E(CPU& cpu) {}
static void Op_SUB_A_H(CPU& cpu) {}
static void Op_SUB_A_L(CPU& cpu) {}
static void Op_SUB_A_pHL(CPU& cpu) {}

/** SBC A,r8 ********************************************************************************************************/
static void Op_SBC_A_A(CPU& cpu) {}
static void Op_SBC_A_B(CPU& cpu) {}
static void Op_SBC_A_C(CPU& cpu) {}
static void Op_SBC_A_D(CPU& cpu) {}
static void Op_SBC_A_E(CPU& cpu) {}
static void Op_SBC_A_H(CPU& cpu) {}
static void Op_SBC_A_L(CPU& cpu) {}
static void Op_SBC_A_pHL(CPU& cpu) {}

/** AND A,r8 ********************************************************************************************************/
static void Op_AND_A_A(CPU& cpu) {}
static void Op_AND_A_B(CPU& cpu) {}
static void Op_AND_A_C(CPU& cpu) {}
static void Op_AND_A_D(CPU& cpu) {}
static void Op_AND_A_E(CPU& cpu) {}
static void Op_AND_A_H(CPU& cpu) {}
static void Op_AND_A_L(CPU& cpu) {}
static void Op_AND_A_pHL(CPU& cpu) {}

/** XOR A,r8 ********************************************************************************************************/
static void Op_XOR_A_A(CPU& cpu) {}
static void Op_XOR_A_B(CPU& cpu) {}
static void Op_XOR_A_C(CPU& cpu) {}
static void Op_XOR_A_D(CPU& cpu) {}
static void Op_XOR_A_E(CPU& cpu) {}
static void Op_XOR_A_H(CPU& cpu) {}
static void Op_XOR_A_L(CPU& cpu) {}
static void Op_XOR_A_pHL(CPU& cpu) {}

/** OR A,r8 *********************************************************************************************************/
static void Op_OR_A_A(CPU& cpu) {}
static void Op_OR_A_B(CPU& cpu) {}
static void Op_OR_A_C(CPU& cpu) {}
static void Op_OR_A_D(CPU& cpu) {}
static void Op_OR_A_E(CPU& cpu) {}
static void Op_OR_A_H(CPU& cpu) {}
static void Op_OR_A_L(CPU& cpu) {}
static void Op_OR_A_pHL(CPU& cpu) {}

/** CP A,r8 ********************************************************************************************************/
static void Op_CP_A_A(CPU& cpu) {}
static void Op_CP_A_B(CPU& cpu) {}
static void Op_CP_A_C(CPU& cpu) {}
static void Op_CP_A_D(CPU& cpu) {}
static void Op_CP_A_E(CPU& cpu) {}
static void Op_CP_A_H(CPU& cpu) {}
static void Op_CP_A_L(CPU& cpu) {}
static void Op_CP_A_pHL(CPU& cpu) {}

/** ADD A,n8 ********************************************************************************************************/
static void Op_ADD_A_n8(CPU& cpu) {}

/** ADC A,n8 ********************************************************************************************************/
static void Op_ADC_A_n8(CPU& cpu) {}

/** SUB A,n8 ********************************************************************************************************/
static void Op_SUB_A_n8(CPU& cpu) {}

/** SBC A,n8 ********************************************************************************************************/
static void Op_SBC_A_n8(CPU& cpu) {}

/** AND A,n8 ********************************************************************************************************/
static void Op_AND_A_n8(CPU& cpu) {}

/** XOR A,n8 ********************************************************************************************************/
static void Op_XOR_A_n8(CPU& cpu) {}

/** OR A,n8 *********************************************************************************************************/
static void Op_OR_A_n8(CPU& cpu) {}

/** CP A,n8 *********************************************************************************************************/
static void Op_CP_A_n8(CPU& cpu) {}

/** RET cc ***********************************************************************************************************/
static void Op_RET_NZ(CPU& cpu) {}
static void Op_RET_Z(CPU& cpu) {}
static void Op_RET_NC(CPU& cpu) {}
static void Op_RET_C(CPU& cpu) {}

/** RET **************************************************************************************************************/
static void Op_RET(CPU& cpu) {}

/** RETI *************************************************************************************************************/
static void Op_RETI(CPU& cpu) {}

/** JP cc,n16 ********************************************************************************************************/
static void Op_JP_NZ_n16(CPU& cpu) {}
static void Op_JP_Z_n16(CPU& cpu) {}
static void Op_JP_NC_n16(CPU& cpu) {}
static void Op_JP_C_n16(CPU& cpu) {}

/** JP n16 ***********************************************************************************************************/
static void Op_JP_n16(CPU& cpu) {}

/** JP HL ************************************************************************************************************/
static void Op_JP_HL(CPU& cpu) {}

/** CALL cc,n16 ******************************************************************************************************/
static void Op_CALL_NZ_n16(CPU& cpu) {}
static void Op_CALL_Z_n16(CPU& cpu) {}
static void Op_CALL_NC_n16(CPU& cpu) {}
static void Op_CALL_C_n16(CPU& cpu) {}

/** CALL n16 *********************************************************************************************************/
static void Op_CALL_n16(CPU& cpu) {}

/** RST vec **********************************************************************************************************/
static void Op_RST_00H(CPU& cpu) {}
static void Op_RST_08H(CPU& cpu) {}
static void Op_RST_10H(CPU& cpu) {}
static void Op_RST_18H(CPU& cpu) {}
static void Op_RST_20H(CPU& cpu) {}
static void Op_RST_28H(CPU& cpu) {}
static void Op_RST_30H(CPU& cpu) {}
static void Op_RST_38H(CPU& cpu) {}

/** POP r16 **********************************************************************************************************/
static void Op_POP_AF(CPU& cpu) {}
static void Op_POP_BC(CPU& cpu) {}
static void Op_POP_DE(CPU& cpu) {}
static void Op_POP_HL(CPU& cpu) {}

/** PUSH r16 *********************************************************************************************************/
static void Op_PUSH_AF(CPU& cpu) {}
static void Op_PUSH_BC(CPU& cpu) {}
static void Op_PUSH_DE(CPU& cpu) {}
static void Op_PUSH_HL(CPU& cpu) {}

/** LDH [C],A ********************************************************************************************************/
static void Op_LDH_pC_A(CPU& cpu) {}

/** LDH [n8],A *******************************************************************************************************/
static void Op_LDH_pn8_A(CPU& cpu) {}

/** LDH [n16],A ******************************************************************************************************/
static void Op_LD_pn16_A(CPU& cpu) {}

/** LDH [C],A ********************************************************************************************************/
static void Op_LDH_A_pC(CPU& cpu) {}

/** LDH A,[n8] *******************************************************************************************************/
static void Op_LDH_A_pn8(CPU& cpu) {}

/** LDH A,[n16] ******************************************************************************************************/
static void Op_LD_A_pn16(CPU& cpu) {}

/** ADD SP,e8 ********************************************************************************************************/
static void Op_ADD_SP_e8(CPU& cpu) {}

/** LD HL,SP+e8 ******************************************************************************************************/
static void Op_LD_HL_SP_plus_e8(CPU& cpu) {}

/** LD SP,HL *********************************************************************************************************/
static void Op_LD_SP_HL(CPU& cpu) {}

/** DI ***************************************************************************************************************/
static void Op_DI(CPU& cpu) {}

/** EI ***************************************************************************************************************/
static void Op_EI(CPU& cpu) {}

/** Prefix ***************************************************************************************************************/
void Op_Handle_CB(CPU& cpu) {}

/** Invalid ***************************************************************************************************************/
void Op_Invalid(CPU& cpu) {}

#endif  // __OPCODES_H__