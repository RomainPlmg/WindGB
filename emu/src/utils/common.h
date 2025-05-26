#pragma once

#include <cstdint>
#include <iostream>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

constexpr bool GET_BIT(u32 a, u8 n) { return ((a & (1 << n)) != 0); }
constexpr void SET_BIT(u32 a, u8 n, bool val) { val ? a |= (1 << n) : a &= ~(1 << n); }
void NO_IMPL();