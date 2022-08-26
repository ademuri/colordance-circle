#include "Random.hpp"

#include "ColordanceTypes.hpp"

Random::Random() : InterfaceEffect() {
  controlPoles.reserve(Pole::kNumPoles);
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles.emplace_back(FRAMES_PER_LOOP);
  }
  InitializeEffect();
}

void Random::DoUpdate(uint16_t frame, uint16_t lastFrame) {
  if (doMove) {
    controlPoles[movingPoleIndex].SetShiftSpeed(Speed::kStill);
    movingPoleIndex = frame % 6;
    controlPoles[movingPoleIndex].SetShiftSpeed(Speed::kDefault);
  }
}

void Random::DoSetGrid(Poles& poles) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    poles[pole].SetGridLights(controlPoles[pole].GetGrid());
  }
}

void Random::DoSetEffectButton(Buttons buttons, uint8_t buttonIndex) {
  // for (int i = 0; i < Pole::kNumPoles; i++) {
  //   buttons.SetButton(buttonIndex, i,
  //   CRGB(CHSV(controlPoles[i].GetHue(),255,100)));
  // }
}

void Random::DoSetOptionButtons(Buttons buttons) {}

/**
 * Change the mode (grid animation).
 */
void Random::UpdateOption1() {}

void Random::UpdateOption2() {
  // still = !still;
  // for (ControlPole& pole : controlPoles) {
  //   pole.SetShiftSpeed(still ? Speed::kStill : Speed::kDefault);
  // }
}

/**
 * Change the number of poles on.
 */
void Random::UpdateSlider1(uint8_t val) {
  // hueDistance = val / 6;
  // UpdateHues();
}

void Random::UpdateHues() {
  // uint8_t hue = baseHue;
  // for (ControlPole& pole : controlPoles) {
  //   pole.SetHue(hue);
  //   hue += hueDistance;
  // }
}
/**
 * Changes the hue distance
 */
void Random::UpdateSlider2(uint8_t val) {}

void Random::DoAutomaticShift(bool didManual) { doMove = true; }

void Random::DoAutomaticPartialShift(uint8_t shiftFraction) { return; }

void Random::DoManualShift(bool didAutomatic) { doMove = true; }

void Random::InitializeEffect() {
  poleOffset = 0;
  for (ControlPole& pole : controlPoles) {
    pole.SetMode(Mode::kLine);
    pole.SetShiftSpeed(Speed::kStill);
    pole.SetShiftOffset(3);
    pole.ResetFade();
    pole.SetLightCount(2);
    pole.SetBackAndForth(false);
    pole.SetReverse(false);
    pole.SetSmoothColor(true);
  }
}
