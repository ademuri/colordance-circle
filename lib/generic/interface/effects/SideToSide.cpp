#include "SideToSide.hpp"

#include "ColordanceTypes.hpp"

SideToSide::SideToSide() : InterfaceEffect() {
  controlPoles.reserve(Pole::kNumPoles);
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles.emplace_back(FRAMES_PER_LOOP);
  }
  InitializeEffect();
}

void SideToSide::DoUpdate(uint16_t frame, uint16_t lastFrame) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    controlPoles[pole].TurnOffAll();
    shiftIndex = controlPoles[pole].UpdateGrid(frame, lastFrame, false);
  }
}

void SideToSide::DoSetGrid(Poles& poles) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    if (pole < numOfPolesOn) {
      uint8_t effectivePole = (pole + poleOffset) % Pole::kNumPoles;
      poles[effectivePole].SetGridLights(controlPoles[pole].GetGrid());
    }
  }
}

void SideToSide::DoSetEffectButton(Buttons buttons, uint8_t buttonIndex) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    buttons.SetButton(buttonIndex, pole, CRGB(controlPoles[pole].GetHSV()));
  }
}

void SideToSide::DoSetOptionButtons(Buttons buttons) {
  // Option 1
  uint8_t modeHue = modeIndex * (255 / kNumModes);
  for (int i = 0; i < 4; i++) {
    buttons.SetButton(7, i, CRGB(CHSV(modeHue, 255, 200)));
  }

  uint8_t baseHue = controlPoles[0].GetHue();
  // Option 2
  buttons.SetButton(8, shiftIndex % 4, CRGB(CHSV(baseHue, 255, 200)));

  // Slider 1
  // Shows hueshift with hue
  for (int i = 0; i < numOfPolesOn / 2; i++) {
    buttons.SetButton(12, i, CRGB(CHSV(baseHue, 255, 200)));
  }

  // Slider 2
  for (int i = 0; i < 3; i++) {
    buttons.SetButton(13, i, CRGB(CHSV(baseHue + hueDistance * i, 255, 255)));
  }
}

/**
 * Change the mode (grid animation).
 */
void SideToSide::UpdateOption1() {
  modeIndex = (modeIndex + 1) % (sizeof(modes) / sizeof(Mode));
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles[i].SetMode(modes[modeIndex]);
    controlPoles[i].SetRotation(rotations[modeIndex]);
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
  uint8_t newNumOfPolesOn = 1 + val * 4 / 255;
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
 * Changes the hue distance
 */
void SideToSide::UpdateSlider2(uint8_t val) {
  hueDistance = val / 4;
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles[i].SetHueDistance(hueDistance);
  }
}

void SideToSide::DoAutomaticShift(bool didManual) {
  UNUSED(didManual);
  for (ControlPole& pole : controlPoles) {
    pole.ResetFade();
  }
  if (numOfPolesOn == Pole::kNumPoles) {
    return;
  }
  if ((goBackwards && poleOffset == 0) ||
      (!goBackwards && poleOffset == Pole::kNumPoles - numOfPolesOn)) {
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

void SideToSide::DoAutomaticPartialShift(uint8_t shiftFraction) {
  UNUSED(shiftFraction);
  return;
}

void SideToSide::DoManualShift(bool didAutomatic) {
  UNUSED(didAutomatic);
  return;
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

void SideToSide::InitializeEffect() {
  poleOffset = 0;
  for (ControlPole& pole : controlPoles) {
    pole.ResetFade();
  }
  ResetModes();
}
