#ifndef CONTROL_POLE_EFFECT_DIVERGE_HPP_
#define CONTROL_POLE_EFFECT_DIVERGE_HPP_

#include <vector>

#include "ColordanceTypes.hpp"
#include "ControlPoleEffect.hpp"

class ControlPoleEffectDiverge : public ControlPoleEffect {
 public:
  ControlPoleEffectDiverge(uint16_t framesPerLoop);

 protected:
  void DoSetGrid(uint8_t shiftIndex) override;
  uint8_t GetShiftsPerLoop() override;
};

#endif
