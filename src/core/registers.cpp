#include "registers.h"

uint16_t Registers::GetAndIncrPC() {
    uint16_t retPC = this->PC;
    this->PC++;
    return retPC;
}

uint16_t Registers::IncrPC() {
    this->PC++;
    return this->PC;
}