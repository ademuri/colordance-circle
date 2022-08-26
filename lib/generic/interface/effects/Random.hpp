#pragma once

#include <vector>

#include "Buttons.hpp"
#include "ColordanceTypes.hpp"
#include "Pole.hpp"
#include "control-pole/ControlPole.hpp"
#include "interface/InterfaceEffect.hpp"

class Random : public InterfaceEffect {
 public:
  Random();

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

  uint8_t movingPoleIndex = 0;

  uint8_t poleOffset = 0;
  bool goBackwards = false;

  bool doMove = true;
  bool still = false;

  uint8_t baseHue = 0;
  uint8_t hueDistance = 42;

  uint8_t numOfPolesOn = 6;
  bool backAndForth = true;
  bool smoothPoleShift = true;
};
