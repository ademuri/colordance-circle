#include "ControlPoleEffect.hpp"

ControlPoleEffect::ControlPoleEffect() {
  for (int x = 0; x < kGridWidth; x++) {
    std::vector<CHSV> row;
    for (int y = 0; y < kGridHeight; y++) {
      row.push_back({0, 0, 0});
    }
    grid_lights.push_back(row);
  }
}

void ControlPoleEffect::TurnOffAll() {
  for (int x = 0; x < kGridWidth; x++) {
    for (int y = 0; y < kGridHeight; y++) {
      grid_lights[x][y].val = 0;
    }
  }
}

void ControlPoleEffect::SetGrid(uint32_t timer, uint16_t timeElapsedelapsed) {
  uint16_t millisPerShift = GetMillisPerShift();
  uint8_t shiftIndex = GetShiftIndexAndSetOffset(timer + timerShiftOffset);

  uint16_t adjustedMillisPerShift =
      millisPerShift == 0 ? GetSpeedConstant() : millisPerShift;
  if (!smoothColor && shiftIndex == lastShiftIndex) {
    return;
  } else if (!smoothColor) {
    currentHueShift += (hueShift + hueOffset);
  } else {
    currentHueShift = (hueShift + hueOffset) * timer / adjustedMillisPerShift;
  }

  lastHueShift = currentHueShift;
  currentHue = baseHue + currentHueShift;

  TurnOffAll();
  DoSetGrid(AdjustShiftIndex(shiftIndex));
  lastShiftIndex = shiftIndex;
}

void ControlPoleEffect::SetBaseHue(uint8_t hue) {
  // currentHue += hue - baseHue;
  if (baseHue != hue) {
    currentHue = hue;
  }
  baseHue = hue;
}

void ControlPoleEffect::SetBaseSat(uint8_t sat) { baseSat = sat; }

void ControlPoleEffect::SetBaseVal(uint8_t val) { baseVal = val; }

void ControlPoleEffect::SetLightCount(uint8_t count) { lightCount = count; }

void ControlPoleEffect::SetSpeed(uint8_t speed) { this->speed = speed; }

void ControlPoleEffect::SetHueShift(uint8_t shift) { hueShift = shift; }

void ControlPoleEffect::SetHueDistance(uint8_t distance) {
  hueDistance = distance;
}

void ControlPoleEffect::SetBackAndForth(bool backAndForth) {
  this->backAndForth = backAndForth;
}

void ControlPoleEffect::SetSmoothColor(bool smoothColor) {
  this->smoothColor = smoothColor;
}

void ControlPoleEffect::SetReverse(bool reverse) { this->reverse = reverse; }

void ControlPoleEffect::SetRotation(uint8_t rotate) { rotation = rotate; }

uint16_t ControlPoleEffect::GetMillisPerShift() {
  return speed == 0 ? 0 : GetSpeedConstant() / speed;
}

uint16_t ControlPoleEffect::GetMillisPerLoop() {
  return GetMillisPerShift() * GetShiftsPerLoop();
}

uint16_t ControlPoleEffect::GetPartialMillisPerLoop() {
  return GetMillisPerShift() * 2;
}

uint8_t ControlPoleEffect::GetShiftIndexAndSetOffset(uint32_t timer) {
  uint16_t millisPerShift = GetMillisPerShift();
  uint8_t shiftsPerLoop = GetShiftsPerLoop();

  uint16_t adjustedMillisPerShift =
      millisPerShift == 0 ? GetSpeedConstant() : millisPerShift;
  uint8_t shiftIndex = (timer % (adjustedMillisPerShift * shiftsPerLoop)) /
                       adjustedMillisPerShift;
  if (reverse) {
    shiftIndex = shiftsPerLoop - shiftIndex - 1;
  }

  if (shiftsPerLoop != lastShiftsPerLoop) {
    timerShiftOffset = 0;
  } else if (millisPerShift != 0 &&
             (millisPerShift != lastMillisPerShift || lastReverse != reverse)) {
    uint8_t indexDifference = shiftsPerLoop + lastShiftIndex - shiftIndex;
    timerShiftOffset += millisPerShift * (indexDifference % shiftsPerLoop);
    shiftIndex = lastShiftIndex;
  }
  lastShiftsPerLoop = shiftsPerLoop;
  lastMillisPerShift = millisPerShift;
  lastReverse = reverse;

  return shiftIndex;
}

uint8_t ControlPoleEffect::AdjustShiftIndex(uint8_t shiftIndex) {
  uint16_t millisPerShift = GetMillisPerShift();
  uint8_t shiftsPerLoop = GetShiftsPerLoop();
  if (millisPerShift == 0) {
    return 0;
  }
  if (backAndForth && shiftIndex > shiftsPerLoop / 2) {
    return shiftsPerLoop - shiftIndex;
  }
  return shiftIndex;
}

uint32_t ControlPoleEffect::GetTimerShiftOffset() { return timerShiftOffset; }

void ControlPoleEffect::ResetTimerShiftOffset() { timerShiftOffset = 0; }

CHSV ControlPoleEffect::GetLight(uint8_t x, uint8_t y) {
  return grid_lights[x][y];
}

std::vector<std::vector<CHSV>> ControlPoleEffect::GetGrid() {
  return grid_lights;
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
