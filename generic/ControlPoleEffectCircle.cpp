#include "ControlPoleEffectCircle.hpp"

ControlPoleEffectCircle::ControlPoleEffectCircle(uint16_t framesPerLoop)
    : ControlPoleEffect(framesPerLoop) {}

uint8_t ControlPoleEffectCircle::GetShiftsPerLoop() { return 8; }

void ControlPoleEffectCircle::DoSetGrid(uint8_t shiftIndex) {
  uint8_t rotationOffset = rotation + 1;
  uint8_t offsetFix1 = 0;
  uint8_t offsetFix2 = 0;
  if (lightCount > 2 && rotation == 3) {
    offsetFix1 = lightCount == 4 ? -1 : 0;
    offsetFix2 = -1;
  }
  switch (lightCount) {
    case (4):
      grid_lights[GetIndex(shiftIndex + 3 * rotationOffset + 2)]
                 [GetIndex(shiftIndex + 3 * rotationOffset)] = CHSV(
                     currentHue + GetHueDistance(hueDistance, 3, lightCount),
                     baseSat, baseVal);
    case (3):
      grid_lights[GetIndex(shiftIndex + 2 * rotationOffset + 2 + offsetFix2)]
                 [GetIndex(shiftIndex + 2 * rotationOffset + offsetFix2)] =
                     CHSV(currentHue +
                              GetHueDistance(hueDistance, 2, lightCount),
                          baseSat, baseVal);
    case (2):
      grid_lights[GetIndex(shiftIndex + rotationOffset + 2 + offsetFix1)]
                 [GetIndex(shiftIndex + rotationOffset + offsetFix1)] = CHSV(
                     currentHue + GetHueDistance(hueDistance, 1, lightCount),
                     baseSat, baseVal);
    case (1):
      grid_lights[GetIndex(shiftIndex + 2)][GetIndex(shiftIndex)] =
          CHSV(currentHue + GetHueDistance(hueDistance, 0, lightCount), baseSat,
               baseVal);
  }
}

uint8_t ControlPoleEffectCircle::GetIndex(uint8_t shiftIndex) {
  shiftIndex %= 8;
  return shiftIndex < 4 ? shiftIndex : 7 - shiftIndex;
}
