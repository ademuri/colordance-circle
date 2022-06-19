#include "SideToSide.hpp"

#include "ColordanceTypes.hpp"

SideToSide::SideToSide() : InterfaceEffect() {
  controlPoles.reserve(Pole::kNumPoles);
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles.emplace_back(FRAMES_PER_LOOP);
  }
  ResetEffect();
}

bool SideToSide::ContinuousShift() { return true; }

void SideToSide::DoSetGrid(std::vector<Pole*>& poles, uint16_t frame) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    controlPoles[pole].TurnOffAll();
    std::vector<std::vector<CHSV>> const& grid = controlPoles[pole].GetGrid(
        frame, lastFrame, false);  // Update all grids
    if (pole < numOfPolesOn) {
      uint8_t effectivePole = (pole + poleOffset) % Pole::kNumPoles;
      poles[effectivePole]->SetGridLights(grid);
    }
  }
  lastFrame = frame;
}

/**
 * Change the mode (grid animation).
 */
void SideToSide::UpdateOption1() {
  modeIndex++;
  modeIndex %= sizeof(modes);
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles[i].SetMode(modes[modeIndex]);
  }
  ResetModes();
}

void SideToSide::UpdateOption2() {
  backAndForth = !backAndForth;
  SetBackAndForth();
}

void SideToSide::SetBackAndForth() {
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles[i].SetBackAndForth(backAndForth);
  }
}
/**
 * Change the number of poles on.
 */
void SideToSide::UpdateSlider1(uint8_t val) {
  uint8_t newNumOfPolesOn = 1 + val / (255 / 4);
  if (newNumOfPolesOn + poleOffset >= Pole::kNumPoles) {
    poleOffset = Pole::kNumPoles - newNumOfPolesOn;
  }
  if (newNumOfPolesOn != numOfPolesOn) {
    numOfPolesOn = newNumOfPolesOn;
    UpdateHues();
  }
  for (ControlPole& pole : controlPoles) {
    pole.SetLightCount(numOfPolesOn == 4 ? 3 : 4);
  }
}

void SideToSide::UpdateHues() {
  uint8_t poleHueDifference = 255 / numOfPolesOn;
  uint8_t polesOnCount = 0;
  for (int i = 0; i < numOfPolesOn; i++) {
    controlPoles[i].SetHue(polesOnCount++ * poleHueDifference);
  }
}

/**
 * Chages the hue distance
 */
void SideToSide::UpdateSlider2(uint8_t val) {
  uint8_t hueDistance = val / 4;
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles[i].SetHueDistance(hueDistance);
  }
}

void SideToSide::DoShift(uint8_t shiftPosition) {
  if (shiftPosition != 0) {
    return;
  }
  for (ControlPole& pole : controlPoles) {
    pole.ResetFade();
  }
  if (numOfPolesOn == Pole::kNumPoles) {
    return;
  }
  if (goBackwards && poleOffset == 0 ||
      !goBackwards && poleOffset == Pole::kNumPoles - numOfPolesOn) {
    goBackwards = !goBackwards;
  }
  if (smoothPoleShift && numOfPolesOn > 1) {
    if (goBackwards) {
      controlPoles[0].FadeIn(600);
      controlPoles[numOfPolesOn - 1].FadeOut(600);
    } else {
      controlPoles[numOfPolesOn - 1].FadeIn(600);
      controlPoles[0].FadeOut(600);
    }
  }
  poleOffset += goBackwards ? -1 : 1;
}

void SideToSide::ResetModes() {
  for (ControlPole& pole : controlPoles) {
    pole.ResetFade();
    pole.SetShiftSpeed(Speed::kDefault);
    pole.SetLightCount(4);
    pole.SetBackAndForth(backAndForth);
    pole.SetSmoothColor(true);
    pole.SetReverse(false);
    pole.SetRotation(0);
  }
  UpdateHues();
}

void SideToSide::ResetEffect() {
  poleOffset = 0;
  for (ControlPole& pole : controlPoles) {
    pole.ResetFade();
  }
  ResetModes();
}
