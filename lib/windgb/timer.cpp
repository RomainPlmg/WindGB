#include "timer.hpp"

#include <array>
#include <cstdint>

#include "bus.hpp"
#include "common.hpp"
#include "io.hpp"
#include "logger.hpp"

namespace WindGB {

static constexpr std::array TIMA_DIV_BIT = {9, 3, 5, 7};

Timer::Timer(Bus& bus, IO& io)
    : bus_(bus),
      div_(io.get_data()[REG_DIV_ADDR - IO_ADDR_START]),
      tima_(io.get_data()[REG_TIMA_ADDR - IO_ADDR_START]),
      tma_(io.get_data()[REG_TMA_ADDR - IO_ADDR_START]),
      tac_(io.get_data()[REG_TAC_ADDR - IO_ADDR_START]),
      if_(io.get_data()[REG_IF_ADDR - IO_ADDR_START]) {}

void Timer::init() {
    div_16_ = 0;
    LOG_INFO("Timer initialized");
}

void Timer::tick() {
    const uint16_t div_back = div_16_;
    div_16_++;
    div_ = static_cast<uint8_t>(div_16_ >> 8);

    if (const bool tima_enabled = tac_ & 0b100; !tima_enabled) return;

    static bool overflow = false;
    if (overflow) {
        static uint8_t overflow_counter = 0;
        overflow_counter++;
        if (overflow_counter >= 16) {
            tima_ = tma_;
            if_ |= (1 << 2);
            overflow = false;
            overflow_counter = 0;
            return;
        }
    }

    const int offset = TIMA_DIV_BIT[tac_ & 0b11];
    const bool new_bit = (div_16_ >> offset) & 1;

    if (const bool old_bit = (div_back >> offset) & 1; old_bit && !new_bit) {  // Detect falling edge on the corresponding bit in DIV register
        if (tima_ >= 0xFF) {                                                   // Overflow
            tima_ = tma_;
            if_ |= (1 << 2);
            // overflow = true;
        } else {
            tima_++;
        }
    }
}

void Timer::reset_counter() {
    div_16_ = 0;
    div_ = 0;
}

}  // namespace WindGB