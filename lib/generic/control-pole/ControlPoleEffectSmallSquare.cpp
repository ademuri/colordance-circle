#include "ControlPoleEffectSmallSquare.hpp"

ControlPoleEffectSmallSquare::ControlPoleEffectSmallSquare()
    : ControlPoleEffect() {}

uint8_t ControlPoleEffectSmallSquare::GetShiftsPerLoop() { return 4; }

uint8_t ControlPoleEffectSmallSquare::GetRotations() { return 1; }

void ControlPoleEffectSmallSquare::DoSetGrid(Grid<CHSV> &grid_lights,
                                             uint8_t shiftIndex) {
  for (std::uint8_t n = 0; n != lightCount; ++n) {
    uint8_t adjustedIndex = (shiftIndex + n) % 4;
    auto &grid_light =
        grid_lights[adjustedIndex % 2 + 1][((adjustedIndex + 1) % 4) / 2 + 1];
    grid_light =
        CHSV(currentHue + GetHueDistance(hueDistance, adjustedIndex, 4),
             baseSat, baseVal);
  }
}
