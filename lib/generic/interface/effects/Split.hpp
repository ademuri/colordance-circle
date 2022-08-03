#pragma once

#include <vector>

#include "ColordanceTypes.hpp"
#include "Pole.hpp"
#include "control-pole/ControlPole.hpp"
#include "interface/InterfaceEffect.hpp"

class Split : public InterfaceEffect {
 public:
  Split();

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
  void SetHues(uint8_t sat);
  void SetBackAndForth();
  void ResetModes();

  std::vector<ControlPole> controlPoles;

  bool startOffset = 0;
  uint8_t loopFrame = 0;
  uint8_t baseHue = 0;
  uint8_t maxSat = 127;

  bool goBackwards = false;

  uint8_t poleOffset = 0;

  Mode modes[2] = {Mode::kCircle, Mode::kSmallSquare};
  uint8_t modeIndex = 0;
  const uint8_t kNumModes = 2;
  bool backAndForth = true;
  bool smoothPoleShift = true;
};
