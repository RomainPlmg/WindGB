#pragma once

#include <string>

#include "bus.h"
#include "cpu.h"
#include "registers.h"
#include "utils/common.h"
#include "utils/log.h"

using InstructionFunc = void (*)(CPU&, Bus&);  // Callback, takes CPU reference and return static void

struct Instruction {
    std::string name;
    InstructionFunc Execute;
};

// Declaration of the opcodes table
extern std::array<Instruction, 256> InstructionTable;
extern std::array<Instruction, 256> PrefixInstructionTable;

static void In_Nop(CPU& cpu, Bus& memBus) { return; }  // Nop

/** LD r16,n16 *******************************************************************************************************/
static void In_LD_BC_n16(CPU& cpu, Bus& memBus) {  // LD BC, n16
    u16 value = cpu.Fetch16();
    cpu.GetRegisters()->BC = value;
    cpu.AddCycles(3);
}
static void In_LD_DE_n16(CPU& cpu, Bus& memBus) {  // LD DE, n16
    u16 value = cpu.Fetch16();
    cpu.GetRegisters()->DE = value;
    cpu.AddCycles(3);
}
static void In_LD_HL_n16(CPU& cpu, Bus& memBus) {  // LD HL, n16
    u16 value = cpu.Fetch16();
    cpu.GetRegisters()->HL = value;
    cpu.AddCycles(3);
}
static void In_LD_SP_n16(CPU& cpu, Bus& memBus) {  // LD SP, n16
    u16 value = cpu.Fetch16();
    cpu.GetRegisters()->SP = value;
    cpu.AddCycles(3);
}

/** LD [r16],A *******************************************************************************************************/
static void In_LD_pBC_A(CPU& cpu, Bus& memBus) {  // LD [BC], A
    u8 data = cpu.GetRegisters()->A;
    u16 addr = cpu.GetRegisters()->BC;
    memBus.Write(addr, data);
    cpu.AddCycles(2);
}
static void In_LD_pDE_A(CPU& cpu, Bus& memBus) {  // LD [DE], A
    u8 data = cpu.GetRegisters()->A;
    u16 addr = cpu.GetRegisters()->DE;
    memBus.Write(addr, data);
    cpu.AddCycles(2);
}
static void In_LD_pHL_plus_A(CPU& cpu, Bus& memBus) {  // LD [HL+], A
    u8 data = cpu.GetRegisters()->A;
    u16 addr = cpu.GetRegisters()->HL++;
    memBus.Write(addr, data);
    cpu.AddCycles(2);
}
static void In_LD_pHL_minus_A(CPU& cpu, Bus& memBus) {  // LD [HL-], A
    u8 data = cpu.GetRegisters()->A;
    u16 addr = cpu.GetRegisters()->HL--;
    memBus.Write(addr, data);
    cpu.AddCycles(2);
}

/** INC r16 **********************************************************************************************************/
static void In_INC_BC(CPU& cpu, Bus& memBus) {  // INC BC
    cpu.GetRegisters()->BC++;
    cpu.AddCycles(2);
}
static void In_INC_DE(CPU& cpu, Bus& memBus) {  // INC DE
    cpu.GetRegisters()->DE++;
    cpu.AddCycles(2);
}
static void In_INC_HL(CPU& cpu, Bus& memBus) {  // INC HL
    cpu.GetRegisters()->HL++;
    cpu.AddCycles(2);
}
static void In_INC_SP(CPU& cpu, Bus& memBus) {  // INC SP
    cpu.GetRegisters()->SP++;
    cpu.AddCycles(2);
}

/** INC r8 ***********************************************************************************************************/
static void In_INC_A(CPU& cpu, Bus& memBus) {  // INC A
    Registers* reg = cpu.GetRegisters();

    u8 result = reg->A + 1;

    // Set flags
    reg->SetFlag(Registers::Flag::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::Flag::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::Flag::H, (reg->A & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->A = result;
    cpu.AddCycles(1);
}
static void In_INC_B(CPU& cpu, Bus& memBus) {  // INC B
    Registers* reg = cpu.GetRegisters();

    u8 result = reg->B + 1;

    // Set flags
    reg->SetFlag(Registers::Flag::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::Flag::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::Flag::H, (reg->B & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->B = result;
    cpu.AddCycles(1);
}
static void In_INC_C(CPU& cpu, Bus& memBus) {  // INC C
    Registers* reg = cpu.GetRegisters();

    u8 result = reg->C + 1;

    // Set flags
    reg->SetFlag(Registers::Flag::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::Flag::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::Flag::H, (reg->C & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->C = result;
    cpu.AddCycles(1);
}
static void In_INC_D(CPU& cpu, Bus& memBus) {  // INC D
    Registers* reg = cpu.GetRegisters();

    u8 result = reg->D + 1;

    // Set flags
    reg->SetFlag(Registers::Flag::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::Flag::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::Flag::H, (reg->D & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->D = result;
    cpu.AddCycles(1);
}
static void In_INC_E(CPU& cpu, Bus& memBus) {  // INC E
    Registers* reg = cpu.GetRegisters();

    u8 result = reg->E + 1;

    // Set flags
    reg->SetFlag(Registers::Flag::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::Flag::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::Flag::H, (reg->E & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->E = result;
    cpu.AddCycles(1);
}
static void In_INC_H(CPU& cpu, Bus& memBus) {  // INC H
    Registers* reg = cpu.GetRegisters();

    u8 result = reg->H + 1;

    // Set flags
    reg->SetFlag(Registers::Flag::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::Flag::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::Flag::H, (reg->H & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->H = result;
    cpu.AddCycles(1);
}
static void In_INC_L(CPU& cpu, Bus& memBus) {  // INC L
    Registers* reg = cpu.GetRegisters();

    u8 result = reg->L + 1;

    // Set flags
    reg->SetFlag(Registers::Flag::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::Flag::N, false);                    // N: Always disabled for INC
    reg->SetFlag(Registers::Flag::H, (reg->L & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg->L = result;
    cpu.AddCycles(1);
}
static void In_INC_pHL(CPU& cpu, Bus& memBus) {  // INC [HL]
    // Read the value in memory at address HL
    u16 addr = cpu.GetRegisters()->HL;
    u8 value = memBus.Read(addr);

    // Calculate the new value
    u8 newValue = value + 1;

    // Write the new value to RAM
    memBus.Write(addr, newValue);

    // Update flags
    Registers* reg = cpu.GetRegisters();
    reg->SetFlag(Registers::Flag::Z, newValue == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::Flag::N, false);                      // N: Always disabled for INC
    reg->SetFlag(Registers::Flag::H, (value & 0x0F) + 1 > 0x0F);  // H: Activated if a bit overflow 3->4

    cpu.AddCycles(3);
}

/** DEC r8 ***********************************************************************************************************/
static void In_DEC_A(CPU& cpu, Bus& memBus) {  // DEC A
    Registers* reg = cpu.GetRegisters();

    u8 result = reg->A - 1;

    // Set flags
    reg->SetFlag(Registers::Flag::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::Flag::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::Flag::H, (reg->A & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->A = result;

    cpu.AddCycles(1);
}
static void In_DEC_B(CPU& cpu, Bus& memBus) {  // DEC B
    Registers* reg = cpu.GetRegisters();

    u8 result = reg->B - 1;

    // Set flags
    reg->SetFlag(Registers::Flag::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::Flag::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::Flag::H, (reg->B & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->B = result;

    cpu.AddCycles(1);
}
static void In_DEC_C(CPU& cpu, Bus& memBus) {  // DEC C
    Registers* reg = cpu.GetRegisters();

    u8 result = reg->C - 1;

    // Set flags
    reg->SetFlag(Registers::Flag::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::Flag::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::Flag::H, (reg->C & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->C = result;

    cpu.AddCycles(1);
}
static void In_DEC_D(CPU& cpu, Bus& memBus) {  // DEC D
    Registers* reg = cpu.GetRegisters();

    u8 result = reg->D - 1;

    // Set flags
    reg->SetFlag(Registers::Flag::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::Flag::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::Flag::H, (reg->D & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->D = result;

    cpu.AddCycles(1);
}
static void In_DEC_E(CPU& cpu, Bus& memBus) {  // DEC E
    Registers* reg = cpu.GetRegisters();

    u8 result = reg->E - 1;

    // Set flags
    reg->SetFlag(Registers::Flag::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::Flag::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::Flag::H, (reg->E & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->E = result;

    cpu.AddCycles(1);
}
static void In_DEC_H(CPU& cpu, Bus& memBus) {  // DEC H
    Registers* reg = cpu.GetRegisters();

    u8 result = reg->H - 1;

    // Set flags
    reg->SetFlag(Registers::Flag::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::Flag::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::Flag::H, (reg->H & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->H = result;

    cpu.AddCycles(1);
}
static void In_DEC_L(CPU& cpu, Bus& memBus) {  // DEC L
    Registers* reg = cpu.GetRegisters();

    u8 result = reg->L - 1;

    // Set flags
    reg->SetFlag(Registers::Flag::Z, result == 0);              // Z: Set if the result is 0
    reg->SetFlag(Registers::Flag::N, true);                     // N: Always set for DEC
    reg->SetFlag(Registers::Flag::H, (reg->L & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg->L = result;

    cpu.AddCycles(1);
}
static void In_DEC_pHL(CPU& cpu, Bus& memBus) {  // DEC [HL]
    Registers* reg = cpu.GetRegisters();
    u16 addr = reg->HL;

    u8 value = memBus.Read(addr);
    u8 newValue = value - 1;
    memBus.Write(addr, newValue);

    // Update flags
    reg->SetFlag(Registers::Flag::Z, newValue == 0);           // Z: Set if result == 0
    reg->SetFlag(Registers::Flag::N, true);                    // N: Always set for DEC
    reg->SetFlag(Registers::Flag::H, (value & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    cpu.AddCycles(3);
}

/** LD r8,n8 *********************************************************************************************************/
static void In_LD_A_n8(CPU& cpu, Bus& memBus) {  // LD A, n8
    u8 value = cpu.Fetch8();
    cpu.GetRegisters()->A = value;

    cpu.AddCycles(2);
}
static void In_LD_B_n8(CPU& cpu, Bus& memBus) {  // LD B, n8
    u8 value = cpu.Fetch8();
    cpu.GetRegisters()->B = value;

    cpu.AddCycles(2);
}
static void In_LD_C_n8(CPU& cpu, Bus& memBus) {  // LD C, n8
    u8 value = cpu.Fetch8();
    cpu.GetRegisters()->C = value;

    cpu.AddCycles(2);
}
static void In_LD_D_n8(CPU& cpu, Bus& memBus) {  // LD D, n8
    u8 value = cpu.Fetch8();
    cpu.GetRegisters()->D = value;

    cpu.AddCycles(2);
}
static void In_LD_E_n8(CPU& cpu, Bus& memBus) {  // LD E, n8
    u8 value = cpu.Fetch8();
    cpu.GetRegisters()->E = value;

    cpu.AddCycles(2);
}
static void In_LD_H_n8(CPU& cpu, Bus& memBus) {  // LD H, n8
    u8 value = cpu.Fetch8();
    cpu.GetRegisters()->H = value;

    cpu.AddCycles(2);
}
static void In_LD_L_n8(CPU& cpu, Bus& memBus) {  // LD L, n8
    u8 value = cpu.Fetch8();
    cpu.GetRegisters()->L = value;

    cpu.AddCycles(2);
}
static void In_LD_pHL_n8(CPU& cpu, Bus& memBus) {  // LD [HL], n8
    u8 value = cpu.Fetch8();
    u16 addr = cpu.GetRegisters()->HL;
    memBus.Write(addr, value);

    cpu.AddCycles(3);
}

/** RLCA *************************************************************************************************************/
static void In_RLCA(CPU& cpu, Bus& memBus) {  // RLCA
    Registers* reg = cpu.GetRegisters();
    u8& regA = reg->A;
    u8 carry = (reg->A & 0x80) >> 7;

    regA = (regA << 1) | carry;

    // Set flags
    reg->SetFlag(Registers::Flag::Z, false);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(1);
}

/** LD [n16],SP ******************************************************************************************************/
static void In_LD_pn16_SP(CPU& cpu, Bus& memBus) {  // LD [n16], SP
    u16 addr = cpu.Fetch16();
    u16 regSP = cpu.GetRegisters()->SP;

    memBus.Write(addr, regSP & 0xFF);
    memBus.Write(addr + 1, regSP >> 8);

    cpu.AddCycles(5);
}

/** ADD HL,r16 *******************************************************************************************************/
static void In_ADD_HL_BC(CPU& cpu, Bus& memBus) {  // ADD HL, BC
    Registers* reg = cpu.GetRegisters();
    u16 regHL = reg->HL;
    u16 regBC = reg->BC;

    u32 result = regHL + regBC;  // u32 to detect overflow
    reg->HL = result & 0xFFFF;   // Keep only the fist 16 bits

    // Set flags
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regHL & 0x0FFF) + (regBC & 0x0FFF)) > 0x0FFF);  // Half-carry if overflow on 11 bits
    reg->SetFlag(Registers::Flag::C, result > 0xFFFF);                                 // Carry if overflow on 16 bits

    cpu.AddCycles(2);
}
static void In_ADD_HL_DE(CPU& cpu, Bus& memBus) {  // ADD HL, DE
    Registers* reg = cpu.GetRegisters();
    u16 regHL = reg->HL;
    u16 regDE = reg->DE;

    u32 result = regHL + regDE;  // u32 to detect overflow
    reg->HL = result & 0xFFFF;   // Keep only the fist 16 bits

    // Set flags
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regHL & 0x0FFF) + (regDE & 0x0FFF)) > 0x0FFF);  // Half-carry if overflow on 11 bits
    reg->SetFlag(Registers::Flag::C, result > 0xFFFF);                                 // Carry if overflow on 16 bits

    cpu.AddCycles(2);
}
static void In_ADD_HL_HL(CPU& cpu, Bus& memBus) {  // ADD HL, HL
    Registers* reg = cpu.GetRegisters();
    u16 regHL = reg->HL;

    u32 result = regHL + regHL;  // u32 to detect overflow
    reg->HL = result & 0xFFFF;   // Keep only the fist 16 bits

    // Set flags
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regHL & 0x0FFF) + (regHL & 0x0FFF)) > 0x0FFF);  // Half-carry if overflow on 11 bits
    reg->SetFlag(Registers::Flag::C, result > 0xFFFF);                                 // Carry if overflow on 16 bits

    cpu.AddCycles(2);
}
static void In_ADD_HL_SP(CPU& cpu, Bus& memBus) {  // ADD HL, DE
    Registers* reg = cpu.GetRegisters();
    u16 regHL = reg->HL;
    u16 regSP = reg->SP;

    u32 result = regHL + regSP;  // u32 to detect overflow
    reg->HL = result & 0xFFFF;   // Keep only the fist 16 bits

    // Set flags
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regHL & 0x0FFF) + (regSP & 0x0FFF)) > 0x0FFF);  // Half-carry if overflow on 11 bits
    reg->SetFlag(Registers::Flag::C, result > 0xFFFF);                                 // Carry if overflow on 16 bits

    cpu.AddCycles(2);
}

/** LD A,[r16] *******************************************************************************************************/
static void In_LD_A_pBC(CPU& cpu, Bus& memBus) {  // LD A, [BC]
    Registers* reg = cpu.GetRegisters();
    u16 addr = reg->BC;
    u8 value = memBus.Read(addr);
    reg->A = value;

    cpu.AddCycles(2);
}
static void In_LD_A_pDE(CPU& cpu, Bus& memBus) {  // LD A, [DE]
    Registers* reg = cpu.GetRegisters();
    u16 addr = reg->DE;
    u8 value = memBus.Read(addr);
    reg->A = value;

    cpu.AddCycles(2);
}
static void In_LD_A_pHL_plus(CPU& cpu, Bus& memBus) {  // LD A, [HL+]
    Registers* reg = cpu.GetRegisters();
    u16 addr = reg->HL++;
    u8 value = memBus.Read(addr);
    reg->A = value;

    cpu.AddCycles(2);
}
static void In_LD_A_pHL_minus(CPU& cpu, Bus& memBus) {  // LD A, [HL-]
    Registers* reg = cpu.GetRegisters();
    u16 addr = reg->HL--;
    u8 value = memBus.Read(addr);
    reg->A = value;

    cpu.AddCycles(2);
}

/** DEC r16 **********************************************************************************************************/
static void In_DEC_BC(CPU& cpu, Bus& memBus) {  // DEC BC
    cpu.GetRegisters()->BC--;
    cpu.AddCycles(2);
}
static void In_DEC_DE(CPU& cpu, Bus& memBus) {  // DEC DE
    cpu.GetRegisters()->DE--;
    cpu.AddCycles(2);
}
static void In_DEC_HL(CPU& cpu, Bus& memBus) {  // DEC HL
    cpu.GetRegisters()->HL--;
    cpu.AddCycles(2);
}
static void In_DEC_SP(CPU& cpu, Bus& memBus) {  // DEC SP
    cpu.GetRegisters()->SP--;
    cpu.AddCycles(2);
}

/** RRCA *************************************************************************************************************/
static void In_RRCA(CPU& cpu, Bus& memBus) {  // RRCA
    Registers* reg = cpu.GetRegisters();
    u8 carry = reg->A & 0x01;

    reg->A = (reg->A >> 1) | (carry << 7);

    // Set flags
    reg->SetFlag(Registers::Flag::Z, false);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(1);
}

/** STOP *************************************************************************************************************/
static void In_STOP(CPU& cpu, Bus& memBus) {  // TODO
    // exit(0);
}

/** RLA **************************************************************************************************************/
static void In_RLA(CPU& cpu, Bus& memBus) {  // RLA
    Registers* reg = cpu.GetRegisters();
    u8 oldCarry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u8 newCarry = (reg->A & 0x80) >> 7;
    reg->A = reg->A << 1 | oldCarry;

    // Set flags
    reg->SetFlag(Registers::Flag::Z, false);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, newCarry);

    cpu.AddCycles(1);
}

/** JR n8 ************************************************************************************************************/
static void In_JR_e8(CPU& cpu, Bus& memBus) {  // JR e8
    int8_t value = static_cast<int8_t>(cpu.Fetch8());
    cpu.GetRegisters()->PC += value;

    cpu.AddCycles(3);
}

/** RRA **************************************************************************************************************/
static void In_RRA(CPU& cpu, Bus& memBus) {  // RRA
    Registers* reg = cpu.GetRegisters();
    u8 oldCarry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u8 newCarry = reg->A & 0x01;
    reg->A = reg->A >> 1 | (oldCarry << 7);

    // Set flags
    reg->SetFlag(Registers::Flag::Z, false);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, newCarry);

    cpu.AddCycles(1);
}

/** JR cc,n8 *********************************************************************************************************/
static void In_JR_NZ_e8(CPU& cpu, Bus& memBus) {  // JR NZ, e8
    Registers* reg = cpu.GetRegisters();
    int8_t value = static_cast<int8_t>(cpu.Fetch8());
    int16_t regPC = reg->PC;
    if (!reg->GetFlag(Registers::Flag::Z)) {
        reg->PC = static_cast<u16>(regPC + value);
        cpu.AddCycles(3);
    } else {
        cpu.AddCycles(2);
    }
}
static void In_JR_Z_e8(CPU& cpu, Bus& memBus) {  // JR Z, e8
    Registers* reg = cpu.GetRegisters();
    int8_t value = static_cast<int8_t>(cpu.Fetch8());
    if (reg->GetFlag(Registers::Flag::Z)) {
        reg->PC = static_cast<u16>(reg->PC + value);
        cpu.AddCycles(3);
    } else {
        cpu.AddCycles(2);
    }
}
static void In_JR_NC_e8(CPU& cpu, Bus& memBus) {  // JR NC, e8
    Registers* reg = cpu.GetRegisters();
    int8_t value = static_cast<int8_t>(cpu.Fetch8());
    if (!reg->GetFlag(Registers::Flag::C)) {
        reg->PC = static_cast<u16>(reg->PC + value);
        cpu.AddCycles(3);
    } else {
        cpu.AddCycles(2);
    }
}
static void In_JR_C_e8(CPU& cpu, Bus& memBus) {  // JR NC, e8
    Registers* reg = cpu.GetRegisters();
    int8_t value = static_cast<int8_t>(cpu.Fetch8());
    if (reg->GetFlag(Registers::Flag::C)) {
        reg->PC = static_cast<u16>(reg->PC + value);
        cpu.AddCycles(3);
    } else {
        cpu.AddCycles(2);
    }
}

/** DAA **************************************************************************************************************/
static void In_DAA(CPU& cpu, Bus& memBus) {  // DAA
    Registers* reg = cpu.GetRegisters();
    u8 adjustment = 0;
    bool setC = false;
    if (reg->GetFlag(Registers::Flag::N)) {
        if (reg->GetFlag(Registers::Flag::H)) adjustment += 0x06;
        if (reg->GetFlag(Registers::Flag::C)) {
            adjustment += 0x60;
            setC = true;
        }
        reg->A -= adjustment;
    } else {
        if (reg->GetFlag(Registers::Flag::H) || (reg->A & 0x0F) > 0x09) adjustment += 0x06;
        if (reg->GetFlag(Registers::Flag::C) || reg->A > 0x99) {
            adjustment += 0x60;
            setC = true;
        }
        reg->A += adjustment;
    }

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, setC);

    cpu.AddCycles(1);
}

/** CPL **************************************************************************************************************/
static void In_CPL(CPU& cpu, Bus& memBus) {  // CPL
    Registers* reg = cpu.GetRegisters();
    reg->A = ~reg->A;

    // Set flags
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(1);
}

/** SCF **************************************************************************************************************/
static void In_SCF(CPU& cpu, Bus& memBus) {  // SCF
    Registers* reg = cpu.GetRegisters();

    // Set flags
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, true);

    cpu.AddCycles(1);
}

/** CCF **************************************************************************************************************/
static void In_CCF(CPU& cpu, Bus& memBus) {  // CCF
    Registers* reg = cpu.GetRegisters();

    bool cFlag = reg->GetFlag(Registers::Flag::C) ? false : true;

    // Set flags
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, cFlag);

    cpu.AddCycles(1);
}

/** LD r8,r8 *********************************************************************************************************/
static void In_LD_A_A(CPU& cpu, Bus& memBus) {  // LD A, A
    cpu.AddCycles(1);
}
static void In_LD_A_B(CPU& cpu, Bus& memBus) {  // LD A, B
    Registers* reg = cpu.GetRegisters();
    reg->A = reg->B;
    cpu.AddCycles(1);
}
static void In_LD_A_C(CPU& cpu, Bus& memBus) {  // LD A, C
    Registers* reg = cpu.GetRegisters();
    reg->A = reg->C;
    cpu.AddCycles(1);
}
static void In_LD_A_D(CPU& cpu, Bus& memBus) {  // LD A, D
    Registers* reg = cpu.GetRegisters();
    reg->A = reg->D;
    cpu.AddCycles(1);
}
static void In_LD_A_E(CPU& cpu, Bus& memBus) {  // LD A, E
    Registers* reg = cpu.GetRegisters();
    reg->A = reg->E;
    cpu.AddCycles(1);
}
static void In_LD_A_H(CPU& cpu, Bus& memBus) {  // LD A, H
    Registers* reg = cpu.GetRegisters();
    reg->A = reg->H;
    cpu.AddCycles(1);
}
static void In_LD_A_L(CPU& cpu, Bus& memBus) {  // LD A, L
    Registers* reg = cpu.GetRegisters();
    reg->A = reg->L;
    cpu.AddCycles(1);
}
static void In_LD_A_pHL(CPU& cpu, Bus& memBus) {  // LD A, [HL]
    Registers* reg = cpu.GetRegisters();
    u8 value = memBus.Read(reg->HL);
    reg->A = value;
    cpu.AddCycles(1);
}

static void In_LD_B_A(CPU& cpu, Bus& memBus) {  // LD B, A
    Registers* reg = cpu.GetRegisters();
    reg->B = reg->A;
    cpu.AddCycles(1);
}
static void In_LD_B_B(CPU& cpu, Bus& memBus) {  // LD B, B
    cpu.AddCycles(1);
}
static void In_LD_B_C(CPU& cpu, Bus& memBus) {  // LD B, C
    Registers* reg = cpu.GetRegisters();
    reg->B = reg->C;
    cpu.AddCycles(1);
}
static void In_LD_B_D(CPU& cpu, Bus& memBus) {  // LD B, D
    Registers* reg = cpu.GetRegisters();
    reg->B = reg->D;
    cpu.AddCycles(1);
}
static void In_LD_B_E(CPU& cpu, Bus& memBus) {  // LD B, E
    Registers* reg = cpu.GetRegisters();
    reg->B = reg->E;
    cpu.AddCycles(1);
}
static void In_LD_B_H(CPU& cpu, Bus& memBus) {  // LD B, H
    Registers* reg = cpu.GetRegisters();
    reg->B = reg->H;
    cpu.AddCycles(1);
}
static void In_LD_B_L(CPU& cpu, Bus& memBus) {
    // LD B, A
    Registers* reg = cpu.GetRegisters();
    reg->B = reg->L;
    cpu.AddCycles(1);
}
static void In_LD_B_pHL(CPU& cpu, Bus& memBus) {  // LD B, [HL]
    Registers* reg = cpu.GetRegisters();
    u8 value = memBus.Read(reg->HL);
    reg->B = value;
    cpu.AddCycles(1);
}

static void In_LD_C_A(CPU& cpu, Bus& memBus) {  // LD C, A
    Registers* reg = cpu.GetRegisters();
    reg->C = reg->A;
    cpu.AddCycles(1);
}
static void In_LD_C_B(CPU& cpu, Bus& memBus) {  // LD C, B
    Registers* reg = cpu.GetRegisters();
    reg->C = reg->B;
    cpu.AddCycles(1);
}
static void In_LD_C_C(CPU& cpu, Bus& memBus) {  // LD C, C
    cpu.AddCycles(1);
}
static void In_LD_C_D(CPU& cpu, Bus& memBus) {  // LD C, D
    Registers* reg = cpu.GetRegisters();
    reg->C = reg->D;
    cpu.AddCycles(1);
}
static void In_LD_C_E(CPU& cpu, Bus& memBus) {  // LD C, E
    Registers* reg = cpu.GetRegisters();
    reg->C = reg->E;
    cpu.AddCycles(1);
}
static void In_LD_C_H(CPU& cpu, Bus& memBus) {  // LD C, H
    Registers* reg = cpu.GetRegisters();
    reg->C = reg->H;
    cpu.AddCycles(1);
}
static void In_LD_C_L(CPU& cpu, Bus& memBus) {  // LD C, L
    Registers* reg = cpu.GetRegisters();
    reg->C = reg->L;
    cpu.AddCycles(1);
}
static void In_LD_C_pHL(CPU& cpu, Bus& memBus) {  // LD C, [HL]
    Registers* reg = cpu.GetRegisters();
    u8 value = memBus.Read(reg->HL);
    reg->C = value;
    cpu.AddCycles(1);
}

static void In_LD_D_A(CPU& cpu, Bus& memBus) {  // LD D, A
    Registers* reg = cpu.GetRegisters();
    reg->D = reg->A;
    cpu.AddCycles(1);
}
static void In_LD_D_B(CPU& cpu, Bus& memBus) {  // LD D, B
    Registers* reg = cpu.GetRegisters();
    reg->D = reg->B;
    cpu.AddCycles(1);
}
static void In_LD_D_C(CPU& cpu, Bus& memBus) {  // LD D, C
    Registers* reg = cpu.GetRegisters();
    reg->D = reg->C;
    cpu.AddCycles(1);
}
static void In_LD_D_D(CPU& cpu, Bus& memBus) {  // LD D, D
    cpu.AddCycles(1);
}
static void In_LD_D_E(CPU& cpu, Bus& memBus) {  // LD D, E
    Registers* reg = cpu.GetRegisters();
    reg->D = reg->E;
    cpu.AddCycles(1);
}
static void In_LD_D_H(CPU& cpu, Bus& memBus) {  // LD D, H
    Registers* reg = cpu.GetRegisters();
    reg->D = reg->H;
    cpu.AddCycles(1);
}
static void In_LD_D_L(CPU& cpu, Bus& memBus) {  // LD D, L
    Registers* reg = cpu.GetRegisters();
    reg->D = reg->L;
    cpu.AddCycles(1);
}
static void In_LD_D_pHL(CPU& cpu, Bus& memBus) {  // LD D, [HL]
    Registers* reg = cpu.GetRegisters();
    u8 value = memBus.Read(reg->HL);
    reg->D = value;
    cpu.AddCycles(1);
}

static void In_LD_E_A(CPU& cpu, Bus& memBus) {  // LD E, A
    Registers* reg = cpu.GetRegisters();
    reg->E = reg->A;
    cpu.AddCycles(1);
}
static void In_LD_E_B(CPU& cpu, Bus& memBus) {  // LD E, B
    Registers* reg = cpu.GetRegisters();
    reg->E = reg->B;
    cpu.AddCycles(1);
}
static void In_LD_E_C(CPU& cpu, Bus& memBus) {  // LD E, C
    Registers* reg = cpu.GetRegisters();
    reg->E = reg->C;
    cpu.AddCycles(1);
}
static void In_LD_E_D(CPU& cpu, Bus& memBus) {  // LD E, D
    Registers* reg = cpu.GetRegisters();
    reg->E = reg->D;
    cpu.AddCycles(1);
}
static void In_LD_E_E(CPU& cpu, Bus& memBus) {  // LD E, E
    cpu.AddCycles(1);
}
static void In_LD_E_H(CPU& cpu, Bus& memBus) {  // LD E, H
    Registers* reg = cpu.GetRegisters();
    reg->E = reg->H;
    cpu.AddCycles(1);
}
static void In_LD_E_L(CPU& cpu, Bus& memBus) {  // LD E, L
    Registers* reg = cpu.GetRegisters();
    reg->E = reg->L;
    cpu.AddCycles(1);
}
static void In_LD_E_pHL(CPU& cpu, Bus& memBus) {  // LD E, [HL]
    Registers* reg = cpu.GetRegisters();
    u8 value = memBus.Read(reg->HL);
    reg->E = value;
    cpu.AddCycles(1);
}

static void In_LD_H_A(CPU& cpu, Bus& memBus) {  // LD H, A
    Registers* reg = cpu.GetRegisters();
    reg->H = reg->A;
    cpu.AddCycles(1);
}
static void In_LD_H_B(CPU& cpu, Bus& memBus) {  // LD H, B
    Registers* reg = cpu.GetRegisters();
    reg->H = reg->B;
    cpu.AddCycles(1);
}
static void In_LD_H_C(CPU& cpu, Bus& memBus) {  // LD H, C
    Registers* reg = cpu.GetRegisters();
    reg->H = reg->C;
    cpu.AddCycles(1);
}
static void In_LD_H_D(CPU& cpu, Bus& memBus) {  // LD H, D
    Registers* reg = cpu.GetRegisters();
    reg->H = reg->D;
    cpu.AddCycles(1);
}
static void In_LD_H_E(CPU& cpu, Bus& memBus) {  // LD H, E
    Registers* reg = cpu.GetRegisters();
    reg->H = reg->E;
    cpu.AddCycles(1);
}
static void In_LD_H_H(CPU& cpu, Bus& memBus) {  // LD H, H
    cpu.AddCycles(1);
}
static void In_LD_H_L(CPU& cpu, Bus& memBus) {  // LD H, L
    Registers* reg = cpu.GetRegisters();
    reg->H = reg->L;
    cpu.AddCycles(1);
}
static void In_LD_H_pHL(CPU& cpu, Bus& memBus) {  // LD H, [HL]
    Registers* reg = cpu.GetRegisters();
    u8 value = memBus.Read(reg->HL);
    reg->H = value;
    cpu.AddCycles(1);
}

static void In_LD_L_A(CPU& cpu, Bus& memBus) {  // LD L, A
    Registers* reg = cpu.GetRegisters();
    reg->L = reg->A;
    cpu.AddCycles(1);
}
static void In_LD_L_B(CPU& cpu, Bus& memBus) {  // LD L, B
    Registers* reg = cpu.GetRegisters();
    reg->L = reg->B;
    cpu.AddCycles(1);
}
static void In_LD_L_C(CPU& cpu, Bus& memBus) {  // LD L, C
    Registers* reg = cpu.GetRegisters();
    reg->L = reg->C;
    cpu.AddCycles(1);
}
static void In_LD_L_D(CPU& cpu, Bus& memBus) {  // LD L, D
    Registers* reg = cpu.GetRegisters();
    reg->L = reg->D;
    cpu.AddCycles(1);
}
static void In_LD_L_E(CPU& cpu, Bus& memBus) {  // LD L, E
    Registers* reg = cpu.GetRegisters();
    reg->L = reg->E;
    cpu.AddCycles(1);
}
static void In_LD_L_H(CPU& cpu, Bus& memBus) {  // LD L, H
    Registers* reg = cpu.GetRegisters();
    reg->L = reg->H;
    cpu.AddCycles(1);
}
static void In_LD_L_L(CPU& cpu, Bus& memBus) {  // LD L, L
    cpu.AddCycles(1);
}
static void In_LD_L_pHL(CPU& cpu, Bus& memBus) {  // LD L, [HL]
    Registers* reg = cpu.GetRegisters();
    u8 value = memBus.Read(reg->HL);
    reg->L = value;
    cpu.AddCycles(1);
}

/** LD [HL],r8 *************************************************************************************************************/
static void In_LD_pHL_A(CPU& cpu, Bus& memBus) {  // LD [HL], A
    Registers* reg = cpu.GetRegisters();
    memBus.Write(reg->HL, reg->A);
    cpu.AddCycles(2);
}
static void In_LD_pHL_B(CPU& cpu, Bus& memBus) {  // LD [HL], B
    Registers* reg = cpu.GetRegisters();
    memBus.Write(reg->HL, reg->B);
    cpu.AddCycles(2);
}
static void In_LD_pHL_C(CPU& cpu, Bus& memBus) {  // LD [HL], C
    Registers* reg = cpu.GetRegisters();
    memBus.Write(reg->HL, reg->C);
    cpu.AddCycles(2);
}
static void In_LD_pHL_D(CPU& cpu, Bus& memBus) {  // LD [HL], D
    Registers* reg = cpu.GetRegisters();
    memBus.Write(reg->HL, reg->D);
    cpu.AddCycles(2);
}
static void In_LD_pHL_E(CPU& cpu, Bus& memBus) {  // LD [HL], E
    Registers* reg = cpu.GetRegisters();
    memBus.Write(reg->HL, reg->E);
    cpu.AddCycles(2);
}
static void In_LD_pHL_H(CPU& cpu, Bus& memBus) {  // LD [HL], H
    Registers* reg = cpu.GetRegisters();
    memBus.Write(reg->HL, reg->H);
    cpu.AddCycles(2);
}
static void In_LD_pHL_L(CPU& cpu, Bus& memBus) {  // LD [HL], L
    Registers* reg = cpu.GetRegisters();
    memBus.Write(reg->HL, reg->L);
    cpu.AddCycles(2);
}

/** HALT ************************************************************************************************************/
static void In_HALT(CPU& cpu, Bus& memBus) {  // HALT
    cpu.Halt();
}  // TODO

/** ADD A,r8 ********************************************************************************************************/
static void In_ADD_A_A(CPU& cpu, Bus& memBus) {  // ADD A, A
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u16 result = regA + regA;  // u16 to detect overflow
    reg->A = result & 0xFF;    // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (regA & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                           // Carry if overflow on 7 bits

    cpu.AddCycles(1);
}
static void In_ADD_A_B(CPU& cpu, Bus& memBus) {  // ADD A, B
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u16 result = regA + reg->B;  // u16 to detect overflow
    reg->A = result & 0xFF;      // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (reg->B & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                             // Carry if overflow on 7 bits

    cpu.AddCycles(1);
}
static void In_ADD_A_C(CPU& cpu, Bus& memBus) {  // ADD A, C
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u16 result = regA + reg->C;  // u16 to detect overflow
    reg->A = result & 0xFF;      // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (reg->C & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                             // Carry if overflow on 7 bits

    cpu.AddCycles(1);
}
static void In_ADD_A_D(CPU& cpu, Bus& memBus) {  // ADD A, D
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u16 result = regA + reg->D;  // u16 to detect overflow
    reg->A = result & 0xFF;      // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (reg->D & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                             // Carry if overflow on 7 bits

    cpu.AddCycles(1);
}
static void In_ADD_A_E(CPU& cpu, Bus& memBus) {  // ADD A, E
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u16 result = regA + reg->E;  // u16 to detect overflow
    reg->A = result & 0xFF;      // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (reg->E & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                             // Carry if overflow on 7 bits

    cpu.AddCycles(1);
}
static void In_ADD_A_H(CPU& cpu, Bus& memBus) {  // ADD A, H
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u16 result = regA + reg->H;  // u16 to detect overflow
    reg->A = result & 0xFF;      // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (reg->H & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                             // Carry if overflow on 7 bits

    cpu.AddCycles(1);
}
static void In_ADD_A_L(CPU& cpu, Bus& memBus) {  // ADD A, L
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u16 result = regA + reg->L;  // u16 to detect overflow
    reg->A = result & 0xFF;      // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (reg->L & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                             // Carry if overflow on 7 bits

    cpu.AddCycles(1);
}

/** ADD A,[HL] ******************************************************************************************************/
static void In_ADD_A_pHL(CPU& cpu, Bus& memBus) {  // ADD A, [HL]
    Registers* reg = cpu.GetRegisters();
    u8 value = memBus.Read(reg->HL);
    u8 regA = reg->A;

    u16 result = regA + value;  // u16 to detect overflow
    reg->A = result & 0xFF;     // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (value & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                            // Carry if overflow on 7 bits

    cpu.AddCycles(2);
}

/** ADC A,r8 ********************************************************************************************************/
static void In_ADC_A_A(CPU& cpu, Bus& memBus) {  // ADC A, A
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA + regA + carry;  // u16 to detect overflow
    reg->A = result & 0xFF;            // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (regA & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                                   // Carry if overflow on 7 bits

    cpu.AddCycles(1);
}
static void In_ADC_A_B(CPU& cpu, Bus& memBus) {  // ADC A, B
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA + reg->B + carry;  // u16 to detect overflow
    reg->A = result & 0xFF;              // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (reg->B & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                                     // Carry if overflow on 7 bits

    cpu.AddCycles(1);
}
static void In_ADC_A_C(CPU& cpu, Bus& memBus) {  // ADC A, C
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA + reg->C + carry;  // u16 to detect overflow
    reg->A = result & 0xFF;              // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (reg->C & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                                     // Carry if overflow on 7 bits

    cpu.AddCycles(1);
}
static void In_ADC_A_D(CPU& cpu, Bus& memBus) {  // ADC A, D
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA + reg->D + carry;  // u16 to detect overflow
    reg->A = result & 0xFF;              // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (reg->D & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                                     // Carry if overflow on 7 bits

    cpu.AddCycles(1);
}
static void In_ADC_A_E(CPU& cpu, Bus& memBus) {  // ADC A, E
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA + reg->E + carry;  // u16 to detect overflow
    reg->A = result & 0xFF;              // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (reg->E & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                                     // Carry if overflow on 7 bits

    cpu.AddCycles(1);
}
static void In_ADC_A_H(CPU& cpu, Bus& memBus) {  // ADC A, H
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA + reg->H + carry;  // u16 to detect overflow
    reg->A = result & 0xFF;              // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (reg->H & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                                     // Carry if overflow on 7 bits

    cpu.AddCycles(1);
}
static void In_ADC_A_L(CPU& cpu, Bus& memBus) {  // ADC A, L
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA + reg->L + carry;  // u16 to detect overflow
    reg->A = result & 0xFF;              // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (reg->L & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                                     // Carry if overflow on 7 bits

    cpu.AddCycles(1);
}

/** ADC A,[HL] ********************************************************************************************************/
static void In_ADC_A_pHL(CPU& cpu, Bus& memBus) {  // ADC A, [HL]
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 value = memBus.Read(reg->HL);
    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA + value + carry;  // u16 to detect overflow
    reg->A = result & 0xFF;             // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (value & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                                    // Carry if overflow on 7 bits

    cpu.AddCycles(2);
}

/** SUB A,r8 ********************************************************************************************************/
static void In_SUB_A_A(CPU& cpu, Bus& memBus) {  // SUB A, A
    Registers* reg = cpu.GetRegisters();

    reg->A = 0;  // Because A - A = 0

    // Flags
    reg->SetFlag(Registers::Flag::Z, true);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_SUB_A_B(CPU& cpu, Bus& memBus) {  // SUB A, B
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u16 result = regA - reg->B;  // u16 to detect borrow
    reg->A = result & 0xFF;      // Keep only the fist 8 bits

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, (regA & 0x0F) < (reg->B & 0x0F));
    reg->SetFlag(Registers::Flag::C, regA < reg->B);

    cpu.AddCycles(1);
}
static void In_SUB_A_C(CPU& cpu, Bus& memBus) {  // SUB A, C
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u16 result = regA - reg->C;  // u16 to detect borrow
    reg->A = result & 0xFF;      // Keep only the fist 8 bits

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, (regA & 0x0F) < (reg->C & 0x0F));
    reg->SetFlag(Registers::Flag::C, regA < reg->C);

    cpu.AddCycles(1);
}
static void In_SUB_A_D(CPU& cpu, Bus& memBus) {  // SUB A, D
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u16 result = regA - reg->D;  // u16 to detect borrow
    reg->A = result & 0xFF;      // Keep only the fist 8 bits

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, (regA & 0x0F) < (reg->D & 0x0F));
    reg->SetFlag(Registers::Flag::C, regA < reg->D);

    cpu.AddCycles(1);
}
static void In_SUB_A_E(CPU& cpu, Bus& memBus) {  // SUB A, E
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u16 result = regA - reg->E;  // u16 to detect borrow
    reg->A = result & 0xFF;      // Keep only the fist 8 bits

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, (regA & 0x0F) < (reg->E & 0x0F));
    reg->SetFlag(Registers::Flag::C, regA < reg->E);

    cpu.AddCycles(1);
}
static void In_SUB_A_H(CPU& cpu, Bus& memBus) {  // SUB A, H
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u16 result = regA - reg->H;  // u16 to detect borrow
    reg->A = result & 0xFF;      // Keep only the fist 8 bits

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, (regA & 0x0F) < (reg->H & 0x0F));
    reg->SetFlag(Registers::Flag::C, regA < reg->H);

    cpu.AddCycles(1);
}
static void In_SUB_A_L(CPU& cpu, Bus& memBus) {  // SUB A, L
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u16 result = regA - reg->L;  // u16 to detect borrow
    reg->A = result & 0xFF;      // Keep only the fist 8 bits

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, (regA & 0x0F) < (reg->L & 0x0F));
    reg->SetFlag(Registers::Flag::C, regA < reg->L);

    cpu.AddCycles(1);
}

/** SUB A,[HL] ******************************************************************************************************/
static void In_SUB_A_pHL(CPU& cpu, Bus& memBus) {  // SUB A, [HL]
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;
    u8 value = memBus.Read(reg->HL);

    u16 result = regA - value;  // u16 to detect borrow
    reg->A = result & 0xFF;     // Keep only the fist 8 bits

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, (regA & 0x0F) < (value & 0x0F));
    reg->SetFlag(Registers::Flag::C, regA < value);

    cpu.AddCycles(2);
}

/** SBC A,r8 ********************************************************************************************************/
static void In_SBC_A_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA - regA - carry;

    reg->A = result & 0xFF;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, ((regA ^ regA ^ result) & 0x10) != 0);
    reg->SetFlag(Registers::Flag::C, carry != 0);

    cpu.AddCycles(1);
}
static void In_SBC_A_B(CPU& cpu, Bus& memBus) {  // SBC A, B
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;
    u8 regB = reg->B;

    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA - regB - carry;  // u16 to detect borrow
    reg->A = result & 0xFF;            // Keep only the fist 8 bits

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, ((regA ^ regB ^ result) & 0x10) != 0);
    reg->SetFlag(Registers::Flag::C, regA < regB + carry);

    cpu.AddCycles(1);
}
static void In_SBC_A_C(CPU& cpu, Bus& memBus) {  // SBC A, C
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA - reg->C - carry;  // u16 to detect borrow
    reg->A = result & 0xFF;              // Keep only the fist 8 bits

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, ((regA ^ reg->C ^ result) & 0x10) != 0);
    reg->SetFlag(Registers::Flag::C, regA < reg->C + carry);

    cpu.AddCycles(1);
}
static void In_SBC_A_D(CPU& cpu, Bus& memBus) {  // SBC A, D
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA - reg->D - carry;  // u16 to detect borrow
    reg->A = result & 0xFF;              // Keep only the fist 8 bits

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, ((regA ^ reg->D ^ result) & 0x10) != 0);
    reg->SetFlag(Registers::Flag::C, regA < reg->D + carry);

    cpu.AddCycles(1);
}
static void In_SBC_A_E(CPU& cpu, Bus& memBus) {  // SBC A, E
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA - reg->E - carry;  // u16 to detect borrow
    reg->A = result & 0xFF;              // Keep only the fist 8 bits

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, ((regA ^ reg->E ^ result) & 0x10) != 0);
    reg->SetFlag(Registers::Flag::C, regA < reg->E + carry);

    cpu.AddCycles(1);
}
static void In_SBC_A_H(CPU& cpu, Bus& memBus) {  // SBC A, H
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA - reg->H - carry;  // u16 to detect borrow
    reg->A = result & 0xFF;              // Keep only the fist 8 bits

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, ((regA ^ reg->H ^ result) & 0x10) != 0);
    reg->SetFlag(Registers::Flag::C, regA < reg->H + carry);

    cpu.AddCycles(1);
}
static void In_SBC_A_L(CPU& cpu, Bus& memBus) {  // SBC A, L
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA - reg->L - carry;  // u16 to detect borrow
    reg->A = result & 0xFF;              // Keep only the fist 8 bits

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, ((regA ^ reg->L ^ result) & 0x10) != 0);
    reg->SetFlag(Registers::Flag::C, regA < reg->L + carry);

    cpu.AddCycles(1);
}

/** SBC A,[HL] ******************************************************************************************************/
static void In_SBC_A_pHL(CPU& cpu, Bus& memBus) {  // SBC A, [HL]
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 value = memBus.Read(reg->HL);
    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA - value - carry;  // u16 to detect borrow
    reg->A = result & 0xFF;             // Keep only the fist 8 bits

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, ((regA ^ value ^ result) & 0x10) != 0);
    reg->SetFlag(Registers::Flag::C, regA < value + carry);

    cpu.AddCycles(2);
}

/** AND A,r8 ********************************************************************************************************/
static void In_AND_A_A(CPU& cpu, Bus& memBus) {  // AND A, A
    Registers* reg = cpu.GetRegisters();

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_AND_A_B(CPU& cpu, Bus& memBus) {  // AND A, B
    Registers* reg = cpu.GetRegisters();
    reg->A &= reg->B;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_AND_A_C(CPU& cpu, Bus& memBus) {  // AND A, C
    Registers* reg = cpu.GetRegisters();
    reg->A &= reg->C;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_AND_A_D(CPU& cpu, Bus& memBus) {  // AND A, D
    Registers* reg = cpu.GetRegisters();
    reg->A &= reg->D;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_AND_A_E(CPU& cpu, Bus& memBus) {  // AND A, E
    Registers* reg = cpu.GetRegisters();
    reg->A &= reg->E;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_AND_A_H(CPU& cpu, Bus& memBus) {  // AND A, H
    Registers* reg = cpu.GetRegisters();
    reg->A &= reg->H;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_AND_A_L(CPU& cpu, Bus& memBus) {  // AND A, L
    Registers* reg = cpu.GetRegisters();
    reg->A &= reg->L;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}

/** AND A,[HL] ******************************************************************************************************/
static void In_AND_A_pHL(CPU& cpu, Bus& memBus) {  // AND A, [HL]
    Registers* reg = cpu.GetRegisters();
    u8 value = memBus.Read(reg->HL);
    reg->A &= value;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(2);
}

/** XOR A,r8 ********************************************************************************************************/
static void In_XOR_A_A(CPU& cpu, Bus& memBus) {  // XOR A, A
    Registers* reg = cpu.GetRegisters();
    reg->A = 0;

    // Flags
    reg->SetFlag(Registers::Flag::Z, true);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_XOR_A_B(CPU& cpu, Bus& memBus) {  // XOR A, B
    Registers* reg = cpu.GetRegisters();
    reg->A ^= reg->B;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_XOR_A_C(CPU& cpu, Bus& memBus) {  // XOR A, C
    Registers* reg = cpu.GetRegisters();
    reg->A ^= reg->C;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_XOR_A_D(CPU& cpu, Bus& memBus) {  // XOR A, D
    Registers* reg = cpu.GetRegisters();
    reg->A ^= reg->D;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_XOR_A_E(CPU& cpu, Bus& memBus) {  // XOR A, E
    Registers* reg = cpu.GetRegisters();
    reg->A ^= reg->E;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_XOR_A_H(CPU& cpu, Bus& memBus) {  // XOR A, H
    Registers* reg = cpu.GetRegisters();
    reg->A ^= reg->H;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_XOR_A_L(CPU& cpu, Bus& memBus) {  // XOR A, L
    Registers* reg = cpu.GetRegisters();
    reg->A ^= reg->L;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}

/** XOR A,[HL] ******************************************************************************************************/
static void In_XOR_A_pHL(CPU& cpu, Bus& memBus) {  // XOR A, [HL]
    Registers* reg = cpu.GetRegisters();
    u8 value = memBus.Read(reg->HL);
    reg->A ^= value;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(2);
}

/** OR A,r8 *********************************************************************************************************/
static void In_OR_A_A(CPU& cpu, Bus& memBus) {  // OR A, A
    Registers* reg = cpu.GetRegisters();

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_OR_A_B(CPU& cpu, Bus& memBus) {  // OR A, B
    Registers* reg = cpu.GetRegisters();
    reg->A |= reg->B;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_OR_A_C(CPU& cpu, Bus& memBus) {  // OR A, C
    Registers* reg = cpu.GetRegisters();
    reg->A |= reg->C;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_OR_A_D(CPU& cpu, Bus& memBus) {  // OR A, D
    Registers* reg = cpu.GetRegisters();
    reg->A |= reg->D;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_OR_A_E(CPU& cpu, Bus& memBus) {  // OR A, E
    Registers* reg = cpu.GetRegisters();
    reg->A |= reg->E;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_OR_A_H(CPU& cpu, Bus& memBus) {  // OR A, H
    Registers* reg = cpu.GetRegisters();
    reg->A |= reg->H;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_OR_A_L(CPU& cpu, Bus& memBus) {  // OR A, L
    Registers* reg = cpu.GetRegisters();
    reg->A |= reg->L;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}

/** OR A,[HL] *******************************************************************************************************/
static void In_OR_A_pHL(CPU& cpu, Bus& memBus) {  // OR A, [HL]
    Registers* reg = cpu.GetRegisters();
    u8 value = memBus.Read(reg->HL);
    reg->A |= value;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(2);
}

/** CP A,r8 ********************************************************************************************************/
static void In_CP_A_A(CPU& cpu, Bus& memBus) {  // CP A, A
    Registers* reg = cpu.GetRegisters();

    // Flags
    reg->SetFlag(Registers::Flag::Z, true);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(1);
}
static void In_CP_A_B(CPU& cpu, Bus& memBus) {  // CP A, B
    Registers* reg = cpu.GetRegisters();

    u16 result = reg->A - reg->B;  // u16 to detect borrow

    // Flags
    reg->SetFlag(Registers::Flag::Z, result == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, (reg->A & 0x0F) < (reg->B & 0x0F));
    reg->SetFlag(Registers::Flag::C, reg->B > reg->A);

    cpu.AddCycles(1);
}
static void In_CP_A_C(CPU& cpu, Bus& memBus) {  // CP A, C
    Registers* reg = cpu.GetRegisters();

    u16 result = reg->A - reg->C;  // u16 to detect borrow

    // Flags
    reg->SetFlag(Registers::Flag::Z, result == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, (reg->A & 0x0F) < (reg->C & 0x0F));
    reg->SetFlag(Registers::Flag::C, reg->C > reg->A);

    cpu.AddCycles(1);
}
static void In_CP_A_D(CPU& cpu, Bus& memBus) {  // CP A, D
    Registers* reg = cpu.GetRegisters();

    u16 result = reg->A - reg->D;  // u16 to detect borrow

    // Flags
    reg->SetFlag(Registers::Flag::Z, result == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, (reg->A & 0x0F) < (reg->D & 0x0F));
    reg->SetFlag(Registers::Flag::C, reg->D > reg->A);

    cpu.AddCycles(1);
}
static void In_CP_A_E(CPU& cpu, Bus& memBus) {  // CP A, E
    Registers* reg = cpu.GetRegisters();

    u16 result = reg->A - reg->E;  // u16 to detect borrow

    // Flags
    reg->SetFlag(Registers::Flag::Z, result == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, (reg->A & 0x0F) < (reg->E & 0x0F));
    reg->SetFlag(Registers::Flag::C, reg->E > reg->A);

    cpu.AddCycles(1);
}
static void In_CP_A_H(CPU& cpu, Bus& memBus) {  // CP A, H
    Registers* reg = cpu.GetRegisters();

    u16 result = reg->A - reg->H;  // u16 to detect borrow

    // Flags
    reg->SetFlag(Registers::Flag::Z, result == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, (reg->A & 0x0F) < (reg->H & 0x0F));
    reg->SetFlag(Registers::Flag::C, reg->H > reg->A);

    cpu.AddCycles(1);
}
static void In_CP_A_L(CPU& cpu, Bus& memBus) {  // CP A, L
    Registers* reg = cpu.GetRegisters();

    u16 result = reg->A - reg->L;  // u16 to detect borrow

    // Flags
    reg->SetFlag(Registers::Flag::Z, result == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, (reg->A & 0x0F) < (reg->L & 0x0F));
    reg->SetFlag(Registers::Flag::C, reg->L > reg->A);

    cpu.AddCycles(1);
}
static void In_CP_A_pHL(CPU& cpu, Bus& memBus) {  // CP A, [HL]
    Registers* reg = cpu.GetRegisters();

    u8 value = memBus.Read(reg->HL);
    u16 result = reg->A - value;  // u16 to detect borrow

    // Flags
    reg->SetFlag(Registers::Flag::Z, result == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, (reg->A & 0x0F) < (value & 0x0F));
    reg->SetFlag(Registers::Flag::C, value > reg->A);

    cpu.AddCycles(2);
}

/** ADD A,n8 ********************************************************************************************************/
static void In_ADD_A_n8(CPU& cpu, Bus& memBus) {  // ADD A, n8
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 value = cpu.Fetch8();
    u16 result = regA + value;  // u16 to detect overflow
    reg->A = result & 0xFF;     // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (value & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                            // Carry if overflow on 7 bits

    cpu.AddCycles(2);
}

/** ADC A,n8 ********************************************************************************************************/
static void In_ADC_A_n8(CPU& cpu, Bus& memBus) {  // ADC A, n8
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 value = cpu.Fetch8();
    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA + value + carry;  // u16 to detect overflow
    reg->A = result & 0xFF;             // Keep only the fist 8 bits

    // Set flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regA & 0x0F) + (value & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, result > 0xFF);                                    // Carry if overflow on 7 bits

    cpu.AddCycles(2);
}

/** SUB A,n8 ********************************************************************************************************/
static void In_SUB_A_n8(CPU& cpu, Bus& memBus) {  // SUB A, n8
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 value = cpu.Fetch8();
    u16 result = regA - value;  // u16 to detect borrow
    reg->A = result & 0xFF;     // Keep only the fist 8 bits

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, (regA & 0x0F) < (value & 0x0F));
    reg->SetFlag(Registers::Flag::C, result > 0xFF);

    cpu.AddCycles(2);
}

/** SBC A,n8 ********************************************************************************************************/
static void In_SBC_A_n8(CPU& cpu, Bus& memBus) {  // SBC A, n8
    Registers* reg = cpu.GetRegisters();
    u8 regA = reg->A;

    u8 value = cpu.Fetch8();
    u8 carry = reg->GetFlag(Registers::Flag::C) ? 1 : 0;
    u16 result = regA - value - carry;  // u16 to detect borrow
    reg->A = result & 0xFF;             // Keep only the fist 8 bits

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, ((regA ^ value ^ result) & 0x10));
    reg->SetFlag(Registers::Flag::C, result > 0xFF);

    cpu.AddCycles(2);
}

/** AND A,n8 ********************************************************************************************************/
static void In_AND_A_n8(CPU& cpu, Bus& memBus) {  // AND A, n8
    Registers* reg = cpu.GetRegisters();
    u8 value = cpu.Fetch8();
    reg->A &= value;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(2);
}

/** XOR A,n8 ********************************************************************************************************/
static void In_XOR_A_n8(CPU& cpu, Bus& memBus) {  // XOR A, n8
    Registers* reg = cpu.GetRegisters();
    u8 value = cpu.Fetch8();
    reg->A ^= value;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(2);
}

/** OR A,n8 *********************************************************************************************************/
static void In_OR_A_n8(CPU& cpu, Bus& memBus) {  // OR A, n8
    Registers* reg = cpu.GetRegisters();
    u8 value = cpu.Fetch8();
    reg->A |= value;

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(2);
}

/** CP A,n8 *********************************************************************************************************/
static void In_CP_A_n8(CPU& cpu, Bus& memBus) {  // CP A, n8
    Registers* reg = cpu.GetRegisters();

    u8 value = cpu.Fetch8();
    u16 result = reg->A - value;  // u16 to detect borrow

    // Flags
    reg->SetFlag(Registers::Flag::Z, result == 0);
    reg->SetFlag(Registers::Flag::N, true);
    reg->SetFlag(Registers::Flag::H, (reg->A & 0x0F) < (value & 0x0F));
    reg->SetFlag(Registers::Flag::C, value > reg->A);

    cpu.AddCycles(2);
}

/** RET cc ***********************************************************************************************************/
static void In_RET_NZ(CPU& cpu, Bus& memBus) {  // RET NZ
    Registers* reg = cpu.GetRegisters();

    if (!reg->GetFlag(Registers::Flag::Z)) {
        reg->PC = cpu.Pop16Stack();
        cpu.AddCycles(3);
    }
    cpu.AddCycles(2);
}
static void In_RET_Z(CPU& cpu, Bus& memBus) {  // RET Z
    Registers* reg = cpu.GetRegisters();

    if (reg->GetFlag(Registers::Flag::Z)) {
        reg->PC = cpu.Pop16Stack();
        cpu.AddCycles(3);
    }
    cpu.AddCycles(2);
}
static void In_RET_NC(CPU& cpu, Bus& memBus) {  // RET NC
    Registers* reg = cpu.GetRegisters();

    if (!reg->GetFlag(Registers::Flag::C)) {
        reg->PC = cpu.Pop16Stack();
        cpu.AddCycles(3);
    }
    cpu.AddCycles(2);
}
static void In_RET_C(CPU& cpu, Bus& memBus) {  // RET C
    Registers* reg = cpu.GetRegisters();

    if (reg->GetFlag(Registers::Flag::C)) {
        reg->PC = cpu.Pop16Stack();
        cpu.AddCycles(3);
    }

    cpu.AddCycles(2);
}

/** RET **************************************************************************************************************/
static void In_RET(CPU& cpu, Bus& memBus) {  // RET
    Registers* reg = cpu.GetRegisters();
    reg->PC = cpu.Pop16Stack();
    cpu.AddCycles(4);
}

/** RETI *************************************************************************************************************/
static void In_RETI(CPU& cpu, Bus& memBus) {  // RETI
    Registers* reg = cpu.GetRegisters();
    reg->PC = cpu.Pop16Stack();
    cpu.GetInterrupHandler()->SetIME(true);
    cpu.AddCycles(4);
}

/** JP cc,n16 ********************************************************************************************************/
static void In_JP_NZ_n16(CPU& cpu, Bus& memBus) {  // JP NZ, n16
    Registers* reg = cpu.GetRegisters();
    u16 value = cpu.Fetch16();

    if (!reg->GetFlag(Registers::Flag::Z)) {
        reg->PC = value;
        cpu.AddCycles(1);
    }
    cpu.AddCycles(3);
}
static void In_JP_Z_n16(CPU& cpu, Bus& memBus) {  // JP Z, n16
    Registers* reg = cpu.GetRegisters();
    u16 value = cpu.Fetch16();

    if (reg->GetFlag(Registers::Flag::Z)) {
        reg->PC = value;
        cpu.AddCycles(1);
    }
    cpu.AddCycles(3);
}
static void In_JP_NC_n16(CPU& cpu, Bus& memBus) {  // JP NC, n16
    Registers* reg = cpu.GetRegisters();
    u16 value = cpu.Fetch16();

    if (!reg->GetFlag(Registers::Flag::C)) {
        reg->PC = value;
        cpu.AddCycles(1);
    }
    cpu.AddCycles(3);
}
static void In_JP_C_n16(CPU& cpu, Bus& memBus) {  // JP C, n16
    Registers* reg = cpu.GetRegisters();
    u16 value = cpu.Fetch16();

    if (reg->GetFlag(Registers::Flag::C)) {
        reg->PC = value;
        cpu.AddCycles(1);
    }
    cpu.AddCycles(3);
}

/** JP n16 ***********************************************************************************************************/
static void In_JP_n16(CPU& cpu, Bus& memBus) {  // JP n16
    Registers* reg = cpu.GetRegisters();
    u16 value = cpu.Fetch16();
    reg->PC = value;
    cpu.AddCycles(4);
}

/** JP HL ************************************************************************************************************/
static void In_JP_HL(CPU& cpu, Bus& memBus) {  // JP HL
    Registers* reg = cpu.GetRegisters();
    reg->PC = reg->HL;
    cpu.AddCycles(4);
}

/** CALL cc,n16 ******************************************************************************************************/
static void In_CALL_NZ_n16(CPU& cpu, Bus& memBus) {  // CALL NZ, n16
    Registers* reg = cpu.GetRegisters();
    u16 addr = cpu.Fetch16();

    if (!reg->GetFlag(Registers::Flag::Z)) {
        cpu.Push16Stack(reg->PC);
        reg->PC = addr;
        cpu.AddCycles(3);
    }
    cpu.AddCycles(3);
}
static void In_CALL_Z_n16(CPU& cpu, Bus& memBus) {  // CALL Z, n16
    Registers* reg = cpu.GetRegisters();
    u16 addr = cpu.Fetch16();

    if (reg->GetFlag(Registers::Flag::Z)) {
        cpu.Push16Stack(reg->PC);
        reg->PC = addr;
        cpu.AddCycles(3);
    }
    cpu.AddCycles(3);
}
static void In_CALL_NC_n16(CPU& cpu, Bus& memBus) {  // CALL NC, n16
    Registers* reg = cpu.GetRegisters();
    u16 addr = cpu.Fetch16();

    if (!reg->GetFlag(Registers::Flag::C)) {
        cpu.Push16Stack(reg->PC);
        reg->PC = addr;
        cpu.AddCycles(3);
    }
    cpu.AddCycles(3);
}
static void In_CALL_C_n16(CPU& cpu, Bus& memBus) {  // CALL C, n16
    Registers* reg = cpu.GetRegisters();
    u16 addr = cpu.Fetch16();

    if (reg->GetFlag(Registers::Flag::C)) {
        cpu.Push16Stack(reg->PC);
        reg->PC = addr;
        cpu.AddCycles(3);
    }
    cpu.AddCycles(3);
}

/** CALL n16 *********************************************************************************************************/
static void In_CALL_n16(CPU& cpu, Bus& memBus) {  // CALL n16
    Registers* reg = cpu.GetRegisters();

    u16 addr = cpu.Fetch16();

    cpu.Push16Stack(reg->PC);
    reg->PC = addr;
    cpu.AddCycles(6);
}

/** RST vec **********************************************************************************************************/
static void In_RST_00H(CPU& cpu, Bus& memBus) {  // RST 00H
    Registers* reg = cpu.GetRegisters();
    cpu.Push16Stack(reg->PC);
    reg->PC = 0x00;
    cpu.AddCycles(4);
}
static void In_RST_08H(CPU& cpu, Bus& memBus) {  // RST 08H
    Registers* reg = cpu.GetRegisters();
    cpu.Push16Stack(reg->PC);
    reg->PC = 0x08;
    cpu.AddCycles(4);
}
static void In_RST_10H(CPU& cpu, Bus& memBus) {  // RST 10H
    Registers* reg = cpu.GetRegisters();
    cpu.Push16Stack(reg->PC);
    reg->PC = 0x10;
    cpu.AddCycles(4);
}
static void In_RST_18H(CPU& cpu, Bus& memBus) {  // RST 18H
    Registers* reg = cpu.GetRegisters();
    cpu.Push16Stack(reg->PC);
    reg->PC = 0x18;
    cpu.AddCycles(4);
}
static void In_RST_20H(CPU& cpu, Bus& memBus) {  // RST 20H
    Registers* reg = cpu.GetRegisters();
    cpu.Push16Stack(reg->PC);
    reg->PC = 0x20;
    cpu.AddCycles(4);
}
static void In_RST_28H(CPU& cpu, Bus& memBus) {  // RST 28H
    Registers* reg = cpu.GetRegisters();
    cpu.Push16Stack(reg->PC);
    reg->PC = 0x28;
    cpu.AddCycles(4);
}
static void In_RST_30H(CPU& cpu, Bus& memBus) {  // RST 30H
    Registers* reg = cpu.GetRegisters();
    cpu.Push16Stack(reg->PC);
    reg->PC = 0x30;
    cpu.AddCycles(4);
}
static void In_RST_38H(CPU& cpu, Bus& memBus) {  // RST 38H
    Registers* reg = cpu.GetRegisters();
    cpu.Push16Stack(reg->PC);
    reg->PC = 0x38;
    cpu.AddCycles(4);
}

/** POP AF ***********************************************************************************************************/
static void In_PIn_AF(CPU& cpu, Bus& memBus) {  // POP AF
    Registers* reg = cpu.GetRegisters();
    reg->AF = cpu.Pop16Stack();
    reg->F &= 0xF0;  // 4 LSB of F registers need to be always at 0

    // Flags
    reg->SetFlag(Registers::Flag::Z, (reg->F & 0x80) != 0);
    reg->SetFlag(Registers::Flag::N, (reg->F & 0x40) != 0);
    reg->SetFlag(Registers::Flag::H, (reg->F & 0x20) != 0);
    reg->SetFlag(Registers::Flag::C, (reg->F & 0x10) != 0);

    cpu.AddCycles(3);
}

/** POP r16 **********************************************************************************************************/
static void In_PIn_BC(CPU& cpu, Bus& memBus) {  // POP BC
    Registers* reg = cpu.GetRegisters();
    reg->BC = cpu.Pop16Stack();
    cpu.AddCycles(3);
}
static void In_PIn_DE(CPU& cpu, Bus& memBus) {  // POP DE
    Registers* reg = cpu.GetRegisters();
    reg->DE = cpu.Pop16Stack();
    cpu.AddCycles(3);
}
static void In_PIn_HL(CPU& cpu, Bus& memBus) {  // POP HL
    Registers* reg = cpu.GetRegisters();
    reg->HL = cpu.Pop16Stack();
    cpu.AddCycles(3);
}

/** PUSH AF **********************************************************************************************************/
static void In_PUSH_AF(CPU& cpu, Bus& memBus) {  // PUSH AF
    Registers* reg = cpu.GetRegisters();

    // Clear the 4 LSB of F register (for security)
    reg->F &= 0xF0;

    cpu.Push16Stack(reg->AF);
    cpu.AddCycles(4);
}

/** PUSH r16 *********************************************************************************************************/
static void In_PUSH_BC(CPU& cpu, Bus& memBus) {  // PUSH BC
    Registers* reg = cpu.GetRegisters();

    cpu.Push16Stack(reg->BC);
    cpu.AddCycles(4);
}
static void In_PUSH_DE(CPU& cpu, Bus& memBus) {  // PUSH DE
    Registers* reg = cpu.GetRegisters();

    cpu.Push16Stack(reg->DE);
    cpu.AddCycles(4);
}
static void In_PUSH_HL(CPU& cpu, Bus& memBus) {  // PUSH HL
    Registers* reg = cpu.GetRegisters();

    cpu.Push16Stack(reg->HL);
    cpu.AddCycles(4);
}

/** LDH [C],A ********************************************************************************************************/
static void In_LDH_pC_A(CPU& cpu, Bus& memBus) {  // LDH [C], A
    Registers* reg = cpu.GetRegisters();

    u16 addr = 0xFF00 + reg->C;
    memBus.Write(addr, reg->A);

    cpu.AddCycles(2);
}

/** LDH [n8],A *******************************************************************************************************/
static void In_LDH_pn8_A(CPU& cpu, Bus& memBus) {  // LDH [n8], A
    Registers* reg = cpu.GetRegisters();

    u16 addr = 0xFF00 + cpu.Fetch8();
    memBus.Write(addr, reg->A);

    cpu.AddCycles(3);
}

/** LD [n16],A *******************************************************************************************************/
static void In_LD_pn16_A(CPU& cpu, Bus& memBus) {  // LD [n16], A
    Registers* reg = cpu.GetRegisters();

    u16 addr = cpu.Fetch16();
    memBus.Write(addr, reg->A);

    cpu.AddCycles(3);
}

/** LDH A,[C] ********************************************************************************************************/
static void In_LDH_A_pC(CPU& cpu, Bus& memBus) {  // LDH A, [C]
    Registers* reg = cpu.GetRegisters();

    u8 value = memBus.Read(0xFF00 + reg->C);
    reg->A = value;

    cpu.AddCycles(2);
}

/** LDH A,[n8] *******************************************************************************************************/
static void In_LDH_A_pn8(CPU& cpu, Bus& memBus) {  // LDH A, [n8]
    Registers* reg = cpu.GetRegisters();

    u16 addr = 0xFF00 + cpu.Fetch8();
    u8 value = memBus.Read(addr);
    reg->A = value;

    cpu.AddCycles(3);
}

/** LD A,[n16] ******************************************************************************************************/
static void In_LD_A_pn16(CPU& cpu, Bus& memBus) {  // LD A, [n16]
    Registers* reg = cpu.GetRegisters();

    u16 addr = cpu.Fetch16();
    u8 value = memBus.Read(addr);
    reg->A = value;

    cpu.AddCycles(4);
}

/** ADD SP,e8 ********************************************************************************************************/
static void In_ADD_SP_e8(CPU& cpu, Bus& memBus) {  // ADD SP, e8
    Registers* reg = cpu.GetRegisters();
    u16 regSP = reg->SP;

    int8_t value = static_cast<int8_t>(cpu.Fetch8());
    u32 result = regSP + value;
    reg->SP = result & 0xFFFF;  // Keep only the fist 16 bits

    // Flags
    reg->SetFlag(Registers::Flag::Z, false);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regSP & 0x0F) + (value & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, ((regSP & 0xFF) + (value & 0xFF)) > 0xFF);  // Carry if overflow on 7 bits

    cpu.AddCycles(4);
}

/** LD HL,SP+e8 ******************************************************************************************************/
static void In_LD_HL_SP_plus_e8(CPU& cpu, Bus& memBus) {  // LD HL, SP+e8
    Registers* reg = cpu.GetRegisters();
    u16 regSP = reg->SP;

    int8_t value = static_cast<int8_t>(cpu.Fetch8());
    u32 result = regSP + value;
    reg->HL = result & 0xFFFF;

    // Flags
    reg->SetFlag(Registers::Flag::Z, false);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, ((regSP & 0x0F) + (value & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg->SetFlag(Registers::Flag::C, ((regSP & 0xFF) + (value & 0xFF)) > 0xFF);  // Carry if overflow on 7 bits

    cpu.AddCycles(3);
}

/** LD SP,HL *********************************************************************************************************/
static void In_LD_SP_HL(CPU& cpu, Bus& memBus) {  // LD SP, HL
    Registers* reg = cpu.GetRegisters();
    reg->SP = reg->HL;
    cpu.AddCycles(2);
}

/** DI ***************************************************************************************************************/
static void In_DI(CPU& cpu, Bus& memBus) {  // DI
    cpu.GetInterrupHandler()->SetIME(false);
    cpu.AddCycles(1);
}

/** EI ***************************************************************************************************************/
static void In_EI(CPU& cpu, Bus& memBus) {
    cpu.RequestIMEEnable();
    cpu.AddCycles(1);
}

/** Prefix ***********************************************************************************************************/
static void In_Handle_CB(CPU& cpu, Bus& memBus) {}

/** Invalid **********************************************************************************************************/
static void In_Invalid(CPU& cpu, Bus& memBus) {
    LOG_ERROR("Invalid instruction");
    exit(100);
}

/***********************/
/* PREFIX INSTRUCTIONS */
/***********************/
/** RLC r8 ***********************************************************************************************************/
static void In_RLC_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->B & 0x80;
    reg->B = (reg->B << 1) | (carry ? 1 : 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->B == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_RLC_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->C & 0x80;
    reg->C = (reg->C << 1) | (carry ? 1 : 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->C == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_RLC_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->D & 0x80;
    reg->D = (reg->D << 1) | (carry ? 1 : 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->D == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_RLC_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->E & 0x80;
    reg->E = (reg->E << 1) | (carry ? 1 : 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->E == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_RLC_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->H & 0x80;
    reg->H = (reg->H << 1) | (carry ? 1 : 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->H == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_RLC_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->L & 0x80;
    reg->L = (reg->L << 1) | (carry ? 1 : 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->L == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_RLC_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    bool carry = target & 0x80;
    target = (target << 1) | (carry ? 1 : 0);

    memBus.Write(reg->HL, target);

    // Flags
    reg->SetFlag(Registers::Flag::Z, target == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(4);
}
static void In_RLC_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->A & 0x80;
    reg->A = (reg->A << 1) | (carry ? 1 : 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A ? false : true);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}

/** RRC r8 ***********************************************************************************************************/
static void In_RRC_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->B & 0x01;
    reg->B = (reg->B >> 1) | (carry << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->B == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_RRC_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->C & 0x01;
    reg->C = (reg->C >> 1) | (carry << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->C == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_RRC_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->D & 0x01;
    reg->D = (reg->D >> 1) | (carry << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->D == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_RRC_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->E & 0x01;
    reg->E = (reg->E >> 1) | (carry << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->E == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_RRC_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->H & 0x01;
    reg->H = (reg->H >> 1) | (carry << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->H == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_RRC_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->L & 0x01;
    reg->L = (reg->L >> 1) | (carry << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->L == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_RRC_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    bool carry = target & 0x01;
    target = (target >> 1) | (carry << 7);

    memBus.Write(reg->HL, target);

    // Flags
    reg->SetFlag(Registers::Flag::Z, target == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_RRC_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->A & 0x01;
    reg->A = (reg->A >> 1) | (carry << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}

/** RL r8 ***********************************************************************************************************/
static void In_RL_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool new_carry = reg->B & 0x80;
    bool carry = reg->GetFlag(Registers::Flag::C);
    reg->B = (reg->B << 1) | (carry ? 1 : 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->B == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, new_carry);

    cpu.AddCycles(2);
}
static void In_RL_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool new_carry = reg->C & 0x80;
    bool carry = reg->GetFlag(Registers::Flag::C);
    reg->C = (reg->C << 1) | (carry ? 1 : 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->C == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, new_carry);

    cpu.AddCycles(2);
}
static void In_RL_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool new_carry = reg->D & 0x80;
    bool carry = reg->GetFlag(Registers::Flag::C);
    reg->D = (reg->D << 1) | (carry ? 1 : 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->D == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, new_carry);

    cpu.AddCycles(2);
}
static void In_RL_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool new_carry = reg->E & 0x80;
    bool carry = reg->GetFlag(Registers::Flag::C);
    reg->E = (reg->E << 1) | (carry ? 1 : 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->E == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, new_carry);

    cpu.AddCycles(2);
}
static void In_RL_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool new_carry = reg->H & 0x80;
    bool carry = reg->GetFlag(Registers::Flag::C);
    reg->H = (reg->H << 1) | (carry ? 1 : 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->H == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, new_carry);

    cpu.AddCycles(2);
}
static void In_RL_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool new_carry = reg->L & 0x80;
    bool carry = reg->GetFlag(Registers::Flag::C);
    reg->L = (reg->L << 1) | (carry ? 1 : 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->L == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, new_carry);

    cpu.AddCycles(2);
}
static void In_RL_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    bool new_carry = target & 0x80;
    bool carry = reg->GetFlag(Registers::Flag::C);
    target = (target << 1) | (carry ? 1 : 0);

    memBus.Write(reg->HL, target);

    // Flags
    reg->SetFlag(Registers::Flag::Z, target == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, new_carry);

    cpu.AddCycles(4);
}
static void In_RL_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool new_carry = reg->A & 0x80;
    bool carry = reg->GetFlag(Registers::Flag::C);
    reg->A = (reg->A << 1) | (carry ? 1 : 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, new_carry);

    cpu.AddCycles(2);
}

/** RR r8 ***********************************************************************************************************/
static void In_RR_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool new_carry = reg->B & 0x01;
    bool carry = reg->GetFlag(Registers::Flag::C);
    reg->B = (reg->B >> 1) | (carry << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->B == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, new_carry);

    cpu.AddCycles(2);
}
static void In_RR_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool new_carry = reg->C & 0x01;
    bool carry = reg->GetFlag(Registers::Flag::C);
    reg->C = (reg->C >> 1) | (carry << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->C == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, new_carry);

    cpu.AddCycles(2);
}
static void In_RR_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool new_carry = reg->D & 0x01;
    bool carry = reg->GetFlag(Registers::Flag::C);
    reg->D = (reg->D >> 1) | (carry << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->D == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, new_carry);

    cpu.AddCycles(2);
}
static void In_RR_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool new_carry = reg->E & 0x01;
    bool carry = reg->GetFlag(Registers::Flag::C);
    reg->E = (reg->E >> 1) | (carry << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->E == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, new_carry);

    cpu.AddCycles(2);
}
static void In_RR_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool new_carry = reg->H & 0x01;
    bool carry = reg->GetFlag(Registers::Flag::C);
    reg->H = (reg->H >> 1) | (carry << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->H == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, new_carry);

    cpu.AddCycles(2);
}
static void In_RR_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool new_carry = reg->L & 0x01;
    bool carry = reg->GetFlag(Registers::Flag::C);
    reg->L = (reg->L >> 1) | (carry << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->L == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, new_carry);

    cpu.AddCycles(2);
}
static void In_RR_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    bool new_carry = target & 0x01;
    bool carry = reg->GetFlag(Registers::Flag::C);
    target = (target >> 1) | (carry << 7);

    memBus.Write(reg->HL, target);

    // Flags
    reg->SetFlag(Registers::Flag::Z, target == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, new_carry);

    cpu.AddCycles(4);
}
static void In_RR_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool new_carry = reg->A & 0x01;
    bool carry = reg->GetFlag(Registers::Flag::C);
    reg->A = (reg->A >> 1) | (carry << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, new_carry);

    cpu.AddCycles(2);
}

/** SLA r8 ***********************************************************************************************************/
static void In_SLA_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->B & 0x80;
    reg->B = (reg->B << 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->B == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SLA_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->C & 0x80;
    reg->C = (reg->C << 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->C == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SLA_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->D & 0x80;
    reg->D = (reg->D << 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->D == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SLA_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->E & 0x80;
    reg->E = (reg->E << 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->E == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SLA_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->H & 0x80;
    reg->H = (reg->H << 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->H == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SLA_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->L & 0x80;
    reg->L = (reg->L << 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->L == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SLA_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    bool carry = target & 0x80;
    target = (target << 1);

    memBus.Write(reg->HL, target);

    // Flags
    reg->SetFlag(Registers::Flag::Z, target == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(4);
}
static void In_SLA_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->A & 0x80;
    reg->A = (reg->A << 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}

/** SRA r8 ***********************************************************************************************************/
static void In_SRA_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->B & 0x01;
    bool signBit = reg->B & 0x80;

    reg->B = (reg->B >> 1) | (signBit << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->B == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SRA_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->C & 0x01;
    bool signBit = reg->C & 0x80;
    reg->C = (reg->C >> 1) | (signBit << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->C == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SRA_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->D & 0x01;
    bool signBit = reg->D & 0x80;
    reg->D = (reg->D >> 1) | (signBit << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->D == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SRA_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->E & 0x01;
    bool signBit = reg->E & 0x80;
    reg->E = (reg->E >> 1) | (signBit << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->E == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SRA_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->H & 0x01;
    bool signBit = reg->H & 0x80;
    reg->H = (reg->H >> 1) | (signBit << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->H == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SRA_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->L & 0x01;
    bool signBit = reg->L & 0x80;
    reg->L = (reg->L >> 1) | (signBit << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->L == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SRA_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    bool carry = target & 0x01;
    bool signBit = target & 0x80;
    target = (target >> 1) | (signBit << 7);

    memBus.Write(reg->HL, target);

    // Flags
    reg->SetFlag(Registers::Flag::Z, target == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(4);
}
static void In_SRA_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->A & 0x01;
    bool signBit = reg->A & 0x80;
    reg->A = (reg->A >> 1) | (signBit << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}

/** SWAP r8 ***********************************************************************************************************/
static void In_SWAP_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 low = reg->B & 0x0F;
    u8 high = reg->B & 0xF0;

    reg->B = (low << 4) | (high >> 4);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->B == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(2);
}
static void In_SWAP_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 low = reg->C & 0x0F;
    u8 high = reg->C & 0xF0;

    reg->C = (low << 4) | (high >> 4);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->C == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(2);
}
static void In_SWAP_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 low = reg->D & 0x0F;
    u8 high = reg->D & 0xF0;

    reg->D = (low << 4) | (high >> 4);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->D == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(2);
}
static void In_SWAP_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 low = reg->E & 0x0F;
    u8 high = reg->E & 0xF0;

    reg->E = (low << 4) | (high >> 4);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->E == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(2);
}
static void In_SWAP_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 low = reg->H & 0x0F;
    u8 high = reg->H & 0xF0;

    reg->H = (low << 4) | (high >> 4);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->H == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(2);
}
static void In_SWAP_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 low = reg->L & 0x0F;
    u8 high = reg->L & 0xF0;

    reg->L = (low << 4) | (high >> 4);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->L == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(2);
}
static void In_SWAP_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    u8 low = target & 0x0F;
    u8 high = target & 0xF0;

    target = (low << 4) | (high >> 4);

    memBus.Write(reg->HL, target);

    // Flags
    reg->SetFlag(Registers::Flag::Z, target == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(4);
}
static void In_SWAP_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 low = reg->A & 0x0F;
    u8 high = reg->A & 0xF0;

    reg->A = (low << 4) | (high >> 4);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, false);

    cpu.AddCycles(2);
}

/** SRL r8 ***********************************************************************************************************/
static void In_SRL_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->B & 0x01;

    reg->B = (reg->B >> 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->B == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SRL_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->C & 0x01;

    reg->C = (reg->C >> 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->C == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SRL_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->D & 0x01;

    reg->D = (reg->D >> 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->D == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SRL_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->E & 0x01;

    reg->E = (reg->E >> 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->E == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SRL_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->H & 0x01;

    reg->H = (reg->H >> 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->H == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SRL_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->L & 0x01;

    reg->L = (reg->L >> 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->L == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}
static void In_SRL_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    bool carry = target & 0x01;

    target = (target >> 1);

    memBus.Write(reg->HL, target);

    // Flags
    reg->SetFlag(Registers::Flag::Z, target == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(4);
}
static void In_SRL_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool carry = reg->A & 0x01;

    reg->A = (reg->A >> 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, reg->A == 0);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, false);
    reg->SetFlag(Registers::Flag::C, carry);

    cpu.AddCycles(2);
}

/** BIT b3, r8 *******************************************************************************************************/
static void In_BIT_0_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->B & (1 << 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_0_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->C & (1 << 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_0_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->D & (1 << 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_0_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->E & (1 << 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_0_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->H & (1 << 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_0_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->L & (1 << 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_0_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    bool result = target & (1 << 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(3);
}
static void In_BIT_0_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->A & (1 << 0);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}

static void In_BIT_1_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->B & (1 << 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_1_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->C & (1 << 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_1_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->D & (1 << 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_1_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->E & (1 << 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_1_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->H & (1 << 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_1_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->L & (1 << 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_1_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    bool result = target & (1 << 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(3);
}
static void In_BIT_1_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->A & (1 << 1);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}

static void In_BIT_2_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->B & (1 << 2);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_2_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->C & (1 << 2);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_2_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->D & (1 << 2);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_2_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->E & (1 << 2);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_2_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->H & (1 << 2);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_2_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->L & (1 << 2);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_2_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    bool result = target & (1 << 2);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(3);
}
static void In_BIT_2_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->A & (1 << 2);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}

static void In_BIT_3_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->B & (1 << 3);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_3_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->C & (1 << 3);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_3_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->D & (1 << 3);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_3_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->E & (1 << 3);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_3_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->H & (1 << 3);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_3_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->L & (1 << 3);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_3_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    bool result = target & (1 << 3);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(3);
}
static void In_BIT_3_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->A & (1 << 3);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}

static void In_BIT_4_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->B & (1 << 4);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_4_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->C & (1 << 4);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_4_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->D & (1 << 4);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_4_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->E & (1 << 4);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_4_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->H & (1 << 4);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_4_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->L & (1 << 4);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_4_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    bool result = target & (1 << 4);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(3);
}
static void In_BIT_4_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->A & (1 << 4);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}

static void In_BIT_5_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->B & (1 << 5);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_5_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->C & (1 << 5);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_5_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->D & (1 << 5);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_5_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->E & (1 << 5);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_5_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->H & (1 << 5);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_5_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->L & (1 << 5);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_5_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    bool result = target & (1 << 5);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(3);
}
static void In_BIT_5_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->A & (1 << 5);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}

static void In_BIT_6_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->B & (1 << 6);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_6_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->C & (1 << 6);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_6_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->D & (1 << 6);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_6_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->E & (1 << 6);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_6_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->H & (1 << 6);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_6_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->L & (1 << 6);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_6_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    bool result = target & (1 << 6);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(3);
}
static void In_BIT_6_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->A & (1 << 6);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}

static void In_BIT_7_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->B & (1 << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_7_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->C & (1 << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_7_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->D & (1 << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_7_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->E & (1 << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_7_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->H & (1 << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_7_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->L & (1 << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}
static void In_BIT_7_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    bool result = target & (1 << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(3);
}
static void In_BIT_7_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    bool result = reg->A & (1 << 7);

    // Flags
    reg->SetFlag(Registers::Flag::Z, !result);
    reg->SetFlag(Registers::Flag::N, false);
    reg->SetFlag(Registers::Flag::H, true);

    cpu.AddCycles(2);
}

/** RES b3, r8 *******************************************************************************************************/
static void In_RES_0_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->B &= ~(1 << 0);

    cpu.AddCycles(2);
}
static void In_RES_0_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->C &= ~(1 << 0);

    cpu.AddCycles(2);
}
static void In_RES_0_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->D &= ~(1 << 0);

    cpu.AddCycles(2);
}
static void In_RES_0_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->E &= ~(1 << 0);

    cpu.AddCycles(2);
}
static void In_RES_0_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->H &= ~(1 << 0);

    cpu.AddCycles(2);
}
static void In_RES_0_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->L &= ~(1 << 0);

    cpu.AddCycles(2);
}
static void In_RES_0_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    target &= ~(1 << 0);

    memBus.Write(reg->HL, target);

    cpu.AddCycles(4);
}
static void In_RES_0_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->A &= ~(1 << 0);

    cpu.AddCycles(2);
}

static void In_RES_1_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->B &= ~(1 << 1);

    cpu.AddCycles(2);
}
static void In_RES_1_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->C &= ~(1 << 1);

    cpu.AddCycles(2);
}
static void In_RES_1_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->D &= ~(1 << 1);

    cpu.AddCycles(2);
}
static void In_RES_1_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->E &= ~(1 << 1);

    cpu.AddCycles(2);
}
static void In_RES_1_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->H &= ~(1 << 1);

    cpu.AddCycles(2);
}
static void In_RES_1_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->L &= ~(1 << 1);

    cpu.AddCycles(2);
}
static void In_RES_1_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    target &= ~(1 << 1);

    memBus.Write(reg->HL, target);

    cpu.AddCycles(4);
}
static void In_RES_1_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->A &= ~(1 << 1);

    cpu.AddCycles(2);
}

static void In_RES_2_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->B &= ~(1 << 2);

    cpu.AddCycles(2);
}
static void In_RES_2_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->C &= ~(1 << 2);

    cpu.AddCycles(2);
}
static void In_RES_2_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->D &= ~(1 << 2);

    cpu.AddCycles(2);
}
static void In_RES_2_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->E &= ~(1 << 2);

    cpu.AddCycles(2);
}
static void In_RES_2_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->H &= ~(1 << 2);

    cpu.AddCycles(2);
}
static void In_RES_2_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->L &= ~(1 << 2);

    cpu.AddCycles(2);
}
static void In_RES_2_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    target &= ~(1 << 2);

    memBus.Write(reg->HL, target);

    cpu.AddCycles(4);
}
static void In_RES_2_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->A &= ~(1 << 2);

    cpu.AddCycles(2);
}

static void In_RES_3_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->B &= ~(1 << 3);

    cpu.AddCycles(2);
}
static void In_RES_3_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->C &= ~(1 << 3);

    cpu.AddCycles(2);
}
static void In_RES_3_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->D &= ~(1 << 3);

    cpu.AddCycles(2);
}
static void In_RES_3_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->E &= ~(1 << 3);

    cpu.AddCycles(2);
}
static void In_RES_3_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->H &= ~(1 << 3);

    cpu.AddCycles(2);
}
static void In_RES_3_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->L &= ~(1 << 3);

    cpu.AddCycles(2);
}
static void In_RES_3_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    target &= ~(1 << 3);

    memBus.Write(reg->HL, target);

    cpu.AddCycles(4);
}
static void In_RES_3_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->A &= ~(1 << 3);

    cpu.AddCycles(2);
}

static void In_RES_4_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->B &= ~(1 << 4);

    cpu.AddCycles(2);
}
static void In_RES_4_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->C &= ~(1 << 4);

    cpu.AddCycles(2);
}
static void In_RES_4_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->D &= ~(1 << 4);

    cpu.AddCycles(2);
}
static void In_RES_4_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->E &= ~(1 << 4);

    cpu.AddCycles(2);
}
static void In_RES_4_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->H &= ~(1 << 4);

    cpu.AddCycles(2);
}
static void In_RES_4_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->L &= ~(1 << 4);

    cpu.AddCycles(2);
}
static void In_RES_4_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    target &= ~(1 << 4);

    memBus.Write(reg->HL, target);

    cpu.AddCycles(4);
}
static void In_RES_4_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->A &= ~(1 << 4);

    cpu.AddCycles(2);
}

static void In_RES_5_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->B &= ~(1 << 5);

    cpu.AddCycles(2);
}
static void In_RES_5_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->C &= ~(1 << 5);

    cpu.AddCycles(2);
}
static void In_RES_5_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->D &= ~(1 << 5);

    cpu.AddCycles(2);
}
static void In_RES_5_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->E &= ~(1 << 5);

    cpu.AddCycles(2);
}
static void In_RES_5_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->H &= ~(1 << 5);

    cpu.AddCycles(2);
}
static void In_RES_5_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->L &= ~(1 << 5);

    cpu.AddCycles(2);
}
static void In_RES_5_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    target &= ~(1 << 5);

    memBus.Write(reg->HL, target);

    cpu.AddCycles(4);
}
static void In_RES_5_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->A &= ~(1 << 5);

    cpu.AddCycles(2);
}

static void In_RES_6_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->B &= ~(1 << 6);

    cpu.AddCycles(2);
}
static void In_RES_6_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->C &= ~(1 << 6);

    cpu.AddCycles(2);
}
static void In_RES_6_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->D &= ~(1 << 6);

    cpu.AddCycles(2);
}
static void In_RES_6_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->E &= ~(1 << 6);

    cpu.AddCycles(2);
}
static void In_RES_6_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->H &= ~(1 << 6);

    cpu.AddCycles(2);
}
static void In_RES_6_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->L &= ~(1 << 6);

    cpu.AddCycles(2);
}
static void In_RES_6_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    target &= ~(1 << 6);

    memBus.Write(reg->HL, target);

    cpu.AddCycles(4);
}
static void In_RES_6_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->A &= ~(1 << 6);

    cpu.AddCycles(2);
}

static void In_RES_7_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->B &= ~(1 << 7);

    cpu.AddCycles(2);
}
static void In_RES_7_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->C &= ~(1 << 7);

    cpu.AddCycles(2);
}
static void In_RES_7_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->D &= ~(1 << 7);

    cpu.AddCycles(2);
}
static void In_RES_7_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->E &= ~(1 << 7);

    cpu.AddCycles(2);
}
static void In_RES_7_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->H &= ~(1 << 7);

    cpu.AddCycles(2);
}
static void In_RES_7_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->L &= ~(1 << 7);

    cpu.AddCycles(2);
}
static void In_RES_7_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    target &= ~(1 << 7);

    memBus.Write(reg->HL, target);

    cpu.AddCycles(4);
}
static void In_RES_7_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->A &= ~(1 << 7);

    cpu.AddCycles(2);
}

/** SET b3, r8 *******************************************************************************************************/
static void In_SET_0_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->B |= (1 << 0);

    cpu.AddCycles(2);
}
static void In_SET_0_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->C |= (1 << 0);

    cpu.AddCycles(2);
}
static void In_SET_0_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->D |= (1 << 0);

    cpu.AddCycles(2);
}
static void In_SET_0_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->E |= (1 << 0);

    cpu.AddCycles(2);
}
static void In_SET_0_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->H |= (1 << 0);

    cpu.AddCycles(2);
}
static void In_SET_0_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->L |= (1 << 0);

    cpu.AddCycles(2);
}
static void In_SET_0_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    target |= (1 << 0);

    memBus.Write(reg->HL, target);

    cpu.AddCycles(4);
}
static void In_SET_0_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->A |= (1 << 0);

    cpu.AddCycles(2);
}

static void In_SET_1_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->B |= (1 << 1);

    cpu.AddCycles(2);
}
static void In_SET_1_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->C |= (1 << 1);

    cpu.AddCycles(2);
}
static void In_SET_1_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->D |= (1 << 1);

    cpu.AddCycles(2);
}
static void In_SET_1_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->E |= (1 << 1);

    cpu.AddCycles(2);
}
static void In_SET_1_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->H |= (1 << 1);

    cpu.AddCycles(2);
}
static void In_SET_1_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->L |= (1 << 1);

    cpu.AddCycles(2);
}
static void In_SET_1_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    target |= (1 << 1);

    memBus.Write(reg->HL, target);

    cpu.AddCycles(4);
}
static void In_SET_1_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->A |= (1 << 1);

    cpu.AddCycles(2);
}

static void In_SET_2_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->B |= (1 << 2);

    cpu.AddCycles(2);
}
static void In_SET_2_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->C |= (1 << 2);

    cpu.AddCycles(2);
}
static void In_SET_2_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->D |= (1 << 2);

    cpu.AddCycles(2);
}
static void In_SET_2_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->E |= (1 << 2);

    cpu.AddCycles(2);
}
static void In_SET_2_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->H |= (1 << 2);

    cpu.AddCycles(2);
}
static void In_SET_2_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->L |= (1 << 2);

    cpu.AddCycles(2);
}
static void In_SET_2_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    target |= (1 << 2);

    memBus.Write(reg->HL, target);

    cpu.AddCycles(4);
}
static void In_SET_2_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->A |= (1 << 2);

    cpu.AddCycles(2);
}

static void In_SET_3_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->B |= (1 << 3);

    cpu.AddCycles(2);
}
static void In_SET_3_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->C |= (1 << 3);

    cpu.AddCycles(2);
}
static void In_SET_3_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->D |= (1 << 3);

    cpu.AddCycles(2);
}
static void In_SET_3_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->E |= (1 << 3);

    cpu.AddCycles(2);
}
static void In_SET_3_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->H |= (1 << 3);

    cpu.AddCycles(2);
}
static void In_SET_3_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->L |= (1 << 3);

    cpu.AddCycles(2);
}
static void In_SET_3_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    target |= (1 << 3);

    memBus.Write(reg->HL, target);

    cpu.AddCycles(4);
}
static void In_SET_3_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->A |= (1 << 3);

    cpu.AddCycles(2);
}

static void In_SET_4_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->B |= (1 << 4);

    cpu.AddCycles(2);
}
static void In_SET_4_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->C |= (1 << 4);

    cpu.AddCycles(2);
}
static void In_SET_4_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->D |= (1 << 4);

    cpu.AddCycles(2);
}
static void In_SET_4_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->E |= (1 << 4);

    cpu.AddCycles(2);
}
static void In_SET_4_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->H |= (1 << 4);

    cpu.AddCycles(2);
}
static void In_SET_4_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->L |= (1 << 4);

    cpu.AddCycles(2);
}
static void In_SET_4_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    target |= (1 << 4);

    memBus.Write(reg->HL, target);

    cpu.AddCycles(4);
}
static void In_SET_4_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->A |= (1 << 4);

    cpu.AddCycles(2);
}

static void In_SET_5_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->B |= (1 << 5);

    cpu.AddCycles(2);
}
static void In_SET_5_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->C |= (1 << 5);

    cpu.AddCycles(2);
}
static void In_SET_5_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->D |= (1 << 5);

    cpu.AddCycles(2);
}
static void In_SET_5_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->E |= (1 << 5);

    cpu.AddCycles(2);
}
static void In_SET_5_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->H |= (1 << 5);

    cpu.AddCycles(2);
}
static void In_SET_5_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->L |= (1 << 5);

    cpu.AddCycles(2);
}
static void In_SET_5_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    target |= (1 << 5);

    memBus.Write(reg->HL, target);

    cpu.AddCycles(4);
}
static void In_SET_5_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->A |= (1 << 5);

    cpu.AddCycles(2);
}

static void In_SET_6_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->B |= (1 << 6);

    cpu.AddCycles(2);
}
static void In_SET_6_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->C |= (1 << 6);

    cpu.AddCycles(2);
}
static void In_SET_6_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->D |= (1 << 6);

    cpu.AddCycles(2);
}
static void In_SET_6_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->E |= (1 << 6);

    cpu.AddCycles(2);
}
static void In_SET_6_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->H |= (1 << 6);

    cpu.AddCycles(2);
}
static void In_SET_6_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->L |= (1 << 6);

    cpu.AddCycles(2);
}
static void In_SET_6_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    target |= (1 << 6);

    memBus.Write(reg->HL, target);

    cpu.AddCycles(4);
}
static void In_SET_6_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->A |= (1 << 6);

    cpu.AddCycles(2);
}

static void In_SET_7_B(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->B |= (1 << 7);

    cpu.AddCycles(2);
}
static void In_SET_7_C(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->C |= (1 << 7);

    cpu.AddCycles(2);
}
static void In_SET_7_D(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->D |= (1 << 7);

    cpu.AddCycles(2);
}
static void In_SET_7_E(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->E |= (1 << 7);

    cpu.AddCycles(2);
}
static void In_SET_7_H(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->H |= (1 << 7);

    cpu.AddCycles(2);
}
static void In_SET_7_L(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->L |= (1 << 7);

    cpu.AddCycles(2);
}
static void In_SET_7_pHL(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    u8 target = memBus.Read(reg->HL);
    target |= (1 << 7);

    memBus.Write(reg->HL, target);

    cpu.AddCycles(4);
}
static void In_SET_7_A(CPU& cpu, Bus& memBus) {
    Registers* reg = cpu.GetRegisters();
    reg->A |= (1 << 7);

    cpu.AddCycles(2);
}