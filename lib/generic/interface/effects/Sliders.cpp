#include "Sliders.hpp"

#include "ColordanceTypes.hpp"

Sliders::Sliders()
    : InterfaceEffect(),
      poles{ControlPole(FRAMES_PER_LOOP), ControlPole(FRAMES_PER_LOOP)},
      pole_left(poles.data() + 0),
      pole_right(poles.data() + 1) {
  pole_left->SetMode(Mode::kSmallSquare);
  pole_right->SetMode(Mode::kCorners);
  pole_right->SetReverse(true);
  ResetModes();
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

void Sliders::DoSetOptionButtons(Buttons buttons) {}

void Sliders::UpdateOption1() {
  mode++;
  mode %= kNumModes;
  pole_left->SetMode(modesLeft[mode]);
  pole_right->SetMode(modesLeft[mode]);
  // Have to do this after setting mode because code is dumb - make code better.
  ResetModes();
}

/**
 * Cycle hues.
 */
void Sliders::UpdateOption2() {
  backAndForth = !backAndForth;
  for (auto &pole : this->poles) {
    pole.SetBackAndForth(backAndForth);
  }
}

/**
 * Sliders move which pole the lights are on
 */
void Sliders::UpdateSlider1(uint8_t val) { leftIndex = (255 - val) / 43; }

void Sliders::UpdateSlider2(uint8_t val) { rightIndex = (255 - val) / 43; }

void Sliders::DoManualShift(bool didManual) {
  if (leftIndex == rightIndex) {
    uint8_t hueLeftOld = hueLeft;
    hueLeft = hueRight;
    hueRight = hueLeftOld;
    pole_left->SetHue(hueLeft);
    pole_right->SetHue(hueRight);
  } else {
    std::swap(pole_left, pole_right);
  }
}

void Sliders::DoAutomaticShift(bool didManual) { return; }

void Sliders::DoAutomaticPartialShift(uint8_t shiftFraction) { return; }

void Sliders::ResetModes() {
  pole_left->SetHue(hueLeft);
  pole_right->SetHue(hueRight);
  pole_left->SetReverse(false);
  pole_right->SetReverse(true);
  for (auto &pole : poles) {
    pole.SetShiftSpeed(Speed::kDefault);
    pole.SetHueDistance(10);
    pole.SetLightCount(4);
    pole.SetSmoothColor(true);
    pole.SetBackAndForth(false);
    pole.SetRotation(0);
  }
}

void Sliders::InitializeEffect() { ResetModes(); }
