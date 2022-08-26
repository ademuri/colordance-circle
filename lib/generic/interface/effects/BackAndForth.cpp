#include "BackAndForth.hpp"

#include "ColordanceTypes.hpp":

/**
 * @brief Effect with 2 opposing poles on.
 */
BackAndForth::BackAndForth()
    : InterfaceEffect(),
      controlPoles{ControlPole(FRAMES_PER_LOOP), ControlPole(FRAMES_PER_LOOP)},
      controlPoleLeft(controlPoles.data() + 0),
      controlPoleRight(controlPoles.data() + 1) {
  InitializeEffect();
}

void BackAndForth::DoUpdate(uint16_t frame, uint16_t lastFrame) {
  if (oscillateSat) {
    UpdateColor(frame);
  }
  controlPoleLeft->TurnOffAll();
  controlPoleRight->TurnOffAll();

  controlPoleLeft->UpdateGrid(frame, lastFrame, false);
  controlPoleRight->UpdateGrid(frame, lastFrame, false);
}

void BackAndForth::DoSetGrid(Poles& poles) {
  poles[leftIndex % 6].SetGridLights(controlPoleLeft->GetGrid());
  poles[rightIndex % 6].SetGridLights(controlPoleRight->GetGrid());
}

void BackAndForth::DoSetEffectButton(Buttons buttons, uint8_t buttonIndex) {
  buttons.SetButton(buttonIndex, leftIndex % 6,
                    CRGB(controlPoleLeft->GetHSV()));
  buttons.SetButton(buttonIndex, rightIndex % 6,
                    CRGB(controlPoleRight->GetHSV()));
}

void BackAndForth::DoSetOptionButtons(Buttons buttons) {
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

void BackAndForth::UpdateColor(uint16_t frame) {
  uint16_t effectiveBeatsPerShift = beatsPerShift != 0 ? beatsPerShift : 4;
  uint16_t shiftFrame = beatsSinceAutoShift * FRAMES_PER_LOOP + frame;
  uint16_t framesPerHalfShift = effectiveBeatsPerShift * FRAMES_PER_LOOP / 2;

  if (shiftFrame < framesPerHalfShift) {
    hueDistance = 255 * shiftFrame / framesPerHalfShift;
  } else {
    hueDistance =
        255 * (2 * framesPerHalfShift - shiftFrame) / framesPerHalfShift;
  }

  for (ControlPole& pole : controlPoles) {
    pole.SetHueDistance(hueDistance / 4);  // divide by light count
    pole.SetSat(255);
    pole.SetVal(255);
  }
}

/**
 * @brief Changes the grid effect.
 */
void BackAndForth::UpdateOption1() {
  modeIndex++;
  modeIndex %= kNumModes;
  controlPoleLeft->SetMode(modes[modeIndex]);
  controlPoleRight->SetMode(modes[modeIndex]);
  // controlPoleLeft->SetShiftSpeed(Speed::kDefault);
  // controlPoleRight->SetShiftSpeed(Speed::kDefault);
}

/**
 * @brief Fades the overall saturation in and out thoughout the shift.
 */
void BackAndForth::UpdateOption2() {
  oscillateSat = !oscillateSat;
  if (oscillateSat) {
    // Disable Slider2
  }
}

/**
 * @brief Changes the hue distance between the poles.
 * Goes from the same hue to opposing hues.
 */
void BackAndForth::UpdateSlider1(uint8_t val) {
  hueVal = val / 4;
  controlPoleLeft->SetHue(0 - hueVal);
  controlPoleRight->SetHue(hueVal);
}

/**
 * @brief Chages the hue distance of the grids.
 */
void BackAndForth::UpdateSlider2(uint8_t val) {
  if (oscillateSat) {
    return;
  }
  hueDistance = val / 4;
  controlPoleLeft->SetHueDistance(hueDistance);
  controlPoleRight->SetHueDistance(hueDistance);
}

void BackAndForth::DoAutomaticShift(bool didManual) {
  if (!didManual) {
    UpdateIndex();
  }
}

void BackAndForth::DoAutomaticPartialShift(uint8_t shiftFraction) {
  if (shiftFraction != 2) {
    return;
  }
  if (leftIndex == 0) {
    goIn = true;
  } else if (leftIndex == 2) {
    goIn = false;
  }
  controlPoleLeft->SetReverse(!goIn);
  controlPoleRight->SetReverse(goIn);
}

void BackAndForth::DoManualShift(bool didAutomatic) {
  if (!didAutomatic) {
    UpdateIndex();
  }
}

void BackAndForth::UpdateIndex() {
  if (goIn && rightIndex == 0 || !goIn && leftIndex == 0) {
    goIn = !goIn;
  }
  if (goIn) {
    leftIndex++;
    rightIndex--;
  } else {
    leftIndex--;
    rightIndex++;
  }
  controlPoleLeft->SetReverse(!goIn);
  controlPoleRight->SetReverse(goIn);
}

void BackAndForth::InitializeEffect() {
  controlPoleLeft->SetHue(0);
  controlPoleRight->SetHue(127);
  controlPoleLeft->SetReverse(!goIn);
  controlPoleRight->SetReverse(goIn);
  for (ControlPole& pole : controlPoles) {
    pole.SetShiftSpeed(Speed::kDefault);
    pole.SetLightCount(4);
    pole.SetSmoothColor(false);
    pole.SetBackAndForth(false);
    pole.ResetFade();
    pole.SetRotation(0);
    pole.SetMode(modes[modeIndex]);
  }
  option2Hue = 64;
}
