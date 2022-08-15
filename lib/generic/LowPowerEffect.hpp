#pragma once

#include "Effect.hpp"

// Runs when the battery voltage is low. Turns on minimal lights to make the
// piece visible.
class LowPowerEffect : public Effect {
 public:
  LowPowerEffect(Poles& poles, Buttons& buttons, ParamController& paramController);

  void DoStep() override;
};