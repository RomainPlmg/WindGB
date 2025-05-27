#pragma once

#include "bus.h"
#include "utils/common.h"

constexpr u16 TIMER_DIV_REG_ADDR = 0xFF04;
constexpr u16 TIMER_TIMA_REG_ADDR = 0xFF05;
constexpr u16 TIMER_TMA_REG_ADDR = 0xFF06;
constexpr u16 TIMER_TAC_REG_ADDR = 0xFF07;

// For more info: https://gbdev.io/pandocs/Timer_and_Divider_Registers.html
class Timer {
   public:
    Timer(Bus& memBus);

    void Reset();
    void Step(int cycles);

   private:
    Bus& m_Bus;
    int m_DIVCounter;
    int m_TIMACounter;
};