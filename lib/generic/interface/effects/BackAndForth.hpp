#pragma once

#include "ColordanceTypes.hpp"
#include "Pole.hpp"
#include "control-pole/ControlPole.hpp"
#include "interface/InterfaceEffect.hpp"

class BackAndForth : public InterfaceEffect {
 public:
  BackAndForth();

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
  void SetBackAndForth();
  void ResetModes();

  ControlPole controlPoleLeft;
  ControlPole controlPoleRight;

  uint8_t leftIndex = 2;
  uint8_t rightIndex = 3;

  Mode modes[4] = {Mode::kLine, Mode::kCircle, Mode::kPinwheel, Mode::kDiverge};
  uint8_t modeIndex = 0;
  const uint8_t kNumModes = 3;

  bool goIn = true;
  bool leftReverse = true;
  bool rightReverse = false;
  uint8_t hueDistance = 127;
  uint8_t hueStart = 0;
  uint8_t hueVal = 0;

  bool smoothPoleShift = true;
};
