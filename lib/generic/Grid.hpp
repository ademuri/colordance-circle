#pragma once

#include <array>
#include <cstdint>

constexpr std::uint8_t gridWidth = 4;
constexpr std::uint8_t gridHeight = 4;

template<typename T>
using Grid = std::array<std::array<T, gridWidth>, gridHeight>;
 