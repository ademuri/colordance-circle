#include "Split.hpp"

#include "ColordanceTypes.hpp"

Split::Split() : InterfaceEffect() {
  controlPoles.reserve(Pole::kNumPoles);
  for (int i = 0; i < 2; i++) {
    controlPoles.emplace_back(FRAMES_PER_LOOP);
  }
  InitializeEffect();
}

void Split::DoUpdate(uint16_t frame, uint16_t lastFrame) {
  for (ControlPole& pole : controlPoles) {
    pole.TurnOffAll();
  }

  bool flipHue = false;
  if (lastFrame > frame) {
    increaseSat = !increaseSat;
    if (increaseSat) {
      flipHue = true;
    }
  }

  if (white) {
    UpdateWhite(frame, flipHue);
  } else {
    UpdateColor(frame);
  }

  controlPoles[0].UpdateGrid(frame, lastFrame, true);
  controlPoles[1].UpdateGrid(frame, lastFrame, true);
}

void Split::DoSetGrid(Poles& poles) {
  poles[leftPole].SetGridLights(controlPoles[0].GetGrid());
  poles[5 - leftPole].SetGridLights(controlPoles[1].GetGrid());
}

void Split::DoSetEffectButton(Buttons buttons, uint8_t buttonIndex) {}

void Split::DoSetOptionButtons(Buttons buttons) {}

void Split::UpdateWhite(uint16_t frame, bool flipHue) {
  uint8_t sat = 255 * frame / FRAMES_PER_LOOP;
  if (!increaseSat) {
    sat = 255 - sat;
  }
  uint8_t val = (sat * (255 - kValAtSat0) / 255) + kValAtSat0;
  for (ControlPole& pole : controlPoles) {
    if (flipHue) {
      pole.IncrementHue(127);
    }
    pole.SetHueDistance(0);
    pole.SetSat(sat);
    pole.SetVal(val);
  }
}

void Split::UpdateColor(uint16_t frame) {
  uint8_t hueDistance = (255 * frame / FRAMES_PER_LOOP) / 4;
  if (increaseSat) {
    hueDistance = 255 / 4 - hueDistance;
  }
  for (ControlPole& pole : controlPoles) {
    pole.SetHueDistance(hueDistance);
    pole.SetSat(255);
    pole.SetVal(255);
  }
}

/**
 * Change the mode (grid animation).
 */
void Split::UpdateOption1() { white = !white; }

void Split::UpdateOption2() {}

/**
 * Change the Hue
 */
void Split::UpdateSlider1(uint8_t val) {}

void Split::SetHues(uint8_t sat) {}

/**
 * Changes the hue shift
 */
void Split::UpdateSlider2(uint8_t val) {}

void Split::DoAutomaticShift(bool didManual) {
  // leftPole++;
}

void Split::DoAutomaticPartialShift(uint8_t shiftFraction) { return; }

void Split::DoManualShift(bool didAutomatic) {}

void Split::ResetModes() {
  for (ControlPole& pole : controlPoles) {
    pole.SetShiftSpeed(Speed::kStill);
    pole.ResetFade();
    pole.SetLightCount(4);
    pole.SetBackAndForth(false);
    pole.SetSmoothColor(true);
    pole.SetReverse(false);
    pole.SetRotation(0);
    pole.SetHueShift(16);
    pole.SetGridFade(0);
  }
  controlPoles[0].SetHue(baseHue);
  controlPoles[1].SetHue(baseHue + 127);
}

void Split::InitializeEffect() {
  for (ControlPole& pole : controlPoles) {
    pole.SetMode(modes[modeIndex]);
    pole.ResetFade();
  }
  ResetModes();
}
