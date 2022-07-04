#pragma once

#include <array>
#include <cstdint>

inline constexpr std::uint8_t gridWidth = 4;
inline constexpr std::uint8_t gridHeight = 4;

template<typename T>
using Grid = std::array<std::array<T, gridWidth>, gridHeight>;
 