#include "BackAndForth.hpp"

#include "ColordanceTypes.hpp"

BackAndForth::BackAndForth() : InterfaceEffect() {
  controlPoleLeft = new ControlPole(FRAMES_PER_LOOP);
  controlPoleRight = new ControlPole(FRAMES_PER_LOOP);
  controlPoleLeft->SetHue(0);
  controlPoleRight->SetHue(127);
}

void BackAndForth::DoSetGrid(std::vector<Pole*> poles, uint16_t frame) {
  poles[leftIndex]->SetGridLights(controlPoleLeft->GetGrid(frame, lastFrame));
  poles[rightIndex]->SetGridLights(controlPoleRight->GetGrid(frame, lastFrame));
  lastFrame = frame;
}

void BackAndForth::UpdateOption1() {
  modeIndex++;
  modeIndex %= sizeof(modes);
  controlPoleLeft->SetMode(modes[modeIndex]);
  controlPoleRight->SetMode(modes[modeIndex]);
}

void BackAndForth::UpdateOption2() {}

/**
 * Change the number of poles on.
 */
void BackAndForth::UpdateSlider1(uint8_t val) {}

/**
 * Chages the hue distance
 */
void BackAndForth::UpdateSlider2(uint8_t val) {
  uint8_t hueDistance = val / 4;
  controlPoleLeft->SetHueDistance(hueDistance);
  controlPoleRight->SetHueDistance(hueDistance);
}

void BackAndForth::DoShift(uint8_t shiftPosition) {
  if (shiftPosition == 2) {
    if (leftIndex == 0) {
      controlPoleLeft->SetReverse(true);
      controlPoleRight->SetReverse(false);
    } else if (leftIndex == 2) {
      controlPoleLeft->SetReverse(false);
      controlPoleRight->SetReverse(true);
    }
  } else if (shiftPosition == 0) {
    if (leftIndex == 0) {
      goIn = true;
      controlPoleLeft->SetReverse(true);
      controlPoleRight->SetReverse(false);
    } else if (leftIndex == 2) {
      goIn = false;
      controlPoleLeft->SetReverse(false);
      controlPoleRight->SetReverse(true);
    }
    if (goIn) {
      leftIndex++;
      rightIndex--;
    } else {
      leftIndex--;
      rightIndex++;
    }
  }
}

void BackAndForth::Reset() {}