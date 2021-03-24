#include "ControlPole.hpp"

#include <cstdio>

#include "ControlPoleEffectCircle.hpp"
#include "ControlPoleEffectCross.hpp"
#include "ControlPoleEffectLine.hpp"

ControlPole::ControlPole(uint8_t index) {
  this->index = index;
  effectCross = new ControlPoleEffectCross();
  effectLine = new ControlPoleEffectLine();
  effectCircle = new ControlPoleEffectCircle();
  currentEffect = effectLine;
}

void ControlPole::SetHue(uint8_t hue) { currentEffect->SetBaseHue(hue); }

void ControlPole::SetSat(uint8_t sat) { currentEffect->SetBaseSat(sat); }

void ControlPole::SetVal(uint8_t val) { currentEffect->SetBaseVal(val); }

void ControlPole::SetMode(uint8_t mode) {
  if (mode == lastMode) {
    return;
  }
  currentEffect->ResetTimerShiftOffset();
  if (mode < 4) {
    currentEffect = effectLine;
    effectLine->SetRotation(mode);
  } else if (mode < 6) {
    currentEffect = effectCross;
    effectCross->SetRotation(mode - 4);
  } else if (mode < 10) {
    currentEffect = effectCircle;
    effectCircle->SetRotation(mode - 6);
  }
  lastMode = mode;
}

void ControlPole::SetLightCount(uint8_t count) {
  currentEffect->SetLightCount(count);
}

void ControlPole::SetSpeed(uint8_t speed) { currentEffect->SetSpeed(speed); }

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

uint32_t ControlPole::GetMillisPerShift() {
  return currentEffect->GetMillisPerShift();
}

uint32_t ControlPole::GetMillisPerLoop() {
  return currentEffect->GetMillisPerLoop();
}

uint32_t ControlPole::GetPartialMillisPerLoop() {
  return currentEffect->GetPartialMillisPerLoop();
}

uint32_t ControlPole::GetTimerShiftOffset() {
  return currentEffect->GetTimerShiftOffset();
}

std::vector<std::vector<CHSV>> ControlPole::GetGrid(uint32_t timer,
                                                    uint16_t timeElapsed) {
  currentEffect->SetGrid(timer, timeElapsed);
  return currentEffect->GetGrid();
}
