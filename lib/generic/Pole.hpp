#pragma once

#include <array>

#include "ColordanceTypes.hpp"
#include "Grid.hpp"

class Pole {
 public:
  Pole();

  void SetGridLight(uint8_t x, uint8_t y, const CRGB &rgb);
  void SetGridLight(uint8_t x, uint8_t y, const CHSV &hsv);
  void SetGridLights(Grid<CHSV> const &grid_lights);
  void MultiplyGridLight(uint8_t x, uint8_t y, const CRGB &rgb);
  void MultiplyGridLight(uint8_t x, uint8_t y, const CHSV &hsv);
  void MultiplyGridLights(Grid<CHSV> const &grid_lights);
  void ClearGridLights();

  Grid<CRGB> const &get_grid_lights() const {
    return grid_lights;
  }

  static const uint8_t kNumPoles = 6;

 private:
  Grid<CRGB> grid_lights;
};

using Poles = std::array<Pole, Pole::kNumPoles>;