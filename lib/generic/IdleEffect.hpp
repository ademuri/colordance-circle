#pragma once

#include "ColordanceTypes.hpp"
#include "Effect.hpp"

// Runs the "idle" mode when no-one is interacting with us. Minimizes power
// draw, while changing enough to draw people in.
class IdleEffect : public Effect {
 public:
  IdleEffect(Poles& poles, ParamController& paramController);

  void DoStep() override;

 private:
  // Returns the sin of the angle, gating the minimum value to 96. The LEDs
  // don't turn on for lower brightness values, so this avoids wasting power.
  static uint8_t Brightness(uint8_t angle);
};
