#pragma once

#include <array>

#include "Buttons.hpp"
#include "ColordanceTypes.hpp"
#include "Grid.hpp"
#include "Pole.hpp"
#include "control-pole/ControlPole.hpp"
#include "interface/InterfaceEffect.hpp"

class Sliders : public InterfaceEffect {
 public:
  Sliders();
  Sliders(Sliders const &) = delete;
  Sliders &operator=(Sliders const &) = delete;

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
  void UpdateGrid(Grid<CHSV> &pole, uint8_t position, uint8_t hue, uint8_t sat);

  void ResetModes();

  std::array<ControlPole, 2> poles;
  ControlPole *pole_left;
  ControlPole *pole_right;

  uint8_t count = 0;

  uint8_t leftIndex = 0;
  uint8_t rightIndex = 5;
  bool swap = false;

  uint8_t hueLeft = 0;
  uint8_t hueRight = 127;

  uint8_t modeLeft = 0;
  uint8_t modeRight = 0;

  uint8_t numOfPolesOn = 1;
  bool backAndForth = false;
  bool smoothPoleShift = false;
};
