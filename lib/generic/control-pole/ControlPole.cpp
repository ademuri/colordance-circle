#include "ControlPole.hpp"

#include "ControlPoleEffectCircle.hpp"
#include "ControlPoleEffectCross.hpp"
#include "ControlPoleEffectDiverge.hpp"
#include "ControlPoleEffectLine.hpp"
#include "ControlPoleEffectPinwheel.hpp"
#include "Pole.hpp"

ControlPole::ControlPole(uint16_t framesPerLoop)
    : framesPerLoop(framesPerLoop) {
  for (auto& row : grid_lights) {
    for (auto& value : row) {
      value = CHSV{0, 0, 0};
    }
  }
}

void ControlPole::SetHue(uint8_t hue) { baseHue = hue; }

void ControlPole::IncrementHue(uint8_t hue) { baseHue += hue; }

void ControlPole::SetSat(uint8_t sat) {
  currentEffect->SetBaseSat(sat);
  baseSat = sat;
}

void ControlPole::SetVal(uint8_t val) {
  currentEffect->SetBaseVal(val);
  baseVal = val;
}

void ControlPole::SetMode(Mode mode) {
  if (mode == lastMode) {
    return;
  }
  switch (mode) {
    case Mode::kCircle:
      currentEffect = std::addressof(effectCircle);
      break;
    case Mode::kCorners:
      currentEffect = std::addressof(effectCorners);
      break;
    case Mode::kCross:
      currentEffect = std::addressof(effectCross);
      break;
    case Mode::kDiverge:
      currentEffect = std::addressof(effectDiverge);
      break;
    case Mode::kLine:
      currentEffect = std::addressof(effectLine);
      break;
    case Mode::kPinwheel:
      currentEffect = std::addressof(effectPinwheel);
      break;
    case Mode::kSmallSquare:
      currentEffect = std::addressof(effectSmallSquare);
      break;
    default:
      currentEffect = std::addressof(effectLine);
  }
  currentEffect->SetLightCount(lightCount);
  currentEffect->SetHueDistance(hueDistance);
  currentEffect->SetBaseSat(baseSat);
  currentEffect->SetBaseVal(baseVal);
  lastMode = mode;
}

void ControlPole::SetRotation(uint8_t rotation) {
  currentEffect->SetRotation(rotation % currentEffect->GetRotations());
}

void ControlPole::SetShiftSpeed(Speed speed) { this->speed = speed; }

void ControlPole::SetShiftOffset(uint8_t offset) { shiftOffset = offset; }

void ControlPole::SetLightCount(uint8_t count) {
  currentEffect->SetLightCount(count);
  lightCount = count;
}

void ControlPole::SetHueShift(uint8_t shift) { hueShift = shift; }

void ControlPole::SetHueDistance(uint8_t distance) {
  currentEffect->SetHueDistance(distance);
  hueDistance = distance;
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

void ControlPole::SetGridFade(uint8_t fadeFrames) {
  gridFadeFrames = fadeFrames;
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

uint8_t ControlPole::GetHue() { return actualHue; }

uint8_t ControlPole::GetHueDistance() { return hueDistance; }

CHSV ControlPole::GetHSV() { return CHSV(hue, baseSat, baseVal); }

uint8_t ControlPole::GetShiftsPerLoop() {
  return currentEffect->GetAdjustedShiftsPerLoop(backAndForth);
}

uint8_t ControlPole::GetLastShiftIndex() { return lastShiftIndex; }

uint8_t ControlPole::UpdateGrid(uint16_t frame, uint16_t lastFrame,
                                bool multiply) {
  uint16_t const framesPerShift =
      currentEffect->GetFramesPerShift(framesPerLoop, backAndForth);
  uint16_t const framesSinceLast =
      frame > lastFrame ? frame - lastFrame : frame + framesPerLoop - lastFrame;

  uint16_t const shiftsPerLoop =
      currentEffect->GetAdjustedShiftsPerLoop(backAndForth);
  uint8_t const lastShiftIndex = lastFrame / framesPerShift;
  uint8_t shiftIndex = frame / framesPerShift;

  hue = baseHue + GetUpdatedHueShift(framesSinceLast);
  if (smoothColor || lastFrame > frame) {
    currentEffect->SetHue(hue);
    actualHue = hue;
  }

  if (backAndForth && shiftIndex == 0 && lastShiftIndex != 0) {
    goBackwards = !goBackwards;
  }
  if (goBackwards) {
    shiftIndex = shiftsPerLoop - shiftIndex - (backAndForth ? 0 : 1);
  }

  if (speed == Speed::kStill) {
    shiftIndex = lastEffectiveShiftIndex;
  }

  // else if (speed == Speed::kHalf && shiftsPerLoop % 2 == 0) {
  //   if (shiftIndex == 0 && lastShiftIndex != 0) {
  //     didFirstHalf = !didFirstHalf;
  //   }
  //   shiftIndex = shiftIndex/2 + (didFirstHalf ? shiftsPerLoop/2 : 0);
  //   if (goBackwards) {}
  // }

  // } else if (speed == Speed::kDouble) {
  //   shiftsPerLoop *= 2;
  //   shiftIndex*=2;
  //   if ((frame % shiftsPerLoop) > framesPerShift/2)  {
  //     shiftIndex++;
  //   }
  //   shiftIndex %= shiftsPerLoop;
  // }

  if (!multiply) {
    TurnOffAll();
  }

  lastEffectiveShiftIndex = shiftIndex;

  fadeInFramesLeft -=
      framesSinceLast < fadeInFramesLeft ? framesSinceLast : fadeInFramesLeft;
  fadeOutFramesLeft -=
      framesSinceLast < fadeOutFramesLeft ? framesSinceLast : fadeOutFramesLeft;
  uint8_t val = fadeInFramesLeft != 0
                    ? 255 * (fadeInFrames - fadeInFramesLeft) / fadeInFrames
                : fadeOutFramesLeft != 0
                    ? 255 * fadeOutFramesLeft / fadeOutFrames
                : fadeOutFrames != 0 ? 0
                                     : baseVal;
  currentEffect->SetBaseVal(val);

  // uint16_t framesSinceLastShift = frame % framesPerShift;
  // if (framesSinceLastShift < gridFadeFrames) {
  //   currentEffect->SetBaseVal(val -
  //                             val * framesSinceLastShift / gridFadeFrames);
  //   currentEffect->SetGrid(grid_lights,
  //                          (shiftsPerLoop - 1 + shiftIndex) % shiftsPerLoop);
  //   currentEffect->SetBaseVal(val * framesSinceLastShift / gridFadeFrames);
  // }

  if (speed == Speed::kOffset) {
    shiftIndex = shiftOffset % shiftsPerLoop;
  }

  currentEffect->SetGrid(grid_lights, shiftIndex);

  return shiftIndex;
}

Grid<CHSV> const& ControlPole::GetGrid() { return grid_lights; }

uint8_t ControlPole::GetUpdatedHueShift(uint16_t framesSinceLast) {
  uint16_t framesPerShift =
      currentEffect->GetFramesPerShift(framesPerLoop, backAndForth);
  currentHueShift += hueShift * framesSinceLast / framesPerShift;
  hueShiftRemainder += (hueShift * framesSinceLast) % framesPerShift;

  currentHueShift += hueShiftRemainder / framesPerShift;
  hueShiftRemainder %= framesPerShift;

  return currentHueShift;
}

void ControlPole::TurnOffAll() {
  for (auto& row : grid_lights) {
    for (auto& element : row) {
      element.val = 0;
    }
  }
}
