#ifndef CONTROL_POLE_EFFECT_TWINKLE_HPP_
#define CONTROL_POLE_EFFECT_TWINKLE_HPP_

#include <vector>

#include "ColordanceTypes.hpp"
#include "ControlPoleEffect.hpp"

class ControlPoleEffectTwinkle : public ControlPoleEffect {
 public:
  ControlPoleEffectTwinkle(uint16_t framesPerLoop);

 protected:
  void DoSetGrid(uint8_t shiftIndex) override;
  uint8_t GetShiftsPerLoop() override;

 private:
  uint8_t GetBigSquare(uint8_t shiftIndex);
  uint8_t GetLittleSquare(uint8_t shiftIndex);
};

#endif
