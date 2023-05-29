#include "Sliders.hpp"

#include "ColordanceTypes.hpp"

Sliders::Sliders()
    : InterfaceEffect(),
      poles{ControlPole(FRAMES_PER_LOOP), ControlPole(FRAMES_PER_LOOP)},
      pole_left(poles.data() + 0),
      pole_right(poles.data() + 1) {
  InitializeEffect();
}

void Sliders::DoUpdate(uint16_t frame, uint16_t lastFrame) {
  for (auto &pole : this->poles) {
    pole.TurnOffAll();
  }
  pole_left->UpdateGrid(frame, lastFrame, false);
  pole_right->UpdateGrid(frame, lastFrame, false);
}

void Sliders::DoSetGrid(Poles &poles) {
  poles[leftIndex].MultiplyGridLights(pole_left->GetGrid());
  poles[rightIndex].MultiplyGridLights(pole_right->GetGrid());
}

void Sliders::DoSetEffectButton(Buttons buttons, uint8_t buttonIndex) {
  if (leftIndex == rightIndex) {
    buttons.SetButton(buttonIndex, leftIndex, CRGB(200, 200, 200));
  } else {
    buttons.SetButton(buttonIndex, leftIndex, CRGB(pole_left->GetHSV()));
    buttons.SetButton(buttonIndex, rightIndex, CRGB(pole_right->GetHSV()));
  }
}

void Sliders::DoSetOptionButtons(Buttons buttons) {
  // Option 1
  uint8_t modeHue = modeLeft * (255 / kNumModes);
  for (int i = 0; i < 4; i++) {
    buttons.SetButton(7, i, CRGB(CHSV(modeHue, 255, 200)));
  }

  modeHue = modeRight * (255 / kNumModes);
  for (int i = 0; i < 4; i++) {
    buttons.SetButton(8, i, CRGB(CHSV(modeHue, 255, 200)));
  }

  // Slider 1
  for (int i = 0; i < 3; i++) {
    buttons.SetButton(12, i, CRGB(CHSV(pole_left->GetHue(), 255, 170)));
  }

  // Slider 2
  for (int i = 0; i < 3; i++) {
    buttons.SetButton(12, i, CRGB(CHSV(pole_right->GetHue(), 255, 170)));
  }
}

void Sliders::UpdateOption1() {
  modeLeft++;
  modeLeft %= kNumModes;
  pole_left->SetMode(modesLeft[modeLeft]);
}

/**
 * Cycle hues.
 */
void Sliders::UpdateOption2() {
  modeRight++;
  modeRight %= kNumModes;
  pole_right->SetMode(modesRight[modeRight]);
}

/**
 * Sliders move which pole the lights are on
 */
void Sliders::UpdateSlider1(uint8_t val) { leftIndex = val / 43; }

void Sliders::UpdateSlider2(uint8_t val) { rightIndex = val / 43; }

void Sliders::DoManualShift(bool didManual) {
  UNUSED(didManual);
  if (leftIndex == rightIndex) {
    // uint8_t hueLeftOld = hueLeft;
    // hueLeft = hueRight;
    // hueRight = hueLeftOld;
    // pole_left->SetHue(hueLeft);
    // pole_right->SetHue(hueRight);
  } else {
    std::swap(pole_left, pole_right);
  }
}

void Sliders::DoAutomaticShift(bool didManual) {
  UNUSED(didManual);
  return;
}

void Sliders::DoAutomaticPartialShift(uint8_t shiftFraction) {
  UNUSED(shiftFraction);
  return;
}

void Sliders::ResetModes() {
  pole_left->SetHue(0);
  pole_right->SetHue(127);
  pole_left->SetReverse(false);
  pole_right->SetReverse(true);
  for (auto &pole : poles) {
    pole.SetShiftSpeed(Speed::kDefault);
    pole.SetHueDistance(10);
    pole.SetLightCount(4);
    pole.SetSmoothColor(true);
    pole.SetBackAndForth(false);
    pole.SetRotation(0);
    pole.SetHueShift(10);
  }
}

void Sliders::InitializeEffect() { ResetModes(); }
