#include "ControlPoleEffectDiverge.hpp"

ControlPoleEffectDiverge::ControlPoleEffectDiverge() : ControlPoleEffect() {}

uint8_t ControlPoleEffectDiverge::GetShiftsPerLoop() { return 4; }

uint8_t ControlPoleEffectDiverge::GetRotations() { return 1; }

void ControlPoleEffectDiverge::DoSetGrid(
    std::vector<std::vector<CHSV>>& grid_lights, uint8_t shiftIndex) {
  for (uint8_t lightIndex = 0; lightIndex < lightCount; lightIndex++) {
    grid_lights[lightIndex % 2 == 0 ? shiftIndex
                                    : (3 - shiftIndex)][lightIndex] =
        CHSV(currentHue + GetHueDistance(hueDistance, lightIndex, lightCount),
             baseSat, baseVal);
  }
}
