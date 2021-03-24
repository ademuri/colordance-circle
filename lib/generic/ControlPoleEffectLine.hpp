#ifndef CONTROL_POLE_EFFECT_LINE_HPP_
#define CONTROL_POLE_EFFECT_LINE_HPP_

#include <vector>

#include "ColordanceTypes.hpp"
#include "ControlPoleEffect.hpp"

class ControlPoleEffectLine : public ControlPoleEffect {
 public:
  ControlPoleEffectLine();

 protected:
  void DoSetGrid(uint8_t shiftIndex) override;
  uint16_t GetSpeedConstant() override;
  uint8_t GetShiftsPerLoop() override;

 private:
  const uint16_t SPEED_CONSTANT = 1200;  // Millis per shift at speed 1
};

#endif
