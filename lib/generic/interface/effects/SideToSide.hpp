#ifndef SIDE_TO_SIDE_HPP_
#define SIDE_TO_SIDE_HPP_

#include <vector>

#include "ColordanceTypes.hpp"
#include "Pole.hpp"
#include "control-pole/ControlPole.hpp"
#include "interface/InterfaceEffect.hpp"

class SideToSide : public InterfaceEffect {
 public:
  SideToSide(std::vector<HelperPole*> helperPoles);

 protected:
  bool ContinuousShift();
  void DoSetGrid(std::vector<Pole*> poles, uint16_t frame) override;
  void UpdateOption1() override;
  void UpdateOption2() override;
  void UpdateSlider1(uint8_t val) override;
  void UpdateSlider2(uint8_t val) override;
  void DoShift(uint8_t shiftPosition) override;
  void Reset() override;

 private:
  void UpdateHues();
  void SetBackAndForth();

  std::vector<ControlPole*> controlPoles;
  uint32_t lastFrame = 0;

  uint8_t poleOffset = 0;
  bool goBackwards = false;

  uint8_t modes[5] = {0, 2, 6, 10, 11};
  uint8_t modeIndex = 0;
  uint8_t numOfPolesOn = 1;
  bool backAndForth = true;
  bool smoothPoleShift = true;
};

#endif
