#include "io.hpp"

#include "common.hpp"
#include "logger.hpp"

namespace WindGB {

IO::IO() {
    joypad_ = std::make_unique<Joypad>();
    assert(joypad_);
}

uint8_t IO::read(const uint16_t addr) const {
    const uint16_t index = addr - IO_ADDR_START;
    if (addr == 0xFF00) {
        return joypad_->get_output();
    }
    return data_[index];
}

void IO::write(const uint16_t addr, const uint8_t data) {
    const uint16_t index = addr - IO_ADDR_START;
    if (addr == 0xFF00) {
        joypad_->set_sel(data);
    } else {
        data_[index] = data;
    }
}

}  // namespace WindGB