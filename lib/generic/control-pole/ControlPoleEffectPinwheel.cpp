#include "ControlPoleEffectPinwheel.hpp"

ControlPoleEffectPinwheel::ControlPoleEffectPinwheel() : ControlPoleEffect() {}

uint8_t ControlPoleEffectPinwheel::GetShiftsPerLoop() { return 12; }

uint8_t ControlPoleEffectPinwheel::GetRotations() { return 1; }

void ControlPoleEffectPinwheel::DoSetGrid(
    Grid<CHSV>& grid_lights, uint8_t shiftIndex) {
  grid_lights[GetBigSquare(shiftIndex)][GetBigSquare(12 - shiftIndex)] =
      CHSV(currentHue + GetHueDistance(hueDistance, 0, 4), baseSat, baseVal);
  grid_lights[GetLittleSquare(shiftIndex)][GetLittleSquare(12 - shiftIndex)] =
      CHSV(currentHue + GetHueDistance(hueDistance, 1, 4), baseSat, baseVal);
  grid_lights[GetLittleSquare(shiftIndex + 6)][GetLittleSquare(18 -
                                                               shiftIndex)] =
      CHSV(currentHue + GetHueDistance(hueDistance, 2, 4), baseSat, baseVal);
  grid_lights[GetBigSquare(shiftIndex + 6)][GetBigSquare(18 - shiftIndex)] =
      CHSV(currentHue + GetHueDistance(hueDistance, 3, 4), baseSat, baseVal);

  if (lightCount == 2) {
    shiftIndex = (shiftIndex + 3) % 12;
    grid_lights[GetBigSquare(shiftIndex)][GetBigSquare(12 - shiftIndex)] = CHSV(
        currentHue + GetHueDistance(hueDistance, 0, 4) + 128, baseSat, baseVal);
    grid_lights[GetLittleSquare(shiftIndex)][GetLittleSquare(12 - shiftIndex)] =
        CHSV(currentHue + GetHueDistance(hueDistance, 1, 4) + 128, baseSat,
             baseVal);
    grid_lights[GetLittleSquare(shiftIndex + 6)]
               [GetLittleSquare(18 - shiftIndex)] =
                   CHSV(currentHue + GetHueDistance(hueDistance, 2, 4) + 128,
                        baseSat, baseVal);
    grid_lights[GetBigSquare(shiftIndex + 6)][GetBigSquare(18 - shiftIndex)] =
        CHSV(currentHue + GetHueDistance(hueDistance, 3, 4) + 128, baseSat,
             baseVal);
  }
}

uint8_t ControlPoleEffectPinwheel::GetBigSquare(uint8_t shiftIndex) {
  shiftIndex %= 12;
  return (shiftIndex < 4
              ? shiftIndex
              : shiftIndex < 7 ? 3 : shiftIndex < 10 ? 9 - shiftIndex : 0) %
         4;
}

uint8_t ControlPoleEffectPinwheel::GetLittleSquare(uint8_t shiftIndex) {
  shiftIndex %= 12;
  return (shiftIndex < 2 ? 1 : shiftIndex < 8 ? 2 : 1) % 4;
}
