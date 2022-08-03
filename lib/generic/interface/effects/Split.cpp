#include "Split.hpp"

#include <iostream>

#include "ColordanceTypes.hpp"

Split::Split() : InterfaceEffect() {
  controlPoles.reserve(Pole::kNumPoles);
  for (int i = 0; i < 4; i++) {
    controlPoles.emplace_back(FRAMES_PER_LOOP);
  }
  ResetEffect();
}

bool Split::ContinuousShift() { return true; }

/**
 * 0: 0 1 2 3 -> 2
 * 1: 0 1 -> 1 : 2 3 -> 4
 * 2: 0 -> 0 : 1 -> 2 : 2 -> 3 : 3 -> 5
 */
void Split::DoSetGrid(Poles& poles, uint16_t frame, uint16_t lastFrame) {
  /* 0: 0 -> 127, 1: 127 -> 256, 2: 256 -> 127, 3: 127 -> 0 */
  uint8_t sat = 127 * frame / (FRAMES_PER_LOOP * beatsPerShift) +
                127 * beatsSinceLastShift / beatsPerShift;
  if (loopFrame > 1) {
    sat = 127 - sat;
  }
  if (loopFrame == 1 || loopFrame == 2) {
    sat += 128;
  }
  SetHues(sat);

  for (ControlPole& pole : controlPoles) {
    pole.TurnOffAll();
  }

  for (int controlPole = 0; controlPole < 4; controlPole++) {
    Grid<CHSV> const& grid = controlPoles[controlPole].GetGrid(
        frame, lastFrame, true);  // Update all grids
    uint8_t pole = 2 + startOffset;
    if (loopFrame == 1 || loopFrame == 3) {
      pole = controlPole < 2 ? 1 : 4;
    } else if (loopFrame == 2) {
      pole = controlPole == 0 ? 0 : controlPole == 3 ? 5 : controlPole + 1;
    }
    poles[pole].MultiplyGridLights(grid);
  }
}

/**
 * Change the mode (grid animation).
 */
void Split::UpdateOption1() {
  modeIndex++;
  modeIndex %= kNumModes;
  for (ControlPole& pole : controlPoles) {
    pole.SetMode(modes[modeIndex]);
  }
  ResetModes();
}

void Split::UpdateOption2() {}

/**
 * Change the Hue
 */
void Split::UpdateSlider1(uint8_t val) { baseHue = val; }

void Split::SetHues(uint8_t sat) {
  uint8_t distance = sat / 8;
  controlPoles[0].SetHue(baseHue - distance * 2);
  controlPoles[1].SetHue(baseHue - distance);
  controlPoles[2].SetHue(baseHue + distance);
  controlPoles[3].SetHue(baseHue + distance * 2);
}

/**
 * Changes the hue shift
 */
void Split::UpdateSlider2(uint8_t val) {}

void Split::DoShift(uint8_t shiftPosition) {
  if (shiftPosition != 0) {
    return;
  }
  loopFrame++;
  loopFrame %= 4;
  if (loopFrame == 0) {
    startOffset = !startOffset;
  }
}

void Split::ResetModes() {
  for (int i = 0; i < 4; i++) {
    ControlPole& pole = controlPoles[i];
    pole.SetShiftSpeed(Speed::kDefault);
    if (modes[modeIndex] == Mode::kSmallSquare) {
      pole.SetShiftSpeed(Speed::kStill);
    }
    pole.ResetFade();
    pole.SetShiftOffset(i);
    pole.SetLightCount(1);
    pole.SetBackAndForth(false);
    pole.SetSmoothColor(true);
    pole.SetReverse(false);
    pole.SetRotation(0);
    pole.SetHueShift(0);
    pole.SetGridFade(0);
  }
}

void Split::ResetEffect() {
  poleOffset = 0;
  for (ControlPole& pole : controlPoles) {
    pole.SetMode(modes[modeIndex]);
    pole.ResetFade();
  }
  ResetModes();
}
