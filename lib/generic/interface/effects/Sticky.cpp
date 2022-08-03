#include "Sticky.hpp"

#include "ColordanceTypes.hpp"

Sticky::Sticky() : InterfaceEffect(), moving_pole(FRAMES_PER_LOOP) {
  controlPoles.reserve(Pole::kNumPoles);
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles.emplace_back(FRAMES_PER_LOOP);
  }
  ResetEffect();
}

bool Sticky::ContinuousShift() { return false; }

void Sticky::DoSetGrid(Poles& poles, uint16_t frame, uint16_t lastFrame) {
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    controlPoles[pole].TurnOffAll();
    Grid<CHSV> const& grid = controlPoles[pole].GetGrid(
        frame, lastFrame, false);  // Update all grids
    poles[pole].SetGridLights(grid);
  }
  uint8_t moving_pole_index = 24 * frame / (FRAMES_PER_LOOP * beatsPerShift) +
                              24 * beatsSinceLastShift / beatsPerShift;
  moving_pole.SetShiftOffset(moving_pole_index % 4);
  Grid<CHSV> const& grid =
      moving_pole.GetGrid(frame, lastFrame, false);  // Update all grids
  poles[moving_pole_index / 4].MultiplyGridLights(grid);
}

/**
 * Change the mode (grid animation).
 */
void Sticky::UpdateOption1() {
  modeIndex++;
  modeIndex %= kNumModes;
  for (int i = 0; i < Pole::kNumPoles; i++) {
    controlPoles[i].SetMode(modes[modeIndex]);
  }
  ResetModes();
}

void Sticky::UpdateOption2() {
  still = !still;
  for (ControlPole& pole : controlPoles) {
    pole.SetShiftSpeed(still ? Speed::kStill : Speed::kDefault);
  }
}

/**
 * Change the number of poles on.
 */
void Sticky::UpdateSlider1(uint8_t val) {
  hueDistance = val / 6;
  UpdateHues();
}

void Sticky::UpdateHues() {
  uint8_t hue = 0;
  for (ControlPole& pole : controlPoles) {
    pole.SetHue(hue);
    hue += hueDistance;
  }
}
/**
 * Changes the hue distance
 */
void Sticky::UpdateSlider2(uint8_t val) {}

void Sticky::DoShift(uint8_t shiftPosition) {
  if (shiftPosition != 0) {
    return;
  }
}

void Sticky::ResetModes() {
  for (ControlPole& pole : controlPoles) {
    pole.ResetFade();
    pole.SetShiftOffset(0);
    pole.SetShiftSpeed(Speed::kDefault);
    pole.SetLightCount(1);
    pole.SetBackAndForth(true);
    pole.SetSmoothColor(true);
    pole.SetReverse(false);
    pole.SetRotation(0);
  }
}

void Sticky::ResetEffect() {
  poleOffset = 0;
  for (ControlPole& pole : controlPoles) {
    pole.ResetFade();
  }
  moving_pole.SetMode(Mode::kLine);
  moving_pole.SetLightCount(4);
  moving_pole.SetBackAndForth(false);
  moving_pole.SetShiftSpeed(Speed::kStill);
  ResetModes();
}
