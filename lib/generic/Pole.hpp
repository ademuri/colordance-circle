#pragma once

#include <vector>

#include "ColordanceTypes.hpp"

class Pole {
 public:
  Pole();

  void SetGridLight(uint8_t x, uint8_t y, const CRGB &rgb);
  void SetGridLight(uint8_t x, uint8_t y, const CHSV &hsv);
  void SetGridLights(std::vector<std::vector<CHSV>> const &grid_lights);
  void MultiplyGridLight(uint8_t x, uint8_t y, const CRGB &rgb);
  void MultiplyGridLight(uint8_t x, uint8_t y, const CHSV &hsv);
  void MultiplyGridLights(std::vector<std::vector<CHSV>> const &grid_lights);
  void ClearGridLights();

  std::vector<std::vector<CRGB>> const &get_grid_lights() const {
    return grid_lights;
  }

  static const uint8_t kGridWidth = 4;
  static const uint8_t kGridHeight = 4;
  static const uint8_t kNumPoles = 6;

 private:
  std::vector<std::vector<CRGB>> grid_lights;
};
