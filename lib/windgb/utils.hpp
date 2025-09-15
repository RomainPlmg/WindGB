#pragma once

#include <cstdint>
#include <iomanip>
#include <sstream>

namespace WindGB {

std::string to_hex4(uint16_t data) {
    std::ostringstream oss;
    oss << "0x" << std::uppercase << std::hex << std::setw(4) << std::setfill('0') << data;
    return oss.str();
}

}  // namespace WindGB