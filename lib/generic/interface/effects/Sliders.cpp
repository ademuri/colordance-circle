#include "Sliders.hpp"

#include "ColordanceTypes.hpp"

Sliders::Sliders() :
  InterfaceEffect(),
  pole_left(std::make_unique<ControlPole>(FRAMES_PER_LOOP)),
  pole_right(std::make_unique<ControlPole>(FRAMES_PER_LOOP))
{
  ResetModes();
}

bool Sliders::ContinuousShift() { return true; }

void Sliders::DoSetGrid(std::vector<Pole *> &poles, uint16_t frame) {
  pole_right->TurnOffAll();
  pole_left->TurnOffAll();
  bool multiply = leftIndex == rightIndex ? true : false;
  poles[leftIndex]->MultiplyGridLights(
      pole_left->GetGrid(frame, lastFrame, false));
  poles[rightIndex]->MultiplyGridLights(
      pole_right->GetGrid(frame, lastFrame, multiply));

  lastFrame = frame;
}

void Sliders::UpdateOption1() {
  mode++;
  mode %= kNumModes;
  if (mode == 0) {
    pole_left->SetMode(Mode::kLine);
    pole_right->SetMode(Mode::kLine);
  } else {
    pole_left->SetMode(Mode::kCircle);
    pole_right->SetMode(Mode::kCircle);
  }
  // Have to do this after setting mode because code is dumb - make code better.
  ResetModes();
  if (mode == 0) {
  } else {
    pole_right->SetReverse(true);
  }
}

/**
 * Cycle hues.
 */
void Sliders::UpdateOption2() {
  smoothHue = !smoothHue;
  pole_left->SetSmoothColor(smoothHue);
  pole_right->SetSmoothColor(smoothHue);
}

/**
 * Sliders move which pole the lights are on
 */
void Sliders::UpdateSlider1(uint8_t val) { leftIndex = val / 43; }

void Sliders::UpdateSlider2(uint8_t val) { rightIndex = val / 43; }

void Sliders::DoShift(uint8_t shiftPosition) {
  if (shiftPosition == 0) {
    if (leftIndex == rightIndex) {
      uint8_t hueLeftOld = hueLeft;
      hueLeft = hueRight;
      hueRight = hueLeftOld;
      pole_left->SetHue(hueLeft);
      pole_right->SetHue(hueRight);
    } else {
      using std::swap;
      swap(pole_left, pole_right);
    }
  }
}

void Sliders::ResetModes() {
  pole_left->SetHueDistance(10);
  pole_right->SetHueDistance(10);
  pole_left->SetHue(hueLeft);
  pole_right->SetHue(hueRight);
  pole_left->SetLightCount(4);
  pole_right->SetLightCount(4);
  pole_left->SetReverse(false);
  pole_right->SetReverse(false);
  pole_left->SetSmoothColor(smoothHue);
  pole_right->SetSmoothColor(smoothHue);
}

void Sliders::ResetEffect() { ResetModes(); }
