#include "ControlPoleEffectSquare.hpp"

ControlPoleEffectSquare::ControlPoleEffectSquare(uint16_t framesPerLoop)
    : ControlPoleEffect(framesPerLoop) {}

uint8_t ControlPoleEffectSquare::GetShiftsPerLoop() { return 4; }

void ControlPoleEffectSquare::DoSetGrid(uint8_t shiftIndex) {
  uint8_t small = 1;
  uint8_t big = 2;
  if (rotation == 1) {
    small = 0;
    big = 3;
  }
  switch (lightCount) {
    case (4):
      grid_lights[small][big] =
          CHSV(currentHue + GetHueDistance(hueDistance, 3, lightCount), baseSat,
               baseVal);
    case (3):
      grid_lights[big][big] =
          CHSV(currentHue + GetHueDistance(hueDistance, 2, lightCount), baseSat,
               baseVal);
    case (2):
      grid_lights[big][small] =
          CHSV(currentHue + GetHueDistance(hueDistance, 1, lightCount), baseSat,
               baseVal);
    case (1):
      grid_lights[small][small] =
          CHSV(currentHue + GetHueDistance(hueDistance, 0, lightCount), baseSat,
               baseVal);
  }
}
