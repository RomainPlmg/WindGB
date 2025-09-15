#pragma once

#include <atomic>

namespace WindGB {

enum class JoypadButton {
    A,
    B,
    START,
    SELECT,
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

struct JoypadState {
    bool dpad, button;
    std::atomic<bool> a, b, start, select;
    std::atomic<bool> up, down, left, right;
};

class Joypad {
   public:
    [[nodiscard]] uint8_t get_output() const;
    JoypadState& get_state() { return state_; }

    void set_sel(uint8_t data);
    void set_button(JoypadButton button, bool state);

    [[nodiscard]] bool is_button_released();

   private:
    std::atomic<uint8_t> last_reg_state_ = 0xCF;
    JoypadState state_ = {};
};

}  // namespace WindGB
