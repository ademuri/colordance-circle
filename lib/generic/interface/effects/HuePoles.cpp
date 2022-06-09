#include "HuePoles.hpp"

#include "ColordanceTypes.hpp"

HuePoles::HuePoles() : InterfaceEffect() {
  controlPoles.reserve(Pole::kNumPoles);
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles.emplace_back(FRAMES_PER_LOOP);
  }
  ResetEffect();
}

bool HuePoles::ContinuousShift() { return true; }

void HuePoles::DoSetGrid(std::vector<Pole*>& poles, uint16_t frame) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    poles[pole]->SetGridLights(
        controlPoles[pole].GetGrid(frame, lastFrame, false));
  }
  lastFrame = frame;
}

/**
 * Change the mode (grid animation).
 */
void HuePoles::UpdateOption1() {}

void HuePoles::UpdateOption2() {
  smoothColor = !smoothColor;
  for (auto& pole : controlPoles) {
    pole.SetSmoothColor(smoothColor);
  }
}

/**
 * Chages Speed
 */
void HuePoles::UpdateSlider1(uint8_t val) {
  val = val / 64;

  for (auto& pole : controlPoles) {
    switch (val) {
      case 0:
        pole.SetShiftSpeed(Speed::kStill);
        break;
      case 1:
        pole.SetShiftSpeed(Speed::kHalf);
      case 3:
        pole.SetShiftSpeed(Speed::kDouble);
      default:
        pole.SetShiftSpeed(Speed::kDefault);
    }
  }
}

/**
 * Change color shift.
 */
void HuePoles::UpdateSlider2(uint8_t val) {
  for (auto& pole : controlPoles) {
    pole.SetHueShift(val / 5);
  }
}

void HuePoles::DoShift(uint8_t shiftPosition) {}

void HuePoles::ResetEffect() {
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles[i].SetMode(modes[0]);
    controlPoles[i].SetBackAndForth(true);
    controlPoles[i].SetSmoothColor(true);
    controlPoles[i].SetLightCount(2);
    controlPoles[i].SetHue(43 * i);
  }
}