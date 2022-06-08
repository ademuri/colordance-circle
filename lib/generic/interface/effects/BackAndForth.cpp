#include "BackAndForth.hpp"

#include "ColordanceTypes.hpp"

BackAndForth::BackAndForth()
    : InterfaceEffect(),
      controlPoleLeft(FRAMES_PER_LOOP),
      controlPoleRight(FRAMES_PER_LOOP) {
  controlPoleLeft.SetHue(0);
  controlPoleRight.SetHue(127);
  controlPoleLeft.SetReverse(true);
}

bool BackAndForth::ContinuousShift() { return true; }

void BackAndForth::DoSetGrid(std::vector<Pole*>& poles, uint16_t frame) {
  poles[leftIndex % 6]->SetGridLights(
      controlPoleLeft.GetGrid(frame, lastFrame, false));
  poles[rightIndex % 6]->SetGridLights(
      controlPoleRight.GetGrid(frame, lastFrame, false));
  lastFrame = frame;
}

void BackAndForth::UpdateOption1() {
  modeIndex++;
  modeIndex %= sizeof(modes);
  controlPoleLeft.SetMode(modes[modeIndex]);
  controlPoleRight.SetMode(modes[modeIndex]);
}

void BackAndForth::UpdateOption2() {
  leftReverse = !leftReverse;
  rightReverse = !rightReverse;
  controlPoleLeft.SetReverse(leftReverse);
  controlPoleRight.SetReverse(rightReverse);
}

/**
 * Change the fade.
 */
void BackAndForth::UpdateSlider1(uint8_t val) {
  val /= 4;
  controlPoleLeft.SetHue(val);
  controlPoleRight.SetHue(127 - val);
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

void BackAndForth::ResetEffect() {}
