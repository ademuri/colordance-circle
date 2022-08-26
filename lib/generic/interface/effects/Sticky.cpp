#include "Sticky.hpp"

#include "ColordanceTypes.hpp"

Sticky::Sticky()
    : InterfaceEffect(),
      movingPoles{ControlPole(FRAMES_PER_LOOP), ControlPole(FRAMES_PER_LOOP)},
      autoMovingPole(movingPoles.data() + 0),
      movingPole(movingPoles.data() + 1) {
  controlPoles.reserve(Pole::kNumPoles);
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles.emplace_back(FRAMES_PER_LOOP);
  }
  InitializeEffect();
}

void Sticky::DoUpdate(uint16_t frame, uint16_t lastFrame) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    controlPoles[pole].TurnOffAll();
    controlPoles[pole].UpdateGrid(frame, lastFrame, false);
  }

  if (beatsPerShift > 0) {
    autoMovingPoleIndex = 24 * frame / (FRAMES_PER_LOOP * beatsPerShift) +
                          24 * beatsSinceAutoShift / beatsPerShift;
    autoMovingPole->SetShiftOffset(autoMovingPoleIndex % 4);
    autoMovingPole->UpdateGrid(frame, lastFrame, false);
    autoMovingPoleIndex /= 4;
  }

  if (frame < lastFrame && movingPoleIndex <= 6) {
    movingPoleIndex++;
  }
  if (movingPoleIndex < 6) {
    movingPole->UpdateGrid(frame, lastFrame, false);
  }
  baseHue += 5;
}

void Sticky::DoSetGrid(Poles& poles) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    poles[pole].SetGridLights(controlPoles[pole].GetGrid());
  }
  poles[autoMovingPoleIndex % 6].SetGridLights(autoMovingPole->GetGrid());
  poles[movingPoleIndex].SetGridLights(movingPole->GetGrid());
}

void Sticky::DoSetEffectButton(Buttons buttons, uint8_t buttonIndex) {
  for (int i = 0; i < Pole::kNumPoles; i++) {
    buttons.SetButton(buttonIndex, i,
                      CRGB(CHSV(controlPoles[i].GetHue(), 255, 100)));
  }
  if (beatsPerShift > 0) {
    buttons.SetButton(buttonIndex, autoMovingPoleIndex % 6,
                      CRGB(autoMovingPole->GetHSV()));
  }
  if (movingPoleIndex < 6) {
    buttons.SetButton(buttonIndex, movingPoleIndex, CRGB(movingPole->GetHSV()));
  }
}

void Sticky::DoSetOptionButtons(Buttons buttons) {}

/**
 * Change the mode (grid animation).
 */
void Sticky::UpdateOption1() {}

void Sticky::UpdateOption2() {
  still = !still;
  for (ControlPole& pole : controlPoles) {
    pole.SetShiftSpeed(still ? Speed::kStill : Speed::kDefault);
  }
}

/**
 * Change the number of poles on.
 */
void Sticky::UpdateSlider1(uint8_t val) {
  hueDistance = val / 6;
  UpdateHues();
}

void Sticky::UpdateHues() {
  uint8_t hue = baseHue;
  for (ControlPole& pole : controlPoles) {
    pole.SetHue(hue);
    hue += hueDistance;
  }
}
/**
 * Changes the hue distance
 */
void Sticky::UpdateSlider2(uint8_t val) {}

void Sticky::DoAutomaticShift(bool didManual) {
  autoMovingPole->SetHue(baseHue + 127);
}

void Sticky::DoAutomaticPartialShift(uint8_t shiftFraction) { return; }

void Sticky::DoManualShift(bool didAutomatic) {
  if (!didAutomatic && movingPoleIndex == 6) {
    movingPoleIndex = 0;
    movingPole->SetHue(baseHue + 127);
  }
}

void Sticky::InitializeEffect() {
  poleOffset = 0;
  for (ControlPole& pole : controlPoles) {
    pole.SetMode(Mode::kLine);
    pole.SetShiftSpeed(Speed::kStill);
    pole.SetShiftOffset(3);
    pole.ResetFade();
    pole.SetLightCount(1);
    pole.SetBackAndForth(false);
    pole.SetReverse(false);
    pole.SetSmoothColor(true);
  }
  for (ControlPole& pole : movingPoles) {
    pole.SetMode(Mode::kLine);
    pole.SetShiftSpeed(Speed::kStill);
    pole.SetLightCount(3);
    pole.SetBackAndForth(false);
    pole.SetHueShift(0);
    pole.SetHueDistance(0);
  }
}
