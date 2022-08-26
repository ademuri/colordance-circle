#pragma once

#include <vector>

#include "Buttons.hpp"
#include "ColordanceTypes.hpp"
#include "Pole.hpp"
#include "control-pole/ControlPole.hpp"
#include "interface/InterfaceEffect.hpp"

class HuePoles : public InterfaceEffect {
 public:
  HuePoles();

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
  void SetBackAndForth();

  void ResetModes();
  std::vector<ControlPole> controlPoles;

  uint8_t poleOffset = 0;
  bool goBackwards = false;
  bool smoothColor = true;
  bool still = true;
  uint8_t hueOffset = 0;

  Mode modes[4] = {Mode::kLine, Mode::kCircle, Mode::kDiverge,
                   Mode::kSmallSquare};
  uint8_t modeIndex = 0;
  const uint8_t kNumModes = 4;
  bool backAndForth = true;
  bool smoothPoleShift = true;

  uint8_t shiftIndex = 0;
  uint8_t hueDistance = 0;
};
