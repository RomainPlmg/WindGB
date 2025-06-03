#include "timer.h"

#include "io.h"
#include "utils/log.h"

static constexpr std::array<int, 4> TIMER_FREQ = {1024, 16, 64, 256};
static constexpr std::array<int, 4> TIMA_DIV_BIT = {9, 3, 5, 7};

Timer::Timer(Bus& memBus) : m_Bus(memBus) {}

void Timer::Reset() {
    m_DIVCounter = 0;
    m_TIMA = 0;
    m_TMA = 0;
    m_TAC = 0;
}

void Timer::Step() {
    // DIV counter
    u16 oldDIVCounter = m_DIVCounter;  // For the TIMA, see below
    m_DIVCounter++;

    // TIMA
    bool TIMAEnable = m_TAC & 0b100;
    if (!TIMAEnable) return;

    int bit = TIMA_DIV_BIT[m_TAC & 0b11];
    bool newBit = (m_DIVCounter >> bit) & 1;
    bool oldBit = (oldDIVCounter >> bit) & 1;

    if (oldBit & !newBit) {  // Detect falling edge on the corresponding bit in DIV register
        if (m_TIMA == 0xFF) {
            m_TIMA = m_TMA;
            u8 IF = m_Bus.Read(INTERRUPT_FLAGS_ADDR);
            IF |= (1 << 2);
            m_Bus.Write(INTERRUPT_FLAGS_ADDR, IF);
        } else {
            m_TIMA++;
        }
    }
}

u8 Timer::Read(u16 addr) {
    switch (addr) {
        case TIMER_DIV_REG_ADDR:
            return m_DIVCounter >> 8;

        case TIMER_TIMA_REG_ADDR:
            return m_TIMA;

        case TIMER_TMA_REG_ADDR:
            return m_TMA;

        case TIMER_TAC_REG_ADDR:
            return m_TAC;

        default:
            LOG_ERROR("Invalid addr {:02X} for Timer read.");
            return 0xFF;
    }
}

void Timer::Write(u16 addr, u8 data) {
    switch (addr) {
        case TIMER_DIV_REG_ADDR:
            LOG_INFO("Reset DIV counter");
            m_DIVCounter = 0;
            break;

        case TIMER_TIMA_REG_ADDR:
            m_TIMA = data;
            break;

        case TIMER_TMA_REG_ADDR:
            m_TMA = data;
            break;

        case TIMER_TAC_REG_ADDR:
            m_TAC = data;
            break;

        default:
            LOG_ERROR("Invalid addr {:02X} for Timer write.");
            break;
    }
}