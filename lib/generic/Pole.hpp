#pragma once

#include <array>

#include "ColordanceTypes.hpp"
#include "Grid.hpp"

constexpr uint8_t kLightsPerPole = 45;

using PoleLights = std::array<CRGB, kLightsPerPole>;

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

  void SetPoleLight(uint8_t n, const CRGB &rgb);
  void ClearPoleLights();

  Grid<CRGB> const &get_grid_lights() const { return grid_lights; }
  PoleLights const &get_pole_lights() const { return pole_lights; }

  // If any channel is below `kMinBrightess`, sets it to 0. The LEDs on the
  // light panels do not light up reliably below a brightness of 10. Setting
  // these to 0 below this brightness makes colors more consistent.
  static CRGB ClampCRGBForDisplay(CRGB value);

  static constexpr uint8_t kNumPoles = 6;

 private:
  Grid<CRGB> grid_lights;
  PoleLights pole_lights;

  static constexpr uint8_t kMinBrightness = 10;
};

using Poles = std::array<Pole, Pole::kNumPoles>;