#include "ControlPole.hpp"

#include <cstdio>

#include "ControlPoleEffectCircle.hpp"
#include "ControlPoleEffectCross.hpp"
#include "ControlPoleEffectDiverge.hpp"
#include "ControlPoleEffectLine.hpp"
#include "ControlPoleEffectTwinkle.hpp"

ControlPole::ControlPole(uint8_t index, uint16_t framesPerLoop) {
  this->index = index;
  effects[0] = new ControlPoleEffectCross(framesPerLoop);
  effects[1] = new ControlPoleEffectLine(framesPerLoop);
  effects[2] = new ControlPoleEffectCircle(framesPerLoop);
  effects[3] = new ControlPoleEffectDiverge(framesPerLoop);
  effects[4] = new ControlPoleEffectTwinkle(framesPerLoop);
  currentEffect = effects[1];
}

void ControlPole::SetHue(uint8_t hue) {
  for (ControlPoleEffect* effect : effects) {
    effect->SetBaseHue(hue);
  }
}

void ControlPole::SetSat(uint8_t sat) { currentEffect->SetBaseSat(sat); }

void ControlPole::SetVal(uint8_t val) { currentEffect->SetBaseVal(val); }

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
  } else {
    currentEffect = effects[4];
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

uint32_t ControlPole::GetTimerShiftOffset() {
  return currentEffect->GetTimerShiftOffset();
}

std::vector<std::vector<CHSV>> ControlPole::GetGrid(uint16_t frame,
                                                    uint16_t lastFrame) {
  for (ControlPoleEffect* effect : effects) {
    effect->PrepareFrame(frame, lastFrame);
  }
  currentEffect->SetGrid();

  return currentEffect->GetGrid();
}
