#pragma once

#include "ColordanceTypes.hpp"
#include "Effect.hpp"

// Displays a test pattern, to verify that all lights are working correctly.
class TestLightsEffect : public Effect {
 public:
  TestLightsEffect(Poles& poles, ParamController& paramController);

  void DoStep() override;

 private:
  static constexpr uint32_t kTimeStep = 500;
};
