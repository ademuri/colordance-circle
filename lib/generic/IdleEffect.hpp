#pragma once

#include "Effect.hpp"

// Runs the "idle" mode when no-one is interacting with us. Minimizes power
// draw, while changing enough to draw people in.
class IdleEffect : public Effect {
 public:
  IdleEffect(Poles& poles, ParamController& paramController);

  void DoStep() override;
};
