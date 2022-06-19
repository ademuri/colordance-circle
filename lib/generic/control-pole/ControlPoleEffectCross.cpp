#include "ControlPoleEffectCross.hpp"

ControlPoleEffectCross::ControlPoleEffectCross() : ControlPoleEffect() {}

uint8_t ControlPoleEffectCross::GetShiftsPerLoop() { return 4; }

uint8_t ControlPoleEffectCross::GetRotations() { return 1; }

void ControlPoleEffectCross::DoSetGrid(
    std::vector<std::vector<CHSV>>& grid_lights, uint8_t shiftIndex) {
  grid_lights[shiftIndex % 4][shiftIndex % 4] =
      CHSV(currentHue + GetHueDistance(hueDistance, 0, 2), baseSat, baseVal);
  grid_lights[(3 - shiftIndex) % 4][shiftIndex % 4] =
      CHSV(currentHue + GetHueDistance(hueDistance, 1, 2), baseSat, baseVal);
}