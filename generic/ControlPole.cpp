#include "ControlPole.hpp"

#include <cstdio>

#include "ControlPoleEffectCircle.hpp"
#include "ControlPoleEffectCross.hpp"
#include "ControlPoleEffectDiverge.hpp"
#include "ControlPoleEffectLine.hpp"
#include "ControlPoleEffectSquare.hpp"
#include "ControlPoleEffectTwinkle.hpp"

ControlPole::ControlPole(uint8_t index, uint16_t framesPerLoop) {
  this->index = index;
  effectSquare = new ControlPoleEffectSquare(framesPerLoop);
  effectCross = new ControlPoleEffectCross(framesPerLoop);
  effectLine = new ControlPoleEffectLine(framesPerLoop);
  effectCircle = new ControlPoleEffectCircle(framesPerLoop);
  effectDiverge = new ControlPoleEffectDiverge(framesPerLoop);
  effectPinwheel = new ControlPoleEffectTwinkle(framesPerLoop);
  currentEffect = effectSquare;
}

void ControlPole::SetHue(uint8_t hue) { currentEffect->SetBaseHue(hue); }

void ControlPole::SetSat(uint8_t sat) { currentEffect->SetBaseSat(sat); }

void ControlPole::SetVal(uint8_t val) { currentEffect->SetBaseVal(val); }

void ControlPole::SetMode(uint8_t mode) {
  if (mode == lastMode) {
    return;
  }
  currentEffect->ResetTimerShiftOffset();
  if (mode < 2) {
    currentEffect = effectSquare;  // 0-1
    effectSquare->SetRotation(mode);
  } else if (mode < 6) {
    currentEffect = effectLine;  // 2-5
    effectLine->SetRotation(mode - 2);
  } else if (mode < 10) {
    currentEffect = effectCircle;  // 6-9
    effectCircle->SetRotation(mode - 6);
  } else if (mode < 11) {
    currentEffect = effectPinwheel;  // 10
  } else if (mode < 13) {
    currentEffect = effectCross;  // 11-12
    effectCross->SetRotation(mode - 11);
  } else {
    currentEffect = effectDiverge;  // 13
  }
  lastMode = mode;
}

void ControlPole::SetLightCount(uint8_t count) {
  currentEffect->SetLightCount(count);
}

void ControlPole::SetHueShift(uint8_t shift) {
  currentEffect->SetHueShift(shift);
}

void ControlPole::SetHueDistance(uint8_t distance) {
  currentEffect->SetHueDistance(distance);
}

void ControlPole::SetBackAndForth(bool backAndForth) {
  currentEffect->SetBackAndForth(backAndForth);
}

void ControlPole::SetSmoothColor(bool smoothColor) {
  currentEffect->SetSmoothColor(smoothColor);
}

void ControlPole::SetReverse(bool reverse) {
  currentEffect->SetReverse(reverse);
}

void ControlPole::SetStaticShiftIndex(uint8_t index) {
  currentEffect->SetStaticShiftIndex(index);
}

void ControlPole::Reset() { currentEffect->Reset(); }

uint32_t ControlPole::GetTimerShiftOffset() {
  return currentEffect->GetTimerShiftOffset();
}

std::vector<std::vector<CHSV>> ControlPole::GetGrid(uint16_t frame,
                                                    uint16_t lastFrame) {
  currentEffect->SetGrid(frame, lastFrame);
  return currentEffect->GetGrid();
}
