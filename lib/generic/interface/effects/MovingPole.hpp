#pragma once

#include <vector>

#include "Buttons.hpp"
#include "ColordanceTypes.hpp"
#include "Pole.hpp"
#include "control-pole/ControlPole.hpp"
#include "interface/InterfaceEffect.hpp"

class MovingPole : public InterfaceEffect {
 public:
  MovingPole();

 protected:
  void DoUpdate(uint16_t frame, uint16_t lastFrame) override;
  void DoSetGrid(Poles &poles) override;
  void DoSetEffectButton(Buttons buttons, uint8_t buttonIndex) override;
  void DoSetOptionButtons(Buttons buttons) override;
  void UpdateOption1() override;
  void UpdateOption2() override;
  void UpdateSlider1(uint8_t val) override;
  void UpdateSlider2(uint8_t val) override;
  void DoAutomaticShift(bool didManual) override;
  void DoAutomaticPartialShift(uint8_t shiftFraction) override;
  void DoManualShift(bool didAutomatic) override;
  void InitializeEffect() override;

 private:
  void UpdateHues();

  std::vector<ControlPole> controlPoles;

  std::array<ControlPole, 2> movingPoles;
  ControlPole *autoMovingPole;
  ControlPole *movingPole;
  uint8_t movingPoleIndex = 0;
  uint8_t autoMovingPoleIndex = 0;

  uint8_t poleOffset = 0;
  bool goBackwards = false;

  bool still = false;

  uint8_t baseHue = 0;
  uint8_t hueDistance = 42;

  Mode modes[5] = {Mode::kLine, Mode::kLine, Mode::kCircle, Mode::kPinwheel,
                   Mode::kSmallSquare};
  Speed speeds[5] = {Speed::kDefault, Speed::kStill, Speed::kDefault,
                     Speed::kDefault, Speed::kDefault};
  uint8_t rotations[5] = {0, 2, 0, 0, 0};
  uint8_t modeIndex = 0;
  const uint8_t kNumModes = 5;

  uint8_t numOfPolesOn = 6;
  bool backAndForth = true;
  bool smoothPoleShift = true;

  uint8_t movingSpeed = 0;
  uint8_t movingSpeed255 = 0;
  uint8_t beatLoops = 0;
  uint8_t lastBeatsSinceAutoShift = 0;

  uint8_t currentFrame = 0;
};
