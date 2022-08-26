#include "HuePoles.hpp"

#include "ColordanceTypes.hpp"

HuePoles::HuePoles() : InterfaceEffect() {
  controlPoles.reserve(Pole::kNumPoles);
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles.emplace_back(FRAMES_PER_LOOP);
  }
  InitializeEffect();
}

void HuePoles::DoUpdate(uint16_t frame, uint16_t lastFrame) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    controlPoles[pole].TurnOffAll();
    shiftIndex = controlPoles[pole].UpdateGrid(frame, lastFrame, false);
  }
}

void HuePoles::DoSetGrid(Poles& poles) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    poles[pole].SetGridLights(controlPoles[pole].GetGrid());
  }
}

void HuePoles::DoSetEffectButton(Buttons buttons, uint8_t buttonIndex) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    buttons.SetButton(buttonIndex, pole, CRGB(controlPoles[pole].GetHSV()));
  }
}

void HuePoles::DoSetOptionButtons(Buttons buttons) {
  // Option 1
  uint8_t modeHue = modeIndex * (255 / kNumModes);
  for (int i = 0; i < 4; i++) {
    buttons.SetButton(7, i, CRGB(CHSV(modeHue, 255, 200)));
  }

  uint8_t baseHue = controlPoles[0].GetHue();
  // Option 2
  if (still) {
    buttons.SetButton(8, 0, CRGB(CHSV(baseHue, 255, 255)));
  } else {
    buttons.SetButton(8, shiftIndex % 4, CRGB(CHSV(baseHue, 255, 200)));
  }

  // Slider 1
  // Shows hueshift with hue
  for (int i = 0; i < 3; i++) {
    buttons.SetButton(12, i, CRGB(CHSV(baseHue, 255, 200)));
  }

  // Slider 2
  buttons.SetButton(13, 0, CRGB(CHSV(baseHue, 255, 255)));
  buttons.SetButton(13, 2, CRGB(CHSV(baseHue + hueDistance, 255, 255)));
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
  hueDistance = val / 2;
  for (auto& pole : controlPoles) {
    pole.SetHueDistance(hueDistance);
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
    controlPoles[i].SetRotation(2);
  }
}

void HuePoles::InitializeEffect() {
  still = true;
  ResetModes();
}