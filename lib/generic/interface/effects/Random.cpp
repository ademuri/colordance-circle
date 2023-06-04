#include "Random.hpp"

#include "ColordanceTypes.hpp"

constexpr uint8_t kNumModes = 3;
constexpr std::array<Mode, kNumModes> modes = {Mode::kLine, Mode::kCircle,
                                               Mode::kSmallSquare};

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
    movingPoleIndex = (frame + lastFrame + controlPoles[0].GetHue()) % 6;
    controlPoles[movingPoleIndex].SetShiftSpeed(Speed::kDefault);
    doMove = false;
  }
  for (ControlPole& pole : controlPoles) {
    pole.UpdateGrid(frame, lastFrame, false);
  }
  previousFrame = frame;
}

void Random::DoSetGrid(Poles& poles) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    poles[pole].SetGridLights(controlPoles[pole].GetGrid());
  }
}

void Random::DoSetEffectButton(Buttons buttons, uint8_t buttonIndex) {
  for (int i = 0; i < Pole::kNumPoles; i++) {
    buttons.SetButton(buttonIndex, i,
                      CRGB(CHSV(controlPoles[i].GetHue(), 255, 150)));
  }
  buttons.SetButton(buttonIndex, movingPoleIndex,
                    CHSV(controlPoles[movingPoleIndex].GetHue(), 255,
                         previousFrame / FRAMES_PER_LOOP));
}

void Random::DoSetOptionButtons(Buttons buttons) {
  // Option 1
  uint8_t modeHue = modeIndex * (255 / kNumModes);
  for (int i = 0; i < 4; i++) {
    buttons.SetButton(7, i, CRGB(CHSV(modeHue, 255, 200)));
  }

  uint8_t baseHue = controlPoles[0].GetHue();
  // Option 2
  for (int i = 0; i < 4; i++) {
    buttons.SetButton(8, i, CRGB(CHSV(baseHue, 255, 200)));
  }

  // Slider 1
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
void Random::UpdateOption1() {
  modeIndex++;
  modeIndex %= kNumModes;
  for (ControlPole& pole : controlPoles) {
    pole.SetMode(modes[modeIndex]);
  }
}

void Random::UpdateOption2() {
  smoothColor = !smoothColor;
  for (ControlPole& pole : controlPoles) {
    pole.SetSmoothColor(smoothColor);
  }
}

/**
 * Change the number of poles on.
 */
void Random::UpdateSlider1(uint8_t val) {
  for (ControlPole& pole : controlPoles) {
    pole.SetHueShift(val / 10);
  }
}
/**
 * Changes the hue distance
 */
void Random::UpdateSlider2(uint8_t val) {
  hueDistance = val / 4;
  for (ControlPole& pole : controlPoles) {
    pole.SetHueDistance(hueDistance);
  }
}

void Random::DoAutomaticShift(bool didManual) {
  UNUSED(didManual);
  doMove = true;
}

void Random::DoAutomaticPartialShift(uint8_t shiftFraction) {
  UNUSED(shiftFraction);
  return;
}

void Random::DoManualShift(bool didAutomatic) {
  UNUSED(didAutomatic);
  doMove = true;
}

void Random::InitializeEffect() {
  uint8_t hue = 0;
  for (ControlPole& pole : controlPoles) {
    pole.SetMode(Mode::kLine);
    pole.SetHue(hue);
    pole.SetShiftSpeed(Speed::kStill);
    pole.SetShiftOffset(3);
    pole.ResetFade();
    pole.SetLightCount(2);
    pole.SetBackAndForth(false);
    pole.SetReverse(false);
    pole.SetSmoothColor(true);
    hue += 42;
  }
}
