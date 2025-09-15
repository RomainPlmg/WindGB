#pragma once

#include "bus.hpp"
#include "cpu.hpp"
#include "logger.hpp"

namespace WindGB {

using InstructionFunc = void (*)(CPU&, Bus&);  // Callback, takes CPU reference and return [[maybe_unused]] static void

struct Instruction {
    std::string name;
    InstructionFunc execute;
};

// Declaration of the opcodes table
extern std::array<Instruction, 256> instruction_table;
extern std::array<Instruction, 256> prefix_instruction_table;

[[maybe_unused]] static void In_Nop([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {}  // Nop

/** LD r16,n16 *******************************************************************************************************/
[[maybe_unused]] static void In_LD_BC_n16([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD BC, n16
    uint16_t value = cpu.fetch16();
    cpu.regs.BC = value;
}
[[maybe_unused]] static void In_LD_DE_n16([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD DE, n16
    uint16_t value = cpu.fetch16();
    cpu.regs.DE = value;
}
[[maybe_unused]] static void In_LD_HL_n16([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD HL, n16
    uint16_t value = cpu.fetch16();
    cpu.regs.HL = value;
}
[[maybe_unused]] static void In_LD_SP_n16([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD SP, n16
    uint16_t value = cpu.fetch16();
    cpu.regs.SP = value;
}

/** LD [r16],A *******************************************************************************************************/
[[maybe_unused]] static void In_LD_pBC_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD [BC], A
    uint8_t data = cpu.regs.A;
    uint16_t addr = cpu.regs.BC;
    bus.write(addr, data);
}
[[maybe_unused]] static void In_LD_pDE_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD [DE], A
    uint8_t data = cpu.regs.A;
    uint16_t addr = cpu.regs.DE;
    bus.write(addr, data);
}
[[maybe_unused]] static void In_LD_pHL_plus_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD [HL+], A
    uint8_t data = cpu.regs.A;
    uint16_t addr = cpu.regs.HL++;
    bus.write(addr, data);
}
[[maybe_unused]] static void In_LD_pHL_minus_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD [HL-], A
    uint8_t data = cpu.regs.A;
    uint16_t addr = cpu.regs.HL--;
    bus.write(addr, data);
}

/** INC r16 **********************************************************************************************************/
[[maybe_unused]] static void In_INC_BC([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // INC BC
    cpu.regs.BC++;
    bus.cycles(1);
}
[[maybe_unused]] static void In_INC_DE([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // INC DE
    cpu.regs.DE++;
    bus.cycles(1);
}
[[maybe_unused]] static void In_INC_HL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // INC HL
    cpu.regs.HL++;
    bus.cycles(1);
}
[[maybe_unused]] static void In_INC_SP([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // INC SP
    cpu.regs.SP++;
    bus.cycles(1);
}

/** INC r8 ***********************************************************************************************************/
[[maybe_unused]] static void In_INC_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // INC A
    auto& reg = cpu.regs;

    uint8_t result = reg.A + 1;

    // Set flags
    reg.set_flag(Registers::Flag::Z, result == 0);             // Z: Set if the result is 0
    reg.set_flag(Registers::Flag::N, false);                   // N: Always disabled for INC
    reg.set_flag(Registers::Flag::H, (reg.A & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg.A = result;
}
[[maybe_unused]] static void In_INC_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // INC B
    auto& reg = cpu.regs;

    uint8_t result = reg.B + 1;

    // Set flags
    reg.set_flag(Registers::Flag::Z, result == 0);             // Z: Set if the result is 0
    reg.set_flag(Registers::Flag::N, false);                   // N: Always disabled for INC
    reg.set_flag(Registers::Flag::H, (reg.B & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg.B = result;
}
[[maybe_unused]] static void In_INC_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // INC C
    auto& reg = cpu.regs;

    uint8_t result = reg.C + 1;

    // Set flags
    reg.set_flag(Registers::Flag::Z, result == 0);             // Z: Set if the result is 0
    reg.set_flag(Registers::Flag::N, false);                   // N: Always disabled for INC
    reg.set_flag(Registers::Flag::H, (reg.C & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg.C = result;
}
[[maybe_unused]] static void In_INC_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // INC D
    auto& reg = cpu.regs;

    uint8_t result = reg.D + 1;

    // Set flags
    reg.set_flag(Registers::Flag::Z, result == 0);             // Z: Set if the result is 0
    reg.set_flag(Registers::Flag::N, false);                   // N: Always disabled for INC
    reg.set_flag(Registers::Flag::H, (reg.D & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg.D = result;
}
[[maybe_unused]] static void In_INC_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // INC E
    auto& reg = cpu.regs;

    uint8_t result = reg.E + 1;

    // Set flags
    reg.set_flag(Registers::Flag::Z, result == 0);             // Z: Set if the result is 0
    reg.set_flag(Registers::Flag::N, false);                   // N: Always disabled for INC
    reg.set_flag(Registers::Flag::H, (reg.E & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg.E = result;
}
[[maybe_unused]] static void In_INC_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // INC H
    auto& reg = cpu.regs;

    uint8_t result = reg.H + 1;

    // Set flags
    reg.set_flag(Registers::Flag::Z, result == 0);             // Z: Set if the result is 0
    reg.set_flag(Registers::Flag::N, false);                   // N: Always disabled for INC
    reg.set_flag(Registers::Flag::H, (reg.H & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg.H = result;
}
[[maybe_unused]] static void In_INC_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // INC L
    auto& reg = cpu.regs;

    uint8_t result = reg.L + 1;

    // Set flags
    reg.set_flag(Registers::Flag::Z, result == 0);             // Z: Set if the result is 0
    reg.set_flag(Registers::Flag::N, false);                   // N: Always disabled for INC
    reg.set_flag(Registers::Flag::H, (reg.L & 0x0F) == 0x0F);  // H: Activated if a bit overflow 3->4

    reg.L = result;
}
[[maybe_unused]] static void In_INC_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // INC [HL]
    // read the value in memory at address HL
    uint16_t addr = cpu.regs.HL;
    uint8_t value = bus.read(addr);

    // Calculate the new value
    uint8_t newValue = value + 1;

    // write the new value to RAM
    bus.write(addr, newValue);

    // Update flags
    auto& reg = cpu.regs;
    reg.set_flag(Registers::Flag::Z, newValue == 0);              // Z: Set if the result is 0
    reg.set_flag(Registers::Flag::N, false);                      // N: Always disabled for INC
    reg.set_flag(Registers::Flag::H, (value & 0x0F) + 1 > 0x0F);  // H: Activated if a bit overflow 3->4
}

/** DEC r8 ***********************************************************************************************************/
[[maybe_unused]] static void In_DEC_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // DEC A
    auto& reg = cpu.regs;

    uint8_t result = reg.A - 1;

    // Set flags
    reg.set_flag(Registers::Flag::Z, result == 0);             // Z: Set if the result is 0
    reg.set_flag(Registers::Flag::N, true);                    // N: Always set for DEC
    reg.set_flag(Registers::Flag::H, (reg.A & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg.A = result;
}
[[maybe_unused]] static void In_DEC_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // DEC B
    auto& reg = cpu.regs;

    uint8_t result = reg.B - 1;

    // Set flags
    reg.set_flag(Registers::Flag::Z, result == 0);             // Z: Set if the result is 0
    reg.set_flag(Registers::Flag::N, true);                    // N: Always set for DEC
    reg.set_flag(Registers::Flag::H, (reg.B & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg.B = result;
}
[[maybe_unused]] static void In_DEC_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // DEC C
    auto& reg = cpu.regs;

    uint8_t result = reg.C - 1;

    // Set flags
    reg.set_flag(Registers::Flag::Z, result == 0);             // Z: Set if the result is 0
    reg.set_flag(Registers::Flag::N, true);                    // N: Always set for DEC
    reg.set_flag(Registers::Flag::H, (reg.C & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg.C = result;
}
[[maybe_unused]] static void In_DEC_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // DEC D
    auto& reg = cpu.regs;

    uint8_t result = reg.D - 1;

    // Set flags
    reg.set_flag(Registers::Flag::Z, result == 0);             // Z: Set if the result is 0
    reg.set_flag(Registers::Flag::N, true);                    // N: Always set for DEC
    reg.set_flag(Registers::Flag::H, (reg.D & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg.D = result;
}
[[maybe_unused]] static void In_DEC_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // DEC E
    auto& reg = cpu.regs;

    uint8_t result = reg.E - 1;

    // Set flags
    reg.set_flag(Registers::Flag::Z, result == 0);             // Z: Set if the result is 0
    reg.set_flag(Registers::Flag::N, true);                    // N: Always set for DEC
    reg.set_flag(Registers::Flag::H, (reg.E & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg.E = result;
}
[[maybe_unused]] static void In_DEC_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // DEC H
    auto& reg = cpu.regs;

    uint8_t result = reg.H - 1;

    // Set flags
    reg.set_flag(Registers::Flag::Z, result == 0);             // Z: Set if the result is 0
    reg.set_flag(Registers::Flag::N, true);                    // N: Always set for DEC
    reg.set_flag(Registers::Flag::H, (reg.H & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg.H = result;
}
[[maybe_unused]] static void In_DEC_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // DEC L
    auto& reg = cpu.regs;

    uint8_t result = reg.L - 1;

    // Set flags
    reg.set_flag(Registers::Flag::Z, result == 0);             // Z: Set if the result is 0
    reg.set_flag(Registers::Flag::N, true);                    // N: Always set for DEC
    reg.set_flag(Registers::Flag::H, (reg.L & 0x0F) == 0x00);  // H: Set if borrow from bit 4

    reg.L = result;
}
[[maybe_unused]] static void In_DEC_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // DEC [HL]
    auto& reg = cpu.regs;
    uint16_t addr = reg.HL;

    uint8_t value = bus.read(addr);
    uint8_t newValue = value - 1;
    bus.write(addr, newValue);

    // Update flags
    reg.set_flag(Registers::Flag::Z, newValue == 0);           // Z: Set if result == 0
    reg.set_flag(Registers::Flag::N, true);                    // N: Always set for DEC
    reg.set_flag(Registers::Flag::H, (value & 0x0F) == 0x00);  // H: Set if borrow from bit 4
}

/** LD r8,n8 *********************************************************************************************************/
[[maybe_unused]] static void In_LD_A_n8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD A, n8
    uint8_t value = cpu.fetch8();
    cpu.regs.A = value;
}
[[maybe_unused]] static void In_LD_B_n8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD B, n8
    uint8_t value = cpu.fetch8();
    cpu.regs.B = value;
}
[[maybe_unused]] static void In_LD_C_n8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD C, n8
    uint8_t value = cpu.fetch8();
    cpu.regs.C = value;
}
[[maybe_unused]] static void In_LD_D_n8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD D, n8
    uint8_t value = cpu.fetch8();
    cpu.regs.D = value;
}
[[maybe_unused]] static void In_LD_E_n8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD E, n8
    uint8_t value = cpu.fetch8();
    cpu.regs.E = value;
}
[[maybe_unused]] static void In_LD_H_n8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD H, n8
    uint8_t value = cpu.fetch8();
    cpu.regs.H = value;
}
[[maybe_unused]] static void In_LD_L_n8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD L, n8
    uint8_t value = cpu.fetch8();
    cpu.regs.L = value;
}
[[maybe_unused]] static void In_LD_pHL_n8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD [HL], n8
    uint8_t value = cpu.fetch8();
    uint16_t addr = cpu.regs.HL;
    bus.write(addr, value);
}

/** RLCA *************************************************************************************************************/
[[maybe_unused]] static void In_RLCA([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RLCA
    auto& reg = cpu.regs;
    uint8_t& regA = reg.A;
    uint8_t carry = (reg.A & 0x80) >> 7;

    regA = (regA << 1) | carry;

    // Set flags
    reg.set_flag(Registers::Flag::Z, false);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}

/** LD [n16],SP ******************************************************************************************************/
[[maybe_unused]] static void In_LD_pn16_SP([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD [n16], SP
    uint16_t addr = cpu.fetch16();
    uint16_t regSP = cpu.regs.SP;

    bus.write(addr, regSP & 0xFF);
    bus.write(addr + 1, regSP >> 8);
}

/** ADD HL,r16 *******************************************************************************************************/
[[maybe_unused]] static void In_ADD_HL_BC([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADD HL, BC
    auto& reg = cpu.regs;
    uint16_t regHL = reg.HL;
    uint16_t regBC = reg.BC;

    uint32_t result = regHL + regBC;  // uint32_t to detect overflow
    reg.HL = result & 0xFFFF;         // Keep only the fist 16 bits

    // Set flags
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regHL & 0x0FFF) + (regBC & 0x0FFF)) > 0x0FFF);  // Half-carry if overflow on 11 bits
    reg.set_flag(Registers::Flag::C, result > 0xFFFF);                                 // Carry if overflow on 16 bits

    bus.cycles(1);
}
[[maybe_unused]] static void In_ADD_HL_DE([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADD HL, DE
    auto& reg = cpu.regs;
    uint16_t regHL = reg.HL;
    uint16_t regDE = reg.DE;

    uint32_t result = regHL + regDE;  // uint32_t to detect overflow
    reg.HL = result & 0xFFFF;         // Keep only the fist 16 bits

    // Set flags
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regHL & 0x0FFF) + (regDE & 0x0FFF)) > 0x0FFF);  // Half-carry if overflow on 11 bits
    reg.set_flag(Registers::Flag::C, result > 0xFFFF);                                 // Carry if overflow on 16 bits

    bus.cycles(1);
}
[[maybe_unused]] static void In_ADD_HL_HL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADD HL, HL
    auto& reg = cpu.regs;
    uint16_t regHL = reg.HL;

    uint32_t result = regHL + regHL;  // uint32_t to detect overflow
    reg.HL = result & 0xFFFF;         // Keep only the fist 16 bits

    // Set flags
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regHL & 0x0FFF) + (regHL & 0x0FFF)) > 0x0FFF);  // Half-carry if overflow on 11 bits
    reg.set_flag(Registers::Flag::C, result > 0xFFFF);                                 // Carry if overflow on 16 bits

    bus.cycles(1);
}
[[maybe_unused]] static void In_ADD_HL_SP([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADD HL, DE
    auto& reg = cpu.regs;
    uint16_t regHL = reg.HL;
    uint16_t regSP = reg.SP;

    uint32_t result = regHL + regSP;  // uint32_t to detect overflow
    reg.HL = result & 0xFFFF;         // Keep only the fist 16 bits

    // Set flags
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regHL & 0x0FFF) + (regSP & 0x0FFF)) > 0x0FFF);  // Half-carry if overflow on 11 bits
    reg.set_flag(Registers::Flag::C, result > 0xFFFF);                                 // Carry if overflow on 16 bits

    bus.cycles(1);
}

/** LD A,[r16] *******************************************************************************************************/
[[maybe_unused]] static void In_LD_A_pBC([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD A, [BC]
    auto& reg = cpu.regs;
    uint16_t addr = reg.BC;
    uint8_t value = bus.read(addr);
    reg.A = value;
}
[[maybe_unused]] static void In_LD_A_pDE([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD A, [DE]
    auto& reg = cpu.regs;
    uint16_t addr = reg.DE;
    uint8_t value = bus.read(addr);
    reg.A = value;
}
[[maybe_unused]] static void In_LD_A_pHL_plus([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD A, [HL+]
    auto& reg = cpu.regs;
    uint16_t addr = reg.HL++;
    uint8_t value = bus.read(addr);
    reg.A = value;
}
[[maybe_unused]] static void In_LD_A_pHL_minus([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD A, [HL-]
    auto& reg = cpu.regs;
    uint16_t addr = reg.HL--;
    uint8_t value = bus.read(addr);
    reg.A = value;
}

/** DEC r16 **********************************************************************************************************/
[[maybe_unused]] static void In_DEC_BC([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // DEC BC
    cpu.regs.BC--;
    bus.cycles(1);
}
[[maybe_unused]] static void In_DEC_DE([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // DEC DE
    cpu.regs.DE--;
    bus.cycles(1);
}
[[maybe_unused]] static void In_DEC_HL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // DEC HL
    cpu.regs.HL--;
    bus.cycles(1);
}
[[maybe_unused]] static void In_DEC_SP([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // DEC SP
    cpu.regs.SP--;
    bus.cycles(1);
}

/** RRCA *************************************************************************************************************/
[[maybe_unused]] static void In_RRCA([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RRCA
    auto& reg = cpu.regs;
    uint8_t carry = reg.A & 0x01;

    reg.A = (reg.A >> 1) | (carry << 7);

    // Set flags
    reg.set_flag(Registers::Flag::Z, false);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}

/** STOP *************************************************************************************************************/
[[maybe_unused]] static void In_STOP([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // TODO
    // exit(0);
}

/** RLA **************************************************************************************************************/
[[maybe_unused]] static void In_RLA([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RLA
    auto& reg = cpu.regs;
    uint8_t oldCarry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint8_t newCarry = (reg.A & 0x80) >> 7;
    reg.A = reg.A << 1 | oldCarry;

    // Set flags
    reg.set_flag(Registers::Flag::Z, false);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, newCarry);
}

/** JR n8 ************************************************************************************************************/
[[maybe_unused]] static void In_JR_e8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // JR e8
    auto value = static_cast<int8_t>(cpu.fetch8());
    cpu.regs.PC += value;

    bus.cycles(1);
}

/** RRA **************************************************************************************************************/
[[maybe_unused]] static void In_RRA([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RRA
    auto& reg = cpu.regs;
    uint8_t oldCarry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint8_t newCarry = reg.A & 0x01;
    reg.A = reg.A >> 1 | (oldCarry << 7);

    // Set flags
    reg.set_flag(Registers::Flag::Z, false);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, newCarry);
}

/** JR cc,n8 *********************************************************************************************************/
[[maybe_unused]] static void In_JR_NZ_e8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // JR NZ, e8
    auto& reg = cpu.regs;
    auto value = static_cast<int8_t>(cpu.fetch8());
    auto regPC = static_cast<int16_t>(reg.PC);
    if (!reg.get_flag(Registers::Flag::Z)) {
        reg.PC = static_cast<uint16_t>(regPC + value);
        bus.cycles(1);
    }
}
[[maybe_unused]] static void In_JR_Z_e8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // JR Z, e8
    auto& reg = cpu.regs;
    auto value = static_cast<int8_t>(cpu.fetch8());
    if (reg.get_flag(Registers::Flag::Z)) {
        reg.PC = static_cast<uint16_t>(reg.PC + value);
        bus.cycles(1);
    }
}
[[maybe_unused]] static void In_JR_NC_e8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // JR NC, e8
    auto& reg = cpu.regs;
    int8_t value = static_cast<int8_t>(cpu.fetch8());
    if (!reg.get_flag(Registers::Flag::C)) {
        reg.PC = static_cast<uint16_t>(reg.PC + value);
        bus.cycles(1);
    }
}
[[maybe_unused]] static void In_JR_C_e8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // JR NC, e8
    auto& reg = cpu.regs;
    int8_t value = static_cast<int8_t>(cpu.fetch8());
    if (reg.get_flag(Registers::Flag::C)) {
        reg.PC = static_cast<uint16_t>(reg.PC + value);
        bus.cycles(1);
    }
}

/** DAA **************************************************************************************************************/
[[maybe_unused]] static void In_DAA([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // DAA
    auto& reg = cpu.regs;
    uint8_t adjustment = 0;
    bool setC = false;
    if (reg.get_flag(Registers::Flag::N)) {
        if (reg.get_flag(Registers::Flag::H)) adjustment += 0x06;
        if (reg.get_flag(Registers::Flag::C)) {
            adjustment += 0x60;
            setC = true;
        }
        reg.A -= adjustment;
    } else {
        if (reg.get_flag(Registers::Flag::H) || (reg.A & 0x0F) > 0x09) adjustment += 0x06;
        if (reg.get_flag(Registers::Flag::C) || reg.A > 0x99) {
            adjustment += 0x60;
            setC = true;
        }
        reg.A += adjustment;
    }

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, setC);
}

/** CPL **************************************************************************************************************/
[[maybe_unused]] static void In_CPL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // CPL
    auto& reg = cpu.regs;
    reg.A = ~reg.A;

    // Set flags
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, true);
}

/** SCF **************************************************************************************************************/
[[maybe_unused]] static void In_SCF([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SCF
    auto& reg = cpu.regs;

    // Set flags
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, true);
}

/** CCF **************************************************************************************************************/
[[maybe_unused]] static void In_CCF([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // CCF
    auto& reg = cpu.regs;

    bool cFlag = reg.get_flag(Registers::Flag::C) ? false : true;

    // Set flags
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, cFlag);
}

/** LD r8,r8 *********************************************************************************************************/
[[maybe_unused]] static void In_LD_A_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD A, A
}
[[maybe_unused]] static void In_LD_A_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD A, B
    auto& reg = cpu.regs;
    reg.A = reg.B;
}
[[maybe_unused]] static void In_LD_A_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD A, C
    auto& reg = cpu.regs;
    reg.A = reg.C;
}
[[maybe_unused]] static void In_LD_A_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD A, D
    auto& reg = cpu.regs;
    reg.A = reg.D;
}
[[maybe_unused]] static void In_LD_A_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD A, E
    auto& reg = cpu.regs;
    reg.A = reg.E;
}
[[maybe_unused]] static void In_LD_A_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD A, H
    auto& reg = cpu.regs;
    reg.A = reg.H;
}
[[maybe_unused]] static void In_LD_A_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD A, L
    auto& reg = cpu.regs;
    reg.A = reg.L;
}
[[maybe_unused]] static void In_LD_A_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD A, [HL]
    auto& reg = cpu.regs;
    uint8_t value = bus.read(reg.HL);
    reg.A = value;
}

[[maybe_unused]] static void In_LD_B_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD B, A
    auto& reg = cpu.regs;
    reg.B = reg.A;
}
[[maybe_unused]] static void In_LD_B_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD B, B
}
[[maybe_unused]] static void In_LD_B_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD B, C
    auto& reg = cpu.regs;
    reg.B = reg.C;
}
[[maybe_unused]] static void In_LD_B_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD B, D
    auto& reg = cpu.regs;
    reg.B = reg.D;
}
[[maybe_unused]] static void In_LD_B_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD B, E
    auto& reg = cpu.regs;
    reg.B = reg.E;
}
[[maybe_unused]] static void In_LD_B_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD B, H
    auto& reg = cpu.regs;
    reg.B = reg.H;
}
[[maybe_unused]] static void In_LD_B_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    // LD B, A
    auto& reg = cpu.regs;
    reg.B = reg.L;
}
[[maybe_unused]] static void In_LD_B_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD B, [HL]
    auto& reg = cpu.regs;
    uint8_t value = bus.read(reg.HL);
    reg.B = value;
}

[[maybe_unused]] static void In_LD_C_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD C, A
    auto& reg = cpu.regs;
    reg.C = reg.A;
}
[[maybe_unused]] static void In_LD_C_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD C, B
    auto& reg = cpu.regs;
    reg.C = reg.B;
}
[[maybe_unused]] static void In_LD_C_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD C, C
}
[[maybe_unused]] static void In_LD_C_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD C, D
    auto& reg = cpu.regs;
    reg.C = reg.D;
}
[[maybe_unused]] static void In_LD_C_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD C, E
    auto& reg = cpu.regs;
    reg.C = reg.E;
}
[[maybe_unused]] static void In_LD_C_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD C, H
    auto& reg = cpu.regs;
    reg.C = reg.H;
}
[[maybe_unused]] static void In_LD_C_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD C, L
    auto& reg = cpu.regs;
    reg.C = reg.L;
}
[[maybe_unused]] static void In_LD_C_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD C, [HL]
    auto& reg = cpu.regs;
    uint8_t value = bus.read(reg.HL);
    reg.C = value;
}

[[maybe_unused]] static void In_LD_D_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD D, A
    auto& reg = cpu.regs;
    reg.D = reg.A;
}
[[maybe_unused]] static void In_LD_D_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD D, B
    auto& reg = cpu.regs;
    reg.D = reg.B;
}
[[maybe_unused]] static void In_LD_D_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD D, C
    auto& reg = cpu.regs;
    reg.D = reg.C;
}
[[maybe_unused]] static void In_LD_D_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD D, D
}
[[maybe_unused]] static void In_LD_D_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD D, E
    auto& reg = cpu.regs;
    reg.D = reg.E;
}
[[maybe_unused]] static void In_LD_D_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD D, H
    auto& reg = cpu.regs;
    reg.D = reg.H;
}
[[maybe_unused]] static void In_LD_D_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD D, L
    auto& reg = cpu.regs;
    reg.D = reg.L;
}
[[maybe_unused]] static void In_LD_D_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD D, [HL]
    auto& reg = cpu.regs;
    uint8_t value = bus.read(reg.HL);
    reg.D = value;
}

[[maybe_unused]] static void In_LD_E_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD E, A
    auto& reg = cpu.regs;
    reg.E = reg.A;
}
[[maybe_unused]] static void In_LD_E_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD E, B
    auto& reg = cpu.regs;
    reg.E = reg.B;
}
[[maybe_unused]] static void In_LD_E_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD E, C
    auto& reg = cpu.regs;
    reg.E = reg.C;
}
[[maybe_unused]] static void In_LD_E_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD E, D
    auto& reg = cpu.regs;
    reg.E = reg.D;
}
[[maybe_unused]] static void In_LD_E_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD E, E
}
[[maybe_unused]] static void In_LD_E_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD E, H
    auto& reg = cpu.regs;
    reg.E = reg.H;
}
[[maybe_unused]] static void In_LD_E_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD E, L
    auto& reg = cpu.regs;
    reg.E = reg.L;
}
[[maybe_unused]] static void In_LD_E_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD E, [HL]
    auto& reg = cpu.regs;
    uint8_t value = bus.read(reg.HL);
    reg.E = value;
}

[[maybe_unused]] static void In_LD_H_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD H, A
    auto& reg = cpu.regs;
    reg.H = reg.A;
}
[[maybe_unused]] static void In_LD_H_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD H, B
    auto& reg = cpu.regs;
    reg.H = reg.B;
}
[[maybe_unused]] static void In_LD_H_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD H, C
    auto& reg = cpu.regs;
    reg.H = reg.C;
}
[[maybe_unused]] static void In_LD_H_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD H, D
    auto& reg = cpu.regs;
    reg.H = reg.D;
}
[[maybe_unused]] static void In_LD_H_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD H, E
    auto& reg = cpu.regs;
    reg.H = reg.E;
}
[[maybe_unused]] static void In_LD_H_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD H, H
}
[[maybe_unused]] static void In_LD_H_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD H, L
    auto& reg = cpu.regs;
    reg.H = reg.L;
}
[[maybe_unused]] static void In_LD_H_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD H, [HL]
    auto& reg = cpu.regs;
    uint8_t value = bus.read(reg.HL);
    reg.H = value;
}

[[maybe_unused]] static void In_LD_L_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD L, A
    auto& reg = cpu.regs;
    reg.L = reg.A;
}
[[maybe_unused]] static void In_LD_L_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD L, B
    auto& reg = cpu.regs;
    reg.L = reg.B;
}
[[maybe_unused]] static void In_LD_L_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD L, C
    auto& reg = cpu.regs;
    reg.L = reg.C;
}
[[maybe_unused]] static void In_LD_L_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD L, D
    auto& reg = cpu.regs;
    reg.L = reg.D;
}
[[maybe_unused]] static void In_LD_L_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD L, E
    auto& reg = cpu.regs;
    reg.L = reg.E;
}
[[maybe_unused]] static void In_LD_L_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD L, H
    auto& reg = cpu.regs;
    reg.L = reg.H;
}
[[maybe_unused]] static void In_LD_L_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD L, L
}
[[maybe_unused]] static void In_LD_L_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD L, [HL]
    auto& reg = cpu.regs;
    uint8_t value = bus.read(reg.HL);
    reg.L = value;
}

/** LD [HL],r8 *************************************************************************************************************/
[[maybe_unused]] static void In_LD_pHL_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD [HL], A
    auto& reg = cpu.regs;
    bus.write(reg.HL, reg.A);
}
[[maybe_unused]] static void In_LD_pHL_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD [HL], B
    auto& reg = cpu.regs;
    bus.write(reg.HL, reg.B);
}
[[maybe_unused]] static void In_LD_pHL_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD [HL], C
    auto& reg = cpu.regs;
    bus.write(reg.HL, reg.C);
}
[[maybe_unused]] static void In_LD_pHL_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD [HL], D
    auto& reg = cpu.regs;
    bus.write(reg.HL, reg.D);
}
[[maybe_unused]] static void In_LD_pHL_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD [HL], E
    auto& reg = cpu.regs;
    bus.write(reg.HL, reg.E);
}
[[maybe_unused]] static void In_LD_pHL_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD [HL], H
    auto& reg = cpu.regs;
    bus.write(reg.HL, reg.H);
}
[[maybe_unused]] static void In_LD_pHL_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD [HL], L
    auto& reg = cpu.regs;
    bus.write(reg.HL, reg.L);
}

/** HALT ************************************************************************************************************/
[[maybe_unused]] static void In_HALT([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // HALT
    cpu.halt();
}

/** ADD A,r8 ********************************************************************************************************/
[[maybe_unused]] static void In_ADD_A_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADD A, A
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint16_t result = regA + regA;  // uint16_t to detect overflow
    reg.A = result & 0xFF;          // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (regA & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                           // Carry if overflow on 7 bits
}
[[maybe_unused]] static void In_ADD_A_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADD A, B
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint16_t result = regA + reg.B;  // uint16_t to detect overflow
    reg.A = result & 0xFF;           // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (reg.B & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                            // Carry if overflow on 7 bits
}
[[maybe_unused]] static void In_ADD_A_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADD A, C
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint16_t result = regA + reg.C;  // uint16_t to detect overflow
    reg.A = result & 0xFF;           // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (reg.C & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                            // Carry if overflow on 7 bits
}
[[maybe_unused]] static void In_ADD_A_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADD A, D
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint16_t result = regA + reg.D;  // uint16_t to detect overflow
    reg.A = result & 0xFF;           // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (reg.D & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                            // Carry if overflow on 7 bits
}
[[maybe_unused]] static void In_ADD_A_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADD A, E
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint16_t result = regA + reg.E;  // uint16_t to detect overflow
    reg.A = result & 0xFF;           // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (reg.E & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                            // Carry if overflow on 7 bits
}
[[maybe_unused]] static void In_ADD_A_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADD A, H
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint16_t result = regA + reg.H;  // uint16_t to detect overflow
    reg.A = result & 0xFF;           // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (reg.H & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                            // Carry if overflow on 7 bits
}
[[maybe_unused]] static void In_ADD_A_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADD A, L
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint16_t result = regA + reg.L;  // uint16_t to detect overflow
    reg.A = result & 0xFF;           // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (reg.L & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                            // Carry if overflow on 7 bits
}

/** ADD A,[HL] ******************************************************************************************************/
[[maybe_unused]] static void In_ADD_A_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADD A, [HL]
    auto& reg = cpu.regs;
    uint8_t value = bus.read(reg.HL);
    uint8_t regA = reg.A;

    uint16_t result = regA + value;  // uint16_t to detect overflow
    reg.A = result & 0xFF;           // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (value & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                            // Carry if overflow on 7 bits
}

/** ADC A,r8 ********************************************************************************************************/
[[maybe_unused]] static void In_ADC_A_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADC A, A
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA + regA + carry;  // uint16_t to detect overflow
    reg.A = result & 0xFF;                  // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (regA & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                                   // Carry if overflow on 7 bits
}
[[maybe_unused]] static void In_ADC_A_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADC A, B
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA + reg.B + carry;  // uint16_t to detect overflow
    reg.A = result & 0xFF;                   // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (reg.B & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                                    // Carry if overflow on 7 bits
}
[[maybe_unused]] static void In_ADC_A_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADC A, C
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA + reg.C + carry;  // uint16_t to detect overflow
    reg.A = result & 0xFF;                   // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (reg.C & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                                    // Carry if overflow on 7 bits
}
[[maybe_unused]] static void In_ADC_A_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADC A, D
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA + reg.D + carry;  // uint16_t to detect overflow
    reg.A = result & 0xFF;                   // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (reg.D & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                                    // Carry if overflow on 7 bits
}
[[maybe_unused]] static void In_ADC_A_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADC A, E
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA + reg.E + carry;  // uint16_t to detect overflow
    reg.A = result & 0xFF;                   // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (reg.E & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                                    // Carry if overflow on 7 bits
}
[[maybe_unused]] static void In_ADC_A_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADC A, H
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA + reg.H + carry;  // uint16_t to detect overflow
    reg.A = result & 0xFF;                   // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (reg.H & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                                    // Carry if overflow on 7 bits
}
[[maybe_unused]] static void In_ADC_A_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADC A, L
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA + reg.L + carry;  // uint16_t to detect overflow
    reg.A = result & 0xFF;                   // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (reg.L & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                                    // Carry if overflow on 7 bits
}

/** ADC A,[HL] ********************************************************************************************************/
[[maybe_unused]] static void In_ADC_A_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADC A, [HL]
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t value = bus.read(reg.HL);
    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA + value + carry;  // uint16_t to detect overflow
    reg.A = result & 0xFF;                   // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (value & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                                    // Carry if overflow on 7 bits
}

/** SUB A,r8 ********************************************************************************************************/
[[maybe_unused]] static void In_SUB_A_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SUB A, A
    auto& reg = cpu.regs;

    reg.A = 0;  // Because A - A = 0

    // Flags
    reg.set_flag(Registers::Flag::Z, true);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_SUB_A_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SUB A, B
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint16_t result = regA - reg.B;  // uint16_t to detect borrow
    reg.A = result & 0xFF;           // Keep only the fist 8 bits

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, (regA & 0x0F) < (reg.B & 0x0F));
    reg.set_flag(Registers::Flag::C, regA < reg.B);
}
[[maybe_unused]] static void In_SUB_A_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SUB A, C
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint16_t result = regA - reg.C;  // uint16_t to detect borrow
    reg.A = result & 0xFF;           // Keep only the fist 8 bits

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, (regA & 0x0F) < (reg.C & 0x0F));
    reg.set_flag(Registers::Flag::C, regA < reg.C);
}
[[maybe_unused]] static void In_SUB_A_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SUB A, D
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint16_t result = regA - reg.D;  // uint16_t to detect borrow
    reg.A = result & 0xFF;           // Keep only the fist 8 bits

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, (regA & 0x0F) < (reg.D & 0x0F));
    reg.set_flag(Registers::Flag::C, regA < reg.D);
}
[[maybe_unused]] static void In_SUB_A_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SUB A, E
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint16_t result = regA - reg.E;  // uint16_t to detect borrow
    reg.A = result & 0xFF;           // Keep only the fist 8 bits

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, (regA & 0x0F) < (reg.E & 0x0F));
    reg.set_flag(Registers::Flag::C, regA < reg.E);
}
[[maybe_unused]] static void In_SUB_A_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SUB A, H
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint16_t result = regA - reg.H;  // uint16_t to detect borrow
    reg.A = result & 0xFF;           // Keep only the fist 8 bits

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, (regA & 0x0F) < (reg.H & 0x0F));
    reg.set_flag(Registers::Flag::C, regA < reg.H);
}
[[maybe_unused]] static void In_SUB_A_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SUB A, L
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint16_t result = regA - reg.L;  // uint16_t to detect borrow
    reg.A = result & 0xFF;           // Keep only the fist 8 bits

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, (regA & 0x0F) < (reg.L & 0x0F));
    reg.set_flag(Registers::Flag::C, regA < reg.L);
}

/** SUB A,[HL] ******************************************************************************************************/
[[maybe_unused]] static void In_SUB_A_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SUB A, [HL]
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;
    uint8_t value = bus.read(reg.HL);

    uint16_t result = regA - value;  // uint16_t to detect borrow
    reg.A = result & 0xFF;           // Keep only the fist 8 bits

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, (regA & 0x0F) < (value & 0x0F));
    reg.set_flag(Registers::Flag::C, regA < value);
}

/** SBC A,r8 ********************************************************************************************************/
[[maybe_unused]] static void In_SBC_A_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA - regA - carry;

    reg.A = result & 0xFF;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, ((regA ^ regA ^ result) & 0x10) != 0);
    reg.set_flag(Registers::Flag::C, carry != 0);
}
[[maybe_unused]] static void In_SBC_A_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SBC A, B
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;
    uint8_t regB = reg.B;

    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA - regB - carry;  // uint16_t to detect borrow
    reg.A = result & 0xFF;                  // Keep only the fist 8 bits

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, ((regA ^ regB ^ result) & 0x10) != 0);
    reg.set_flag(Registers::Flag::C, regA < regB + carry);
}
[[maybe_unused]] static void In_SBC_A_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SBC A, C
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA - reg.C - carry;  // uint16_t to detect borrow
    reg.A = result & 0xFF;                   // Keep only the fist 8 bits

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, ((regA ^ reg.C ^ result) & 0x10) != 0);
    reg.set_flag(Registers::Flag::C, regA < reg.C + carry);
}
[[maybe_unused]] static void In_SBC_A_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SBC A, D
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA - reg.D - carry;  // uint16_t to detect borrow
    reg.A = result & 0xFF;                   // Keep only the fist 8 bits

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, ((regA ^ reg.D ^ result) & 0x10) != 0);
    reg.set_flag(Registers::Flag::C, regA < reg.D + carry);
}
[[maybe_unused]] static void In_SBC_A_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SBC A, E
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA - reg.E - carry;  // uint16_t to detect borrow
    reg.A = result & 0xFF;                   // Keep only the fist 8 bits

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, ((regA ^ reg.E ^ result) & 0x10) != 0);
    reg.set_flag(Registers::Flag::C, regA < reg.E + carry);
}
[[maybe_unused]] static void In_SBC_A_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SBC A, H
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA - reg.H - carry;  // uint16_t to detect borrow
    reg.A = result & 0xFF;                   // Keep only the fist 8 bits

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, ((regA ^ reg.H ^ result) & 0x10) != 0);
    reg.set_flag(Registers::Flag::C, regA < reg.H + carry);
}
[[maybe_unused]] static void In_SBC_A_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SBC A, L
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA - reg.L - carry;  // uint16_t to detect borrow
    reg.A = result & 0xFF;                   // Keep only the fist 8 bits

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, ((regA ^ reg.L ^ result) & 0x10) != 0);
    reg.set_flag(Registers::Flag::C, regA < reg.L + carry);
}

/** SBC A,[HL] ******************************************************************************************************/
[[maybe_unused]] static void In_SBC_A_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SBC A, [HL]
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t value = bus.read(reg.HL);
    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA - value - carry;  // uint16_t to detect borrow
    reg.A = result & 0xFF;                   // Keep only the fist 8 bits

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, ((regA ^ value ^ result) & 0x10) != 0);
    reg.set_flag(Registers::Flag::C, regA < value + carry);
}

/** AND A,r8 ********************************************************************************************************/
[[maybe_unused]] static void In_AND_A_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // AND A, A
    auto& reg = cpu.regs;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_AND_A_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // AND A, B
    auto& reg = cpu.regs;
    reg.A &= reg.B;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_AND_A_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // AND A, C
    auto& reg = cpu.regs;
    reg.A &= reg.C;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_AND_A_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // AND A, D
    auto& reg = cpu.regs;
    reg.A &= reg.D;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_AND_A_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // AND A, E
    auto& reg = cpu.regs;
    reg.A &= reg.E;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_AND_A_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // AND A, H
    auto& reg = cpu.regs;
    reg.A &= reg.H;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_AND_A_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // AND A, L
    auto& reg = cpu.regs;
    reg.A &= reg.L;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
    reg.set_flag(Registers::Flag::C, false);
}

/** AND A,[HL] ******************************************************************************************************/
[[maybe_unused]] static void In_AND_A_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // AND A, [HL]
    auto& reg = cpu.regs;
    uint8_t value = bus.read(reg.HL);
    reg.A &= value;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
    reg.set_flag(Registers::Flag::C, false);
}

/** XOR A,r8 ********************************************************************************************************/
[[maybe_unused]] static void In_XOR_A_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // XOR A, A
    auto& reg = cpu.regs;
    reg.A = 0;

    // Flags
    reg.set_flag(Registers::Flag::Z, true);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_XOR_A_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // XOR A, B
    auto& reg = cpu.regs;
    reg.A ^= reg.B;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_XOR_A_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // XOR A, C
    auto& reg = cpu.regs;
    reg.A ^= reg.C;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_XOR_A_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // XOR A, D
    auto& reg = cpu.regs;
    reg.A ^= reg.D;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_XOR_A_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // XOR A, E
    auto& reg = cpu.regs;
    reg.A ^= reg.E;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_XOR_A_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // XOR A, H
    auto& reg = cpu.regs;
    reg.A ^= reg.H;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_XOR_A_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // XOR A, L
    auto& reg = cpu.regs;
    reg.A ^= reg.L;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}

/** XOR A,[HL] ******************************************************************************************************/
[[maybe_unused]] static void In_XOR_A_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // XOR A, [HL]
    auto& reg = cpu.regs;
    uint8_t value = bus.read(reg.HL);
    reg.A ^= value;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}

/** OR A,r8 *********************************************************************************************************/
[[maybe_unused]] static void In_OR_A_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // OR A, A
    auto& reg = cpu.regs;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_OR_A_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // OR A, B
    auto& reg = cpu.regs;
    reg.A |= reg.B;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_OR_A_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // OR A, C
    auto& reg = cpu.regs;
    reg.A |= reg.C;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_OR_A_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // OR A, D
    auto& reg = cpu.regs;
    reg.A |= reg.D;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_OR_A_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // OR A, E
    auto& reg = cpu.regs;
    reg.A |= reg.E;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_OR_A_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // OR A, H
    auto& reg = cpu.regs;
    reg.A |= reg.H;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_OR_A_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // OR A, L
    auto& reg = cpu.regs;
    reg.A |= reg.L;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}

/** OR A,[HL] *******************************************************************************************************/
[[maybe_unused]] static void In_OR_A_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // OR A, [HL]
    auto& reg = cpu.regs;
    uint8_t value = bus.read(reg.HL);
    reg.A |= value;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}

/** CP A,r8 ********************************************************************************************************/
[[maybe_unused]] static void In_CP_A_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // CP A, A
    auto& reg = cpu.regs;

    // Flags
    reg.set_flag(Registers::Flag::Z, true);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_CP_A_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // CP A, B
    auto& reg = cpu.regs;

    uint16_t result = reg.A - reg.B;  // uint16_t to detect borrow

    // Flags
    reg.set_flag(Registers::Flag::Z, result == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, (reg.A & 0x0F) < (reg.B & 0x0F));
    reg.set_flag(Registers::Flag::C, reg.B > reg.A);
}
[[maybe_unused]] static void In_CP_A_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // CP A, C
    auto& reg = cpu.regs;

    uint16_t result = reg.A - reg.C;  // uint16_t to detect borrow

    // Flags
    reg.set_flag(Registers::Flag::Z, result == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, (reg.A & 0x0F) < (reg.C & 0x0F));
    reg.set_flag(Registers::Flag::C, reg.C > reg.A);
}
[[maybe_unused]] static void In_CP_A_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // CP A, D
    auto& reg = cpu.regs;

    uint16_t result = reg.A - reg.D;  // uint16_t to detect borrow

    // Flags
    reg.set_flag(Registers::Flag::Z, result == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, (reg.A & 0x0F) < (reg.D & 0x0F));
    reg.set_flag(Registers::Flag::C, reg.D > reg.A);
}
[[maybe_unused]] static void In_CP_A_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // CP A, E
    auto& reg = cpu.regs;

    uint16_t result = reg.A - reg.E;  // uint16_t to detect borrow

    // Flags
    reg.set_flag(Registers::Flag::Z, result == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, (reg.A & 0x0F) < (reg.E & 0x0F));
    reg.set_flag(Registers::Flag::C, reg.E > reg.A);
}
[[maybe_unused]] static void In_CP_A_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // CP A, H
    auto& reg = cpu.regs;

    uint16_t result = reg.A - reg.H;  // uint16_t to detect borrow

    // Flags
    reg.set_flag(Registers::Flag::Z, result == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, (reg.A & 0x0F) < (reg.H & 0x0F));
    reg.set_flag(Registers::Flag::C, reg.H > reg.A);
}
[[maybe_unused]] static void In_CP_A_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // CP A, L
    auto& reg = cpu.regs;

    uint16_t result = reg.A - reg.L;  // uint16_t to detect borrow

    // Flags
    reg.set_flag(Registers::Flag::Z, result == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, (reg.A & 0x0F) < (reg.L & 0x0F));
    reg.set_flag(Registers::Flag::C, reg.L > reg.A);
}
[[maybe_unused]] static void In_CP_A_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // CP A, [HL]
    auto& reg = cpu.regs;

    uint8_t value = bus.read(reg.HL);
    uint16_t result = reg.A - value;  // uint16_t to detect borrow

    // Flags
    reg.set_flag(Registers::Flag::Z, result == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, (reg.A & 0x0F) < (value & 0x0F));
    reg.set_flag(Registers::Flag::C, value > reg.A);
}

/** ADD A,n8 ********************************************************************************************************/
[[maybe_unused]] static void In_ADD_A_n8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADD A, n8
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t value = cpu.fetch8();
    uint16_t result = regA + value;  // uint16_t to detect overflow
    reg.A = result & 0xFF;           // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (value & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                            // Carry if overflow on 7 bits
}

/** ADC A,n8 ********************************************************************************************************/
[[maybe_unused]] static void In_ADC_A_n8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADC A, n8
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t value = cpu.fetch8();
    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA + value + carry;  // uint16_t to detect overflow
    reg.A = result & 0xFF;                   // Keep only the fist 8 bits

    // Set flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regA & 0x0F) + (value & 0x0F) + carry) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, result > 0xFF);                                    // Carry if overflow on 7 bits
}

/** SUB A,n8 ********************************************************************************************************/
[[maybe_unused]] static void In_SUB_A_n8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SUB A, n8
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t value = cpu.fetch8();
    uint16_t result = regA - value;  // uint16_t to detect borrow
    reg.A = result & 0xFF;           // Keep only the fist 8 bits

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, (regA & 0x0F) < (value & 0x0F));
    reg.set_flag(Registers::Flag::C, result > 0xFF);
}

/** SBC A,n8 ********************************************************************************************************/
[[maybe_unused]] static void In_SBC_A_n8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // SBC A, n8
    auto& reg = cpu.regs;
    uint8_t regA = reg.A;

    uint8_t value = cpu.fetch8();
    uint8_t carry = reg.get_flag(Registers::Flag::C) ? 1 : 0;
    uint16_t result = regA - value - carry;  // uint16_t to detect borrow
    reg.A = result & 0xFF;                   // Keep only the fist 8 bits

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, ((regA ^ value ^ result) & 0x10));
    reg.set_flag(Registers::Flag::C, result > 0xFF);
}

/** AND A,n8 ********************************************************************************************************/
[[maybe_unused]] static void In_AND_A_n8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // AND A, n8
    auto& reg = cpu.regs;
    uint8_t value = cpu.fetch8();
    reg.A &= value;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
    reg.set_flag(Registers::Flag::C, false);
}

/** XOR A,n8 ********************************************************************************************************/
[[maybe_unused]] static void In_XOR_A_n8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // XOR A, n8
    auto& reg = cpu.regs;
    uint8_t value = cpu.fetch8();
    reg.A ^= value;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}

/** OR A,n8 *********************************************************************************************************/
[[maybe_unused]] static void In_OR_A_n8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // OR A, n8
    auto& reg = cpu.regs;
    uint8_t value = cpu.fetch8();
    reg.A |= value;

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}

/** CP A,n8 *********************************************************************************************************/
[[maybe_unused]] static void In_CP_A_n8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // CP A, n8
    auto& reg = cpu.regs;

    uint8_t value = cpu.fetch8();
    uint16_t result = reg.A - value;  // uint16_t to detect borrow

    // Flags
    reg.set_flag(Registers::Flag::Z, result == 0);
    reg.set_flag(Registers::Flag::N, true);
    reg.set_flag(Registers::Flag::H, (reg.A & 0x0F) < (value & 0x0F));
    reg.set_flag(Registers::Flag::C, value > reg.A);
}

/** RET cc ***********************************************************************************************************/
[[maybe_unused]] static void In_RET_NZ([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RET NZ
    auto& reg = cpu.regs;

    if (!reg.get_flag(Registers::Flag::Z)) {
        reg.PC = cpu.pop16();
        bus.cycles(1);
    }
    bus.cycles(1);
}
[[maybe_unused]] static void In_RET_Z([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RET Z
    auto& reg = cpu.regs;

    if (reg.get_flag(Registers::Flag::Z)) {
        reg.PC = cpu.pop16();
        bus.cycles(1);
    }
    bus.cycles(1);
}
[[maybe_unused]] static void In_RET_NC([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RET NC
    auto& reg = cpu.regs;

    if (!reg.get_flag(Registers::Flag::C)) {
        reg.PC = cpu.pop16();
        bus.cycles(1);
    }
    bus.cycles(1);
}
[[maybe_unused]] static void In_RET_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RET C
    auto& reg = cpu.regs;

    if (reg.get_flag(Registers::Flag::C)) {
        reg.PC = cpu.pop16();
        bus.cycles(1);
    }
    bus.cycles(1);
}

/** RET **************************************************************************************************************/
[[maybe_unused]] static void In_RET([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RET
    auto& reg = cpu.regs;
    reg.PC = cpu.pop16();
    bus.cycles(1);
}

/** RETI *************************************************************************************************************/
[[maybe_unused]] static void In_RETI([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RETI
    auto& reg = cpu.regs;
    reg.PC = cpu.pop16();
    cpu.get_interrupt_handler().ime = true;
    bus.cycles(1);
}

/** JP cc,n16 ********************************************************************************************************/
[[maybe_unused]] static void In_JP_NZ_n16([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // JP NZ, n16
    auto& reg = cpu.regs;
    uint16_t value = cpu.fetch16();

    if (!reg.get_flag(Registers::Flag::Z)) {
        reg.PC = value;
        bus.cycles(1);
    }
}
[[maybe_unused]] static void In_JP_Z_n16([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // JP Z, n16
    auto& reg = cpu.regs;
    uint16_t value = cpu.fetch16();

    if (reg.get_flag(Registers::Flag::Z)) {
        reg.PC = value;
        bus.cycles(1);
    }
}
[[maybe_unused]] static void In_JP_NC_n16([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // JP NC, n16
    auto& reg = cpu.regs;
    uint16_t value = cpu.fetch16();

    if (!reg.get_flag(Registers::Flag::C)) {
        reg.PC = value;
        bus.cycles(1);
    }
}
[[maybe_unused]] static void In_JP_C_n16([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // JP C, n16
    auto& reg = cpu.regs;
    uint16_t value = cpu.fetch16();

    if (reg.get_flag(Registers::Flag::C)) {
        reg.PC = value;
        bus.cycles(1);
    }
}

/** JP n16 ***********************************************************************************************************/
[[maybe_unused]] static void In_JP_n16([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // JP n16
    auto& reg = cpu.regs;
    uint16_t value = cpu.fetch16();
    reg.PC = value;
    bus.cycles(1);
}

/** JP HL ************************************************************************************************************/
[[maybe_unused]] static void In_JP_HL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // JP HL
    auto& reg = cpu.regs;
    reg.PC = reg.HL;
}

/** CALL cc,n16 ******************************************************************************************************/
[[maybe_unused]] static void In_CALL_NZ_n16([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // CALL NZ, n16
    auto& reg = cpu.regs;
    uint16_t addr = cpu.fetch16();

    if (!reg.get_flag(Registers::Flag::Z)) {
        cpu.push16(reg.PC);
        reg.PC = addr;
        bus.cycles(1);
    }
}
[[maybe_unused]] static void In_CALL_Z_n16([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // CALL Z, n16
    auto& reg = cpu.regs;
    uint16_t addr = cpu.fetch16();

    if (reg.get_flag(Registers::Flag::Z)) {
        cpu.push16(reg.PC);
        reg.PC = addr;
        bus.cycles(1);
    }
}
[[maybe_unused]] static void In_CALL_NC_n16([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // CALL NC, n16
    auto& reg = cpu.regs;
    uint16_t addr = cpu.fetch16();

    if (!reg.get_flag(Registers::Flag::C)) {
        cpu.push16(reg.PC);
        reg.PC = addr;
        bus.cycles(1);
    }
}
[[maybe_unused]] static void In_CALL_C_n16([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // CALL C, n16
    auto& reg = cpu.regs;
    uint16_t addr = cpu.fetch16();

    if (reg.get_flag(Registers::Flag::C)) {
        cpu.push16(reg.PC);
        reg.PC = addr;
        bus.cycles(1);
    }
}

/** CALL n16 *********************************************************************************************************/
[[maybe_unused]] static void In_CALL_n16([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // CALL n16
    auto& reg = cpu.regs;

    uint16_t addr = cpu.fetch16();

    cpu.push16(reg.PC);
    reg.PC = addr;
    bus.cycles(1);
}

/** RST vec **********************************************************************************************************/
[[maybe_unused]] static void In_RST_00H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RST 00H
    auto& reg = cpu.regs;
    cpu.push16(reg.PC);
    reg.PC = 0x00;
    bus.cycles(1);
}
[[maybe_unused]] static void In_RST_08H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RST 08H
    auto& reg = cpu.regs;
    cpu.push16(reg.PC);
    reg.PC = 0x08;
    bus.cycles(1);
}
[[maybe_unused]] static void In_RST_10H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RST 10H
    auto& reg = cpu.regs;
    cpu.push16(reg.PC);
    reg.PC = 0x10;
    bus.cycles(1);
}
[[maybe_unused]] static void In_RST_18H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RST 18H
    auto& reg = cpu.regs;
    cpu.push16(reg.PC);
    reg.PC = 0x18;
    bus.cycles(1);
}
[[maybe_unused]] static void In_RST_20H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RST 20H
    auto& reg = cpu.regs;
    cpu.push16(reg.PC);
    reg.PC = 0x20;
    bus.cycles(1);
}
[[maybe_unused]] static void In_RST_28H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RST 28H
    auto& reg = cpu.regs;
    cpu.push16(reg.PC);
    reg.PC = 0x28;
    bus.cycles(1);
}
[[maybe_unused]] static void In_RST_30H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RST 30H
    auto& reg = cpu.regs;
    cpu.push16(reg.PC);
    reg.PC = 0x30;
    bus.cycles(1);
}
[[maybe_unused]] static void In_RST_38H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // RST 38H
    auto& reg = cpu.regs;
    cpu.push16(reg.PC);
    reg.PC = 0x38;
    bus.cycles(1);
}

/** POP AF ***********************************************************************************************************/
[[maybe_unused]] static void In_PIn_AF([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // POP AF
    auto& reg = cpu.regs;
    reg.AF = cpu.pop16();
    reg.F &= 0xF0;  // 4 LSB of F registers need to be always at 0

    // Flags
    reg.set_flag(Registers::Flag::Z, (reg.F & 0x80) != 0);
    reg.set_flag(Registers::Flag::N, (reg.F & 0x40) != 0);
    reg.set_flag(Registers::Flag::H, (reg.F & 0x20) != 0);
    reg.set_flag(Registers::Flag::C, (reg.F & 0x10) != 0);
}

/** POP r16 **********************************************************************************************************/
[[maybe_unused]] static void In_PIn_BC([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // POP BC
    auto& reg = cpu.regs;
    reg.BC = cpu.pop16();
}
[[maybe_unused]] static void In_PIn_DE([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // POP DE
    auto& reg = cpu.regs;
    reg.DE = cpu.pop16();
}
[[maybe_unused]] static void In_PIn_HL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // POP HL
    auto& reg = cpu.regs;
    reg.HL = cpu.pop16();
}

/** PUSH AF **********************************************************************************************************/
[[maybe_unused]] static void In_PUSH_AF([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // PUSH AF
    auto& reg = cpu.regs;

    // Clear the 4 LSB of F register (for security)
    reg.F &= 0xF0;

    cpu.push16(reg.AF);
    bus.cycles(1);
}

/** PUSH r16 *********************************************************************************************************/
[[maybe_unused]] static void In_PUSH_BC([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // PUSH BC
    auto& reg = cpu.regs;

    cpu.push16(reg.BC);
    bus.cycles(1);
}
[[maybe_unused]] static void In_PUSH_DE([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // PUSH DE
    auto& reg = cpu.regs;

    cpu.push16(reg.DE);
    bus.cycles(1);
}
[[maybe_unused]] static void In_PUSH_HL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // PUSH HL
    auto& reg = cpu.regs;

    cpu.push16(reg.HL);
    bus.cycles(1);
}

/** LDH [C],A ********************************************************************************************************/
[[maybe_unused]] static void In_LDH_pC_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LDH [C], A
    auto& reg = cpu.regs;

    uint16_t addr = 0xFF00 + reg.C;
    bus.write(addr, reg.A);
}

/** LDH [n8],A *******************************************************************************************************/
[[maybe_unused]] static void In_LDH_pn8_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LDH [n8], A
    auto& reg = cpu.regs;

    uint16_t addr = 0xFF00 + cpu.fetch8();
    bus.write(addr, reg.A);
}

/** LD [n16],A *******************************************************************************************************/
[[maybe_unused]] static void In_LD_pn16_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD [n16], A
    auto& reg = cpu.regs;

    uint16_t addr = cpu.fetch16();
    bus.write(addr, reg.A);
}

/** LDH A,[C] ********************************************************************************************************/
[[maybe_unused]] static void In_LDH_A_pC([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LDH A, [C]
    auto& reg = cpu.regs;

    uint8_t value = bus.read(0xFF00 + reg.C);
    reg.A = value;
}

/** LDH A,[n8] *******************************************************************************************************/
[[maybe_unused]] static void In_LDH_A_pn8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LDH A, [n8]
    auto& reg = cpu.regs;

    uint16_t addr = 0xFF00 + cpu.fetch8();
    uint8_t value = bus.read(addr);
    reg.A = value;
}

/** LD A,[n16] ******************************************************************************************************/
[[maybe_unused]] static void In_LD_A_pn16([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD A, [n16]
    auto& reg = cpu.regs;

    uint16_t addr = cpu.fetch16();
    uint8_t value = bus.read(addr);
    reg.A = value;
}

/** ADD SP,e8 ********************************************************************************************************/
[[maybe_unused]] static void In_ADD_SP_e8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // ADD SP, e8
    auto& reg = cpu.regs;
    uint16_t regSP = reg.SP;

    int8_t value = static_cast<int8_t>(cpu.fetch8());
    uint32_t result = regSP + value;
    reg.SP = result & 0xFFFF;  // Keep only the fist 16 bits

    // Flags
    reg.set_flag(Registers::Flag::Z, false);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regSP & 0x0F) + (value & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, ((regSP & 0xFF) + (value & 0xFF)) > 0xFF);  // Carry if overflow on 7 bits

    bus.cycles(2);
}

/** LD HL,SP+e8 ******************************************************************************************************/
[[maybe_unused]] static void In_LD_HL_SP_plus_e8([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD HL, SP+e8
    auto& reg = cpu.regs;
    uint16_t regSP = reg.SP;

    int8_t value = static_cast<int8_t>(cpu.fetch8());
    uint32_t result = regSP + value;
    reg.HL = result & 0xFFFF;

    // Flags
    reg.set_flag(Registers::Flag::Z, false);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, ((regSP & 0x0F) + (value & 0x0F)) > 0x0F);  // Half-carry if carry from bit 3 to bit 4
    reg.set_flag(Registers::Flag::C, ((regSP & 0xFF) + (value & 0xFF)) > 0xFF);  // Carry if overflow on 7 bits

    bus.cycles(1);
}

/** LD SP,HL *********************************************************************************************************/
[[maybe_unused]] static void In_LD_SP_HL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // LD SP, HL
    auto& reg = cpu.regs;
    reg.SP = reg.HL;
    bus.cycles(1);
}

/** DI ***************************************************************************************************************/
[[maybe_unused]] static void In_DI([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // DI
    cpu.get_interrupt_handler().ime = false;
}

/** EI ***************************************************************************************************************/
[[maybe_unused]] static void In_EI([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {  // EI
    cpu.request_ime_en();
}

/** Prefix ***********************************************************************************************************/
[[maybe_unused]] static void In_Handle_CB([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {}

/** Invalid **********************************************************************************************************/
[[maybe_unused]] static void In_Invalid([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    LOG_ERROR("Invalid instruction.");
    exit(EXIT_FAILURE);
}

/***********************/
/* PREFIX INSTRUCTIONS */
/***********************/
/** RLC r8 ***********************************************************************************************************/
[[maybe_unused]] static void In_RLC_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.B & 0x80;
    reg.B = (reg.B << 1) | (carry ? 1 : 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.B == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_RLC_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.C & 0x80;
    reg.C = (reg.C << 1) | (carry ? 1 : 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.C == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_RLC_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.D & 0x80;
    reg.D = (reg.D << 1) | (carry ? 1 : 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.D == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_RLC_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.E & 0x80;
    reg.E = (reg.E << 1) | (carry ? 1 : 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.E == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_RLC_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.H & 0x80;
    reg.H = (reg.H << 1) | (carry ? 1 : 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.H == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_RLC_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.L & 0x80;
    reg.L = (reg.L << 1) | (carry ? 1 : 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.L == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_RLC_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    bool carry = target & 0x80;
    target = (target << 1) | (carry ? 1 : 0);

    bus.write(reg.HL, target);

    // Flags
    reg.set_flag(Registers::Flag::Z, target == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_RLC_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.A & 0x80;
    reg.A = (reg.A << 1) | (carry ? 1 : 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A ? false : true);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}

/** RRC r8 ***********************************************************************************************************/
[[maybe_unused]] static void In_RRC_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.B & 0x01;
    reg.B = (reg.B >> 1) | (carry << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.B == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_RRC_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.C & 0x01;
    reg.C = (reg.C >> 1) | (carry << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.C == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_RRC_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.D & 0x01;
    reg.D = (reg.D >> 1) | (carry << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.D == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_RRC_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.E & 0x01;
    reg.E = (reg.E >> 1) | (carry << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.E == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_RRC_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.H & 0x01;
    reg.H = (reg.H >> 1) | (carry << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.H == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_RRC_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.L & 0x01;
    reg.L = (reg.L >> 1) | (carry << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.L == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_RRC_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    bool carry = target & 0x01;
    target = (target >> 1) | (carry << 7);

    bus.write(reg.HL, target);

    // Flags
    reg.set_flag(Registers::Flag::Z, target == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_RRC_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.A & 0x01;
    reg.A = (reg.A >> 1) | (carry << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}

/** RL r8 ***********************************************************************************************************/
[[maybe_unused]] static void In_RL_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool new_carry = reg.B & 0x80;
    bool carry = reg.get_flag(Registers::Flag::C);
    reg.B = (reg.B << 1) | (carry ? 1 : 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.B == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, new_carry);
}
[[maybe_unused]] static void In_RL_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool new_carry = reg.C & 0x80;
    bool carry = reg.get_flag(Registers::Flag::C);
    reg.C = (reg.C << 1) | (carry ? 1 : 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.C == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, new_carry);
}
[[maybe_unused]] static void In_RL_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool new_carry = reg.D & 0x80;
    bool carry = reg.get_flag(Registers::Flag::C);
    reg.D = (reg.D << 1) | (carry ? 1 : 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.D == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, new_carry);
}
[[maybe_unused]] static void In_RL_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool new_carry = reg.E & 0x80;
    bool carry = reg.get_flag(Registers::Flag::C);
    reg.E = (reg.E << 1) | (carry ? 1 : 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.E == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, new_carry);
}
[[maybe_unused]] static void In_RL_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool new_carry = reg.H & 0x80;
    bool carry = reg.get_flag(Registers::Flag::C);
    reg.H = (reg.H << 1) | (carry ? 1 : 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.H == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, new_carry);
}
[[maybe_unused]] static void In_RL_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool new_carry = reg.L & 0x80;
    bool carry = reg.get_flag(Registers::Flag::C);
    reg.L = (reg.L << 1) | (carry ? 1 : 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.L == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, new_carry);
}
[[maybe_unused]] static void In_RL_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    bool new_carry = target & 0x80;
    bool carry = reg.get_flag(Registers::Flag::C);
    target = (target << 1) | (carry ? 1 : 0);

    bus.write(reg.HL, target);

    // Flags
    reg.set_flag(Registers::Flag::Z, target == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, new_carry);
}
[[maybe_unused]] static void In_RL_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool new_carry = reg.A & 0x80;
    bool carry = reg.get_flag(Registers::Flag::C);
    reg.A = (reg.A << 1) | (carry ? 1 : 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, new_carry);
}

/** RR r8 ***********************************************************************************************************/
[[maybe_unused]] static void In_RR_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool new_carry = reg.B & 0x01;
    bool carry = reg.get_flag(Registers::Flag::C);
    reg.B = (reg.B >> 1) | (carry << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.B == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, new_carry);
}
[[maybe_unused]] static void In_RR_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool new_carry = reg.C & 0x01;
    bool carry = reg.get_flag(Registers::Flag::C);
    reg.C = (reg.C >> 1) | (carry << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.C == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, new_carry);
}
[[maybe_unused]] static void In_RR_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool new_carry = reg.D & 0x01;
    bool carry = reg.get_flag(Registers::Flag::C);
    reg.D = (reg.D >> 1) | (carry << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.D == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, new_carry);
}
[[maybe_unused]] static void In_RR_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool new_carry = reg.E & 0x01;
    bool carry = reg.get_flag(Registers::Flag::C);
    reg.E = (reg.E >> 1) | (carry << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.E == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, new_carry);
}
[[maybe_unused]] static void In_RR_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool new_carry = reg.H & 0x01;
    bool carry = reg.get_flag(Registers::Flag::C);
    reg.H = (reg.H >> 1) | (carry << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.H == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, new_carry);
}
[[maybe_unused]] static void In_RR_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool new_carry = reg.L & 0x01;
    bool carry = reg.get_flag(Registers::Flag::C);
    reg.L = (reg.L >> 1) | (carry << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.L == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, new_carry);
}
[[maybe_unused]] static void In_RR_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    bool new_carry = target & 0x01;
    bool carry = reg.get_flag(Registers::Flag::C);
    target = (target >> 1) | (carry << 7);

    bus.write(reg.HL, target);

    // Flags
    reg.set_flag(Registers::Flag::Z, target == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, new_carry);
}
[[maybe_unused]] static void In_RR_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool new_carry = reg.A & 0x01;
    bool carry = reg.get_flag(Registers::Flag::C);
    reg.A = (reg.A >> 1) | (carry << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, new_carry);
}

/** SLA r8 ***********************************************************************************************************/
[[maybe_unused]] static void In_SLA_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.B & 0x80;
    reg.B = (reg.B << 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.B == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SLA_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.C & 0x80;
    reg.C = (reg.C << 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.C == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SLA_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.D & 0x80;
    reg.D = (reg.D << 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.D == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SLA_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.E & 0x80;
    reg.E = (reg.E << 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.E == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SLA_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.H & 0x80;
    reg.H = (reg.H << 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.H == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SLA_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.L & 0x80;
    reg.L = (reg.L << 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.L == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SLA_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    bool carry = target & 0x80;
    target = (target << 1);

    bus.write(reg.HL, target);

    // Flags
    reg.set_flag(Registers::Flag::Z, target == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SLA_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.A & 0x80;
    reg.A = (reg.A << 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}

/** SRA r8 ***********************************************************************************************************/
[[maybe_unused]] static void In_SRA_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.B & 0x01;
    bool signBit = reg.B & 0x80;

    reg.B = (reg.B >> 1) | (signBit << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.B == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SRA_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.C & 0x01;
    bool signBit = reg.C & 0x80;
    reg.C = (reg.C >> 1) | (signBit << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.C == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SRA_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.D & 0x01;
    bool signBit = reg.D & 0x80;
    reg.D = (reg.D >> 1) | (signBit << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.D == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SRA_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.E & 0x01;
    bool signBit = reg.E & 0x80;
    reg.E = (reg.E >> 1) | (signBit << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.E == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SRA_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.H & 0x01;
    bool signBit = reg.H & 0x80;
    reg.H = (reg.H >> 1) | (signBit << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.H == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SRA_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.L & 0x01;
    bool signBit = reg.L & 0x80;
    reg.L = (reg.L >> 1) | (signBit << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.L == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SRA_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    bool carry = target & 0x01;
    bool signBit = target & 0x80;
    target = (target >> 1) | (signBit << 7);

    bus.write(reg.HL, target);

    // Flags
    reg.set_flag(Registers::Flag::Z, target == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SRA_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.A & 0x01;
    bool signBit = reg.A & 0x80;
    reg.A = (reg.A >> 1) | (signBit << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}

/** SWAP r8 ***********************************************************************************************************/
[[maybe_unused]] static void In_SWAP_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t low = reg.B & 0x0F;
    uint8_t high = reg.B & 0xF0;

    reg.B = (low << 4) | (high >> 4);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.B == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_SWAP_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t low = reg.C & 0x0F;
    uint8_t high = reg.C & 0xF0;

    reg.C = (low << 4) | (high >> 4);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.C == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_SWAP_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t low = reg.D & 0x0F;
    uint8_t high = reg.D & 0xF0;

    reg.D = (low << 4) | (high >> 4);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.D == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_SWAP_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t low = reg.E & 0x0F;
    uint8_t high = reg.E & 0xF0;

    reg.E = (low << 4) | (high >> 4);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.E == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_SWAP_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t low = reg.H & 0x0F;
    uint8_t high = reg.H & 0xF0;

    reg.H = (low << 4) | (high >> 4);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.H == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_SWAP_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t low = reg.L & 0x0F;
    uint8_t high = reg.L & 0xF0;

    reg.L = (low << 4) | (high >> 4);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.L == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_SWAP_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    uint8_t low = target & 0x0F;
    uint8_t high = target & 0xF0;

    target = (low << 4) | (high >> 4);

    bus.write(reg.HL, target);

    // Flags
    reg.set_flag(Registers::Flag::Z, target == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}
[[maybe_unused]] static void In_SWAP_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t low = reg.A & 0x0F;
    uint8_t high = reg.A & 0xF0;

    reg.A = (low << 4) | (high >> 4);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, false);
}

/** SRL r8 ***********************************************************************************************************/
[[maybe_unused]] static void In_SRL_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.B & 0x01;

    reg.B = (reg.B >> 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.B == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SRL_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.C & 0x01;

    reg.C = (reg.C >> 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.C == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SRL_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.D & 0x01;

    reg.D = (reg.D >> 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.D == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SRL_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.E & 0x01;

    reg.E = (reg.E >> 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.E == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SRL_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.H & 0x01;

    reg.H = (reg.H >> 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.H == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SRL_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.L & 0x01;

    reg.L = (reg.L >> 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.L == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SRL_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    bool carry = target & 0x01;

    target = (target >> 1);

    bus.write(reg.HL, target);

    // Flags
    reg.set_flag(Registers::Flag::Z, target == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}
[[maybe_unused]] static void In_SRL_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool carry = reg.A & 0x01;

    reg.A = (reg.A >> 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, reg.A == 0);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, false);
    reg.set_flag(Registers::Flag::C, carry);
}

/** BIT b3, r8 *******************************************************************************************************/
[[maybe_unused]] static void In_BIT_0_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.B & (1 << 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_0_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.C & (1 << 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_0_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.D & (1 << 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_0_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.E & (1 << 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_0_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.H & (1 << 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_0_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.L & (1 << 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_0_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    bool result = target & (1 << 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_0_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.A & (1 << 0);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}

[[maybe_unused]] static void In_BIT_1_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.B & (1 << 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_1_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.C & (1 << 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_1_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.D & (1 << 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_1_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.E & (1 << 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_1_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.H & (1 << 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_1_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.L & (1 << 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_1_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    bool result = target & (1 << 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_1_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.A & (1 << 1);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}

[[maybe_unused]] static void In_BIT_2_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.B & (1 << 2);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_2_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.C & (1 << 2);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_2_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.D & (1 << 2);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_2_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.E & (1 << 2);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_2_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.H & (1 << 2);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_2_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.L & (1 << 2);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_2_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    bool result = target & (1 << 2);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_2_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.A & (1 << 2);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}

[[maybe_unused]] static void In_BIT_3_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.B & (1 << 3);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_3_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.C & (1 << 3);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_3_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.D & (1 << 3);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_3_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.E & (1 << 3);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_3_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.H & (1 << 3);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_3_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.L & (1 << 3);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_3_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    bool result = target & (1 << 3);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_3_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.A & (1 << 3);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}

[[maybe_unused]] static void In_BIT_4_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.B & (1 << 4);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_4_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.C & (1 << 4);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_4_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.D & (1 << 4);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_4_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.E & (1 << 4);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_4_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.H & (1 << 4);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_4_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.L & (1 << 4);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_4_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    bool result = target & (1 << 4);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_4_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.A & (1 << 4);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}

[[maybe_unused]] static void In_BIT_5_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.B & (1 << 5);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_5_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.C & (1 << 5);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_5_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.D & (1 << 5);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_5_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.E & (1 << 5);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_5_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.H & (1 << 5);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_5_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.L & (1 << 5);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_5_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    bool result = target & (1 << 5);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_5_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.A & (1 << 5);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}

[[maybe_unused]] static void In_BIT_6_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.B & (1 << 6);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_6_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.C & (1 << 6);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_6_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.D & (1 << 6);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_6_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.E & (1 << 6);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_6_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.H & (1 << 6);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_6_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.L & (1 << 6);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_6_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    bool result = target & (1 << 6);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_6_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.A & (1 << 6);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}

[[maybe_unused]] static void In_BIT_7_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.B & (1 << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_7_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.C & (1 << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_7_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.D & (1 << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_7_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.E & (1 << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_7_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.H & (1 << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_7_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.L & (1 << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_7_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    bool result = target & (1 << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}
[[maybe_unused]] static void In_BIT_7_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    bool result = reg.A & (1 << 7);

    // Flags
    reg.set_flag(Registers::Flag::Z, !result);
    reg.set_flag(Registers::Flag::N, false);
    reg.set_flag(Registers::Flag::H, true);
}

/** RES b3, r8 *******************************************************************************************************/
[[maybe_unused]] static void In_RES_0_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.B &= ~(1 << 0);
}
[[maybe_unused]] static void In_RES_0_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.C &= ~(1 << 0);
}
[[maybe_unused]] static void In_RES_0_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.D &= ~(1 << 0);
}
[[maybe_unused]] static void In_RES_0_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.E &= ~(1 << 0);
}
[[maybe_unused]] static void In_RES_0_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.H &= ~(1 << 0);
}
[[maybe_unused]] static void In_RES_0_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.L &= ~(1 << 0);
}
[[maybe_unused]] static void In_RES_0_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    target &= ~(1 << 0);

    bus.write(reg.HL, target);
}
[[maybe_unused]] static void In_RES_0_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.A &= ~(1 << 0);
}

[[maybe_unused]] static void In_RES_1_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.B &= ~(1 << 1);
}
[[maybe_unused]] static void In_RES_1_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.C &= ~(1 << 1);
}
[[maybe_unused]] static void In_RES_1_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.D &= ~(1 << 1);
}
[[maybe_unused]] static void In_RES_1_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.E &= ~(1 << 1);
}
[[maybe_unused]] static void In_RES_1_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.H &= ~(1 << 1);
}
[[maybe_unused]] static void In_RES_1_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.L &= ~(1 << 1);
}
[[maybe_unused]] static void In_RES_1_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    target &= ~(1 << 1);

    bus.write(reg.HL, target);
}
[[maybe_unused]] static void In_RES_1_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.A &= ~(1 << 1);
}

[[maybe_unused]] static void In_RES_2_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.B &= ~(1 << 2);
}
[[maybe_unused]] static void In_RES_2_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.C &= ~(1 << 2);
}
[[maybe_unused]] static void In_RES_2_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.D &= ~(1 << 2);
}
[[maybe_unused]] static void In_RES_2_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.E &= ~(1 << 2);
}
[[maybe_unused]] static void In_RES_2_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.H &= ~(1 << 2);
}
[[maybe_unused]] static void In_RES_2_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.L &= ~(1 << 2);
}
[[maybe_unused]] static void In_RES_2_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;

    uint8_t target = bus.read(reg.HL);
    target &= ~(1 << 2);

    bus.write(reg.HL, target);
}
[[maybe_unused]] static void In_RES_2_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.A &= ~(1 << 2);

    ;
}

[[maybe_unused]] static void In_RES_3_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.B &= ~(1 << 3);
}
[[maybe_unused]] static void In_RES_3_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.C &= ~(1 << 3);
}
[[maybe_unused]] static void In_RES_3_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.D &= ~(1 << 3);
}
[[maybe_unused]] static void In_RES_3_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.E &= ~(1 << 3);
}
[[maybe_unused]] static void In_RES_3_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.H &= ~(1 << 3);
}
[[maybe_unused]] static void In_RES_3_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.L &= ~(1 << 3);
}
[[maybe_unused]] static void In_RES_3_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;

    uint8_t target = bus.read(reg.HL);
    target &= ~(1 << 3);

    bus.write(reg.HL, target);
}
[[maybe_unused]] static void In_RES_3_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.A &= ~(1 << 3);
}

[[maybe_unused]] static void In_RES_4_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.B &= ~(1 << 4);
}
[[maybe_unused]] static void In_RES_4_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.C &= ~(1 << 4);
}
[[maybe_unused]] static void In_RES_4_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.D &= ~(1 << 4);
}
[[maybe_unused]] static void In_RES_4_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.E &= ~(1 << 4);
}
[[maybe_unused]] static void In_RES_4_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.H &= ~(1 << 4);
}
[[maybe_unused]] static void In_RES_4_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.L &= ~(1 << 4);
}
[[maybe_unused]] static void In_RES_4_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    target &= ~(1 << 4);

    bus.write(reg.HL, target);
}
[[maybe_unused]] static void In_RES_4_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.A &= ~(1 << 4);
}

[[maybe_unused]] static void In_RES_5_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.B &= ~(1 << 5);
}
[[maybe_unused]] static void In_RES_5_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.C &= ~(1 << 5);
}
[[maybe_unused]] static void In_RES_5_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.D &= ~(1 << 5);
}
[[maybe_unused]] static void In_RES_5_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.E &= ~(1 << 5);
}
[[maybe_unused]] static void In_RES_5_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.H &= ~(1 << 5);
}
[[maybe_unused]] static void In_RES_5_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.L &= ~(1 << 5);
}
[[maybe_unused]] static void In_RES_5_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    target &= ~(1 << 5);

    bus.write(reg.HL, target);
}
[[maybe_unused]] static void In_RES_5_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.A &= ~(1 << 5);
}

[[maybe_unused]] static void In_RES_6_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.B &= ~(1 << 6);
}
[[maybe_unused]] static void In_RES_6_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.C &= ~(1 << 6);

    ;
}
[[maybe_unused]] static void In_RES_6_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.D &= ~(1 << 6);
}
[[maybe_unused]] static void In_RES_6_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.E &= ~(1 << 6);
}
[[maybe_unused]] static void In_RES_6_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.H &= ~(1 << 6);
}
[[maybe_unused]] static void In_RES_6_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.L &= ~(1 << 6);
}
[[maybe_unused]] static void In_RES_6_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    target &= ~(1 << 6);

    bus.write(reg.HL, target);
}
[[maybe_unused]] static void In_RES_6_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.A &= ~(1 << 6);
}

[[maybe_unused]] static void In_RES_7_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.B &= ~(1 << 7);
}
[[maybe_unused]] static void In_RES_7_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.C &= ~(1 << 7);
}
[[maybe_unused]] static void In_RES_7_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.D &= ~(1 << 7);
}
[[maybe_unused]] static void In_RES_7_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.E &= ~(1 << 7);
}
[[maybe_unused]] static void In_RES_7_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.H &= ~(1 << 7);
}
[[maybe_unused]] static void In_RES_7_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.L &= ~(1 << 7);
}
[[maybe_unused]] static void In_RES_7_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    target &= ~(1 << 7);

    bus.write(reg.HL, target);
}
[[maybe_unused]] static void In_RES_7_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.A &= ~(1 << 7);
}

/** SET b3, r8 *******************************************************************************************************/
[[maybe_unused]] static void In_SET_0_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.B |= (1 << 0);
}
[[maybe_unused]] static void In_SET_0_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.C |= (1 << 0);
}
[[maybe_unused]] static void In_SET_0_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.D |= (1 << 0);
}
[[maybe_unused]] static void In_SET_0_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.E |= (1 << 0);
}
[[maybe_unused]] static void In_SET_0_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.H |= (1 << 0);
}
[[maybe_unused]] static void In_SET_0_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.L |= (1 << 0);
}
[[maybe_unused]] static void In_SET_0_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    target |= (1 << 0);

    bus.write(reg.HL, target);
}
[[maybe_unused]] static void In_SET_0_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.A |= (1 << 0);
}

[[maybe_unused]] static void In_SET_1_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.B |= (1 << 1);
}
[[maybe_unused]] static void In_SET_1_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.C |= (1 << 1);
}
[[maybe_unused]] static void In_SET_1_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.D |= (1 << 1);
}
[[maybe_unused]] static void In_SET_1_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.E |= (1 << 1);
}
[[maybe_unused]] static void In_SET_1_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.H |= (1 << 1);
}
[[maybe_unused]] static void In_SET_1_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.L |= (1 << 1);
}
[[maybe_unused]] static void In_SET_1_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    target |= (1 << 1);

    bus.write(reg.HL, target);
}
[[maybe_unused]] static void In_SET_1_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.A |= (1 << 1);
}

[[maybe_unused]] static void In_SET_2_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.B |= (1 << 2);
}
[[maybe_unused]] static void In_SET_2_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.C |= (1 << 2);
}
[[maybe_unused]] static void In_SET_2_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.D |= (1 << 2);
}
[[maybe_unused]] static void In_SET_2_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.E |= (1 << 2);
}
[[maybe_unused]] static void In_SET_2_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.H |= (1 << 2);
}
[[maybe_unused]] static void In_SET_2_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.L |= (1 << 2);
}
[[maybe_unused]] static void In_SET_2_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    target |= (1 << 2);

    bus.write(reg.HL, target);
}
[[maybe_unused]] static void In_SET_2_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.A |= (1 << 2);
}

[[maybe_unused]] static void In_SET_3_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.B |= (1 << 3);
}
[[maybe_unused]] static void In_SET_3_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.C |= (1 << 3);
}
[[maybe_unused]] static void In_SET_3_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.D |= (1 << 3);
}
[[maybe_unused]] static void In_SET_3_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.E |= (1 << 3);
}
[[maybe_unused]] static void In_SET_3_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.H |= (1 << 3);
}
[[maybe_unused]] static void In_SET_3_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.L |= (1 << 3);
}
[[maybe_unused]] static void In_SET_3_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;

    uint8_t target = bus.read(reg.HL);
    target |= (1 << 3);

    bus.write(reg.HL, target);
}
[[maybe_unused]] static void In_SET_3_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.A |= (1 << 3);
}

[[maybe_unused]] static void In_SET_4_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.B |= (1 << 4);
}
[[maybe_unused]] static void In_SET_4_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.C |= (1 << 4);
}
[[maybe_unused]] static void In_SET_4_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.D |= (1 << 4);
}
[[maybe_unused]] static void In_SET_4_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.E |= (1 << 4);
}
[[maybe_unused]] static void In_SET_4_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.H |= (1 << 4);
}
[[maybe_unused]] static void In_SET_4_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.L |= (1 << 4);
}
[[maybe_unused]] static void In_SET_4_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    target |= (1 << 4);

    bus.write(reg.HL, target);
}
[[maybe_unused]] static void In_SET_4_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.A |= (1 << 4);
}

[[maybe_unused]] static void In_SET_5_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.B |= (1 << 5);
}
[[maybe_unused]] static void In_SET_5_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.C |= (1 << 5);
}
[[maybe_unused]] static void In_SET_5_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.D |= (1 << 5);
}
[[maybe_unused]] static void In_SET_5_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.E |= (1 << 5);
}
[[maybe_unused]] static void In_SET_5_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.H |= (1 << 5);
}
[[maybe_unused]] static void In_SET_5_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.L |= (1 << 5);
}
[[maybe_unused]] static void In_SET_5_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    target |= (1 << 5);

    bus.write(reg.HL, target);
}
[[maybe_unused]] static void In_SET_5_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.A |= (1 << 5);
}

[[maybe_unused]] static void In_SET_6_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.B |= (1 << 6);
}
[[maybe_unused]] static void In_SET_6_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.C |= (1 << 6);
}
[[maybe_unused]] static void In_SET_6_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.D |= (1 << 6);
}
[[maybe_unused]] static void In_SET_6_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.E |= (1 << 6);
}
[[maybe_unused]] static void In_SET_6_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.H |= (1 << 6);
}
[[maybe_unused]] static void In_SET_6_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.L |= (1 << 6);
}
[[maybe_unused]] static void In_SET_6_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    target |= (1 << 6);

    bus.write(reg.HL, target);
}
[[maybe_unused]] static void In_SET_6_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.A |= (1 << 6);
}

[[maybe_unused]] static void In_SET_7_B([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.B |= (1 << 7);
}
[[maybe_unused]] static void In_SET_7_C([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.C |= (1 << 7);
}
[[maybe_unused]] static void In_SET_7_D([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.D |= (1 << 7);
}
[[maybe_unused]] static void In_SET_7_E([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.E |= (1 << 7);
}
[[maybe_unused]] static void In_SET_7_H([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.H |= (1 << 7);
}
[[maybe_unused]] static void In_SET_7_L([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.L |= (1 << 7);
}
[[maybe_unused]] static void In_SET_7_pHL([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    uint8_t target = bus.read(reg.HL);
    target |= (1 << 7);

    bus.write(reg.HL, target);
}
[[maybe_unused]] static void In_SET_7_A([[maybe_unused]] CPU& cpu, [[maybe_unused]] Bus& bus) {
    auto& reg = cpu.regs;
    reg.A |= (1 << 7);
}

}  // namespace WindGB