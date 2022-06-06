#include "HelperPole.hpp"

#include <cstdio>

HelperPole::HelperPole(uint16_t framesPerLoop)
    : FRAMES_PER_LOOP(framesPerLoop) {
  for (int x = 0; x < Pole::kGridWidth; x++) {
    std::vector<CHSV> row;
    for (int y = 0; y < Pole::kGridHeight; y++) {
      row.push_back({0, 0, 0});
    }
    grid_lights.push_back(row);
  }
}

void HelperPole::SetHue(uint8_t hue) { baseHue = hue; }

void HelperPole::SetSat(uint8_t sat) { baseSat = sat; }

void HelperPole::SetVal(uint8_t val) { baseVal = val; }

// void HelperPole::SetMode(uint8_t mode) {
//   if (mode == lastMode) {
//     return;
//   }
// }

void HelperPole::SetLightCount(uint8_t count) { lightCount = count; }

void HelperPole::SetHueShift(uint8_t shift) { hueShift = shift; }

void HelperPole::SetHueDistance(uint8_t distance) { hueDistance = distance; }

void HelperPole::SetBackAndForth(bool backAndForth) {
  this->backAndForth = backAndForth;
}

void HelperPole::SetSmoothColor(bool smoothColor) {
  this->smoothColor = smoothColor;
}

void HelperPole::SetReverse(bool reverse) {
  if (reverse != this->reverse) {
    goBackwards = !goBackwards;
  }
  this->reverse = reverse;
}

void HelperPole::ResetFade() {
  fadeInFrames = 0;
  fadeOutFrames = 0;
  fadeOutFramesLeft = 0;
  fadeInFramesLeft = 0;
}

void HelperPole::FadeIn(uint16_t fadeFrames) {
  fadeInFrames = fadeFrames;
  fadeInFramesLeft = fadeInFrames;
}

void HelperPole::FadeOut(uint16_t fadeFrames) {
  fadeOutFrames = fadeFrames;
  fadeOutFramesLeft = fadeOutFrames;
}

void HelperPole::SetGrid(uint8_t shiftIndex, bool multiply) {
  if (!multiply) {
    TurnOffAll();
  }
  SetStaticSmallSquare(shiftIndex);
}

/** ANIMATIONS **/
void HelperPole::SetStaticSmallSquare(uint8_t shiftIndex) {
  grid_lights[1][1] = CHSV(currentHue + GetHueDistance(hueDistance, 0, 4),
                           currentSat, currentVal);
  grid_lights[1][2] = CHSV(currentHue + GetHueDistance(hueDistance, 2, 4),
                           currentSat, currentVal);
  grid_lights[2][1] = CHSV(currentHue + GetHueDistance(hueDistance, 3, 4),
                           currentSat, currentVal);
  grid_lights[2][2] = CHSV(currentHue + GetHueDistance(hueDistance, 1, 4),
                           currentSat, currentVal);
}

void HelperPole::TurnOffAll() {
  for (int x = 0; x < Pole::kGridWidth; x++) {
    for (int y = 0; y < Pole::kGridHeight; y++) {
      grid_lights[x][y].val = 0;
    }
  }
}

std::vector<std::vector<CHSV>> HelperPole::GetGrid(uint16_t frame,
                                                   uint16_t lastFrame,
                                                   bool multiply) {
  return grid_lights;
  uint16_t framesPerShift = 4;
  //    currentEffect->GetFramesPerShift(FRAMES_PER_LOOP, backAndForth);
  uint8_t lastShiftIndex = lastFrame / framesPerShift;
  uint8_t shiftIndex = frame / framesPerShift;
  uint16_t framesSinceLast = frame > lastFrame
                                 ? frame - lastFrame
                                 : frame + FRAMES_PER_LOOP - lastFrame;

  uint8_t hue = baseHue + GetUpdatedHueShift(framesSinceLast);
  if (smoothColor || lastShiftIndex != shiftIndex) {
    currentHue = hue;
  }

  if (backAndForth && shiftIndex == 0 && lastShiftIndex != 0) {
    goBackwards = !goBackwards;
  }
  uint16_t shiftsPerLoop = GetAdjustedShiftsPerLoop(backAndForth);
  if (goBackwards) {
    shiftIndex = shiftsPerLoop - shiftIndex - (backAndForth ? 0 : 1);
  }

  fadeInFramesLeft -=
      framesSinceLast < fadeInFramesLeft ? framesSinceLast : fadeInFramesLeft;
  fadeOutFramesLeft -=
      framesSinceLast < fadeOutFramesLeft ? framesSinceLast : fadeOutFramesLeft;

  if (fadeInFramesLeft != 0) {
    currentVal =
        (uint16_t)255 * (fadeInFrames - fadeInFramesLeft) / fadeInFrames;
  } else if (fadeOutFramesLeft != 0) {
    currentVal = (uint16_t)255 * fadeOutFramesLeft / fadeOutFrames;
  } else if (fadeOutFrames != 0) {
    currentVal = 0;
  } else {
    currentVal = baseVal;
  }

  SetGrid(shiftIndex, multiply);

  return grid_lights;
}

uint16_t HelperPole::GetFramesPerShift(uint16_t framesPerLoop,
                                       bool backAndForth) {
  return framesPerLoop / GetAdjustedShiftsPerLoop(backAndForth);
}

uint8_t HelperPole::GetAdjustedShiftsPerLoop(bool backAndForth) {
  // return GetShiftsPerLoop() - (backAndForth ? 1 : 0);
  return 4 - (backAndForth ? 1 : 0);
}

uint8_t HelperPole::GetUpdatedHueShift(uint16_t framesSinceLast) {
  uint16_t framesPerShift = GetFramesPerShift(FRAMES_PER_LOOP, backAndForth);
  currentHueShift += hueShift * framesSinceLast / framesPerShift;
  hueShiftRemainder += (hueShift * framesSinceLast) % framesPerShift;

  currentHueShift += hueShiftRemainder / framesPerShift;
  hueShiftRemainder %= framesPerShift;

  return currentHueShift;
}

uint8_t HelperPole::AdjustedBrightness(uint8_t baseVal, uint8_t lightsOn,
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

uint8_t HelperPole::GetHueDistance(uint8_t hueDistance, uint8_t lightIndex,
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

void HelperPole::Reset() {
  TurnOffAll();
  ResetFade();
}