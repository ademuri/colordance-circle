#ifndef CONTROL_POLE_EFFECT_STATIC_HPP_
#define CONTROL_POLE_EFFECT_STATIC_HPP_

#include <vector>

#include "ColordanceTypes.hpp"
#include "ControlPoleEffect.hpp"

class ControlPoleEffectStatic : public ControlPoleEffect {
 public:
  ControlPoleEffectStatic();

 protected:
  void DoSetGrid(uint8_t shiftIndex) override;
  uint8_t GetShiftsPerLoop() override;
};

#endif
