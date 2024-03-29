#include "ControlPoleEffectCorners.hpp"

ControlPoleEffectCorners::ControlPoleEffectCorners() : ControlPoleEffect() {}

uint8_t ControlPoleEffectCorners::GetShiftsPerLoop() { return 4 - lightCount; }

uint8_t ControlPoleEffectCorners::GetRotations() { return 1; }

void ControlPoleEffectCorners::DoSetGrid(Grid<CHSV> &grid_lights,
                                         uint8_t shiftIndex) {
  for (std::uint8_t n = 0; n != lightCount; ++n) {
    auto &grid_light = grid_lights[GetIndex(shiftIndex, n >= 2)]
                                  [GetIndex(shiftIndex, n == 1 or n == 2)];
    grid_light =
        CHSV(currentHue + GetHueDistance(hueDistance, (shiftIndex + n) % 4, 4),
             baseSat, baseVal);
  }
}

uint8_t ControlPoleEffectCorners::GetIndex(uint8_t shiftIndex, uint8_t offset) {
  uint8_t val = (shiftIndex + offset) % 2;
  return val > 0 ? 3 : 0;
}