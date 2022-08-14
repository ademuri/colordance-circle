#pragma once

#include <vector>

#include "ColordanceTypes.hpp"
#include "Pole.hpp"
#include "control-pole/ControlPole.hpp"
#include "interface/InterfaceEffect.hpp"

class SideToSide : public InterfaceEffect {
 public:
  SideToSide();

 protected:
  void DoSetGrid(Poles& poles, uint16_t frame, uint16_t lastFrame) override;
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
  void SetBackAndForth();
  void ResetModes();

  std::vector<ControlPole> controlPoles;

  uint8_t poleOffset = 0;
  bool goBackwards = false;

  Mode modes[3] = {Mode::kLine, Mode::kCircle, Mode::kPinwheel};
  uint8_t modeIndex = 0;
  const uint8_t kNumModes = 3;
  uint8_t numOfPolesOn = 1;
  bool backAndForth = true;
  bool smoothPoleShift = true;
};
