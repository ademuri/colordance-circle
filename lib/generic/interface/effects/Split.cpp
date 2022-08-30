#include "Split.hpp"

#include "ColordanceTypes.hpp"

/**
 * @brief Effect with 2 opposing poles on. DONE
 */
Split::Split()
    : InterfaceEffect(),
      controlPoles{ControlPole(FRAMES_PER_LOOP), ControlPole(FRAMES_PER_LOOP),
                   ControlPole(FRAMES_PER_LOOP)},
      controlPoleLeft(controlPoles.data() + 0),
      controlPoleRight(controlPoles.data() + 1),
      controlPoleMiddle(controlPoles.data() + 2) {
  InitializeEffect();
}

void Split::DoUpdate(uint16_t frame, uint16_t lastFrame) {
  controlPoleLeft->TurnOffAll();
  controlPoleRight->TurnOffAll();
  controlPoleMiddle->TurnOffAll();

  controlPoleLeft->UpdateGrid(frame, lastFrame, false);
  controlPoleRight->UpdateGrid(frame, lastFrame, false);
  controlPoleMiddle->UpdateGrid(frame, lastFrame, false);
}

void Split::DoSetGrid(Poles& poles) {
  poles[0].SetGridLights(controlPoleLeft->GetGrid());
  poles[5].SetGridLights(controlPoleRight->GetGrid());
  uint8_t effectiveMiddleIndex =
      middleIndex > 3 ? 7 - middleIndex : middleIndex + 1;
  poles[effectiveMiddleIndex].SetGridLights(controlPoleMiddle->GetGrid());
}

void Split::DoSetEffectButton(Buttons buttons, uint8_t buttonIndex) {
  buttons.SetButton(buttonIndex, 0, CRGB(controlPoleLeft->GetHSV()));
  buttons.SetButton(buttonIndex, 5, CRGB(controlPoleRight->GetHSV()));
  uint8_t effectiveMiddleIndex =
      middleIndex > 3 ? 7 - middleIndex : middleIndex + 1;
  buttons.SetButton(buttonIndex, effectiveMiddleIndex,
                    CRGB(controlPoleMiddle->GetHSV()));
}

void Split::DoSetOptionButtons(Buttons buttons) {
  // Option 1
  uint8_t modeHue = modeIndex * (255 / kNumModes);
  for (int i = 0; i < 4; i++) {
    buttons.SetButton(7, i, CRGB(CHSV(modeHue, 255, 200)));
  }

  uint8_t baseHue = controlPoleLeft->GetHue();
  // Option 2
  for (int i = 0; i < 4; i++) {
    if (oscillateSat) {
      buttons.SetButton(8, i, CRGB(CHSV(baseHue + hueDistance * i, 255, 200)));
    } else {
      buttons.SetButton(8, i, CRGB(CHSV(baseHue + hueDistance * i, 255, 200)));
    }
  }

  // Slider 1
  buttons.SetButton(12, 0, CRGB(controlPoleLeft->GetHSV()));
  buttons.SetButton(12, 2, CRGB(controlPoleRight->GetHSV()));

  // Slider 2
  if (!oscillateSat) {
    for (int i = 0; i < 3; i++) {
      buttons.SetButton(13, i, CRGB(CHSV(baseHue + hueDistance * i, 255, 255)));
    }
  }
}

/**
 * @brief Changes the grid effect.
 */
void Split::UpdateOption1() {
  modeIndexMiddle++;
  modeIndexMiddle %= kNumModes;
  controlPoleMiddle->SetMode(middleModes[modeIndexMiddle]);
}

/**
 * @brief
 */
void Split::UpdateOption2() {
  modeIndex++;
  modeIndex %= 5;
  controlPoleLeft->SetMode(modes[modeIndex]);
  controlPoleLeft->SetShiftSpeed(speeds[modeIndex]);
  controlPoleLeft->SetRotation(rotations[modeIndex]);
  controlPoleRight->SetMode(modes[modeIndex]);
  controlPoleRight->SetShiftSpeed(speeds[modeIndex]);
  controlPoleRight->SetRotation(rotations[modeIndex]);
}

/**
 * @brief Changes the hue distance between the poles.
 * Goes from the same hue to opposing hues.
 */
void Split::UpdateSlider1(uint8_t val) {
  controlPoleMiddle->SetHueShift(val / 10);
}

/**
 * @brief Chages the hue distance of the grids.
 */
void Split::UpdateSlider2(uint8_t val) { controlPoleMiddle->SetHue(val / 6); }

void Split::DoAutomaticShift(bool didManual) {
  if (!didManual) {
    middleIndex++;
    middleIndex %= 6;
  }
}

void Split::DoAutomaticPartialShift(uint8_t shiftFraction) {}

void Split::DoManualShift(bool didAutomatic) {
  if (!didAutomatic) {
    middleIndex++;
    middleIndex %= 6;
  }
}

void Split::InitializeEffect() {
  for (ControlPole& pole : controlPoles) {
    pole.SetMode(modes[modeIndex]);
    pole.SetHue(baseHue);
    pole.SetShiftSpeed(Speed::kStill);
    pole.SetLightCount(2);
    pole.SetSmoothColor(false);
    pole.SetBackAndForth(false);
    pole.ResetFade();
    pole.SetRotation(0);
    pole.SetHueShift(10);
    controlPoleRight->SetReverse(false);
  }
  controlPoleMiddle->SetMode(modes[modeIndex]);
  controlPoleMiddle->SetShiftSpeed(Speed::kDefault);
  controlPoleMiddle->SetHue(baseHue + 127);
  controlPoleMiddle->SetLightCount(4);
  controlPoleMiddle->SetReverse(true);
}
