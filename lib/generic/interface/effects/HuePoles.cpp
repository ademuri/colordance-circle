#include "HuePoles.hpp"

#include "ColordanceTypes.hpp"

/**
 * @brief Effect with 6 pooes, even hue spread. DE
 */
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
  modeIndex++;
  modeIndex %= kNumModes;
  for (ControlPole& pole : controlPoles) {
    pole.SetMode(modes[modeIndex]);
    pole.SetShiftSpeed(speeds[modeIndex]);
    pole.SetRotation(rotations[modeIndex]);
  }
}

void HuePoles::UpdateOption2() {
  smoothColor = !smoothColor;
  for (ControlPole& pole : controlPoles) {
    pole.SetSmoothColor(smoothColor);
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
  uint8_t hDis = val / 6;
  for (int i = 0; i < 3; i++) {
    controlPoles[i].SetHue(i * hDis);
    controlPoles[i + 3].SetHue(127 + i * hDis);
  }
  hueDistance = 127 - 2 * hDis;  // for button setting
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
    controlPoles[i].SetSmoothColor(true);
    controlPoles[i].SetLightCount(2);
    controlPoles[i].SetHue(43 * i);
    controlPoles[i].SetHueDistance(0);
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