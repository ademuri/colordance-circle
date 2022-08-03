#pragma once

#include <vector>

#include "ColordanceTypes.hpp"
#include "Pole.hpp"
#include "control-pole/ControlPole.hpp"
#include "interface/InterfaceEffect.hpp"

class Sticky : public InterfaceEffect {
 public:
  Sticky();

 protected:
  bool ContinuousShift();
  void DoSetGrid(Poles& poles, uint16_t frame, uint16_t lastFrame) override;
  void UpdateOption1() override;
  void UpdateOption2() override;
  void UpdateSlider1(uint8_t val) override;
  void UpdateSlider2(uint8_t val) override;
  void DoShift(uint8_t shiftPosition) override;
  void ResetEffect() override;

 private:
  void UpdateHues();
  void ResetModes();

  std::vector<ControlPole> controlPoles;
  ControlPole moving_pole;

  uint8_t poleOffset = 0;
  bool goBackwards = false;

  const uint8_t kNumModes = 3;
  Mode modes[3] = {Mode::kLine, Mode::kCircle, Mode::kPinwheel};
  uint8_t modeIndex = 0;

  bool still = false;

  uint8_t hueDistance = 42;

  uint8_t numOfPolesOn = 6;
  bool backAndForth = true;
  bool smoothPoleShift = true;
};
