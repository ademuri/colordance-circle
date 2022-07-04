#include "ControlPoleEffectCircle.hpp"

ControlPoleEffectCircle::ControlPoleEffectCircle() : ControlPoleEffect() {}

uint8_t ControlPoleEffectCircle::GetShiftsPerLoop() { return 8; }

uint8_t ControlPoleEffectCircle::GetRotations() { return 4; }

void ControlPoleEffectCircle::DoSetGrid(
    Grid<CHSV>& grid_lights, uint8_t shiftIndex) {
  uint8_t const rotationOffset = rotation + 1;
  for (std::uint8_t n = 0; n != lightCount; ++n) {
    auto const useOffsetFix = rotation == 3 and (n == 2 or (n == 1 and lightCount == 4));
    auto const baseIndex = shiftIndex + n * rotationOffset + (useOffsetFix ? -1 : 0);
    auto & grid_light = grid_lights[GetIndex(baseIndex + 2)][GetIndex(baseIndex)];
    grid_light = CHSV(currentHue + GetHueDistance(hueDistance, n, lightCount), baseSat, baseVal);
  }
}

uint8_t ControlPoleEffectCircle::GetIndex(uint8_t shiftIndex) {
  shiftIndex %= 8;
  return (shiftIndex < 4 ? shiftIndex : 7 - shiftIndex) % 4;
}
