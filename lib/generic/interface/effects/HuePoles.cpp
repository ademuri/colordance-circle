#include "HuePoles.hpp"

#include "ColordanceTypes.hpp"

HuePoles::HuePoles() : InterfaceEffect() {
  controlPoles.reserve(Pole::kNumPoles);
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles.emplace_back(FRAMES_PER_LOOP);
  }
  InitializeEffect();
}

void HuePoles::DoSetGrid(Poles& poles, uint16_t frame, uint16_t lastFrame) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    controlPoles[pole].TurnOffAll();
    poles[pole].SetGridLights(
        controlPoles[pole].GetGrid(frame, lastFrame, false));
  }
}

/**
 * Change the mode (grid animation).
 */
void HuePoles::UpdateOption1() {
  modeIndex = (modeIndex + 1) % (sizeof(modes) / sizeof(Mode));
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles[i].SetMode(modes[modeIndex]);
  }
  ResetModes();
}

void HuePoles::UpdateOption2() {
  still = !still;
  for (auto& pole : controlPoles) {
    pole.SetShiftSpeed(still ? Speed::kStill : Speed::kDefault);
  }
}

/**
 * Change color shift.
 */
void HuePoles::UpdateSlider1(uint8_t val) {
  for (auto& pole : controlPoles) {
    pole.SetHueShift(val < 10 ? 2 : val / 5);
  }
}

/**
 * Chages Hue Distance
 */
void HuePoles::UpdateSlider2(uint8_t val) {
  for (auto& pole : controlPoles) {
    pole.SetHueDistance(val / 2);
  }
  // val = val / 64;
  // for (auto& pole : controlPoles) {
  //   switch (val) {
  //   case 0:
  //     pole.SetShiftSpeed(Speed::kStill);
  //     break;
  //   case 1:
  //     pole.SetShiftSpeed(Speed::kHalf);
  //     break;
  //   case 3:
  //     pole.SetShiftSpeed(Speed::kDouble);
  //     break;
  //   default:
  //     pole.SetShiftSpeed(Speed::kDefault);
  // }
  //}
}

void HuePoles::DoAutomaticShift(bool didManual) { return; }

void HuePoles::DoAutomaticPartialShift(uint8_t shiftFraction) { return; }

void HuePoles::DoManualShift(bool didAutomatic) {
  smoothColor = !smoothColor;
  for (auto& pole : controlPoles) {
    pole.SetSmoothColor(smoothColor);
  }
}

void HuePoles::ResetModes() {
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

void HuePoles::InitializeEffect() {
  still = true;
  ResetModes();
}