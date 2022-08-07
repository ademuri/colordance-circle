#include "BackAndForth.hpp"

#include "ColordanceTypes.hpp"

BackAndForth::BackAndForth()
    : InterfaceEffect(),
      controlPoleLeft(FRAMES_PER_LOOP),
      controlPoleRight(FRAMES_PER_LOOP) {
  controlPoleLeft.SetHue(0);
  controlPoleRight.SetHue(127);
  controlPoleLeft.SetReverse(true);
  ResetEffect();
}

bool BackAndForth::ContinuousShift() { return true; }

void BackAndForth::DoSetGrid(Poles& poles, uint16_t frame) {
  controlPoleLeft.TurnOffAll();
  controlPoleRight.TurnOffAll();
  poles[leftIndex % 6].SetGridLights(
      controlPoleLeft.GetGrid(frame, lastFrame, false));
  poles[rightIndex % 6].SetGridLights(
      controlPoleRight.GetGrid(frame, lastFrame, false));
  lastFrame = frame;
}

void BackAndForth::UpdateOption1() {
  modeIndex = (modeIndex + 1) % (sizeof(modes) / sizeof(Mode));
  controlPoleLeft.SetMode(modes[modeIndex]);
  controlPoleRight.SetMode(modes[modeIndex]);
  ResetModes();
}

void BackAndForth::UpdateOption2() {
  hueStart += 255 / 4;
  controlPoleLeft.SetHue(hueStart + hueVal);
  controlPoleRight.SetHue(hueStart + 127 - hueVal);
}

/**
 */
void BackAndForth::UpdateSlider1(uint8_t val) {
  hueVal = val / 4;
  controlPoleLeft.SetHue(hueStart + hueVal);
  controlPoleRight.SetHue(hueStart + 127 - hueVal);
}

/**
 * Chages the hue distance
 */
void BackAndForth::UpdateSlider2(uint8_t val) {
  uint8_t hueDistance = val / 4;
  controlPoleLeft.SetHueDistance(hueDistance);
  controlPoleRight.SetHueDistance(hueDistance);
}

void BackAndForth::DoShift(uint8_t shiftPosition) {
  if (shiftPosition == 2 && leftIndex == 0) {
    leftReverse = !leftReverse;
    rightReverse = !rightReverse;
  } else if (shiftPosition == 0) {
    if (leftIndex == 0) {
      goIn = true;
    } else if (rightIndex == 0) {
      goIn = false;
    }
    controlPoleLeft.SetReverse(leftReverse);
    controlPoleRight.SetReverse(rightReverse);

    if (goIn) {
      leftIndex++;
      rightIndex--;
    } else {
      leftIndex--;
      rightIndex++;
    }
  }
}

void BackAndForth::ResetModes() {
  controlPoleLeft.SetShiftSpeed(Speed::kDefault);
  controlPoleRight.SetShiftSpeed(Speed::kDefault);
  controlPoleLeft.SetLightCount(4);
  controlPoleRight.SetLightCount(4);
  controlPoleLeft.SetSmoothColor(false);
  controlPoleRight.SetSmoothColor(false);
  controlPoleLeft.SetBackAndForth(false);
  controlPoleRight.SetBackAndForth(false);
  controlPoleLeft.SetHue(0);
  controlPoleRight.SetHue(127);
  controlPoleLeft.ResetFade();
  controlPoleRight.ResetFade();
  controlPoleLeft.SetRotation(0);
  controlPoleRight.SetRotation(0);
  controlPoleLeft.SetReverse(leftReverse);
  controlPoleRight.SetReverse(rightReverse);
}

void BackAndForth::ResetEffect() {
  controlPoleLeft.SetMode(modes[modeIndex]);
  controlPoleRight.SetMode(modes[modeIndex]);
  ResetModes();
}
