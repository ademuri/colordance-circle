#include "ControlPoleEffectSmallSquare.hpp"

ControlPoleEffectSmallSquare::ControlPoleEffectSmallSquare()
    : ControlPoleEffect() {}

uint8_t ControlPoleEffectSmallSquare::GetShiftsPerLoop() { return 4; }

uint8_t ControlPoleEffectSmallSquare::GetRotations() { return 1; }

void ControlPoleEffectSmallSquare::DoSetGrid(
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

uint8_t ControlPoleEffectSmallSquare::GetIndex(uint8_t shiftIndex,
                                               uint8_t offset) {
  return ((shiftIndex + offset) % 2 + 1) % 4;
}