#include "BackAndForth.hpp"

#include "ColordanceTypes.hpp"

BackAndForth::BackAndForth(std::vector<HelperPole*> const & helperPoles)
    : InterfaceEffect(helperPoles),
      controlPoleLeft(FRAMES_PER_LOOP),
      controlPoleRight(FRAMES_PER_LOOP)
{
  controlPoleLeft.SetHue(0);
  controlPoleRight.SetHue(127);
  controlPoleLeft.SetReverse(true);
}

bool BackAndForth::ContinuousShift() { return true; }

void BackAndForth::DoSetGrid(std::vector<Pole*> & poles, uint16_t frame) {
  poles[leftIndex]->SetGridLights(
      controlPoleLeft.GetGrid(frame, lastFrame, false));
  poles[rightIndex]->SetGridLights(
      controlPoleRight.GetGrid(frame, lastFrame, false));
  lastFrame = frame;
}

void BackAndForth::UpdateOption1() {
  modeIndex++;
  modeIndex %= sizeof(modes);
  controlPoleLeft.SetMode(modes[modeIndex]);
  controlPoleRight.SetMode(modes[modeIndex]);
}

void BackAndForth::UpdateOption2() { cross = !cross; }

/**
 * Change the fade.
 */
void BackAndForth::UpdateSlider1(uint8_t val) {}

/**
 * Chages the hue distance
 */
void BackAndForth::UpdateSlider2(uint8_t val) {
  uint8_t hueDistance = val / 4;
  controlPoleLeft.SetHueDistance(hueDistance);
  controlPoleRight.SetHueDistance(hueDistance);
}

void BackAndForth::DoShift(uint8_t shiftPosition) {
  uint8_t endLeftIndex = cross ? 5 : 2;
  if (shiftPosition == 2) {
    if (leftIndex == 0) {
      controlPoleLeft.SetReverse(true);
      controlPoleRight.SetReverse(false);
    } else if (leftIndex == endLeftIndex) {
      controlPoleLeft.SetReverse(false);
      controlPoleRight.SetReverse(true);
    }
  } else if (shiftPosition == 0) {
    if (leftIndex == 0) {
      goIn = true;
      controlPoleLeft.SetReverse(true);
      controlPoleRight.SetReverse(false);
    } else if (leftIndex == endLeftIndex) {
      goIn = false;
      controlPoleLeft.SetReverse(false);
      controlPoleRight.SetReverse(true);
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