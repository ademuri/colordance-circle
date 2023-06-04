#pragma once

#include "Buttons.hpp"
#include "ColordanceTypes.hpp"
#include "Pole.hpp"
#include "control-pole/ControlPole.hpp"
#include "interface/InterfaceEffect.hpp"

class Split : public InterfaceEffect {
 public:
  Split();

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
  void SetSplit();
  void UpdateColor(uint16_t frame);
  void UpdateIndex();

  std::array<ControlPole, 3> controlPoles;
  ControlPole *controlPoleLeft;
  ControlPole *controlPoleRight;
  ControlPole *controlPoleMiddle;

  uint8_t middleIndex = 0;

  uint8_t modeIndex = 0;
  uint8_t modeIndexMiddle = 0;
  const uint8_t kNumModes = 4;

  bool oscillateSat = false;
  bool increaseSat = false;

  bool goIn = true;
  bool leftReverse = true;
  bool rightReverse = false;
  uint8_t hueDistance = 127;
  uint8_t hueStart = 0;
  uint8_t hueVal = 0;

  uint8_t option2Hue = 64;
  uint8_t baseHue = 0;

  bool smoothPoleShift = true;
};
