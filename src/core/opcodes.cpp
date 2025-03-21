#include "opcodes.h"

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
    Opcode{"LD [n16], SP", 3, 5, 0, Op_LD_pn16_SP},  // 0x08: Copy SP & 0xFF at address n16 and SP >> 8 at address n16 + 1.
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
    Opcode{"JR e8", 2, 3, 0, Op_JR_e8},                 // 0x18: Relative Jump with a signed offset e8.
    Opcode{"ADD HL, DE", 1, 2, 0, Op_ADD_HL_DE},        // 0x19: Add the value in DE to HL.
    Opcode{"LD A, [DE]", 1, 2, 0, Op_LD_A_pDE},         // 0x1A: Copy the byte pointed to by DE into register A.
    Opcode{"DEC DE", 1, 2, 0, Op_DEC_DE},               // 0x1B: Decrement the value in register DE by 1.
    Opcode{"INC E", 1, 1, 0, Op_INC_E},                 // 0x1C: Increment the value in register E by 1.
    Opcode{"DEC E", 1, 1, 0, Op_DEC_E},                 // 0x1D: Decrement the value in register E by 1.
    Opcode{"LD E, n8", 2, 2, 0, Op_LD_E_n8},            // 0x1E: Copy the value n8 into register E.
    Opcode{"RRA", 1, 1, 0, Op_RRA},                     // 0x1F: Rotate register A right, through the carry flag.
    Opcode{"JR NZ, e8", 2, 2, 1, Op_JR_NZ_e8},          // 0x20: Relative Jump with a signed offset e8 if condition NZ is met.
    Opcode{"LD HL, n16", 3, 3, 0, Op_LD_HL_n16},        // 0x21: Copy the value n16 into register HL.
    Opcode{"LD [HL+], A", 1, 2, 0, Op_LD_pHL_plus_A},   // 0x22: Copy the value in register A into the byte pointed by HL and increment HL afterwards.
    Opcode{"INC HL", 1, 2, 0, Op_INC_HL},               // 0x23: Increment the value in register HL by 1.
    Opcode{"INC H", 1, 1, 0, Op_INC_H},                 // 0x24: Increment the value in register H by 1.
    Opcode{"DEC H", 1, 1, 0, Op_DEC_H},                 // 0x25: Decrement the value in register H by 1.
    Opcode{"LD H, n8", 2, 2, 0, Op_LD_H_n8},            // 0x26: Copy the value n8 into register H.
    Opcode{"DAA", 1, 1, 0, Op_DAA},                     // 0x27: Decimal Adjust Accumulator.
    Opcode{"JR Z, e8", 2, 2, 1, Op_JR_Z_e8},            // 0x28: Relative Jump with a signed offset e8 if condition Z is met.
    Opcode{"ADD HL, HL", 1, 2, 0, Op_ADD_HL_HL},        // 0x29: Add the value in HL to HL.
    Opcode{"LD A, [HL+]", 1, 2, 0, Op_LD_A_pHL_plus},   // 0x2A: Copy the byte pointed to by HL into register A, and increment HL afterwards.
    Opcode{"DEC HL", 1, 2, 0, Op_DEC_HL},               // 0x2B: Decrement the value in register HL by 1.
    Opcode{"INC L", 1, 1, 0, Op_INC_L},                 // 0x2C: Increment the value in register L by 1.
    Opcode{"DEC L", 1, 1, 0, Op_DEC_L},                 // 0x2D: Decrement the value in register L by 1.
    Opcode{"LD L, n8", 2, 2, 0, Op_LD_L_n8},            // 0x2E: Copy the value n8 into register L.
    Opcode{"CPL", 1, 1, 0, Op_CPL},                     // 0x2F: ComPLement accumulator (A = ~A); also called bitwise NOT.
    Opcode{"JR NC, e8", 2, 2, 1, Op_JR_NC_e8},          // 0x30: Relative Jump with a signed offset e8 if condition NC is met.
    Opcode{"LD SP, n16", 3, 3, 0, Op_LD_SP_n16},        // 0x31: Copy the value n16 into register SP.
    Opcode{"LD [HL-], A", 1, 2, 0, Op_LD_pHL_minus_A},  // 0x32: Copy the value in register A into the byte pointed by HL and decrement HL afterwards.
    Opcode{"INC SP", 1, 2, 0, Op_INC_SP},               // 0x33: Increment the value in register SP by 1.
    Opcode{"INC [HL]", 1, 3, 0, Op_INC_pHL},            // 0x34: Increment the byte pointed to by HL by 1.
    Opcode{"DEC [HL]", 1, 3, 0, Op_DEC_pHL},            // 0x35: Decrement the byte pointed to by HL by 1.
    Opcode{"LD [HL], n8", 2, 3, 0, Op_LD_pHL_n8},       // 0x36: Copy the value n8 into the byte pointed to by HL.
    Opcode{"SCF", 1, 1, 0, Op_SCF},                     // 0x37: Set Carry Flag.
    Opcode{"JR C, e8", 2, 2, 1, Op_JR_C_e8},            // 0x38: Relative Jump with a signed offset e8 if condition C is met.
    Opcode{"ADD HL, SP", 1, 2, 0, Op_ADD_HL_SP},        // 0x39: Add the value in SP to HL.
    Opcode{"LD A, [HL+]", 1, 2, 0, Op_LD_A_pHL_minus},  // 0x3A: Copy the byte pointed to by HL into register A, and decrement HL afterwards.
    Opcode{"DEC SP", 1, 2, 0, Op_DEC_SP},               // 0x3B: Decrement the value in register SP by 1.
    Opcode{"INC A", 1, 1, 0, Op_INC_A},                 // 0x3C: Increment the value in register A by 1.
    Opcode{"DEC A", 1, 1, 0, Op_DEC_A},                 // 0x3D: Decrement the value in register A by 1.
    Opcode{"LD A, n8", 2, 2, 0, Op_LD_A_n8},            // 0x3E: Copy the value n8 into register A.
    Opcode{"CCF", 1, 1, 0, Op_CCF},                     // 0x3F: Complement Carry Flag.

    // Block 1: 8-bit register-to-register loads
    Opcode{"LD B, B", 1, 1, 0, Op_LD_B_B},       // 0x40: Copy (aka Load) the value in B into B. -> TODO: Check if HALT
    Opcode{"LD B, C", 1, 1, 0, Op_LD_B_C},       // 0x41: Copy (aka Load) the value in C into B.
    Opcode{"LD B, D", 1, 1, 0, Op_LD_B_D},       // 0x42: Copy (aka Load) the value in D into B.
    Opcode{"LD B, E", 1, 1, 0, Op_LD_B_E},       // 0x43: Copy (aka Load) the value in E into B.
    Opcode{"LD B, H", 1, 1, 0, Op_LD_B_H},       // 0x44: Copy (aka Load) the value in H into B.
    Opcode{"LD B, L", 1, 1, 0, Op_LD_B_L},       // 0x45: Copy (aka Load) the value in L into B.
    Opcode{"LD B, [HL]", 1, 2, 0, Op_LD_B_pHL},  // 0x46: Copy (aka Load) the byte pointed by HL into B.
    Opcode{"LD B, A", 1, 1, 0, Op_LD_B_A},       // 0x47: Copy (aka Load) the value in A into B.
    Opcode{"LD C, B", 1, 1, 0, Op_LD_C_B},       // 0x48: Copy (aka Load) the value in B into C.
    Opcode{"LD C, C", 1, 1, 0, Op_LD_C_C},       // 0x49: Copy (aka Load) the value in C into C. -> TODO: Check if HALT
    Opcode{"LD C, D", 1, 1, 0, Op_LD_C_D},       // 0x4A: Copy (aka Load) the value in D into C.
    Opcode{"LD C, E", 1, 1, 0, Op_LD_C_E},       // 0x4B: Copy (aka Load) the value in E into C.
    Opcode{"LD C, H", 1, 1, 0, Op_LD_C_H},       // 0x4C: Copy (aka Load) the value in H into C.
    Opcode{"LD C, L", 1, 1, 0, Op_LD_C_L},       // 0x4D: Copy (aka Load) the value in L into C.
    Opcode{"LD C, [HL]", 1, 2, 0, Op_LD_C_pHL},  // 0x4E: Copy (aka Load) the byte pointed by HL into C.
    Opcode{"LD C, A", 1, 1, 0, Op_LD_C_A},       // 0x4F: Copy (aka Load) the value in A into C.
    Opcode{"LD D, B", 1, 1, 0, Op_LD_D_B},       // 0x50: Copy (aka Load) the value in B into D.
    Opcode{"LD D, C", 1, 1, 0, Op_LD_D_C},       // 0x51: Copy (aka Load) the value in C into D.
    Opcode{"LD D, D", 1, 1, 0, Op_LD_D_D},       // 0x52: Copy (aka Load) the value in D into D. -> TODO: Check if HALT
    Opcode{"LD D, E", 1, 1, 0, Op_LD_D_E},       // 0x53: Copy (aka Load) the value in E into D.
    Opcode{"LD D, H", 1, 1, 0, Op_LD_D_H},       // 0x54: Copy (aka Load) the value in H into D.
    Opcode{"LD D, L", 1, 1, 0, Op_LD_D_L},       // 0x55: Copy (aka Load) the value in L into D.
    Opcode{"LD D, [HL]", 1, 2, 0, Op_LD_D_pHL},  // 0x56: Copy (aka Load) the byte pointed by HL into D.
    Opcode{"LD D, A", 1, 1, 0, Op_LD_D_A},       // 0x57: Copy (aka Load) the value in A into D.
    Opcode{"LD E, B", 1, 1, 0, Op_LD_E_B},       // 0x58: Copy (aka Load) the value in B into E.
    Opcode{"LD E, C", 1, 1, 0, Op_LD_E_C},       // 0x59: Copy (aka Load) the value in C into E.
    Opcode{"LD E, D", 1, 1, 0, Op_LD_E_D},       // 0x5A: Copy (aka Load) the value in D into E.
    Opcode{"LD E, E", 1, 1, 0, Op_LD_E_E},       // 0x5B: Copy (aka Load) the value in E into E. -> TODO: Check if HALT
    Opcode{"LD E, H", 1, 1, 0, Op_LD_E_H},       // 0x5C: Copy (aka Load) the value in H into E.
    Opcode{"LD E, L", 1, 1, 0, Op_LD_E_L},       // 0x5D: Copy (aka Load) the value in L into E.
    Opcode{"LD E, [HL]", 1, 2, 0, Op_LD_E_pHL},  // 0x5E: Copy (aka Load) the byte pointed by HL into E.
    Opcode{"LD E, A", 1, 1, 0, Op_LD_E_A},       // 0x5F: Copy (aka Load) the value in A into E.
    Opcode{"LD H, B", 1, 1, 0, Op_LD_H_B},       // 0x60: Copy (aka Load) the value in B into H.
    Opcode{"LD H, C", 1, 1, 0, Op_LD_H_C},       // 0x61: Copy (aka Load) the value in C into H.
    Opcode{"LD H, D", 1, 1, 0, Op_LD_H_D},       // 0x62: Copy (aka Load) the value in D into H.
    Opcode{"LD H, E", 1, 1, 0, Op_LD_H_E},       // 0x63: Copy (aka Load) the value in E into H.
    Opcode{"LD H, H", 1, 1, 0, Op_LD_H_H},       // 0x64: Copy (aka Load) the value in H into H. -> TODO: Check if HALT
    Opcode{"LD H, L", 1, 1, 0, Op_LD_H_L},       // 0x65: Copy (aka Load) the value in L into H.
    Opcode{"LD H, [HL]", 1, 2, 0, Op_LD_H_pHL},  // 0x66: Copy (aka Load) the byte pointed by HL into H.
    Opcode{"LD H, A", 1, 1, 0, Op_LD_H_A},       // 0x67: Copy (aka Load) the value in A into H.
    Opcode{"LD L, B", 1, 1, 0, Op_LD_L_B},       // 0x68: Copy (aka Load) the value in B into L.
    Opcode{"LD L, C", 1, 1, 0, Op_LD_L_C},       // 0x69: Copy (aka Load) the value in C into L.
    Opcode{"LD L, D", 1, 1, 0, Op_LD_L_D},       // 0x6A: Copy (aka Load) the value in D into L.
    Opcode{"LD L, E", 1, 1, 0, Op_LD_L_E},       // 0x6B: Copy (aka Load) the value in E into L.
    Opcode{"LD L, H", 1, 1, 0, Op_LD_L_H},       // 0x6C: Copy (aka Load) the value in H into L.
    Opcode{"LD L, L", 1, 1, 0, Op_LD_L_L},       // 0x6D: Copy (aka Load) the value in L into L. -> TODO: Check if HALT
    Opcode{"LD L, [HL]", 1, 2, 0, Op_LD_L_pHL},  // 0x6E: Copy (aka Load) the byte pointed by HL into L.
    Opcode{"LD L, A", 1, 1, 0, Op_LD_L_A},       // 0x6F: Copy (aka Load) the value in A into L.
    Opcode{"LD [HL], B", 1, 2, 0, Op_LD_pHL_B},  // 0x70: Copy (aka Load) the value in B into the byte pointed by HL.
    Opcode{"LD [HL], C", 1, 2, 0, Op_LD_pHL_C},  // 0x71: Copy (aka Load) the value in C into the byte pointed by HL.
    Opcode{"LD [HL], D", 1, 2, 0, Op_LD_pHL_D},  // 0x72: Copy (aka Load) the value in D into the byte pointed by HL.
    Opcode{"LD [HL], E", 1, 2, 0, Op_LD_pHL_E},  // 0x73: Copy (aka Load) the value in E into the byte pointed by HL.
    Opcode{"LD [HL], H", 1, 2, 0, Op_LD_pHL_H},  // 0x74: Copy (aka Load) the value in H into the byte pointed by HL.
    Opcode{"LD [HL], L", 1, 2, 0, Op_LD_pHL_L},  // 0x75: Copy (aka Load) the value in L into the byte pointed by HL.
    Opcode{"HALT", 1, 0, 0, Op_HALT},            // 0x76: Enter CPU low-power consumption mode until an interrupt occurs.
    Opcode{"LD [HL], A", 1, 2, 0, Op_LD_pHL_A},  // 0x77: Copy (aka Load) the value in A into the byte pointed by HL.
    Opcode{"LD A, B", 1, 1, 0, Op_LD_A_B},       // 0x78: Copy (aka Load) the value in B into A.
    Opcode{"LD A, C", 1, 1, 0, Op_LD_A_C},       // 0x79: Copy (aka Load) the value in C into A.
    Opcode{"LD A, D", 1, 1, 0, Op_LD_A_D},       // 0x7A: Copy (aka Load) the value in D into A.
    Opcode{"LD A, E", 1, 1, 0, Op_LD_A_E},       // 0x7B: Copy (aka Load) the value in E into A.
    Opcode{"LD A, H", 1, 1, 0, Op_LD_A_H},       // 0x7C: Copy (aka Load) the value in H into A.
    Opcode{"LD A, L", 1, 1, 0, Op_LD_A_L},       // 0x7D: Copy (aka Load) the value in L into A.
    Opcode{"LD A, [HL]", 1, 2, 0, Op_LD_A_pHL},  // 0x7E: Copy (aka Load) the byte pointed by HL into A.
    Opcode{"LD A, A", 1, 1, 0, Op_LD_A_A},       // 0x7F: Copy (aka Load) the value in A into A. -> TODO: Check if HALT

    // Block 2: 8-bit arithmetic
    Opcode{"ADD A, B", 1, 1, 0, Op_ADD_A_B},       // 0x80: Add the value in B to A.
    Opcode{"ADD A, C", 1, 1, 0, Op_ADD_A_C},       // 0x81: Add the value in C to A.
    Opcode{"ADD A, D", 1, 1, 0, Op_ADD_A_D},       // 0x82: Add the value in D to A.
    Opcode{"ADD A, E", 1, 1, 0, Op_ADD_A_E},       // 0x83: Add the value in E to A.
    Opcode{"ADD A, H", 1, 1, 0, Op_ADD_A_H},       // 0x84: Add the value in H to A.
    Opcode{"ADD A, L", 1, 1, 0, Op_ADD_A_L},       // 0x85: Add the value in L to A.
    Opcode{"ADD A, [HL]", 1, 2, 0, Op_ADD_A_pHL},  // 0x86: Add the byte pointed by HL to A.
    Opcode{"ADD A, A", 1, 1, 0, Op_ADD_A_A},       // 0x87: Add the value in A to A.
    Opcode{"ADC A, B", 1, 1, 0, Op_ADC_A_B},       // 0x88: Add the value in B plus the carry flag to A.
    Opcode{"ADC A, C", 1, 1, 0, Op_ADC_A_C},       // 0x89: Add the value in C plus the carry flag to A.
    Opcode{"ADC A, D", 1, 1, 0, Op_ADC_A_D},       // 0x8A: Add the value in D plus the carry flag to A.
    Opcode{"ADC A, E", 1, 1, 0, Op_ADC_A_E},       // 0x8B: Add the value in E plus the carry flag to A.
    Opcode{"ADC A, H", 1, 1, 0, Op_ADC_A_H},       // 0x8C: Add the value in H plus the carry flag to A.
    Opcode{"ADC A, L", 1, 1, 0, Op_ADC_A_L},       // 0x8D: Add the value in L plus the carry flag to A.
    Opcode{"ADC A, [HL]", 1, 2, 0, Op_ADC_A_pHL},  // 0x8E: Add the byte pointed by HL plus the carry flag to A.
    Opcode{"ADC A, A", 1, 1, 0, Op_ADC_A_A},       // 0x8F: Add the value in A plus the carry flag to A.
    Opcode{"SUB A, B", 1, 1, 0, Op_SUB_A_B},       // 0x90: Subtract the value in B from A.
    Opcode{"SUB A, C", 1, 1, 0, Op_SUB_A_C},       // 0x91: Subtract the value in C from A.
    Opcode{"SUB A, D", 1, 1, 0, Op_SUB_A_D},       // 0x92: Subtract the value in D from A.
    Opcode{"SUB A, E", 1, 1, 0, Op_SUB_A_E},       // 0x93: Subtract the value in E from A.
    Opcode{"SUB A, H", 1, 1, 0, Op_SUB_A_H},       // 0x94: Subtract the value in H from A.
    Opcode{"SUB A, L", 1, 1, 0, Op_SUB_A_L},       // 0x95: Subtract the value in L from A.
    Opcode{"SUB A, [HL]", 1, 2, 0, Op_SUB_A_pHL},  // 0x96: Subtract the byte pointed to by HL from A.
    Opcode{"SUB A, A", 1, 1, 0, Op_SUB_A_A},       // 0x97: Subtract the value in A from A.
    Opcode{"SBC A, B", 1, 1, 0, Op_SBC_A_B},       // 0x98: Subtract the value in A and the carry flag from A.
    Opcode{"SBC A, C", 1, 1, 0, Op_SBC_A_C},       // 0x99: Subtract the value in B and the carry flag from A.
    Opcode{"SBC A, D", 1, 1, 0, Op_SBC_A_D},       // 0x9A: Subtract the value in C and the carry flag from A.
    Opcode{"SBC A, E", 1, 1, 0, Op_SBC_A_E},       // 0x9B: Subtract the value in D and the carry flag from A.
    Opcode{"SBC A, H", 1, 1, 0, Op_SBC_A_H},       // 0x9C: Subtract the value in H and the carry flag from A.
    Opcode{"SBC A, L", 1, 1, 0, Op_SBC_A_L},       // 0x9D: Subtract the value in L and the carry flag from A.
    Opcode{"SBC A, [HL]", 1, 2, 0, Op_SBC_A_pHL},  // 0x9E: Subtract the byte pointed to by HL and the carry flagto A.
    Opcode{"SBC A, A", 1, 1, 0, Op_SBC_A_A},       // 0x9F: Subtract the value in A and the carry flag from A.
    Opcode{"AND A, B", 1, 1, 0, Op_AND_A_B},       // 0xA0: Set A to the bitwise AND between the value in B and A.
    Opcode{"AND A, C", 1, 1, 0, Op_AND_A_C},       // 0xA1: Set A to the bitwise AND between the value in C and A.
    Opcode{"AND A, D", 1, 1, 0, Op_AND_A_D},       // 0xA2: Set A to the bitwise AND between the value in D and A.
    Opcode{"AND A, E", 1, 1, 0, Op_AND_A_E},       // 0xA3: Set A to the bitwise AND between the value in E and A.
    Opcode{"AND A, H", 1, 1, 0, Op_AND_A_H},       // 0xA4: Set A to the bitwise AND between the value in H and A.
    Opcode{"AND A, L", 1, 1, 0, Op_AND_A_L},       // 0xA5: Set A to the bitwise AND between the value in L and A.
    Opcode{"AND A, [HL]", 1, 2, 0, Op_AND_A_pHL},  // 0xA6: Set A to the bitwise AND between the byte pointed to by HL and A.
    Opcode{"AND A, A", 1, 1, 0, Op_AND_A_A},       // 0xA7: Set A to the bitwise AND between the value in A and A.
    Opcode{"XOR A, B", 1, 1, 0, Op_XOR_A_B},       // 0xA8: Set A to the bitwise XOR between the value in B and A.
    Opcode{"XOR A, C", 1, 1, 0, Op_XOR_A_C},       // 0xA9: Set A to the bitwise XOR between the value in C and A.
    Opcode{"XOR A, D", 1, 1, 0, Op_XOR_A_D},       // 0xAA: Set A to the bitwise XOR between the value in D and A.
    Opcode{"XOR A, E", 1, 1, 0, Op_XOR_A_E},       // 0xAB: Set A to the bitwise XOR between the value in E and A.
    Opcode{"XOR A, H", 1, 1, 0, Op_XOR_A_H},       // 0xAC: Set A to the bitwise XOR between the value in H and A.
    Opcode{"XOR A, L", 1, 1, 0, Op_XOR_A_L},       // 0xAD: Set A to the bitwise XOR between the value in L and A.
    Opcode{"XOR A, [HL]", 1, 2, 0, Op_XOR_A_pHL},  // 0xAE: Set A to the bitwise XOR between the byte pointed to by HL and A.
    Opcode{"XOR A, A", 1, 1, 0, Op_XOR_A_A},       // 0xAF: Set A to the bitwise XOR between the value in A and A.
    Opcode{"OR A, B", 1, 1, 0, Op_OR_A_B},         // 0xB0: Set A to the bitwise OR between the value in B and A.
    Opcode{"OR A, C", 1, 1, 0, Op_OR_A_C},         // 0xB1: Set A to the bitwise OR between the value in C and A.
    Opcode{"OR A, D", 1, 1, 0, Op_OR_A_D},         // 0xB2: Set A to the bitwise OR between the value in D and A.
    Opcode{"OR A, E", 1, 1, 0, Op_OR_A_E},         // 0xB3: Set A to the bitwise OR between the value in E and A.
    Opcode{"OR A, H", 1, 1, 0, Op_OR_A_H},         // 0xB4: Set A to the bitwise OR between the value in H and A.
    Opcode{"OR A, L", 1, 1, 0, Op_OR_A_L},         // 0xB5: Set A to the bitwise OR between the value in L and A.
    Opcode{"OR A, [HL]", 1, 2, 0, Op_OR_A_pHL},    // 0xB6: Set A to the bitwise OR between the byte pointed to by HL and A.
    Opcode{"OR A, A", 1, 1, 0, Op_OR_A_A},         // 0xB7: Set A to the bitwise OR between the value in A and A.
    Opcode{"CP A, B", 1, 1, 0, Op_CP_A_B},         // 0xB8: ComPare the value in A with the value in B.
    Opcode{"CP A, C", 1, 1, 0, Op_CP_A_C},         // 0xB9: ComPare the value in A with the value in C.
    Opcode{"CP A, D", 1, 1, 0, Op_CP_A_D},         // 0xBA: ComPare the value in A with the value in D.
    Opcode{"CP A, E", 1, 1, 0, Op_CP_A_E},         // 0xBB: ComPare the value in A with the value in E.
    Opcode{"CP A, H", 1, 1, 0, Op_CP_A_H},         // 0xBC: ComPare the value in A with the value in H.
    Opcode{"CP A, L", 1, 1, 0, Op_CP_A_L},         // 0xBD: ComPare the value in A with the value in L.
    Opcode{"CP A, [HL]", 1, 2, 0, Op_CP_A_pHL},    // 0xBE: ComPare the value in A with the byte pointed to by HL.
    Opcode{"CP A, A", 1, 1, 0, Op_CP_A_A},         // 0xBF: ComPare the value in A with the value in A.

    // Block 3
    Opcode{"RET NZ", 1, 2, 3, Op_RET_NZ},                  // 0xC0: Return from subroutine if condition NZ is met.
    Opcode{"POP BC", 1, 3, 0, Op_POP_BC},                  // 0xC1: Pop register BC from the stack.
    Opcode{"JP NZ, n16", 3, 3, 1, Op_JP_NZ_n16},           // 0xC2: Jump to address n16 if condition NZ is met.
    Opcode{"JP n16", 3, 3, 0, Op_JP_n16},                  // 0xC3: Jump to address n16
    Opcode{"CALL NZ,n16", 3, 3, 3, Op_CALL_NZ_n16},        // 0xC4: Call address n16 if condition NZ is met.
    Opcode{"PUSH BC", 1, 4, 0, Op_PUSH_BC},                // 0xC5: Push register BC into the stack.
    Opcode{"ADD A,n8", 2, 2, 0, Op_ADD_A_n8},              // 0xC6: Add the value n8 plus the carry flag to A.
    Opcode{"RST 00H", 1, 4, 0, Op_RST_00H},                // 0xC7: Call address 0x0000.
    Opcode{"RET Z", 1, 2, 3, Op_RET_Z},                    // 0xC8: Return from subroutine if condition Z is met.
    Opcode{"RET", 1, 4, 0, Op_RET},                        // 0xC9: Return from subroutine.
    Opcode{"JP Z, n16", 3, 3, 1, Op_JP_Z_n16},             // 0xCA: Jump to address n16 if condition Z is met.
    Opcode{"Prefix", 0, 0, 0, Op_JP_Z_n16},                // 0xCB: Prefix
    Opcode{"CALL Z, n16", 3, 3, 3, Op_CALL_Z_n16},         // 0xCC: Call address n16 if condition Z is met.
    Opcode{"CALL n16", 3, 6, 0, Op_CALL_n16},              // 0xCD: Call address n16.
    Opcode{"ADC A, n8", 2, 2, 0, Op_ADC_A_n8},             // 0xCE: Add the value n8 plus the carry flag to A.
    Opcode{"RST 08H", 1, 4, 0, Op_RST_08H},                // 0xCF: Call address 0x0008.
    Opcode{"RET NC", 1, 2, 3, Op_RET_NC},                  // 0xD0: Return from subroutine if condition NC is met.
    Opcode{"POP DE", 1, 3, 0, Op_POP_DE},                  // 0xD1: Pop register DE from the stack.
    Opcode{"JP NC, n16", 3, 3, 1, Op_JP_NC_n16},           // 0xD2: Jump to address n16 if condition NC is met.
    Opcode{"INVALID", 0, 0, 0, Op_Invalid},                // 0xD3: INVALID
    Opcode{"CALL NC, n16", 3, 3, 3, Op_CALL_NC_n16},       // 0xD4: Call address n16 if condition NC is met.
    Opcode{"PUSH DE", 1, 4, 0, Op_PUSH_DE},                // 0xD5: Push register DE into the stack.
    Opcode{"SUB A, n8", 2, 2, 0, Op_SUB_A_n8},             // 0xD6: Subtract the value n8 from A.
    Opcode{"RST 10H", 1, 4, 0, Op_RST_10H},                // 0xD7: Call address 0x0010.
    Opcode{"RET C", 1, 2, 3, Op_RET_C},                    // 0xD8: Return from subroutine if condition C is met.
    Opcode{"RETI", 1, 4, 0, Op_RETI},                      // 0xD9: Return from subroutine and enable interrupts.
    Opcode{"JP C, n16", 3, 3, 1, Op_JP_C_n16},             // 0xDA: Jump to address n16 if condition C is met.
    Opcode{"INVALID", 0, 0, 0, Op_Invalid},                // 0xDB: INVALID
    Opcode{"CALL C, n16", 3, 3, 3, Op_CALL_C_n16},         // 0xDC: Call address n16 if condition C is met.
    Opcode{"INVALID", 0, 0, 0, Op_Invalid},                // 0xDD: INVALID
    Opcode{"SBC A, n8", 2, 2, 0, Op_SBC_A_n8},             // 0xDE: Subtract the value n8 and the carry flag from A.
    Opcode{"RST 18H", 1, 4, 0, Op_RST_18H},                // 0xDF: Call address 0x0018.
    Opcode{"LDH [n8], A", 2, 3, 0, Op_LDH_pn8_A},          // 0xE0: Copy the value in register A into the byte at address 0xFF00 + n8.
    Opcode{"POP HL", 1, 3, 0, Op_POP_HL},                  // 0xE1: Pop register HL from the stack.
    Opcode{"LDH [C], A", 1, 2, 0, Op_LDH_pC_A},            // 0xE2: Copy the value in register A into the byte at address 0xFF00 + C.
    Opcode{"INVALID", 0, 0, 0, Op_Invalid},                // 0xE3: INVALID
    Opcode{"INVALID", 0, 0, 0, Op_Invalid},                // 0xE4: INVALID
    Opcode{"PUSH HL", 1, 4, 0, Op_PUSH_HL},                // 0xE5: Push register HL into the stack.
    Opcode{"AND A, n8", 2, 2, 0, Op_AND_A_n8},             // 0xE6: Set A to the bitwise AND between the value n8 and A.
    Opcode{"RST 20H", 1, 4, 0, Op_RST_20H},                // 0xE7: Call address 0x0020.
    Opcode{"ADD SP, e8", 2, 4, 0, Op_ADD_SP_e8},           // 0xE8: Add the signed value e8 to SP.
    Opcode{"JP HL", 1, 1, 0, Op_JP_HL},                    // 0xE9: Jump to address in HL
    Opcode{"LD [n16], A", 3, 4, 0, Op_LD_pn16_A},          // 0xEA: Copy the value in register A into the byte at address n16.
    Opcode{"INVALID", 0, 0, 0, Op_Invalid},                // 0xEB: INVALID
    Opcode{"INVALID", 0, 0, 0, Op_Invalid},                // 0xEC: INVALID
    Opcode{"INVALID", 0, 0, 0, Op_Invalid},                // 0xED: INVALID
    Opcode{"XOR A, n8", 2, 2, 0, Op_XOR_A_n8},             // 0xEE: Set A to the bitwise XOR between the value n8 and A.
    Opcode{"RST 28H", 1, 4, 0, Op_RST_28H},                // 0xEF: Call address 0x0028.
    Opcode{"LDH A, n8", 2, 3, 0, Op_RST_28H},              // 0xF0: Copy the byte at address 0xFF00 + n8 into register A
    Opcode{"POP AF", 1, 3, 0, Op_POP_AF},                  // 0xF1: Pop register AF from the stack.
    Opcode{"LDH A, [C]", 1, 2, 0, Op_LDH_A_pC},            // 0xF2: Copy the byte at address 0xFF00 + C into register A.
    Opcode{"DI", 1, 1, 0, Op_DI},                          // 0xF3: Disable Interrupts by clearing the IME flag.
    Opcode{"INVALID", 0, 0, 0, Op_Invalid},                // 0xF4: INVALID
    Opcode{"PUSH AF", 1, 4, 0, Op_PUSH_AF},                // 0xF5: Push register AF into the stack.
    Opcode{"OR A, n8", 2, 2, 0, Op_OR_A_n8},               // 0xF6: Set A to the bitwise OR between the value n8 and A.
    Opcode{"RST 30H", 1, 4, 0, Op_RST_30H},                // 0xF7: Call address 0x0030.
    Opcode{"LD HL, SP+e8", 2, 3, 0, Op_LD_HL_SP_plus_e8},  // 0xF8: Add the signed value e8 to SP and copy the result in HL.
    Opcode{"LD SP, HL", 1, 2, 0, Op_LD_SP_HL},             // 0xF9: Copy register HL into register SP.
    Opcode{"LD A, [n16]", 3, 4, 0, Op_LD_A_pn16},          // 0xFA: Copy the byte at address n16 into register A.
    Opcode{"EI", 1, 1, 0, Op_EI},                          // 0xFB: Enable Interrupts by setting the IME flag.
    Opcode{"INVALID", 0, 0, 0, Op_Invalid},                // 0xFC: INVALID
    Opcode{"INVALID", 0, 0, 0, Op_Invalid},                // 0xFD: INVALID
    Opcode{"CP A, n8", 2, 3, 0, Op_CP_A_n8},               // 0xFE: ComPare the value in A with the value n8.
    Opcode{"RST 38H", 1, 4, 0, Op_RST_38H},                // 0xFF: Call address 0x0038.
    // TODO: Add missing instructions
};