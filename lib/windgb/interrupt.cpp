#include "interrupt.hpp"

#include <cstdint>

#include "bus.hpp"
#include "common.hpp"
#include "io.hpp"
#include "logger.hpp"

namespace WindGB {

InterruptHandler::InterruptHandler(Bus& bus, IO& io) : bus_(bus), if_(io.get_data()[REG_IF_ADDR - IO_ADDR_START]) {}

bool InterruptHandler::has_pending() const {
    const uint8_t ie = bus_.direct_read(REG_IE_ADDR);
    return (ie & if_ & 0x1F) != 0;
}

uint8_t InterruptHandler::get_next_pending() const {
    const uint8_t ie = bus_.direct_read(REG_IE_ADDR);
    const uint8_t pending = if_ & ie & 0x1F;  // Mask for enabled pending instructions
    for (uint8_t id = 0; id <= 4; id++) {
        if (pending & (1 << id)) {
            return id;
        }
    }
    return 0xFF;
}

void InterruptHandler::clear_flag(uint8_t id) {
    if (id > 4) {
        LOG_ERROR("{} is an invalid interrupt ID", id);
        return;
    }
    if_ &= ~(1 << id);
}

}  // namespace WindGB