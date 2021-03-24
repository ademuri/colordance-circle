#ifndef CONTROL_POLE_EFFECT_CIRCLE_HPP_
#define CONTROL_POLE_EFFECT_CIRCLE_HPP_

#include <vector>

#include "ColordanceTypes.hpp"
#include "ControlPoleEffect.hpp"

class ControlPoleEffectCircle : public ControlPoleEffect {
 public:
  ControlPoleEffectCircle();

 protected:
  void DoSetGrid(uint8_t shiftIndex) override;
  uint16_t GetSpeedConstant() override;
  uint8_t GetShiftsPerLoop() override;

 private:
  uint8_t GetIndex(uint8_t shiftIndex);
  const uint16_t SPEED_CONSTANT = 1200;
};

#endif
