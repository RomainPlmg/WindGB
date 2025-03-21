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
    cpu.AddCycles(3);
}
static void Op_LD_DE_n16(CPU& cpu) {  // LD DE, n16
    uint16_t value = cpu.Fetch16();
    cpu.GetRegisters()->DE = value;
    cpu.AddCycles(3);
}
static void Op_LD_HL_n16(CPU& cpu) {  // LD HL, n16
    uint16_t value = cpu.Fetch16();
    cpu.GetRegisters()->HL = value;
    cpu.AddCycles(3);
}
static void Op_LD_SP_n16(CPU& cpu) {  // LD SP, n16
    uint16_t value = cpu.Fetch16();
    cpu.GetRegisters()->SP = value;
    cpu.AddCycles(3);
}

/** LD [r16],A *******************************************************************************************************/
static void Op_LD_pBC_A(CPU& cpu) {  // LD [BC], A
    uint8_t data = cpu.GetRegisters()->A;
    uint16_t addr = cpu.GetRegisters()->BC;
    cpu.GetRAM().Write(addr, data);
    cpu.AddCycles(2);
}
static void Op_LD_pDE_A(CPU& cpu) {  // LD [DE], A
    uint8_t data = cpu.GetRegisters()->A;
    uint16_t addr = cpu.GetRegisters()->DE;
    cpu.GetRAM().Write(addr, data);
    cpu.AddCycles(2);
}
static void Op_LD_pHL_plus_A(CPU& cpu) {  // LD [HL+], A
    uint8_t data = cpu.GetRegisters()->A;
    uint16_t addr = cpu.GetRegisters()->HL++;
    cpu.GetRAM().Write(addr, data);
    cpu.AddCycles(2);
}
static void Op_LD_pHL_minus_A(CPU& cpu) {  // LD [HL-], A
    uint8_t data = cpu.GetRegisters()->A;
    uint16_t addr = cpu.GetRegisters()->HL--;
    cpu.GetRAM().Write(addr, data);
    cpu.AddCycles(2);
}

/** INC r16 **********************************************************************************************************/
static void Op_INC_BC(CPU& cpu) {  // INC BC
    cpu.GetRegisters()->BC++;
    cpu.AddCycles(2);
}
static void Op_INC_DE(CPU& cpu) {  // INC DE
    cpu.GetRegisters()->DE++;
    cpu.AddCycles(2);
}
static void Op_INC_HL(CPU& cpu) {  // INC HL
    cpu.GetRegisters()->HL++;
    cpu.AddCycles(2);
}
static void Op_INC_SP(CPU& cpu) {  // INC SP
    cpu.GetRegisters()->SP++;
    cpu.AddCycles(2);
}

/** INC r8 ***********************************************************************************************************/
static void Op_INC_A(CPU& cpu) {  // INC A
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->A + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->A & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->A = result;
    cpu.AddCycles(1);
}
static void Op_INC_B(CPU& cpu) {  // INC B
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->B + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->B & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->B = result;
    cpu.AddCycles(1);
}
static void Op_INC_C(CPU& cpu) {  // INC C
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->C + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->C & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->C = result;
    cpu.AddCycles(1);
}
static void Op_INC_D(CPU& cpu) {  // INC D
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->D + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->D & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->D = result;
    cpu.AddCycles(1);
}
static void Op_INC_E(CPU& cpu) {  // INC E
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->E + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->E & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->E = result;
    cpu.AddCycles(1);
}
static void Op_INC_H(CPU& cpu) {  // INC H
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->H + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->H & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->H = result;
    cpu.AddCycles(1);
}
static void Op_INC_L(CPU& cpu) {  // INC L
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->L + 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::FlagBits::H, (reg->L & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->L = result;
    cpu.AddCycles(1);
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

    cpu.AddCycles(3);
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

    cpu.AddCycles(1);
}
static void Op_DEC_B(CPU& cpu) {  // DEC B
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->B - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->B & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->B = result;

    cpu.AddCycles(1);
}
static void Op_DEC_C(CPU& cpu) {  // DEC C
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->C - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->C & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->C = result;

    cpu.AddCycles(1);
}
static void Op_DEC_D(CPU& cpu) {  // DEC D
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->D - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->D & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->D = result;

    cpu.AddCycles(1);
}
static void Op_DEC_E(CPU& cpu) {  // DEC E
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->E - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->E & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->E = result;

    cpu.AddCycles(1);
}
static void Op_DEC_H(CPU& cpu) {  // DEC H
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->H - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->H & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->H = result;

    cpu.AddCycles(1);
}
static void Op_DEC_L(CPU& cpu) {  // DEC L
    Registers* reg = cpu.GetRegisters();

    uint8_t result = reg->L - 1;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::FlagBits::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::FlagBits::H, (reg->L & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->L = result;

    cpu.AddCycles(1);
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

    cpu.AddCycles(3);
}

/** LD r8,n8 *********************************************************************************************************/
static void Op_LD_A_n8(CPU& cpu) {  // LD A, n8
    uint8_t value = cpu.Fetch8();
    cpu.GetRegisters()->A = value;

    cpu.AddCycles(2);
}
static void Op_LD_B_n8(CPU& cpu) {  // LD B, n8
    uint8_t value = cpu.Fetch8();
    cpu.GetRegisters()->B = value;

    cpu.AddCycles(2);
}
static void Op_LD_C_n8(CPU& cpu) {  // LD C, n8
    uint8_t value = cpu.Fetch8();
    cpu.GetRegisters()->C = value;

    cpu.AddCycles(2);
}
static void Op_LD_D_n8(CPU& cpu) {  // LD D, n8
    uint8_t value = cpu.Fetch8();
    cpu.GetRegisters()->D = value;

    cpu.AddCycles(2);
}
static void Op_LD_E_n8(CPU& cpu) {  // LD E, n8
    uint8_t value = cpu.Fetch8();
    cpu.GetRegisters()->E = value;

    cpu.AddCycles(2);
}
static void Op_LD_H_n8(CPU& cpu) {  // LD H, n8
    uint8_t value = cpu.Fetch8();
    cpu.GetRegisters()->H = value;

    cpu.AddCycles(2);
}
static void Op_LD_L_n8(CPU& cpu) {  // LD L, n8
    uint8_t value = cpu.Fetch8();
    cpu.GetRegisters()->L = value;

    cpu.AddCycles(2);
}
static void Op_LD_pHL_n8(CPU& cpu) {  // LD [HL], n8
    uint8_t value = cpu.Fetch8();
    uint16_t addr = cpu.GetRegisters()->HL;
    cpu.GetRAM().Write(addr, value);

    cpu.AddCycles(3);
}

/** RLCA *************************************************************************************************************/
static void Op_RLCA(CPU& cpu) {  // RLCA
    Registers* reg = cpu.GetRegisters();
    uint8_t& regA = reg->A;
    uint8_t carry = (reg->A & 0x80) >> 7;

    regA = (regA << 1) | carry;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, false);
    reg->SetFlag(Registers::FlagBits::N, false);
    reg->SetFlag(Registers::FlagBits::H, false);
    reg->SetFlag(Registers::FlagBits::C, carry);

    cpu.AddCycles(1);
}

/** LD [n16],SP ******************************************************************************************************/
static void Op_LD_pn16_SP(CPU& cpu) {  // LD [n16], SP
    uint16_t addr = cpu.Fetch16();
    uint16_t regSP = cpu.GetRegisters()->SP;

    cpu.GetRAM().Write(addr, regSP & 0xFF);
    cpu.GetRAM().Write(addr + 1, regSP >> 8);

    cpu.AddCycles(5);
}

/** ADD HL,r16 *******************************************************************************************************/
static void Op_ADD_HL_BC(CPU& cpu) {  // ADD HL, BC
    Registers* reg = cpu.GetRegisters();
    uint16_t regHL = reg->HL;
    uint16_t regBC = reg->BC;

    uint32_t result = regHL + regBC;  // uint32_t to detect overflow
    reg->HL = result & 0xFFFF;        // Keep only the fist 16 bits

    // Set flags
    reg->SetFlag(Registers::FlagBits::N, false);
    reg->SetFlag(Registers::FlagBits::H, ((regHL & 0xFFF) + (regBC & 0xFFF)) > 0xFFF);  // Half-carry if overflow on 11 bits
    reg->SetFlag(Registers::FlagBits::C, result > 0xFFFF);                              // Carry if overflow on 16 bits

    cpu.AddCycles(2);
}
static void Op_ADD_HL_DE(CPU& cpu) {  // ADD HL, DE
    Registers* reg = cpu.GetRegisters();
    uint16_t regHL = reg->HL;
    uint16_t regDE = reg->DE;

    uint32_t result = regHL + regDE;  // uint32_t to detect overflow
    reg->HL = result & 0xFFFF;        // Keep only the fist 16 bits

    // Set flags
    reg->SetFlag(Registers::FlagBits::N, false);
    reg->SetFlag(Registers::FlagBits::H, ((regHL & 0xFFF) + (regDE & 0xFFF)) > 0xFFF);  // Half-carry if overflow on 11 bits
    reg->SetFlag(Registers::FlagBits::C, result > 0xFFFF);                              // Carry if overflow on 16 bits

    cpu.AddCycles(2);
}
static void Op_ADD_HL_HL(CPU& cpu) {  // ADD HL, HL
    Registers* reg = cpu.GetRegisters();
    uint16_t regHL = reg->HL;

    uint32_t result = regHL + regHL;  // uint32_t to detect overflow
    reg->HL = result & 0xFFFF;        // Keep only the fist 16 bits

    // Set flags
    reg->SetFlag(Registers::FlagBits::N, false);
    reg->SetFlag(Registers::FlagBits::H, ((regHL & 0xFFF) + (regHL & 0xFFF)) > 0xFFF);  // Half-carry if overflow on 11 bits
    reg->SetFlag(Registers::FlagBits::C, result > 0xFFFF);                              // Carry if overflow on 16 bits

    cpu.AddCycles(2);
}
static void Op_ADD_HL_SP(CPU& cpu) {  // ADD HL, DE
    Registers* reg = cpu.GetRegisters();
    uint16_t regHL = reg->HL;
    uint16_t regSP = reg->SP;

    uint32_t result = regHL + regSP;  // uint32_t to detect overflow
    reg->HL = result & 0xFFFF;        // Keep only the fist 16 bits

    // Set flags
    reg->SetFlag(Registers::FlagBits::N, false);
    reg->SetFlag(Registers::FlagBits::H, ((regHL & 0xFFF) + (regSP & 0xFFF)) > 0xFFF);  // Half-carry if overflow on 11 bits
    reg->SetFlag(Registers::FlagBits::C, result > 0xFFFF);                              // Carry if overflow on 16 bits

    cpu.AddCycles(2);
}

/** LD A,[r16] *******************************************************************************************************/
static void Op_LD_A_pBC(CPU& cpu) {  // LD A, [BC]
    Registers* reg = cpu.GetRegisters();
    uint16_t addr = reg->BC;
    uint8_t value = cpu.GetRAM().Read(addr);
    reg->A = value;

    cpu.AddCycles(2);
}
static void Op_LD_A_pDE(CPU& cpu) {  // LD A, [DE]
    Registers* reg = cpu.GetRegisters();
    uint16_t addr = reg->DE;
    uint8_t value = cpu.GetRAM().Read(addr);
    reg->A = value;

    cpu.AddCycles(2);
}
static void Op_LD_A_pHL_plus(CPU& cpu) {  // LD A, [HL+]
    Registers* reg = cpu.GetRegisters();
    uint16_t addr = reg->HL++;
    uint8_t value = cpu.GetRAM().Read(addr);
    reg->A = value;

    cpu.AddCycles(2);
}
static void Op_LD_A_pHL_minus(CPU& cpu) {  // LD A, [HL-]
    Registers* reg = cpu.GetRegisters();
    uint16_t addr = reg->HL--;
    uint8_t value = cpu.GetRAM().Read(addr);
    reg->A = value;

    cpu.AddCycles(2);
}

/** DEC r16 **********************************************************************************************************/
static void Op_DEC_BC(CPU& cpu) {  // DEC BC
    cpu.GetRegisters()->BC--;
    cpu.AddCycles(2);
}
static void Op_DEC_DE(CPU& cpu) {  // DEC DE
    cpu.GetRegisters()->DE--;
    cpu.AddCycles(2);
}
static void Op_DEC_HL(CPU& cpu) {  // DEC HL
    cpu.GetRegisters()->HL--;
    cpu.AddCycles(2);
}
static void Op_DEC_SP(CPU& cpu) {  // DEC SP
    cpu.GetRegisters()->SP--;
    cpu.AddCycles(2);
}

/** RRCA *************************************************************************************************************/
static void Op_RRCA(CPU& cpu) {  // RRCA
    Registers* reg = cpu.GetRegisters();
    uint8_t carry = reg->A & 0x01;

    reg->A = (reg->A >> 1) | (carry << 7);

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, false);
    reg->SetFlag(Registers::FlagBits::N, false);
    reg->SetFlag(Registers::FlagBits::H, false);
    reg->SetFlag(Registers::FlagBits::C, carry);

    cpu.AddCycles(1);
}

/** STOP *************************************************************************************************************/
static void Op_STOP(CPU& cpu) {}

/** RLA **************************************************************************************************************/
static void Op_RLA(CPU& cpu) {  // RLA
    Registers* reg = cpu.GetRegisters();
    uint8_t oldCarry = reg->GetFlag(Registers::FlagBits::C) ? 1 : 0;
    uint8_t newCarry = (reg->A & 0x80) >> 7;
    reg->A = reg->A << 1 | oldCarry;

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, false);
    reg->SetFlag(Registers::FlagBits::N, false);
    reg->SetFlag(Registers::FlagBits::H, false);
    reg->SetFlag(Registers::FlagBits::C, newCarry);

    cpu.AddCycles(1);
}

/** JR n8 ************************************************************************************************************/
static void Op_JR_e8(CPU& cpu) {  // JR e8
    int8_t value = static_cast<int8_t>(cpu.Fetch8());
    cpu.GetRegisters()->PC += value;

    cpu.AddCycles(3);
}

/** RRA **************************************************************************************************************/
static void Op_RRA(CPU& cpu) {  // RRA
    Registers* reg = cpu.GetRegisters();
    uint8_t oldCarry = reg->GetFlag(Registers::FlagBits::C) ? 1 : 0;
    uint8_t newCarry = reg->A & 0x01;
    reg->A = reg->A >> 1 | (oldCarry << 7);

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, false);
    reg->SetFlag(Registers::FlagBits::N, false);
    reg->SetFlag(Registers::FlagBits::H, false);
    reg->SetFlag(Registers::FlagBits::C, newCarry);

    cpu.AddCycles(1);
}

/** JR cc,n8 *********************************************************************************************************/
static void Op_JR_NZ_e8(CPU& cpu) {  // JR NZ, e8
    Registers* reg = cpu.GetRegisters();
    int8_t value = static_cast<int8_t>(cpu.Fetch8());
    if (!reg->GetFlag(Registers::FlagBits::Z)) {
        cpu.GetRegisters()->PC += value;
        cpu.AddCycles(3);
    } else {
        cpu.AddCycles(2);
    }
}
static void Op_JR_Z_e8(CPU& cpu) {  // JR Z, e8
    Registers* reg = cpu.GetRegisters();
    int8_t value = static_cast<int8_t>(cpu.Fetch8());
    if (reg->GetFlag(Registers::FlagBits::Z)) {
        cpu.GetRegisters()->PC += value;
        cpu.AddCycles(3);
    } else {
        cpu.AddCycles(2);
    }
}
static void Op_JR_NC_e8(CPU& cpu) {  // JR NC, e8
    Registers* reg = cpu.GetRegisters();
    int8_t value = static_cast<int8_t>(cpu.Fetch8());
    if (!reg->GetFlag(Registers::FlagBits::C)) {
        cpu.GetRegisters()->PC += value;
        cpu.AddCycles(3);
    } else {
        cpu.AddCycles(2);
    }
}
static void Op_JR_C_e8(CPU& cpu) {  // JR NC, e8
    Registers* reg = cpu.GetRegisters();
    int8_t value = static_cast<int8_t>(cpu.Fetch8());
    if (reg->GetFlag(Registers::FlagBits::C)) {
        cpu.GetRegisters()->PC += value;
        cpu.AddCycles(3);
    } else {
        cpu.AddCycles(2);
    }
}

/** DAA **************************************************************************************************************/
static void Op_DAA(CPU& cpu) {  // DAA
    Registers* reg = cpu.GetRegisters();
    uint8_t adjustment = 0;
    bool setC = false;
    if (reg->GetFlag(Registers::FlagBits::N)) {
        if (reg->GetFlag(Registers::FlagBits::H)) adjustment += 0x06;
        if (reg->GetFlag(Registers::FlagBits::C)) {
            adjustment += 0x60;
            setC = true;
        }
        reg->A -= adjustment;
    } else {
        if (reg->GetFlag(Registers::FlagBits::H) || reg->A & 0x0F > 0x09) adjustment += 0x06;
        if (reg->GetFlag(Registers::FlagBits::C) || reg->A > 0x99) {
            adjustment += 0x60;
            setC = true;
        }
        reg->A += adjustment;
    }

    // Set flags
    reg->SetFlag(Registers::FlagBits::Z, reg->A == 0);
    reg->SetFlag(Registers::FlagBits::H, false);
    reg->SetFlag(Registers::FlagBits::C, setC);

    cpu.AddCycles(1);
}

/** CPL **************************************************************************************************************/
static void Op_CPL(CPU& cpu) {  // CPL
    Registers* reg = cpu.GetRegisters();
    reg->A = ~reg->A;

    cpu.AddCycles(1);
}

/** SCF **************************************************************************************************************/
static void Op_SCF(CPU& cpu) {  // SCF
    Registers* reg = cpu.GetRegisters();

    // Set flags
    reg->SetFlag(Registers::FlagBits::N, false);
    reg->SetFlag(Registers::FlagBits::H, false);
    reg->SetFlag(Registers::FlagBits::C, true);

    cpu.AddCycles(1);
}

/** CCF **************************************************************************************************************/
static void Op_CCF(CPU& cpu) {  // CCF
    Registers* reg = cpu.GetRegisters();

    bool cFlag = reg->GetFlag(Registers::FlagBits::C) ? false : true;

    // Set flags
    reg->SetFlag(Registers::FlagBits::N, false);
    reg->SetFlag(Registers::FlagBits::H, false);
    reg->SetFlag(Registers::FlagBits::C, cFlag);

    cpu.AddCycles(1);
}

/** LD r8,r8 *********************************************************************************************************/
static void Op_LD_A_A(CPU& cpu) {  // LD A, A
    cpu.AddCycles(1);
}
static void Op_LD_A_B(CPU& cpu) {  // LD A, B
    Registers* reg = cpu.GetRegisters();
    reg->A = reg->B;
    cpu.AddCycles(1);
}
static void Op_LD_A_C(CPU& cpu) {  // LD A, C
    Registers* reg = cpu.GetRegisters();
    reg->A = reg->C;
    cpu.AddCycles(1);
}
static void Op_LD_A_D(CPU& cpu) {  // LD A, D
    Registers* reg = cpu.GetRegisters();
    reg->A = reg->D;
    cpu.AddCycles(1);
}
static void Op_LD_A_E(CPU& cpu) {  // LD A, E
    Registers* reg = cpu.GetRegisters();
    reg->A = reg->E;
    cpu.AddCycles(1);
}
static void Op_LD_A_H(CPU& cpu) {  // LD A, H
    Registers* reg = cpu.GetRegisters();
    reg->A = reg->H;
    cpu.AddCycles(1);
}
static void Op_LD_A_L(CPU& cpu) {  // LD A, L
    Registers* reg = cpu.GetRegisters();
    reg->A = reg->L;
    cpu.AddCycles(1);
}
static void Op_LD_A_pHL(CPU& cpu) {  // LD A, [HL]
    Registers* reg = cpu.GetRegisters();
    uint8_t value = cpu.GetRAM().Read(reg->HL);
    reg->A = value;
    cpu.AddCycles(1);
}

static void Op_LD_B_A(CPU& cpu) {  // LD B, A
    Registers* reg = cpu.GetRegisters();
    reg->B = reg->A;
    cpu.AddCycles(1);
}
static void Op_LD_B_B(CPU& cpu) {  // LD B, B
    cpu.AddCycles(1);
}
static void Op_LD_B_C(CPU& cpu) {  // LD B, C
    Registers* reg = cpu.GetRegisters();
    reg->B = reg->C;
    cpu.AddCycles(1);
}
static void Op_LD_B_D(CPU& cpu) {  // LD B, D
    Registers* reg = cpu.GetRegisters();
    reg->B = reg->D;
    cpu.AddCycles(1);
}
static void Op_LD_B_E(CPU& cpu) {  // LD B, E
    Registers* reg = cpu.GetRegisters();
    reg->B = reg->E;
    cpu.AddCycles(1);
}
static void Op_LD_B_H(CPU& cpu) {  // LD B, H
    Registers* reg = cpu.GetRegisters();
    reg->B = reg->H;
    cpu.AddCycles(1);
}
static void Op_LD_B_L(CPU& cpu) {
    // LD B, A
    Registers* reg = cpu.GetRegisters();
    reg->B = reg->L;
    cpu.AddCycles(1);
}
static void Op_LD_B_pHL(CPU& cpu) {  // LD B, [HL]
    Registers* reg = cpu.GetRegisters();
    uint8_t value = cpu.GetRAM().Read(reg->HL);
    reg->B = value;
    cpu.AddCycles(1);
}

static void Op_LD_C_A(CPU& cpu) {  // LD C, A
    Registers* reg = cpu.GetRegisters();
    reg->C = reg->A;
    cpu.AddCycles(1);
}
static void Op_LD_C_B(CPU& cpu) {  // LD C, B
    Registers* reg = cpu.GetRegisters();
    reg->C = reg->B;
    cpu.AddCycles(1);
}
static void Op_LD_C_C(CPU& cpu) {  // LD C, C
    cpu.AddCycles(1);
}
static void Op_LD_C_D(CPU& cpu) {  // LD C, D
    Registers* reg = cpu.GetRegisters();
    reg->C = reg->D;
    cpu.AddCycles(1);
}
static void Op_LD_C_E(CPU& cpu) {  // LD C, E
    Registers* reg = cpu.GetRegisters();
    reg->C = reg->E;
    cpu.AddCycles(1);
}
static void Op_LD_C_H(CPU& cpu) {  // LD C, H
    Registers* reg = cpu.GetRegisters();
    reg->C = reg->H;
    cpu.AddCycles(1);
}
static void Op_LD_C_L(CPU& cpu) {  // LD C, L
    Registers* reg = cpu.GetRegisters();
    reg->C = reg->L;
    cpu.AddCycles(1);
}
static void Op_LD_C_pHL(CPU& cpu) {  // LD C, [HL]
    Registers* reg = cpu.GetRegisters();
    uint8_t value = cpu.GetRAM().Read(reg->HL);
    reg->C = value;
    cpu.AddCycles(1);
}

static void Op_LD_D_A(CPU& cpu) {}
static void Op_LD_D_B(CPU& cpu) {}
static void Op_LD_D_C(CPU& cpu) {}
static void Op_LD_D_D(CPU& cpu) { cpu.AddCycles(1); }
static void Op_LD_D_E(CPU& cpu) {}
static void Op_LD_D_H(CPU& cpu) {}
static void Op_LD_D_L(CPU& cpu) {}
static void Op_LD_D_pHL(CPU& cpu) {  // LD D, [HL]
    Registers* reg = cpu.GetRegisters();
    uint8_t value = cpu.GetRAM().Read(reg->HL);
    reg->D = value;
    cpu.AddCycles(1);
}

static void Op_LD_E_A(CPU& cpu) {}
static void Op_LD_E_B(CPU& cpu) {}
static void Op_LD_E_C(CPU& cpu) {}
static void Op_LD_E_D(CPU& cpu) {}
static void Op_LD_E_E(CPU& cpu) { cpu.AddCycles(1); }
static void Op_LD_E_H(CPU& cpu) {}
static void Op_LD_E_L(CPU& cpu) {}
static void Op_LD_E_pHL(CPU& cpu) {  // LD E, [HL]
    Registers* reg = cpu.GetRegisters();
    uint8_t value = cpu.GetRAM().Read(reg->HL);
    reg->E = value;
    cpu.AddCycles(1);
}

static void Op_LD_H_A(CPU& cpu) {}
static void Op_LD_H_B(CPU& cpu) {}
static void Op_LD_H_C(CPU& cpu) {}
static void Op_LD_H_D(CPU& cpu) {}
static void Op_LD_H_E(CPU& cpu) {}
static void Op_LD_H_H(CPU& cpu) { cpu.AddCycles(1); }
static void Op_LD_H_L(CPU& cpu) {}
static void Op_LD_H_pHL(CPU& cpu) {  // LD H, [HL]
    Registers* reg = cpu.GetRegisters();
    uint8_t value = cpu.GetRAM().Read(reg->HL);
    reg->H = value;
    cpu.AddCycles(1);
}

static void Op_LD_L_A(CPU& cpu) {}
static void Op_LD_L_B(CPU& cpu) {}
static void Op_LD_L_C(CPU& cpu) {}
static void Op_LD_L_D(CPU& cpu) {}
static void Op_LD_L_E(CPU& cpu) {}
static void Op_LD_L_H(CPU& cpu) {}
static void Op_LD_L_L(CPU& cpu) { cpu.AddCycles(1); }
static void Op_LD_L_pHL(CPU& cpu) {  // LD L, [HL]
    Registers* reg = cpu.GetRegisters();
    uint8_t value = cpu.GetRAM().Read(reg->HL);
    reg->L = value;
    cpu.AddCycles(1);
}

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
static void Op_Handle_CB(CPU& cpu) {}

/** Invalid ***************************************************************************************************************/
static void Op_Invalid(CPU& cpu) {}

#endif  // __OPCODES_H__