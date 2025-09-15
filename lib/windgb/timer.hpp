#pragma once

#include <cstdint>

namespace WindGB {

class Bus;
class IO;

class Timer {
   public:
    Timer(Bus& bus, IO& io);

    void init();
    void tick();
    void reset_counter();

   private:
    Bus& bus_;

    uint16_t div_16_ = 0;
    uint8_t& div_;
    uint8_t& tima_;
    uint8_t& tma_;
    uint8_t& tac_;
    uint8_t& if_;
};

}  // namespace WindGB