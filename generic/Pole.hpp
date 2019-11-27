#ifndef POLE_HPP_
#define POLE_HPP_

#include <vector>
#include "Types.hpp"

class Pole {
 public:
  Pole();

  void SetGridLight(uint8_t x, uint8_t y, const CRGB &rgb);
  void SetGridLight(uint8_t x, uint8_t y, const CHSV &hsv);

  const std::vector<std::vector<CRGB>> get_grid_lights();

 private:
  static const uint8_t grid_width = 3;
  static const uint8_t grid_height = 3;

  std::vector<std::vector<CRGB>> grid_lights;
};

#endif
