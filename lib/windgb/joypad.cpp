#include "joypad.hpp"

namespace WindGB {

uint8_t Joypad::get_output() const {
    uint8_t res = 0xCF;

    if (!state_.button) {  // Buttons active
        if (state_.a) res &= ~0x01;
        if (state_.b) res &= ~0x02;
        if (state_.select) res &= ~0x04;
        if (state_.start) res &= ~0x08;
    }

    if (!state_.dpad) {  // D-PAD active
        if (state_.right) res &= ~0x01;
        if (state_.left) res &= ~0x02;
        if (state_.up) res &= ~0x04;
        if (state_.down) res &= ~0x08;
    }

    return res;
}

void Joypad::set_sel(const uint8_t data) {
    state_.button = data & 0x20;
    state_.dpad = data & 0x10;
}
void Joypad::set_button(const JoypadButton button, const bool state) {
    last_reg_state_ = get_output();
    switch (button) {
        case JoypadButton::A:
            state_.a = state;
            break;
        case JoypadButton::B:
            state_.b = state;
            break;
        case JoypadButton::START:
            state_.start = state;
            break;
        case JoypadButton::SELECT:
            state_.select = state;
            break;
        case JoypadButton::UP:
            state_.up = state;
            break;
        case JoypadButton::DOWN:
            state_.down = state;
            break;
        case JoypadButton::LEFT:
            state_.left = state;
            break;
        case JoypadButton::RIGHT:
            state_.right = state;
            break;
        default:
            break;
    }
}

bool Joypad::is_button_released() {
    const uint8_t new_reg = get_output();

    // Handle interrupt
    for (int i = 0; i < 4; i++) {
        if ((new_reg & (1 << i)) && !(last_reg_state_ & (1 << i))) {
            last_reg_state_ = new_reg;
            return true;
        }
    }
    return false;
}

}  // namespace WindGB