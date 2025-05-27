#include "timer.h"

#include "io_reg.h"

static constexpr std::array<int, 4> TIMER_FREQ = {1024, 16, 64, 256};

Timer::Timer(Bus& memBus) : m_Bus(memBus), m_DIVCounter(0), m_TIMACounter(0) {}

void Timer::Reset() {
    m_DIVCounter = 0;
    m_Bus.Write(TIMER_DIV_REG_ADDR, 0);
}

void Timer::Step(int cycles) {
    // DIV
    m_DIVCounter += cycles;
    if (m_DIVCounter >= 256) {  // Because 4194304Hz / 16384Hz = 256
        m_DIVCounter -= 256;
        u8 DIV = m_Bus.Read(TIMER_DIV_REG_ADDR);
        m_Bus.Write(TIMER_DIV_REG_ADDR, DIV + 1);
    }

    // Check TAC register
    u8 TAC = m_Bus.Read(TIMER_TAC_REG_ADDR);
    bool incrTIMA = TAC & 0b100;
    if (!incrTIMA) return;

    // TIMA
    int freq = TIMER_FREQ[TAC & 0b11];
    m_TIMACounter += cycles;
    if (m_TIMACounter >= freq) {
        m_TIMACounter -= freq;
        u8 TIMA = m_Bus.Read(TIMER_TIMA_REG_ADDR);
        if (TIMA == 0xFF) {  // Overflow
            u8 TMA = m_Bus.Read(TIMER_TMA_REG_ADDR);
            m_Bus.Write(TIMER_TIMA_REG_ADDR, TMA);
            // Set the TIMER interrupt
            u8 IF = m_Bus.Read(IO_REG_INTERRUPT_FLAGS);
            IF |= (1 << 2);
            m_Bus.Write(IO_REG_INTERRUPT_FLAGS, IF);
        } else {
            m_Bus.Write(TIMER_TIMA_REG_ADDR, TIMA + 1);
        }
    }
}
