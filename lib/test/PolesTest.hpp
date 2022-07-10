#pragma once

#include <gtest/gtest.h>

#include "Pole.hpp"

class PolesTest : public ::testing::Test {
 protected:
  Poles poles{};

  static uint16_t Brightness(const CRGB& rgb) { return rgb.r + rgb.g + rgb.b; }

  static uint8_t GetLightCount(const Pole& pole) {
    uint8_t light_count = 0;
    for (auto column : pole.get_grid_lights()) {
      for (CRGB rgb : column) {
        if (Brightness(rgb) > 0) {
          light_count++;
        }
      }
    }
    return light_count;
  }

  uint16_t GetTotalLightCount() const {
    uint16_t light_count = 0;
    for (Pole const& pole : poles) {
      light_count += GetLightCount(pole);
    }
    return light_count;
  }

  uint8_t GetPolesOn() const {
    return std::count_if(poles.begin(), poles.end(), [](Pole const& pole) {
      return GetLightCount(pole) > 0;
    });
  }
};