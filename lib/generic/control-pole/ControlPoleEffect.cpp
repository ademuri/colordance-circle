#include "ControlPoleEffect.hpp"

ControlPoleEffect::ControlPoleEffect() {}

void ControlPoleEffect::SetGrid(Grid<CHSV>& grid_lights,
                                uint8_t shiftIndex) {
  DoSetGrid(grid_lights, shiftIndex);
}

/**
 * shiftsPerLoop should divide framesPerLoop
 */
uint16_t ControlPoleEffect::GetFramesPerShift(uint16_t framesPerLoop,
                                              bool backAndForth) {
  return framesPerLoop / GetAdjustedShiftsPerLoop(backAndForth);
}

void ControlPoleEffect::SetHue(uint8_t hue) { currentHue = hue; }

void ControlPoleEffect::SetBaseSat(uint8_t sat) { baseSat = sat; }

void ControlPoleEffect::SetBaseVal(uint8_t val) { baseVal = val; }

void ControlPoleEffect::SetLightCount(uint8_t count) { lightCount = count; }

void ControlPoleEffect::SetSpeed(uint8_t speed) { this->speed = speed; }

void ControlPoleEffect::SetHueDistance(uint8_t distance) {
  hueDistance = distance;
}

void ControlPoleEffect::SetRotation(uint8_t rotate) { rotation = rotate; }

uint8_t ControlPoleEffect::GetAdjustedShiftsPerLoop(bool backAndForth) {
  return GetShiftsPerLoop() - (backAndForth ? 1 : 0);
}

uint8_t ControlPoleEffect::AdjustedBrightness(uint8_t baseVal, uint8_t lightsOn,
                                              uint8_t minLights) {
  switch (lightsOn - minLights) {
    case 0:
      return baseVal;
    case 1:
      return baseVal * .75;
    case 2:
      return baseVal * .64;
    case 3:
      return baseVal * .58;
  }
  return baseVal;
}

uint8_t ControlPoleEffect::GetHueDistance(uint8_t hueDistance,
                                          uint8_t lightIndex,
                                          uint8_t lightsOn) {
  if (lightIndex >= lightsOn) {
    return 0;  // For convinence
  }
  if (lightsOn % 2 == 0) {
    return (hueDistance / 2) * ((lightIndex - (lightsOn / 2)) * 2 + 1);
  } else {
    return hueDistance * (lightIndex - (lightsOn / 2));
  }
}
