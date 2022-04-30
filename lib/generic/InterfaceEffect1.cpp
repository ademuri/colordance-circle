#include "InterfaceEffect1.hpp"

#include "ColordanceTypes.hpp"

InterfaceEffect1::InterfaceEffect1() : InterfaceEffect() {
  for (int i = 0; i < Pole::kNumPoles; i++) {
    ControlPole* pole = new ControlPole(i, FRAMES_PER_LOOP);
    pole->SetBackAndForth(true);
    pole->SetSmoothColor(true);
    controlPoles.push_back(pole);
  }
}

void InterfaceEffect1::DoSetGrid(std::vector<Pole*> poles, uint16_t frame) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    std::vector<std::vector<CHSV>> grid =
        controlPoles[pole]->GetGrid(frame, lastFrame);  // Update all grids
    if (pole < numOfPolesOn) {
      uint8_t effectivePole = (pole + poleOffset) % Pole::kNumPoles;
      poles[effectivePole]->SetGridLights(grid);
    }
  }
  lastFrame = frame;
}

void InterfaceEffect1::UpdateOption1() {
  modeIndex++;
  modeIndex %= sizeof(modes);
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles[i]->SetMode(modes[modeIndex]);
  }
  UpdateHues();
  SetBackAndForth();
}

void InterfaceEffect1::UpdateOption2() {
  backAndForth = !backAndForth;
  SetBackAndForth();
}

void InterfaceEffect1::SetBackAndForth() {
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles[i]->SetBackAndForth(backAndForth);
  }
}

/**
 * Change the number of poles on.
 */
void InterfaceEffect1::UpdateSlider1(uint8_t val) {
  uint8_t newNumOfPolesOn = 1 + val / 51;
  if (newNumOfPolesOn + poleOffset >= Pole::kNumPoles) {
    poleOffset = Pole::kNumPoles - newNumOfPolesOn;
  }
  if (newNumOfPolesOn != numOfPolesOn) {
    numOfPolesOn = newNumOfPolesOn;
    UpdateHues();
  }
}

void InterfaceEffect1::UpdateHues() {
  uint8_t poleHueDifference = 255 / numOfPolesOn;
  uint8_t polesOnCount = 0;
  for (int i = 0; i < numOfPolesOn; i++) {
    controlPoles[i]->SetHue(polesOnCount++ * poleHueDifference);
  }
}

/**
 * Chages the huge distance
 */
void InterfaceEffect1::UpdateSlider2(uint8_t val) {
  uint8_t hueDistance = val / 4;
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles[i]->SetHueDistance(hueDistance);
  }
}

void InterfaceEffect1::DoShift() {
  if (numOfPolesOn == Pole::kNumPoles) {
    return;
  }
  if (goBackwards && poleOffset == 0 ||
      !goBackwards && poleOffset == Pole::kNumPoles - numOfPolesOn) {
    goBackwards = !goBackwards;
  }
  poleOffset += goBackwards ? -1 : 1;
}

void InterfaceEffect1::Reset() { poleOffset = 0; }