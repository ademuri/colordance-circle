#include "ControlPoleEffectCross.hpp"

ControlPoleEffectCross::ControlPoleEffectCross() : ControlPoleEffect() {}

uint8_t ControlPoleEffectCross::GetShiftsPerLoop() { return 4; }

void ControlPoleEffectCross::DoSetGrid(uint8_t shiftIndex) {
  grid_lights[shiftIndex][shiftIndex] =
      CHSV(currentHue + GetHueDistance(hueDistance, 0, 2), baseSat, baseVal);
  grid_lights[3 - shiftIndex][shiftIndex] =
      CHSV(currentHue + GetHueDistance(hueDistance, 1, 2), baseSat, baseVal);
}