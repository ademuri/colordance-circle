#ifndef BACK_AND_FORTH_HPP_
#define BACK_AND_FORTH_HPP_

#include <vector>

#include "ColordanceTypes.hpp"
#include "Pole.hpp"
#include "control-pole/ControlPole.hpp"
#include "interface/InterfaceEffect.hpp"

class BackAndForth : public InterfaceEffect {
 public:
  BackAndForth(std::vector<HelperPole*> const & helperPoles);

 protected:
  bool ContinuousShift();
  void DoSetGrid(std::vector<Pole*> & poles, uint16_t frame) override;
  void UpdateOption1() override;
  void UpdateOption2() override;
  void UpdateSlider1(uint8_t val) override;
  void UpdateSlider2(uint8_t val) override;
  void DoShift(uint8_t shiftPosition) override;
  void Reset() override;

 private:
  void UpdateHues();
  void SetBackAndForth();

  uint32_t lastFrame = 0;

  ControlPole controlPoleLeft;
  ControlPole controlPoleRight;

  uint8_t leftIndex = 2;
  uint8_t rightIndex = 3;

  uint8_t modes[5] = {0, 2, 6, 10, 11};
  uint8_t modeIndex = 0;

  bool goIn = true;
  bool cross = false;

  bool smoothPoleShift = true;
};

#endif
