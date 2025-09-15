#include "instructions.hpp"

namespace WindGB {

// Instruction table initialisation
std::array<Instruction, 256> instruction_table = {
    // Block 0
    Instruction{"Nop", In_Nop},                  // 0x00: No operation
    Instruction{"LD BC, n16", In_LD_BC_n16},     // 0x01: Copy the value n16 into register BC.
    Instruction{"LD [BC], A", In_LD_pBC_A},      // 0x02: Copy the value in register A into the byte pointed to by BC.
    Instruction{"INC BC", In_INC_BC},            // 0x03: Increment the value in register BC by 1.
    Instruction{"INC B", In_INC_B},              // 0x04: Increment the value in register B by 1.
    Instruction{"DEC B", In_DEC_B},              // 0x05: Decrement the value in register B by 1.
    Instruction{"LD B, n8", In_LD_B_n8},         // 0x06: Copy the value n8 into register B.
    Instruction{"RLCA", In_RLCA},                // 0x07: Rotate register A left.
    Instruction{"LD [n16], SP", In_LD_pn16_SP},  // 0x08: Copy SP & 0xFF at address n16 and SP >> 8 at address n16 + 1.
    Instruction{"ADD HL, BC", In_ADD_HL_BC},     // 0x09: Add the value in BC to HL.
    Instruction{"LD A, [BC]", In_LD_A_pBC},      // 0x0A: Copy the byte pointed to by BC into register A.
    Instruction{"DEC BC", In_DEC_BC},            // 0x0B: Decrement the value in register BC by 1.
    Instruction{"INC C", In_INC_C},              // 0x0C: Increment the value in register C by 1.
    Instruction{"DEC C", In_DEC_C},              // 0x0D: Decrement the value in register C by 1.
    Instruction{"LD C, n8", In_LD_C_n8},         // 0x0E: Copy the value n8 into register C.
    Instruction{"RRCA", In_RRCA},                // 0x0F: Rotate register A right.
    Instruction{"STOP", In_STOP},  // 0x10: Enter CPU very low power mode. Special case, refer to https://rgbds.gbdev.io/docs/v0.9.1/gbz80.7#STOP
    Instruction{"LD DE, n16", In_LD_DE_n16},        // 0x11: Copy the value n16 into register DE.
    Instruction{"LD [DE], A", In_LD_pDE_A},         // 0x12: Copy the value in register A into the byte pointed to by DE.
    Instruction{"INC DE", In_INC_DE},               // 0x13: Increment the value in register DE by 1.
    Instruction{"INC D", In_INC_D},                 // 0x14: Increment the value in register D by 1.
    Instruction{"DEC D", In_DEC_D},                 // 0x15: Decrement the value in register D by 1.
    Instruction{"LD D, n8", In_LD_D_n8},            // 0x16: Copy the value n8 into register D.
    Instruction{"RLA", In_RLA},                     // 0x17: Rotate register A left, through the carry flag.
    Instruction{"JR e8", In_JR_e8},                 // 0x18: Relative Jump with a signed offset e8.
    Instruction{"ADD HL, DE", In_ADD_HL_DE},        // 0x19: Add the value in DE to HL.
    Instruction{"LD A, [DE]", In_LD_A_pDE},         // 0x1A: Copy the byte pointed to by DE into register A.
    Instruction{"DEC DE", In_DEC_DE},               // 0x1B: Decrement the value in register DE by 1.
    Instruction{"INC E", In_INC_E},                 // 0x1C: Increment the value in register E by 1.
    Instruction{"DEC E", In_DEC_E},                 // 0x1D: Decrement the value in register E by 1.
    Instruction{"LD E, n8", In_LD_E_n8},            // 0x1E: Copy the value n8 into register E.
    Instruction{"RRA", In_RRA},                     // 0x1F: Rotate register A right, through the carry flag.
    Instruction{"JR NZ, e8", In_JR_NZ_e8},          // 0x20: Relative Jump with a signed offset e8 if condition NZ is met.
    Instruction{"LD HL, n16", In_LD_HL_n16},        // 0x21: Copy the value n16 into register HL.
    Instruction{"LD [HL+], A", In_LD_pHL_plus_A},   // 0x22: Copy the value in register A into the byte pointed by HL and increment HL afterwards.
    Instruction{"INC HL", In_INC_HL},               // 0x23: Increment the value in register HL by 1.
    Instruction{"INC H", In_INC_H},                 // 0x24: Increment the value in register H by 1.
    Instruction{"DEC H", In_DEC_H},                 // 0x25: Decrement the value in register H by 1.
    Instruction{"LD H, n8", In_LD_H_n8},            // 0x26: Copy the value n8 into register H.
    Instruction{"DAA", In_DAA},                     // 0x27: Decimal Adjust Accumulator.
    Instruction{"JR Z, e8", In_JR_Z_e8},            // 0x28: Relative Jump with a signed offset e8 if condition Z is met.
    Instruction{"ADD HL, HL", In_ADD_HL_HL},        // 0x29: Add the value in HL to HL.
    Instruction{"LD A, [HL+]", In_LD_A_pHL_plus},   // 0x2A: Copy the byte pointed to by HL into register A, and increment HL afterwards.
    Instruction{"DEC HL", In_DEC_HL},               // 0x2B: Decrement the value in register HL by 1.
    Instruction{"INC L", In_INC_L},                 // 0x2C: Increment the value in register L by 1.
    Instruction{"DEC L", In_DEC_L},                 // 0x2D: Decrement the value in register L by 1.
    Instruction{"LD L, n8", In_LD_L_n8},            // 0x2E: Copy the value n8 into register L.
    Instruction{"CPL", In_CPL},                     // 0x2F: ComPLement accumulator (A = ~A); also called bitwise NOT.
    Instruction{"JR NC, e8", In_JR_NC_e8},          // 0x30: Relative Jump with a signed offset e8 if condition NC is met.
    Instruction{"LD SP, n16", In_LD_SP_n16},        // 0x31: Copy the value n16 into register SP.
    Instruction{"LD [HL-], A", In_LD_pHL_minus_A},  // 0x32: Copy the value in register A into the byte pointed by HL and decrement HL afterwards.
    Instruction{"INC SP", In_INC_SP},               // 0x33: Increment the value in register SP by 1.
    Instruction{"INC [HL]", In_INC_pHL},            // 0x34: Increment the byte pointed to by HL by 1.
    Instruction{"DEC [HL]", In_DEC_pHL},            // 0x35: Decrement the byte pointed to by HL by 1.
    Instruction{"LD [HL], n8", In_LD_pHL_n8},       // 0x36: Copy the value n8 into the byte pointed to by HL.
    Instruction{"SCF", In_SCF},                     // 0x37: Set Carry Flag.
    Instruction{"JR C, e8", In_JR_C_e8},            // 0x38: Relative Jump with a signed offset e8 if condition C is met.
    Instruction{"ADD HL, SP", In_ADD_HL_SP},        // 0x39: Add the value in SP to HL.
    Instruction{"LD A, [HL+]", In_LD_A_pHL_minus},  // 0x3A: Copy the byte pointed to by HL into register A, and decrement HL afterwards.
    Instruction{"DEC SP", In_DEC_SP},               // 0x3B: Decrement the value in register SP by 1.
    Instruction{"INC A", In_INC_A},                 // 0x3C: Increment the value in register A by 1.
    Instruction{"DEC A", In_DEC_A},                 // 0x3D: Decrement the value in register A by 1.
    Instruction{"LD A, n8", In_LD_A_n8},            // 0x3E: Copy the value n8 into register A.
    Instruction{"CCF", In_CCF},                     // 0x3F: Complement Carry Flag.

    // Block 1: 8-bit register-to-register loads
    Instruction{"LD B, B", In_LD_B_B},       // 0x40: Copy (aka Load) the value in B into B. -> TODO: Check if HALT
    Instruction{"LD B, C", In_LD_B_C},       // 0x41: Copy (aka Load) the value in C into B.
    Instruction{"LD B, D", In_LD_B_D},       // 0x42: Copy (aka Load) the value in D into B.
    Instruction{"LD B, E", In_LD_B_E},       // 0x43: Copy (aka Load) the value in E into B.
    Instruction{"LD B, H", In_LD_B_H},       // 0x44: Copy (aka Load) the value in H into B.
    Instruction{"LD B, L", In_LD_B_L},       // 0x45: Copy (aka Load) the value in L into B.
    Instruction{"LD B, [HL]", In_LD_B_pHL},  // 0x46: Copy (aka Load) the byte pointed by HL into B.
    Instruction{"LD B, A", In_LD_B_A},       // 0x47: Copy (aka Load) the value in A into B.
    Instruction{"LD C, B", In_LD_C_B},       // 0x48: Copy (aka Load) the value in B into C.
    Instruction{"LD C, C", In_LD_C_C},       // 0x49: Copy (aka Load) the value in C into C. -> TODO: Check if HALT
    Instruction{"LD C, D", In_LD_C_D},       // 0x4A: Copy (aka Load) the value in D into C.
    Instruction{"LD C, E", In_LD_C_E},       // 0x4B: Copy (aka Load) the value in E into C.
    Instruction{"LD C, H", In_LD_C_H},       // 0x4C: Copy (aka Load) the value in H into C.
    Instruction{"LD C, L", In_LD_C_L},       // 0x4D: Copy (aka Load) the value in L into C.
    Instruction{"LD C, [HL]", In_LD_C_pHL},  // 0x4E: Copy (aka Load) the byte pointed by HL into C.
    Instruction{"LD C, A", In_LD_C_A},       // 0x4F: Copy (aka Load) the value in A into C.
    Instruction{"LD D, B", In_LD_D_B},       // 0x50: Copy (aka Load) the value in B into D.
    Instruction{"LD D, C", In_LD_D_C},       // 0x51: Copy (aka Load) the value in C into D.
    Instruction{"LD D, D", In_LD_D_D},       // 0x52: Copy (aka Load) the value in D into D. -> TODO: Check if HALT
    Instruction{"LD D, E", In_LD_D_E},       // 0x53: Copy (aka Load) the value in E into D.
    Instruction{"LD D, H", In_LD_D_H},       // 0x54: Copy (aka Load) the value in H into D.
    Instruction{"LD D, L", In_LD_D_L},       // 0x55: Copy (aka Load) the value in L into D.
    Instruction{"LD D, [HL]", In_LD_D_pHL},  // 0x56: Copy (aka Load) the byte pointed by HL into D.
    Instruction{"LD D, A", In_LD_D_A},       // 0x57: Copy (aka Load) the value in A into D.
    Instruction{"LD E, B", In_LD_E_B},       // 0x58: Copy (aka Load) the value in B into E.
    Instruction{"LD E, C", In_LD_E_C},       // 0x59: Copy (aka Load) the value in C into E.
    Instruction{"LD E, D", In_LD_E_D},       // 0x5A: Copy (aka Load) the value in D into E.
    Instruction{"LD E, E", In_LD_E_E},       // 0x5B: Copy (aka Load) the value in E into E. -> TODO: Check if HALT
    Instruction{"LD E, H", In_LD_E_H},       // 0x5C: Copy (aka Load) the value in H into E.
    Instruction{"LD E, L", In_LD_E_L},       // 0x5D: Copy (aka Load) the value in L into E.
    Instruction{"LD E, [HL]", In_LD_E_pHL},  // 0x5E: Copy (aka Load) the byte pointed by HL into E.
    Instruction{"LD E, A", In_LD_E_A},       // 0x5F: Copy (aka Load) the value in A into E.
    Instruction{"LD H, B", In_LD_H_B},       // 0x60: Copy (aka Load) the value in B into H.
    Instruction{"LD H, C", In_LD_H_C},       // 0x61: Copy (aka Load) the value in C into H.
    Instruction{"LD H, D", In_LD_H_D},       // 0x62: Copy (aka Load) the value in D into H.
    Instruction{"LD H, E", In_LD_H_E},       // 0x63: Copy (aka Load) the value in E into H.
    Instruction{"LD H, H", In_LD_H_H},       // 0x64: Copy (aka Load) the value in H into H. -> TODO: Check if HALT
    Instruction{"LD H, L", In_LD_H_L},       // 0x65: Copy (aka Load) the value in L into H.
    Instruction{"LD H, [HL]", In_LD_H_pHL},  // 0x66: Copy (aka Load) the byte pointed by HL into H.
    Instruction{"LD H, A", In_LD_H_A},       // 0x67: Copy (aka Load) the value in A into H.
    Instruction{"LD L, B", In_LD_L_B},       // 0x68: Copy (aka Load) the value in B into L.
    Instruction{"LD L, C", In_LD_L_C},       // 0x69: Copy (aka Load) the value in C into L.
    Instruction{"LD L, D", In_LD_L_D},       // 0x6A: Copy (aka Load) the value in D into L.
    Instruction{"LD L, E", In_LD_L_E},       // 0x6B: Copy (aka Load) the value in E into L.
    Instruction{"LD L, H", In_LD_L_H},       // 0x6C: Copy (aka Load) the value in H into L.
    Instruction{"LD L, L", In_LD_L_L},       // 0x6D: Copy (aka Load) the value in L into L. -> TODO: Check if HALT
    Instruction{"LD L, [HL]", In_LD_L_pHL},  // 0x6E: Copy (aka Load) the byte pointed by HL into L.
    Instruction{"LD L, A", In_LD_L_A},       // 0x6F: Copy (aka Load) the value in A into L.
    Instruction{"LD [HL], B", In_LD_pHL_B},  // 0x70: Copy (aka Load) the value in B into the byte pointed by HL.
    Instruction{"LD [HL], C", In_LD_pHL_C},  // 0x71: Copy (aka Load) the value in C into the byte pointed by HL.
    Instruction{"LD [HL], D", In_LD_pHL_D},  // 0x72: Copy (aka Load) the value in D into the byte pointed by HL.
    Instruction{"LD [HL], E", In_LD_pHL_E},  // 0x73: Copy (aka Load) the value in E into the byte pointed by HL.
    Instruction{"LD [HL], H", In_LD_pHL_H},  // 0x74: Copy (aka Load) the value in H into the byte pointed by HL.
    Instruction{"LD [HL], L", In_LD_pHL_L},  // 0x75: Copy (aka Load) the value in L into the byte pointed by HL.
    Instruction{"HALT", In_HALT},            // 0x76: Enter CPU low-power consumption mode until an interrupt occurs.
    Instruction{"LD [HL], A", In_LD_pHL_A},  // 0x77: Copy (aka Load) the value in A into the byte pointed by HL.
    Instruction{"LD A, B", In_LD_A_B},       // 0x78: Copy (aka Load) the value in B into A.
    Instruction{"LD A, C", In_LD_A_C},       // 0x79: Copy (aka Load) the value in C into A.
    Instruction{"LD A, D", In_LD_A_D},       // 0x7A: Copy (aka Load) the value in D into A.
    Instruction{"LD A, E", In_LD_A_E},       // 0x7B: Copy (aka Load) the value in E into A.
    Instruction{"LD A, H", In_LD_A_H},       // 0x7C: Copy (aka Load) the value in H into A.
    Instruction{"LD A, L", In_LD_A_L},       // 0x7D: Copy (aka Load) the value in L into A.
    Instruction{"LD A, [HL]", In_LD_A_pHL},  // 0x7E: Copy (aka Load) the byte pointed by HL into A.
    Instruction{"LD A, A", In_LD_A_A},       // 0x7F: Copy (aka Load) the value in A into A. -> TODO: Check if HALT

    // Block 2: 8-bit arithmetic
    Instruction{"ADD A, B", In_ADD_A_B},       // 0x80: Add the value in B to A.
    Instruction{"ADD A, C", In_ADD_A_C},       // 0x81: Add the value in C to A.
    Instruction{"ADD A, D", In_ADD_A_D},       // 0x82: Add the value in D to A.
    Instruction{"ADD A, E", In_ADD_A_E},       // 0x83: Add the value in E to A.
    Instruction{"ADD A, H", In_ADD_A_H},       // 0x84: Add the value in H to A.
    Instruction{"ADD A, L", In_ADD_A_L},       // 0x85: Add the value in L to A.
    Instruction{"ADD A, [HL]", In_ADD_A_pHL},  // 0x86: Add the byte pointed by HL to A.
    Instruction{"ADD A, A", In_ADD_A_A},       // 0x87: Add the value in A to A.
    Instruction{"ADC A, B", In_ADC_A_B},       // 0x88: Add the value in B plus the carry flag to A.
    Instruction{"ADC A, C", In_ADC_A_C},       // 0x89: Add the value in C plus the carry flag to A.
    Instruction{"ADC A, D", In_ADC_A_D},       // 0x8A: Add the value in D plus the carry flag to A.
    Instruction{"ADC A, E", In_ADC_A_E},       // 0x8B: Add the value in E plus the carry flag to A.
    Instruction{"ADC A, H", In_ADC_A_H},       // 0x8C: Add the value in H plus the carry flag to A.
    Instruction{"ADC A, L", In_ADC_A_L},       // 0x8D: Add the value in L plus the carry flag to A.
    Instruction{"ADC A, [HL]", In_ADC_A_pHL},  // 0x8E: Add the byte pointed by HL plus the carry flag to A.
    Instruction{"ADC A, A", In_ADC_A_A},       // 0x8F: Add the value in A plus the carry flag to A.
    Instruction{"SUB A, B", In_SUB_A_B},       // 0x90: Subtract the value in B from A.
    Instruction{"SUB A, C", In_SUB_A_C},       // 0x91: Subtract the value in C from A.
    Instruction{"SUB A, D", In_SUB_A_D},       // 0x92: Subtract the value in D from A.
    Instruction{"SUB A, E", In_SUB_A_E},       // 0x93: Subtract the value in E from A.
    Instruction{"SUB A, H", In_SUB_A_H},       // 0x94: Subtract the value in H from A.
    Instruction{"SUB A, L", In_SUB_A_L},       // 0x95: Subtract the value in L from A.
    Instruction{"SUB A, [HL]", In_SUB_A_pHL},  // 0x96: Subtract the byte pointed to by HL from A.
    Instruction{"SUB A, A", In_SUB_A_A},       // 0x97: Subtract the value in A from A.
    Instruction{"SBC A, B", In_SBC_A_B},       // 0x98: Subtract the value in A and the carry flag from A.
    Instruction{"SBC A, C", In_SBC_A_C},       // 0x99: Subtract the value in B and the carry flag from A.
    Instruction{"SBC A, D", In_SBC_A_D},       // 0x9A: Subtract the value in C and the carry flag from A.
    Instruction{"SBC A, E", In_SBC_A_E},       // 0x9B: Subtract the value in D and the carry flag from A.
    Instruction{"SBC A, H", In_SBC_A_H},       // 0x9C: Subtract the value in H and the carry flag from A.
    Instruction{"SBC A, L", In_SBC_A_L},       // 0x9D: Subtract the value in L and the carry flag from A.
    Instruction{"SBC A, [HL]", In_SBC_A_pHL},  // 0x9E: Subtract the byte pointed to by HL and the carry flagto A.
    Instruction{"SBC A, A", In_SBC_A_A},       // 0x9F: Subtract the value in A and the carry flag from A.
    Instruction{"AND A, B", In_AND_A_B},       // 0xA0: Set A to the bitwise AND between the value in B and A.
    Instruction{"AND A, C", In_AND_A_C},       // 0xA1: Set A to the bitwise AND between the value in C and A.
    Instruction{"AND A, D", In_AND_A_D},       // 0xA2: Set A to the bitwise AND between the value in D and A.
    Instruction{"AND A, E", In_AND_A_E},       // 0xA3: Set A to the bitwise AND between the value in E and A.
    Instruction{"AND A, H", In_AND_A_H},       // 0xA4: Set A to the bitwise AND between the value in H and A.
    Instruction{"AND A, L", In_AND_A_L},       // 0xA5: Set A to the bitwise AND between the value in L and A.
    Instruction{"AND A, [HL]", In_AND_A_pHL},  // 0xA6: Set A to the bitwise AND between the byte pointed to by HL and A.
    Instruction{"AND A, A", In_AND_A_A},       // 0xA7: Set A to the bitwise AND between the value in A and A.
    Instruction{"XOR A, B", In_XOR_A_B},       // 0xA8: Set A to the bitwise XOR between the value in B and A.
    Instruction{"XOR A, C", In_XOR_A_C},       // 0xA9: Set A to the bitwise XOR between the value in C and A.
    Instruction{"XOR A, D", In_XOR_A_D},       // 0xAA: Set A to the bitwise XOR between the value in D and A.
    Instruction{"XOR A, E", In_XOR_A_E},       // 0xAB: Set A to the bitwise XOR between the value in E and A.
    Instruction{"XOR A, H", In_XOR_A_H},       // 0xAC: Set A to the bitwise XOR between the value in H and A.
    Instruction{"XOR A, L", In_XOR_A_L},       // 0xAD: Set A to the bitwise XOR between the value in L and A.
    Instruction{"XOR A, [HL]", In_XOR_A_pHL},  // 0xAE: Set A to the bitwise XOR between the byte pointed to by HL and A.
    Instruction{"XOR A, A", In_XOR_A_A},       // 0xAF: Set A to the bitwise XOR between the value in A and A.
    Instruction{"OR A, B", In_OR_A_B},         // 0xB0: Set A to the bitwise OR between the value in B and A.
    Instruction{"OR A, C", In_OR_A_C},         // 0xB1: Set A to the bitwise OR between the value in C and A.
    Instruction{"OR A, D", In_OR_A_D},         // 0xB2: Set A to the bitwise OR between the value in D and A.
    Instruction{"OR A, E", In_OR_A_E},         // 0xB3: Set A to the bitwise OR between the value in E and A.
    Instruction{"OR A, H", In_OR_A_H},         // 0xB4: Set A to the bitwise OR between the value in H and A.
    Instruction{"OR A, L", In_OR_A_L},         // 0xB5: Set A to the bitwise OR between the value in L and A.
    Instruction{"OR A, [HL]", In_OR_A_pHL},    // 0xB6: Set A to the bitwise OR between the byte pointed to by HL and A.
    Instruction{"OR A, A", In_OR_A_A},         // 0xB7: Set A to the bitwise OR between the value in A and A.
    Instruction{"CP A, B", In_CP_A_B},         // 0xB8: ComPare the value in A with the value in B.
    Instruction{"CP A, C", In_CP_A_C},         // 0xB9: ComPare the value in A with the value in C.
    Instruction{"CP A, D", In_CP_A_D},         // 0xBA: ComPare the value in A with the value in D.
    Instruction{"CP A, E", In_CP_A_E},         // 0xBB: ComPare the value in A with the value in E.
    Instruction{"CP A, H", In_CP_A_H},         // 0xBC: ComPare the value in A with the value in H.
    Instruction{"CP A, L", In_CP_A_L},         // 0xBD: ComPare the value in A with the value in L.
    Instruction{"CP A, [HL]", In_CP_A_pHL},    // 0xBE: ComPare the value in A with the byte pointed to by HL.
    Instruction{"CP A, A", In_CP_A_A},         // 0xBF: ComPare the value in A with the value in A.

    // Block 3
    Instruction{"RET NZ", In_RET_NZ},                  // 0xC0: Return from subroutine if condition NZ is met.
    Instruction{"POP BC", In_PIn_BC},                  // 0xC1: Pop register BC from the stack.
    Instruction{"JP NZ, n16", In_JP_NZ_n16},           // 0xC2: Jump to address n16 if condition NZ is met.
    Instruction{"JP n16", In_JP_n16},                  // 0xC3: Jump to address n16
    Instruction{"CALL NZ,n16", In_CALL_NZ_n16},        // 0xC4: Call address n16 if condition NZ is met.
    Instruction{"PUSH BC", In_PUSH_BC},                // 0xC5: Push register BC into the stack.
    Instruction{"ADD A,n8", In_ADD_A_n8},              // 0xC6: Add the value n8 plus the carry flag to A.
    Instruction{"RST 00H", In_RST_00H},                // 0xC7: Call address 0x0000.
    Instruction{"RET Z", In_RET_Z},                    // 0xC8: Return from subroutine if condition Z is met.
    Instruction{"RET", In_RET},                        // 0xC9: Return from subroutine.
    Instruction{"JP Z, n16", In_JP_Z_n16},             // 0xCA: Jump to address n16 if condition Z is met.
    Instruction{"Prefix", In_JP_Z_n16},                // 0xCB: Prefix
    Instruction{"CALL Z, n16", In_CALL_Z_n16},         // 0xCC: Call address n16 if condition Z is met.
    Instruction{"CALL n16", In_CALL_n16},              // 0xCD: Call address n16.
    Instruction{"ADC A, n8", In_ADC_A_n8},             // 0xCE: Add the value n8 plus the carry flag to A.
    Instruction{"RST 08H", In_RST_08H},                // 0xCF: Call address 0x0008.
    Instruction{"RET NC", In_RET_NC},                  // 0xD0: Return from subroutine if condition NC is met.
    Instruction{"POP DE", In_PIn_DE},                  // 0xD1: Pop register DE from the stack.
    Instruction{"JP NC, n16", In_JP_NC_n16},           // 0xD2: Jump to address n16 if condition NC is met.
    Instruction{"INVALID", In_Invalid},                // 0xD3: INVALID
    Instruction{"CALL NC, n16", In_CALL_NC_n16},       // 0xD4: Call address n16 if condition NC is met.
    Instruction{"PUSH DE", In_PUSH_DE},                // 0xD5: Push register DE into the stack.
    Instruction{"SUB A, n8", In_SUB_A_n8},             // 0xD6: Subtract the value n8 from A.
    Instruction{"RST 10H", In_RST_10H},                // 0xD7: Call address 0x0010.
    Instruction{"RET C", In_RET_C},                    // 0xD8: Return from subroutine if condition C is met.
    Instruction{"RETI", In_RETI},                      // 0xD9: Return from subroutine and enable interrupts.
    Instruction{"JP C, n16", In_JP_C_n16},             // 0xDA: Jump to address n16 if condition C is met.
    Instruction{"INVALID", In_Invalid},                // 0xDB: INVALID
    Instruction{"CALL C, n16", In_CALL_C_n16},         // 0xDC: Call address n16 if condition C is met.
    Instruction{"INVALID", In_Invalid},                // 0xDD: INVALID
    Instruction{"SBC A, n8", In_SBC_A_n8},             // 0xDE: Subtract the value n8 and the carry flag from A.
    Instruction{"RST 18H", In_RST_18H},                // 0xDF: Call address 0x0018.
    Instruction{"LDH [n8], A", In_LDH_pn8_A},          // 0xE0: Copy the value in register A into the byte at address 0xFF00 + n8.
    Instruction{"POP HL", In_PIn_HL},                  // 0xE1: Pop register HL from the stack.
    Instruction{"LDH [C], A", In_LDH_pC_A},            // 0xE2: Copy the value in register A into the byte at address 0xFF00 + C.
    Instruction{"INVALID", In_Invalid},                // 0xE3: INVALID
    Instruction{"INVALID", In_Invalid},                // 0xE4: INVALID
    Instruction{"PUSH HL", In_PUSH_HL},                // 0xE5: Push register HL into the stack.
    Instruction{"AND A, n8", In_AND_A_n8},             // 0xE6: Set A to the bitwise AND between the value n8 and A.
    Instruction{"RST 20H", In_RST_20H},                // 0xE7: Call address 0x0020.
    Instruction{"ADD SP, e8", In_ADD_SP_e8},           // 0xE8: Add the signed value e8 to SP.
    Instruction{"JP HL", In_JP_HL},                    // 0xE9: Jump to address in HL
    Instruction{"LD [n16], A", In_LD_pn16_A},          // 0xEA: Copy the value in register A into the byte at address n16.
    Instruction{"INVALID", In_Invalid},                // 0xEB: INVALID
    Instruction{"INVALID", In_Invalid},                // 0xEC: INVALID
    Instruction{"INVALID", In_Invalid},                // 0xED: INVALID
    Instruction{"XOR A, n8", In_XOR_A_n8},             // 0xEE: Set A to the bitwise XOR between the value n8 and A.
    Instruction{"RST 28H", In_RST_28H},                // 0xEF: Call address 0x0028.
    Instruction{"LDH A, n8", In_LDH_A_pn8},            // 0xF0: Copy the byte at address 0xFF00 + n8 into register A
    Instruction{"POP AF", In_PIn_AF},                  // 0xF1: Pop register AF from the stack.
    Instruction{"LDH A, [C]", In_LDH_A_pC},            // 0xF2: Copy the byte at address 0xFF00 + C into register A.
    Instruction{"DI", In_DI},                          // 0xF3: Disable Interrupts by clearing the IME flag.
    Instruction{"INVALID", In_Invalid},                // 0xF4: INVALID
    Instruction{"PUSH AF", In_PUSH_AF},                // 0xF5: Push register AF into the stack.
    Instruction{"OR A, n8", In_OR_A_n8},               // 0xF6: Set A to the bitwise OR between the value n8 and A.
    Instruction{"RST 30H", In_RST_30H},                // 0xF7: Call address 0x0030.
    Instruction{"LD HL, SP+e8", In_LD_HL_SP_plus_e8},  // 0xF8: Add the signed value e8 to SP and copy the result in HL.
    Instruction{"LD SP, HL", In_LD_SP_HL},             // 0xF9: Copy register HL into register SP.
    Instruction{"LD A, [n16]", In_LD_A_pn16},          // 0xFA: Copy the byte at address n16 into register A.
    Instruction{"EI", In_EI},                          // 0xFB: Enable Interrupts by setting the IME flag.
    Instruction{"INVALID", In_Invalid},                // 0xFC: INVALID
    Instruction{"INVALID", In_Invalid},                // 0xFD: INVALID
    Instruction{"CP A, n8", In_CP_A_n8},               // 0xFE: ComPare the value in A with the value n8.
    Instruction{"RST 38H", In_RST_38H},                // 0xFF: Call address 0x0038.
};

// 0xCB Prefix instruction table initialisation
std::array<Instruction, 256> prefix_instruction_table = {
    Instruction{"RLC B", In_RLC_B},            // 0x00:
    Instruction{"RLC C", In_RLC_C},            // 0x01:
    Instruction{"RLC D", In_RLC_D},            // 0x02:
    Instruction{"RLC E", In_RLC_E},            // 0x03:
    Instruction{"RLC H", In_RLC_H},            // 0x04:
    Instruction{"RLC L", In_RLC_L},            // 0x05:
    Instruction{"RLC [HL]", In_RLC_pHL},       // 0x06:
    Instruction{"RLC A", In_RLC_A},            // 0x07:
    Instruction{"RRC B", In_RRC_B},            // 0x08:
    Instruction{"RRC C", In_RRC_C},            // 0x09:
    Instruction{"RRC D", In_RRC_D},            // 0x0A:
    Instruction{"RRC E", In_RRC_E},            // 0x0B:
    Instruction{"RRC H", In_RRC_H},            // 0x0C:
    Instruction{"RRC L", In_RRC_L},            // 0x0D:
    Instruction{"RRC [HL]", In_RRC_pHL},       // 0x0E:
    Instruction{"RRC A", In_RRC_A},            // 0x0F:
    Instruction{"RL B", In_RL_B},              // 0x10:
    Instruction{"RL C", In_RL_C},              // 0x11:
    Instruction{"RL D", In_RL_D},              // 0x12:
    Instruction{"RL E", In_RL_E},              // 0x13:
    Instruction{"RL H", In_RL_H},              // 0x14:
    Instruction{"RL L", In_RL_L},              // 0x15:
    Instruction{"RL [HL]", In_RL_pHL},         // 0x16:
    Instruction{"RL A", In_RL_A},              // 0x17:
    Instruction{"RR B", In_RR_B},              // 0x18:
    Instruction{"RR C", In_RR_C},              // 0x19:
    Instruction{"RR D", In_RR_D},              // 0x1A:
    Instruction{"RR E", In_RR_E},              // 0x1B:
    Instruction{"RR H", In_RR_H},              // 0x1C:
    Instruction{"RR L", In_RR_L},              // 0x1D:
    Instruction{"RR [HL]", In_RR_pHL},         // 0x1E:
    Instruction{"RR A", In_RR_A},              // 0x1F:
    Instruction{"SLA B", In_SLA_B},            // 0x20:
    Instruction{"SLA C", In_SLA_C},            // 0x21:
    Instruction{"SLA D", In_SLA_D},            // 0x22:
    Instruction{"SLA E", In_SLA_E},            // 0x23:
    Instruction{"SLA H", In_SLA_H},            // 0x24:
    Instruction{"SLA L", In_SLA_L},            // 0x25:
    Instruction{"SLA [HL]", In_SLA_pHL},       // 0x26:
    Instruction{"SLA A", In_SLA_A},            // 0x27:
    Instruction{"SRA B", In_SRA_B},            // 0x28:
    Instruction{"SRA C", In_SRA_C},            // 0x29:
    Instruction{"SRA D", In_SRA_D},            // 0x2A:
    Instruction{"SRA E", In_SRA_E},            // 0x2B:
    Instruction{"SRA H", In_SRA_H},            // 0x2C:
    Instruction{"SRA L", In_SRA_L},            // 0x2D:
    Instruction{"SRA [HL]", In_SRA_pHL},       // 0x2E:
    Instruction{"SRA A", In_SRA_A},            // 0x2F:
    Instruction{"SWAP B", In_SWAP_B},          // 0x30:
    Instruction{"SWAP C", In_SWAP_C},          // 0x31:
    Instruction{"SWAP D", In_SWAP_D},          // 0x32:
    Instruction{"SWAP E", In_SWAP_E},          // 0x33:
    Instruction{"SWAP H", In_SWAP_H},          // 0x34:
    Instruction{"SWAP L", In_SWAP_L},          // 0x35:
    Instruction{"SWAP [HL]", In_SWAP_pHL},     // 0x36:
    Instruction{"SWAP A", In_SWAP_A},          // 0x37:
    Instruction{"SRL B", In_SRL_B},            // 0x38:
    Instruction{"SRL C", In_SRL_C},            // 0x39:
    Instruction{"SRL D", In_SRL_D},            // 0x3A:
    Instruction{"SRL E", In_SRL_E},            // 0x3B:
    Instruction{"SRL H", In_SRL_H},            // 0x3C:
    Instruction{"SRL L", In_SRL_L},            // 0x3D:
    Instruction{"SRL [HL]", In_SRL_pHL},       // 0x3E:
    Instruction{"SRL A", In_SRL_A},            // 0x3F:
    Instruction{"BIT 0, B", In_BIT_0_B},       // 0x40:
    Instruction{"BIT 0, C", In_BIT_0_C},       // 0x41:
    Instruction{"BIT 0, D", In_BIT_0_D},       // 0x42:
    Instruction{"BIT 0, E", In_BIT_0_E},       // 0x43:
    Instruction{"BIT 0, H", In_BIT_0_H},       // 0x44:
    Instruction{"BIT 0, L", In_BIT_0_L},       // 0x45:
    Instruction{"BIT 0, [HL]", In_BIT_0_pHL},  // 0x46:
    Instruction{"BIT 0, A", In_BIT_0_A},       // 0x47:
    Instruction{"BIT 1, B", In_BIT_1_B},       // 0x48:
    Instruction{"BIT 1, C", In_BIT_1_C},       // 0x49:
    Instruction{"BIT 1, D", In_BIT_1_D},       // 0x4A:
    Instruction{"BIT 1, E", In_BIT_1_E},       // 0x4B:
    Instruction{"BIT 1, H", In_BIT_1_H},       // 0x4C:
    Instruction{"BIT 1, L", In_BIT_1_L},       // 0x4D:
    Instruction{"BIT 1, [HL]", In_BIT_1_pHL},  // 0x4E:
    Instruction{"BIT 1, A", In_BIT_1_A},       // 0x4F:
    Instruction{"BIT 2, B", In_BIT_2_B},       // 0x50:
    Instruction{"BIT 2, C", In_BIT_2_C},       // 0x51:
    Instruction{"BIT 2, D", In_BIT_2_D},       // 0x52:
    Instruction{"BIT 2, E", In_BIT_2_E},       // 0x53:
    Instruction{"BIT 2, H", In_BIT_2_H},       // 0x54:
    Instruction{"BIT 2, L", In_BIT_2_L},       // 0x55:
    Instruction{"BIT 2, [HL]", In_BIT_2_pHL},  // 0x56:
    Instruction{"BIT 2, A", In_BIT_2_A},       // 0x57:
    Instruction{"BIT 3, B", In_BIT_3_B},       // 0x58:
    Instruction{"BIT 3, C", In_BIT_3_C},       // 0x59:
    Instruction{"BIT 3, D", In_BIT_3_D},       // 0x5A:
    Instruction{"BIT 3, E", In_BIT_3_E},       // 0x5B:
    Instruction{"BIT 3, H", In_BIT_3_H},       // 0x5C:
    Instruction{"BIT 3, L", In_BIT_3_L},       // 0x5D:
    Instruction{"BIT 3, [HL]", In_BIT_3_pHL},  // 0x5E:
    Instruction{"BIT 3, A", In_BIT_3_A},       // 0x5F:
    Instruction{"BIT 4, B", In_BIT_4_B},       // 0x60:
    Instruction{"BIT 4, C", In_BIT_4_C},       // 0x61:
    Instruction{"BIT 4, D", In_BIT_4_D},       // 0x62:
    Instruction{"BIT 4, E", In_BIT_4_E},       // 0x63:
    Instruction{"BIT 4, H", In_BIT_4_H},       // 0x64:
    Instruction{"BIT 4, L", In_BIT_4_L},       // 0x65:
    Instruction{"BIT 4, [HL]", In_BIT_4_pHL},  // 0x66:
    Instruction{"BIT 4, A", In_BIT_4_A},       // 0x67:
    Instruction{"BIT 5, B", In_BIT_5_B},       // 0x68:
    Instruction{"BIT 5, C", In_BIT_5_C},       // 0x69:
    Instruction{"BIT 5, D", In_BIT_5_D},       // 0x6A:
    Instruction{"BIT 5, E", In_BIT_5_E},       // 0x6B:
    Instruction{"BIT 5, H", In_BIT_5_H},       // 0x6C:
    Instruction{"BIT 5, L", In_BIT_5_L},       // 0x6D:
    Instruction{"BIT 5, [HL]", In_BIT_5_pHL},  // 0x6E:
    Instruction{"BIT 5, A", In_BIT_5_A},       // 0x6F:
    Instruction{"BIT 6, B", In_BIT_6_B},       // 0x70:
    Instruction{"BIT 6, C", In_BIT_6_C},       // 0x71:
    Instruction{"BIT 6, D", In_BIT_6_D},       // 0x72:
    Instruction{"BIT 6, E", In_BIT_6_E},       // 0x73:
    Instruction{"BIT 6, H", In_BIT_6_H},       // 0x74:
    Instruction{"BIT 6, L", In_BIT_6_L},       // 0x75:
    Instruction{"BIT 6, [HL]", In_BIT_6_pHL},  // 0x76:
    Instruction{"BIT 6, A", In_BIT_6_A},       // 0x77:
    Instruction{"BIT 7, B", In_BIT_7_B},       // 0x78:
    Instruction{"BIT 7, C", In_BIT_7_C},       // 0x79:
    Instruction{"BIT 7, D", In_BIT_7_D},       // 0x7A:
    Instruction{"BIT 7, E", In_BIT_7_E},       // 0x7B:
    Instruction{"BIT 7, H", In_BIT_7_H},       // 0x7C:
    Instruction{"BIT 7, L", In_BIT_7_L},       // 0x7D:
    Instruction{"BIT 7, [HL]", In_BIT_7_pHL},  // 0x7E:
    Instruction{"BIT 7, A", In_BIT_7_A},       // 0x7F:
    Instruction{"RES 0, B", In_RES_0_B},       // 0x80:
    Instruction{"RES 0, C", In_RES_0_C},       // 0x81:
    Instruction{"RES 0, D", In_RES_0_D},       // 0x82:
    Instruction{"RES 0, E", In_RES_0_E},       // 0x83:
    Instruction{"RES 0, H", In_RES_0_H},       // 0x84:
    Instruction{"RES 0, L", In_RES_0_L},       // 0x85:
    Instruction{"RES 0, [HL]", In_RES_0_pHL},  // 0x86:
    Instruction{"RES 0, A", In_RES_0_A},       // 0x87:
    Instruction{"RES 1, B", In_RES_1_B},       // 0x88:
    Instruction{"RES 1, C", In_RES_1_C},       // 0x89:
    Instruction{"RES 1, D", In_RES_1_D},       // 0x8A:
    Instruction{"RES 1, E", In_RES_1_E},       // 0x8B:
    Instruction{"RES 1, H", In_RES_1_H},       // 0x8C:
    Instruction{"RES 1, L", In_RES_1_L},       // 0x8D:
    Instruction{"RES 1, [HL]", In_RES_1_pHL},  // 0x8E:
    Instruction{"RES 1, A", In_RES_1_A},       // 0x8F:
    Instruction{"RES 2, B", In_RES_2_B},       // 0x90:
    Instruction{"RES 2, C", In_RES_2_C},       // 0x91:
    Instruction{"RES 2, D", In_RES_2_D},       // 0x92:
    Instruction{"RES 2, E", In_RES_2_E},       // 0x93:
    Instruction{"RES 2, H", In_RES_2_H},       // 0x94:
    Instruction{"RES 2, L", In_RES_2_L},       // 0x95:
    Instruction{"RES 2, [HL]", In_RES_2_pHL},  // 0x96:
    Instruction{"RES 2, A", In_RES_2_A},       // 0x97:
    Instruction{"RES 3, B", In_RES_3_B},       // 0x98:
    Instruction{"RES 3, C", In_RES_3_C},       // 0x99:
    Instruction{"RES 3, D", In_RES_3_D},       // 0x9A:
    Instruction{"RES 3, E", In_RES_3_E},       // 0x9B:
    Instruction{"RES 3, H", In_RES_3_H},       // 0x9C:
    Instruction{"RES 3, L", In_RES_3_L},       // 0x9D:
    Instruction{"RES 3, [HL]", In_RES_3_pHL},  // 0x9E:
    Instruction{"RES 3, A", In_RES_3_A},       // 0x9F:
    Instruction{"RES 4, B", In_RES_4_B},       // 0xA0:
    Instruction{"RES 4, C", In_RES_4_C},       // 0xA1:
    Instruction{"RES 4, D", In_RES_4_D},       // 0xA2:
    Instruction{"RES 4, E", In_RES_4_E},       // 0xA3:
    Instruction{"RES 4, H", In_RES_4_H},       // 0xA4:
    Instruction{"RES 4, L", In_RES_4_L},       // 0xA5:
    Instruction{"RES 4, [HL]", In_RES_4_pHL},  // 0xA6:
    Instruction{"RES 4, A", In_RES_4_A},       // 0xA7:
    Instruction{"RES 5, B", In_RES_5_B},       // 0xA8:
    Instruction{"RES 5, C", In_RES_5_C},       // 0xA9:
    Instruction{"RES 5, D", In_RES_5_D},       // 0xAA:
    Instruction{"RES 5, E", In_RES_5_E},       // 0xAB:
    Instruction{"RES 5, H", In_RES_5_H},       // 0xAC:
    Instruction{"RES 5, L", In_RES_5_L},       // 0xAD:
    Instruction{"RES 5, [HL]", In_RES_5_pHL},  // 0xAE:
    Instruction{"RES 5, A", In_RES_5_A},       // 0xAF:
    Instruction{"RES 6, B", In_RES_6_B},       // 0xB0:
    Instruction{"RES 6, C", In_RES_6_C},       // 0xB1:
    Instruction{"RES 6, D", In_RES_6_D},       // 0xB2:
    Instruction{"RES 6, E", In_RES_6_E},       // 0xB3:
    Instruction{"RES 6, H", In_RES_6_H},       // 0xB4:
    Instruction{"RES 6, L", In_RES_6_L},       // 0xB5:
    Instruction{"RES 6, [HL]", In_RES_6_pHL},  // 0xB6:
    Instruction{"RES 6, A", In_RES_6_A},       // 0xB7:
    Instruction{"RES 7, B", In_RES_7_B},       // 0xB8:
    Instruction{"RES 7, C", In_RES_7_C},       // 0xB9:
    Instruction{"RES 7, D", In_RES_7_D},       // 0xBA:
    Instruction{"RES 7, E", In_RES_7_E},       // 0xBB:
    Instruction{"RES 7, H", In_RES_7_H},       // 0xBC:
    Instruction{"RES 7, L", In_RES_7_L},       // 0xBD:
    Instruction{"RES 7, [HL]", In_RES_7_pHL},  // 0xBE:
    Instruction{"RES 7, A", In_RES_7_A},       // 0xBF:
    Instruction{"SET 0, B", In_SET_0_B},       // 0xC0:
    Instruction{"SET 0, C", In_SET_0_C},       // 0xC1:
    Instruction{"SET 0, D", In_SET_0_D},       // 0xC2:
    Instruction{"SET 0, E", In_SET_0_E},       // 0xC3:
    Instruction{"SET 0, H", In_SET_0_H},       // 0xC4:
    Instruction{"SET 0, L", In_SET_0_L},       // 0xC5:
    Instruction{"SET 0, [HL]", In_SET_0_pHL},  // 0xC6:
    Instruction{"SET 0, A", In_SET_0_A},       // 0xC7:
    Instruction{"SET 1, B", In_SET_1_B},       // 0xC8:
    Instruction{"SET 1, C", In_SET_1_C},       // 0xC9:
    Instruction{"SET 1, D", In_SET_1_D},       // 0xCA:
    Instruction{"SET 1, E", In_SET_1_E},       // 0xCB:
    Instruction{"SET 1, H", In_SET_1_H},       // 0xCC:
    Instruction{"SET 1, L", In_SET_1_L},       // 0xCD:
    Instruction{"SET 1, [HL]", In_SET_1_pHL},  // 0xCE:
    Instruction{"SET 1, A", In_SET_1_A},       // 0xCF:
    Instruction{"SET 2, B", In_SET_2_B},       // 0xD0:
    Instruction{"SET 2, C", In_SET_2_C},       // 0xD1:
    Instruction{"SET 2, D", In_SET_2_D},       // 0xD2:
    Instruction{"SET 2, E", In_SET_2_E},       // 0xD3:
    Instruction{"SET 2, H", In_SET_2_H},       // 0xD4:
    Instruction{"SET 2, L", In_SET_2_L},       // 0xD5:
    Instruction{"SET 2, [HL]", In_SET_2_pHL},  // 0xD6:
    Instruction{"SET 2, A", In_SET_2_A},       // 0xD7:
    Instruction{"SET 3, B", In_SET_3_B},       // 0xD8:
    Instruction{"SET 3, C", In_SET_3_C},       // 0xD9:
    Instruction{"SET 3, D", In_SET_3_D},       // 0xDA:
    Instruction{"SET 3, E", In_SET_3_E},       // 0xDB:
    Instruction{"SET 3, H", In_SET_3_H},       // 0xDC:
    Instruction{"SET 3, L", In_SET_3_L},       // 0xDD:
    Instruction{"SET 3, [HL]", In_SET_3_pHL},  // 0xDE:
    Instruction{"SET 3, A", In_SET_3_A},       // 0xDF:
    Instruction{"SET 4, B", In_SET_4_B},       // 0xE0:
    Instruction{"SET 4, C", In_SET_4_C},       // 0xE1:
    Instruction{"SET 4, D", In_SET_4_D},       // 0xE2:
    Instruction{"SET 4, E", In_SET_4_E},       // 0xE3:
    Instruction{"SET 4, H", In_SET_4_H},       // 0xE4:
    Instruction{"SET 4, L", In_SET_4_L},       // 0xE5:
    Instruction{"SET 4, [HL]", In_SET_4_pHL},  // 0xE6:
    Instruction{"SET 4, A", In_SET_4_A},       // 0xE7:
    Instruction{"SET 5, B", In_SET_5_B},       // 0xE8:
    Instruction{"SET 5, C", In_SET_5_C},       // 0xE9:
    Instruction{"SET 5, D", In_SET_5_D},       // 0xEA:
    Instruction{"SET 5, E", In_SET_5_E},       // 0xEB:
    Instruction{"SET 5, H", In_SET_5_H},       // 0xEC:
    Instruction{"SET 5, L", In_SET_5_L},       // 0xED:
    Instruction{"SET 5, [HL]", In_SET_5_pHL},  // 0xEE:
    Instruction{"SET 5, A", In_SET_5_A},       // 0xEF:
    Instruction{"SET 6, B", In_SET_6_B},       // 0xF0:
    Instruction{"SET 6, C", In_SET_6_C},       // 0xF1:
    Instruction{"SET 6, D", In_SET_6_D},       // 0xF2:
    Instruction{"SET 6, E", In_SET_6_E},       // 0xF3:
    Instruction{"SET 6, H", In_SET_6_H},       // 0xF4:
    Instruction{"SET 6, L", In_SET_6_L},       // 0xF5:
    Instruction{"SET 6, [HL]", In_SET_6_pHL},  // 0xF6:
    Instruction{"SET 6, A", In_SET_6_A},       // 0xF7:
    Instruction{"SET 7, B", In_SET_7_B},       // 0xF8:
    Instruction{"SET 7, C", In_SET_7_C},       // 0xF9:
    Instruction{"SET 7, D", In_SET_7_D},       // 0xFA:
    Instruction{"SET 7, E", In_SET_7_E},       // 0xFB:
    Instruction{"SET 7, H", In_SET_7_H},       // 0xFC:
    Instruction{"SET 7, L", In_SET_7_L},       // 0xFD:
    Instruction{"SET 7, [HL]", In_SET_7_pHL},  // 0xFE:
    Instruction{"SET 7, A", In_SET_7_A},       // 0xFF:
};

}  // namespace WindGB