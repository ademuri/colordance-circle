#include "ControlPoleEffectSmallSquare.hpp"

ControlPoleEffectSmallSquare::ControlPoleEffectSmallSquare()
    : ControlPoleEffect() {}

uint8_t ControlPoleEffectSmallSquare::GetShiftsPerLoop() { return 4; }

uint8_t ControlPoleEffectSmallSquare::GetRotations() { return 1; }

void ControlPoleEffectSmallSquare::DoSetGrid(
    Grid<CHSV> &grid_lights, uint8_t shiftIndex) {
  for (std::uint8_t n = 0; n != lightCount; ++n) {
    auto & grid_light = grid_lights[GetIndex(shiftIndex, n >= 2)][GetIndex(shiftIndex, n == 1 or n == 2)];
    grid_light = CHSV(currentHue + GetHueDistance(hueDistance, (shiftIndex + n) % 4, 4), baseSat, baseVal);
  }
}

uint8_t ControlPoleEffectSmallSquare::GetIndex(uint8_t shiftIndex,
                                               uint8_t offset) {
  return ((shiftIndex + offset) % 2 + 1) % 4;
}