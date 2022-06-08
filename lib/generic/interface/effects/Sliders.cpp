#include "Sliders.hpp"

#include "ColordanceTypes.hpp"

Sliders::Sliders() :
  InterfaceEffect(),
  poles{ControlPole(FRAMES_PER_LOOP), ControlPole(FRAMES_PER_LOOP)},
  pole_left(poles.data() + 0),
  pole_right(poles.data() + 1)
{
  ResetModes();
}

bool Sliders::ContinuousShift() { return true; }

void Sliders::DoSetGrid(std::vector<Pole *> &poles, uint16_t frame) {
  for (auto & pole : this->poles) {
    pole.TurnOffAll();
  }
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
  for (auto & pole : poles) {
    if (mode == 0) {
      pole.SetMode(Mode::kLine);
    } else {
      pole.SetMode(Mode::kCircle);
    }
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
      std::swap(pole_left, pole_right);
    }
  }
}

void Sliders::ResetModes() {
  pole_left->SetHue(hueLeft);
  pole_right->SetHue(hueRight);
  for (auto & pole : poles) {
    pole.SetHueDistance(10);
    pole.SetLightCount(4);
    pole.SetReverse(false);
    pole.SetSmoothColor(smoothHue);
  }
}

void Sliders::ResetEffect() { ResetModes(); }
