#include "ControlPole.hpp"

#include <stdexcept>

#include "ControlPoleEffectCircle.hpp"
#include "ControlPoleEffectCross.hpp"
#include "ControlPoleEffectDiverge.hpp"
#include "ControlPoleEffectLine.hpp"
#include "ControlPoleEffectPinwheel.hpp"
#include "Pole.hpp"

ControlPole::ControlPole(uint16_t framesPerLoop)
    : currentEffect(std::addressof(effectLine)),
      FRAMES_PER_LOOP(framesPerLoop) {
  mode = Mode::kLine;
  lastMode = Mode::kLine;
  speed = Speed::kDefault;

  for (int x = 0; x < Pole::kGridWidth; x++) {
    std::vector<CHSV> row;
    for (int y = 0; y < Pole::kGridHeight; y++) {
      row.push_back({0, 0, 0});
    }
    grid_lights.push_back(row);
  }
}

void ControlPole::SetHue(uint8_t hue) { baseHue = hue; }

void ControlPole::SetSat(uint8_t sat) { currentEffect->SetBaseSat(sat); }

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
  lastMode = mode;
}

void ControlPole::SetRotation(uint8_t rotation) {
  currentEffect->SetRotation(rotation % currentEffect->GetRotations());
}

void ControlPole::SetShiftSpeed(Speed speed) { this->speed = speed; }

void ControlPole::SetLightCount(uint8_t count) {
  currentEffect->SetLightCount(count);
}

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

std::vector<std::vector<CHSV>> const& ControlPole::GetGrid(uint16_t frame,
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

  if (speed == Speed::kStill) {
    shiftIndex = lastEffectiveShiftIndex;
  } 

  // else if (speed == Speed::kHalf) {
  //   if (shiftIndex == 0 && lastShiftIndex == shiftsPerLoop - 1) {
  //     didFirstHalf = !didFirstHalf;
  //   }
  //   shiftsPerLoop = shiftsPerLoop/2;
  //   shiftIndex = shiftIndex/2 + (didFirstHalf ? shiftsPerLoop : 0) * (goBackwards ? -1 : 1);

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

  currentEffect->SetGrid(grid_lights, shiftIndex);

  return grid_lights;
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

void ControlPole::TurnOffAll() {
  for (int x = 0; x < Pole::kGridWidth; x++) {
    for (int y = 0; y < Pole::kGridHeight; y++) {
      grid_lights[x][y].val = 0;
    }
  }
}
