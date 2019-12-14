#ifndef POLE_HPP_
#define POLE_HPP_

#include <vector>
#include "ColordanceTypes.hpp"

class Pole {
 public:
  Pole();

  void SetGridLight(uint8_t x, uint8_t y, const CRGB &rgb);
  void SetGridLight(uint8_t x, uint8_t y, const CHSV &hsv);
  void ClearGridLights();

  const std::vector<std::vector<CRGB>> get_grid_lights();

  static const uint8_t kGridWidth = 4;
  static const uint8_t kGridHeight = 4;
  static const uint8_t kNumPoles = 6;

 private:
  std::vector<std::vector<CRGB>> grid_lights;
};

#endif
