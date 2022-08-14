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
  void SetHues(uint8_t sat);
  void SetBackAndForth();
  void ResetModes();
  void UpdateWhite(uint16_t frame, bool flipHue);
  void UpdateColor(uint16_t frame);

  std::vector<ControlPole> controlPoles;

  bool increaseSat = false;
  uint8_t baseHue = 0;

  const uint8_t kValAtSat0 = 160;

  bool white = true;

  uint8_t leftPole = 0;

  Mode modes[2] = {Mode::kCircle, Mode::kSmallSquare};
  uint8_t modeIndex = 1;
  const uint8_t kNumModes = 2;
  bool smoothPoleShift = true;
};
