#pragma once

#include <array>
#include <vector>

#include "ColordanceTypes.hpp"
#include "Pole.hpp"
#include "control-pole/ControlPole.hpp"
#include "interface/InterfaceEffect.hpp"

class Sliders : public InterfaceEffect {
 public:
  Sliders();
  Sliders(Sliders const &) = delete;
  Sliders &operator=(Sliders const &) = delete;

 protected:
  bool ContinuousShift() override;
  void DoSetGrid(std::vector<Pole> &poles, uint16_t frame) override;
  void UpdateOption1() override;
  void UpdateOption2() override;
  void UpdateSlider1(uint8_t val) override;
  void UpdateSlider2(uint8_t val) override;
  void DoShift(uint8_t shiftPosition) override;
  void ResetEffect() override;

 private:
  void UpdateGrid(std::vector<std::vector<CHSV>> &pole, uint8_t position,
                  uint8_t hue, uint8_t sat);

  void ResetModes();

  std::array<ControlPole, 2> poles;
  ControlPole *pole_left;
  ControlPole *pole_right;

  uint32_t lastFrame = 0;

  uint8_t count = 0;

  uint8_t leftIndex = 0;
  uint8_t rightIndex = 5;
  bool swap = false;

  uint8_t hueLeft = 0;
  uint8_t hueRight = 127;

  uint8_t mode = 0;
  Mode modesLeft[3] = {Mode::kSmallSquare, Mode::kCircle, Mode::kLine};
  Mode modesRight[3] = {Mode::kCorners, Mode::kCircle, Mode::kLine};
  const uint8_t kNumModes = 3;

  uint8_t numOfPolesOn = 1;
  bool backAndForth = false;
  bool smoothPoleShift = false;
};
