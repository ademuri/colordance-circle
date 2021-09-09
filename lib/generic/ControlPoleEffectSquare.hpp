#ifndef CONTROL_POLE_EFFECT_SQUARE_HPP_
#define CONTROL_POLE_EFFECT_SQUARE_HPP_

#include <vector>

#include "ColordanceTypes.hpp"
#include "ControlPoleEffect.hpp"

class ControlPoleEffectSquare : public ControlPoleEffect {
 public:
  ControlPoleEffectSquare(uint16_t framesPerLoop);

 protected:
  void DoSetGrid(uint8_t shiftIndex) override;
  uint8_t GetShiftsPerLoop() override;
};

#endif
