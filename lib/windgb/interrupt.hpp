#pragma once

#include <cstdint>

namespace WindGB {

class Bus;
class IO;

class InterruptHandler {
   public:
    explicit InterruptHandler(Bus& bus, IO& io);

    [[nodiscard]] bool has_pending() const;
    [[nodiscard]] uint8_t get_next_pending() const;
    void clear_flag(uint8_t id);

    bool ime = false;

   private:
    Bus& bus_;

    uint8_t& if_;
};

}  // namespace WindGB