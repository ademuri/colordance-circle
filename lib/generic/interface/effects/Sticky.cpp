#include "Sticky.hpp"

#include "ColordanceTypes.hpp"

Sticky::Sticky() : InterfaceEffect() {
  controlPoles.reserve(Pole::kNumPoles);
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles.emplace_back(FRAMES_PER_LOOP);
  }
  InitializeEffect();
}

void Sticky::DoUpdate(uint16_t frame, uint16_t lastFrame) {
  if (changeMovingPole) {
    movingPoleIndex = frame % Pole::kNumPoles;
    changeMovingPole = false;
  }
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    controlPoles[pole].TurnOffAll();
    controlPoles[pole].UpdateGrid(frame, lastFrame, false);
  }
  movingPole.TurnOffAll();
  movingPole.UpdateGrid(frame, lastFrame, false);
}

void Sticky::DoSetGrid(Poles& poles) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    poles[pole].SetGridLights(controlPoles[pole].GetGrid());
  }
  poles[movingPoleIndex].SetGridLights(movingPole.GetGrid());
}

void Sticky::DoSetEffectButton(Buttons buttons) {}

/**
 * Change the mode (grid animation).
 */
void Sticky::UpdateOption1() {
  modeIndex = (modeIndex + 1) % (sizeof(modes) / sizeof(Mode));
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles[i].SetMode(modes[modeIndex]);
  }
  ResetModes();
}

void Sticky::UpdateOption2() {
  still = !still;
  for (auto& pole : controlPoles) {
    pole.SetShiftSpeed(still ? Speed::kStill : Speed::kDefault);
  }
}

/**
 * Change color shift.
 */
void Sticky::UpdateSlider1(uint8_t val) {
  for (auto& pole : controlPoles) {
    pole.SetHueShift(val < 10 ? 2 : val / 5);
  }
}

/**
 * Chages Hue Distance
 */
void Sticky::UpdateSlider2(uint8_t val) {
  for (auto& pole : controlPoles) {
    pole.SetHueDistance(val / 2);
  }
}

void Sticky::DoAutomaticShift(bool didManual) { changeMovingPole = true; }

void Sticky::DoAutomaticPartialShift(uint8_t shiftFraction) { return; }

void Sticky::DoManualShift(bool didAutomatic) { changeMovingPole = true; }

void Sticky::ResetModes() {
  for (int i = 0; i < Pole::kNumPoles; i++) {
    if (modes[modeIndex] == Mode::kLine || modes[modeIndex] == Mode::kDiverge) {
      controlPoles[i].SetBackAndForth(true);
    } else {
      controlPoles[i].SetBackAndForth(false);
    }
    // don't care about reverse
    controlPoles[i].SetSmoothColor(true);
    controlPoles[i].SetLightCount(2);
    controlPoles[i].SetHue(43 * i + hueOffset);
    controlPoles[i].SetShiftSpeed(still ? Speed::kStill : Speed::kDefault);
    controlPoles[i].ResetFade();
    controlPoles[i].SetReverse(false);
    controlPoles[i].SetRotation(0);
  }
}

void Sticky::InitializeEffect() {
  still = true;
  ResetModes();
}