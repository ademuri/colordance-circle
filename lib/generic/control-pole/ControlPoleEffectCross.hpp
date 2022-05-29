#ifndef CONTROL_POLE_EFFECT_CROSS_HPP_
#define CONTROL_POLE_EFFECT_CROSS_HPP_

#include <vector>

#include "ColordanceTypes.hpp"
#include "ControlPoleEffect.hpp"

class ControlPoleEffectCross : public ControlPoleEffect {
 public:
  ControlPoleEffectCross();

 protected:
  void DoSetGrid(uint8_t shiftIndex) override;
  uint8_t GetShiftsPerLoop() override;
};

#endif
