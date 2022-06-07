#include "ControlPoleEffect.hpp"

ControlPoleEffect::ControlPoleEffect() {
  for (int x = 0; x < kGridWidth; x++) {
    std::vector<CHSV> row;
    for (int y = 0; y < kGridHeight; y++) {
      row.push_back({0, 0, 0});
    }
    grid_lights.push_back(std::move(row));
  }
}

void ControlPoleEffect::TurnOffAll() {
  for (int x = 0; x < kGridWidth; x++) {
    for (int y = 0; y < kGridHeight; y++) {
      grid_lights[x][y].val = 0;
    }
  }
}

void ControlPoleEffect::SetGrid(uint8_t shiftIndex, bool multiply) {
  if (!multiply) {
    TurnOffAll();
  }
  DoSetGrid(shiftIndex);
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

CHSV ControlPoleEffect::GetLight(uint8_t x, uint8_t y) {
  return grid_lights[x][y];
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
