#include "ControlPoleEffect.hpp"

ControlPoleEffect::ControlPoleEffect(uint16_t framesPerLoop)
    : FRAMES_PER_LOOP(framesPerLoop) {
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

/**
 * frame = frame of loop
 */
void ControlPoleEffect::SetGrid(uint16_t frame, uint16_t lastFrame) {
  TurnOffAll();

  uint16_t framesPerShift = GetFramesPerShift();
  uint16_t shiftsPerLoop = GetAdjustedShiftsPerLoop();
  uint8_t shiftIndex = frame / framesPerShift;

  bool sameFrame = false;
  if (lastFrame / framesPerShift == shiftIndex) {
    sameFrame = true;
  }

  if (backAndForth && shiftIndex == 0 && lastFrame / framesPerShift != 0) {
    goBackwards = !goBackwards;
  }
  if (staticShiftIndex < shiftsPerLoop) {
    isStill = true;
    shiftIndex = staticShiftIndex;
  } else if (goBackwards) {
    shiftIndex = shiftsPerLoop - shiftIndex - (backAndForth ? 0 : 1);
  }

  if (smoothColor) {
    if (lastFrame > frame) {
      frame += FRAMES_PER_LOOP - lastFrame;
      lastFrame = 0;
    }
    currentHueShift += hueShift * (frame - lastFrame) / framesPerShift;
    hueShiftRemainder += (hueShift * (frame - lastFrame)) % framesPerShift;
    // Add to hueShift if there is enough remainder
    currentHueShift += hueShiftRemainder / framesPerShift;
    hueShiftRemainder %= framesPerShift;
  } else if (!sameFrame) {
    currentHueShift += hueShift;
  }

  currentHue = baseHue + currentHueShift;

  DoSetGrid(shiftIndex);
}

/**
 * shiftsPerLoop should divide framesPerLoop
 */
uint16_t ControlPoleEffect::GetFramesPerShift() {
  return FRAMES_PER_LOOP / GetAdjustedShiftsPerLoop();
}

void ControlPoleEffect::SetBaseHue(uint8_t hue) { baseHue = hue; }

void ControlPoleEffect::SetBaseSat(uint8_t sat) { baseSat = sat; }

void ControlPoleEffect::SetBaseVal(uint8_t val) { baseVal = val; }

void ControlPoleEffect::SetLightCount(uint8_t count) { lightCount = count; }

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

void ControlPoleEffect::SetReverse(bool reverse) {
  if (this->reverse != reverse) {
    goBackwards = !goBackwards;
  }
  this->reverse = reverse;
}

void ControlPoleEffect::SetRotation(uint8_t rotate) { rotation = rotate; }

uint8_t ControlPoleEffect::GetAdjustedShiftsPerLoop() {
  return GetShiftsPerLoop() - (backAndForth ? 1 : 0);
}

uint32_t ControlPoleEffect::GetTimerShiftOffset() { return timerShiftOffset; }

void ControlPoleEffect::ResetTimerShiftOffset() { timerShiftOffset = 0; }

void ControlPoleEffect::Reset() {
  currentHueShift = 0;
  hueShiftRemainder = 0;
  goBackwards = false;
  reverse = false;
}

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

void ControlPoleEffect::SetStaticShiftIndex(uint8_t index) {
  this->staticShiftIndex = index;
}
