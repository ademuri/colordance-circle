#include "ControlPoleEffectTwinkle.hpp"

ControlPoleEffectTwinkle::ControlPoleEffectTwinkle(uint16_t framesPerLoop)
    : ControlPoleEffect(framesPerLoop) {}

uint8_t ControlPoleEffectTwinkle::GetShiftsPerLoop() { return 12; }

void ControlPoleEffectTwinkle::DoSetGrid(uint8_t shiftIndex) {
  grid_lights[GetBigSquare(shiftIndex)][GetBigSquare(12 - shiftIndex)] =
      CHSV(currentHue + GetHueDistance(hueDistance, 0, 4), baseSat, baseVal);
  grid_lights[GetLittleSquare(shiftIndex)][GetLittleSquare(12 - shiftIndex)] =
      CHSV(currentHue + GetHueDistance(hueDistance, 1, 4), baseSat, baseVal);
  grid_lights[GetLittleSquare(shiftIndex + 6)][GetLittleSquare(18 -
                                                               shiftIndex)] =
      CHSV(currentHue + GetHueDistance(hueDistance, 2, 4), baseSat, baseVal);
  grid_lights[GetBigSquare(shiftIndex + 6)][GetBigSquare(18 - shiftIndex)] =
      CHSV(currentHue + GetHueDistance(hueDistance, 3, 4), baseSat, baseVal);
}

uint8_t ControlPoleEffectTwinkle::GetBigSquare(uint8_t shiftIndex) {
  shiftIndex %= 12;
  return shiftIndex < 4
             ? shiftIndex
             : shiftIndex < 7 ? 3 : shiftIndex < 10 ? 9 - shiftIndex : 0;
}

uint8_t ControlPoleEffectTwinkle::GetLittleSquare(uint8_t shiftIndex) {
  shiftIndex %= 12;
  return shiftIndex < 2 ? 1 : shiftIndex < 8 ? 2 : 1;
}
