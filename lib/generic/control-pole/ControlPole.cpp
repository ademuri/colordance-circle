#include "ControlPole.hpp"

#include <cstdio>

#include "ControlPoleEffectCircle.hpp"
#include "ControlPoleEffectCross.hpp"
#include "ControlPoleEffectDiverge.hpp"
#include "ControlPoleEffectLine.hpp"
#include "ControlPoleEffectPinwheel.hpp"

ControlPole::ControlPole(uint16_t framesPerLoop)
    : FRAMES_PER_LOOP(framesPerLoop) {
  effects[0] = new ControlPoleEffectCross();
  effects[1] = new ControlPoleEffectLine();
  effects[2] = new ControlPoleEffectCircle();
  effects[3] = new ControlPoleEffectDiverge();
  effects[4] = new ControlPoleEffectPinwheel();
  currentEffect = effects[1];
}

void ControlPole::SetHue(uint8_t hue) { baseHue = hue; }

void ControlPole::SetSat(uint8_t sat) { currentEffect->SetBaseSat(sat); }

void ControlPole::SetVal(uint8_t val) {
  currentEffect->SetBaseVal(val);
  baseVal = val;
}

void ControlPole::SetMode(uint8_t mode) {
  if (mode == lastMode) {
    return;
  }
  currentEffect->ResetTimerShiftOffset();
  if (mode < 4) {
    currentEffect = effects[1];
    effects[1]->SetRotation(mode);
  } else if (mode < 6) {
    currentEffect = effects[0];
    effects[0]->SetRotation(mode - 4);
  } else if (mode < 10) {
    currentEffect = effects[2];
    effects[2]->SetRotation(mode - 6);
  } else if (mode < 11) {
    currentEffect = effects[3];
  } else if (mode < 12) {
    currentEffect = effects[4];
  } else {
    currentEffect = effects[5];
  }
  lastMode = mode;
}

void ControlPole::SetLightCount(uint8_t count) {
  currentEffect->SetLightCount(count);
}

void ControlPole::SetSpeed(uint8_t speed) { currentEffect->SetSpeed(speed); }

void ControlPole::SetHueShift(uint8_t shift) { hueShift = shift; }

void ControlPole::SetHueDistance(uint8_t distance) {
  currentEffect->SetHueDistance(distance);
}

void ControlPole::SetBackAndForth(bool backAndForth) {
  this->backAndForth = backAndForth;
}

void ControlPole::SetSmoothColor(bool smoothColor) {
  this->smoothColor = smoothColor;
}

void ControlPole::SetReverse(bool reverse) {
  if (reverse != this->reverse) {
    goBackwards = !goBackwards;
  }
  this->reverse = reverse;
}

void ControlPole::ResetFade() {
  fadeInFrames = 0;
  fadeOutFrames = 0;
  fadeOutFramesLeft = 0;
  fadeInFramesLeft = 0;
}

void ControlPole::FadeIn(uint16_t fadeFrames) {
  fadeInFrames = fadeFrames;
  fadeInFramesLeft = fadeInFrames;
}

void ControlPole::FadeOut(uint16_t fadeFrames) {
  fadeOutFrames = fadeFrames;
  fadeOutFramesLeft = fadeOutFrames;
}

uint32_t ControlPole::GetTimerShiftOffset() {
  return currentEffect->GetTimerShiftOffset();
}

std::vector<std::vector<CHSV>> ControlPole::GetGrid(uint16_t frame,
                                                    uint16_t lastFrame,
                                                    bool multiply) {
  uint16_t framesPerShift =
      currentEffect->GetFramesPerShift(FRAMES_PER_LOOP, backAndForth);
  uint8_t lastShiftIndex = lastFrame / framesPerShift;
  uint8_t shiftIndex = frame / framesPerShift;
  uint16_t framesSinceLast = frame > lastFrame
                                 ? frame - lastFrame
                                 : frame + FRAMES_PER_LOOP - lastFrame;

  uint8_t hue = baseHue + GetUpdatedHueShift(framesSinceLast);
  if (smoothColor || lastShiftIndex != shiftIndex) {
    currentEffect->SetHue(hue);
  }

  if (backAndForth && shiftIndex == 0 && lastShiftIndex != 0) {
    goBackwards = !goBackwards;
  }
  uint16_t shiftsPerLoop =
      currentEffect->GetAdjustedShiftsPerLoop(backAndForth);
  if (goBackwards) {
    shiftIndex = shiftsPerLoop - shiftIndex - (backAndForth ? 0 : 1);
  }

  fadeInFramesLeft -=
      framesSinceLast < fadeInFramesLeft ? framesSinceLast : fadeInFramesLeft;
  fadeOutFramesLeft -=
      framesSinceLast < fadeOutFramesLeft ? framesSinceLast : fadeOutFramesLeft;

  if (fadeInFramesLeft != 0) {
    currentEffect->SetBaseVal((uint16_t)255 *
                              (fadeInFrames - fadeInFramesLeft) / fadeInFrames);
  } else if (fadeOutFramesLeft != 0) {
    currentEffect->SetBaseVal((uint16_t)255 * fadeOutFramesLeft /
                              fadeOutFrames);
  } else if (fadeOutFrames != 0) {
    currentEffect->SetBaseVal(0);
  } else {
    currentEffect->SetBaseVal(baseVal);
  }

  currentEffect->SetGrid(shiftIndex, multiply);

  return currentEffect->GetGrid();
}

uint8_t ControlPole::GetUpdatedHueShift(uint16_t framesSinceLast) {
  uint16_t framesPerShift =
      currentEffect->GetFramesPerShift(FRAMES_PER_LOOP, backAndForth);
  currentHueShift += hueShift * framesSinceLast / framesPerShift;
  hueShiftRemainder += (hueShift * framesSinceLast) % framesPerShift;

  currentHueShift += hueShiftRemainder / framesPerShift;
  hueShiftRemainder %= framesPerShift;

  return currentHueShift;
}