#include "MovingPole.hpp"

#include "ColordanceTypes.hpp"

MovingPole::MovingPole()
    : InterfaceEffect(),
      movingPoles{ControlPole(FRAMES_PER_LOOP), ControlPole(FRAMES_PER_LOOP)},
      autoMovingPole(movingPoles.data() + 0),
      movingPole(movingPoles.data() + 1) {
  controlPoles.reserve(Pole::kNumPoles);
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles.emplace_back(FRAMES_PER_LOOP);
  }
  InitializeEffect();
}

void MovingPole::DoUpdate(uint16_t frame, uint16_t lastFrame) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    controlPoles[pole].TurnOffAll();
    controlPoles[pole].UpdateGrid(frame, lastFrame, false);
  }
  if (lastBeatsSinceAutoShift != beatsSinceAutoShift) {
    beatLoops++;
    beatLoops %= movingSpeed;
  }
  lastBeatsSinceAutoShift = beatsSinceAutoShift;
  uint8_t shiftsPerLoop = autoMovingPole->GetShiftsPerLoop();
  uint8_t effectiveBeatsPerShift = beatsPerShift * movingSpeed;
  if (beatsPerShift > 0) {
    autoMovingPoleIndex =
        (shiftsPerLoop * 6) * frame /
            (FRAMES_PER_LOOP * effectiveBeatsPerShift) +
        (shiftsPerLoop * 6) *
            (beatsSinceAutoShift + beatLoops * beatsPerShift) /
            effectiveBeatsPerShift;
    autoMovingPole->SetShiftOffset(autoMovingPoleIndex % shiftsPerLoop);
    autoMovingPole->UpdateGrid(frame, lastFrame, false);
    autoMovingPoleIndex /= shiftsPerLoop;
  }

  // if (frame < lastFrame && movingPoleIndex < 6) {
  //   movingPoleIndex++;
  // }
  // if (movingPoleIndex < 6) {
  //   movingPole->UpdateGrid(frame, lastFrame, false);
  // }
  baseHue += 5;
  currentFrame = frame;
}

void MovingPole::DoSetGrid(Poles& poles) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    poles[pole].SetGridLights(controlPoles[pole].GetGrid());
  }
  if (beatsPerShift > 0) {
    poles[autoMovingPoleIndex % 6].SetGridLights(autoMovingPole->GetGrid());
  }
  // if (movingPoleIndex < 6) {
  //   poles[movingPoleIndex].SetGridLights(movingPole->GetGrid());
  // }
}

void MovingPole::DoSetEffectButton(Buttons buttons, uint8_t buttonIndex) {
  for (int i = 0; i < Pole::kNumPoles; i++) {
    buttons.SetButton(buttonIndex, i,
                      CRGB(CHSV(controlPoles[i].GetHue(), 255, 100)));
  }
  if (beatsPerShift > 0) {
    buttons.SetButton(buttonIndex, autoMovingPoleIndex % 6,
                      CRGB(autoMovingPole->GetHSV()));
  }
  // if (movingPoleIndex < 6) {
  //   buttons.SetButton(buttonIndex, movingPoleIndex,
  //   CRGB(movingPole->GetHSV()));
  // }
}

void MovingPole::DoSetOptionButtons(Buttons buttons) {
  // Option 1
  uint8_t modeHue = modeIndex * (255 / kNumModes);
  for (int i = 0; i < 4; i++) {
    buttons.SetButton(7, i, CRGB(CHSV(modeHue, 255, 200)));
  }

  // Option 2
  uint8_t baseHue = movingPole->GetHue();
  for (int i = 0; i < 4; i++) {
    if (still) {
      buttons.SetButton(8, 1, CRGB(CHSV(baseHue, 255, 255)));
    } else {
      buttons.SetButton(8, 4 * currentFrame / FRAMES_PER_LOOP,
                        CRGB(CHSV(baseHue + hueDistance * i, 255, 200)));
    }
  }

  // Slider 1
  for (int i = 0; i < 3; i++) {
    buttons.SetButton(12, i, CRGB(CHSV(baseHue + hueDistance * i, 255, 255)));
  }

  // Slider 2
  for (int i = 0; i < 3; i++) {
    buttons.SetButton(13, i, CRGB(CHSV(movingSpeed255, 255, 200)));
  }
}

/**
 * Change the mode (grid animation).
 */
void MovingPole::UpdateOption1() {
  modeIndex++;
  modeIndex %= kNumModes;
  for (ControlPole& pole : controlPoles) {
    pole.SetMode(modes[modeIndex]);
    pole.SetShiftSpeed(speeds[modeIndex]);
    pole.SetRotation(rotations[modeIndex]);
  }
}

void MovingPole::UpdateOption2() {
  still = !still;
  for (ControlPole& pole : controlPoles) {
    pole.SetShiftSpeed(still ? Speed::kStill : Speed::kDefault);
  }
}

/**
 * Change the number of poles on.
 */
void MovingPole::UpdateSlider1(uint8_t val) {
  hueDistance = val / 6;
  for (ControlPole& pole : controlPoles) {
    pole.SetHueDistance(hueDistance);
  }
}

/**
 * Changes the hue distance
 */
void MovingPole::UpdateSlider2(uint8_t val) {
  movingSpeed255 = val;
  movingSpeed = (255 - val) / 52 + 1;
}

void MovingPole::DoAutomaticShift(bool didManual) {
  autoMovingPole->SetHue(baseHue + 127);
}

void MovingPole::DoAutomaticPartialShift(uint8_t shiftFraction) { return; }

void MovingPole::DoManualShift(bool didAutomatic) {
  if (!didAutomatic && movingPoleIndex == 6) {
    movingPoleIndex = 0;
    movingPole->SetHue(baseHue + 127);
  }
}

void MovingPole::InitializeEffect() {
  poleOffset = 0;
  for (ControlPole& pole : controlPoles) {
    pole.SetMode(Mode::kLine);
    pole.SetShiftSpeed(Speed::kStill);
    pole.SetShiftOffset(3);
    pole.ResetFade();
    pole.SetLightCount(1);
    pole.SetBackAndForth(false);
    pole.SetReverse(false);
    pole.SetSmoothColor(true);
  }
  for (ControlPole& pole : movingPoles) {
    pole.SetMode(Mode::kLine);
    pole.SetShiftSpeed(Speed::kOffset);
    pole.SetLightCount(3);
    pole.SetBackAndForth(false);
    pole.SetHueShift(0);
    pole.SetHueDistance(0);
  }
}
