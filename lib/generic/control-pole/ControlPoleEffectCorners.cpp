#include "ControlPoleEffectCorners.hpp"

ControlPoleEffectCorners::ControlPoleEffectCorners() : ControlPoleEffect() {}

uint8_t ControlPoleEffectCorners::GetShiftsPerLoop() { return 4; }

uint8_t ControlPoleEffectCorners::GetRotations() { return 1; }

void ControlPoleEffectCorners::DoSetGrid(
    std::vector<std::vector<CHSV>> &grid_lights, uint8_t shiftIndex) {
  switch (lightCount) {
    case (4):
      grid_lights[GetIndex(shiftIndex, 1)][GetIndex(shiftIndex, 0)] = CHSV(
          currentHue + GetHueDistance(hueDistance, (shiftIndex + 3) % 4, 4),
          baseSat, baseVal);
      // fall through
    case (3):
      grid_lights[GetIndex(shiftIndex, 1)][GetIndex(shiftIndex, 1)] = CHSV(
          currentHue + GetHueDistance(hueDistance, (shiftIndex + 2) % 4, 4),
          baseSat, baseVal);
      // fall through
    case (2):
      grid_lights[GetIndex(shiftIndex, 0)][GetIndex(shiftIndex, 1)] = CHSV(
          currentHue + GetHueDistance(hueDistance, (shiftIndex + 1) % 4, 4),
          baseSat, baseVal);
      // fall through
    case (1):
      grid_lights[GetIndex(shiftIndex, 0)][GetIndex(shiftIndex, 0)] =
          CHSV(currentHue + GetHueDistance(hueDistance, shiftIndex, 4), baseSat,
               baseVal);
  }
}

uint8_t ControlPoleEffectCorners::GetIndex(uint8_t shiftIndex, uint8_t offset) {
  uint8_t val = (shiftIndex + offset) % 2;
  return val > 0 ? 3 : 0;
}