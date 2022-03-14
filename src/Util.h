#pragma once
#include <stdint.h>

inline constexpr uint32_t grayscale(uint8_t level)
{
    return 0xFF000000 | level << 16 | level << 8 | level;
}
static_assert(grayscale(0x12) == 0xFF121212);
static_assert(grayscale(0xFF) == 0xFFFFFFFF);

inline constexpr uint32_t greenscale(uint8_t level)
{
    return 0xFF000000 | level << 8;
}
static_assert(greenscale(0x12) == 0xFF001200);
static_assert(greenscale(0xFF) == 0xFF00FF00);

inline constexpr uint8_t bit(uint8_t idx, uint8_t byte)
{
    return (byte & (1 << idx)) != 0;
}
static_assert(bit(0, 0b000000001) == 1);
static_assert(bit(1, 0b000000010) == 1);

inline constexpr uint8_t combine(uint8_t idx, uint8_t first, uint8_t second)
{
    auto a = bit(idx, first);
    auto b = bit(idx, second);
    return a << 1 | b;
}
static_assert(combine(0, 1, 1) == 3);
