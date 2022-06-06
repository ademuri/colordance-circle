#include "ControlPoleEffectStatic.hpp"

ControlPoleEffectStatic::ControlPoleEffectStatic() : ControlPoleEffect() {}

uint8_t ControlPoleEffectStatic::GetShiftsPerLoop() { return 1; }

void ControlPoleEffectStatic::DoSetGrid(uint8_t shiftIndex) {
  // shiftIndex always 0
  grid_lights[shiftIndex][shiftIndex] =
      CHSV(currentHue + GetHueDistance(hueDistance, 0, 2), baseSat, baseVal);
  grid_lights[3 - shiftIndex][shiftIndex] =
      CHSV(currentHue + GetHueDistance(hueDistance, 1, 2), baseSat, baseVal);
}