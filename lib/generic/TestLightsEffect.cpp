#include "TestLightsEffect.hpp"

#include "PoleEffect.hpp"

TestLightsEffect::TestLightsEffect(Poles& poles,
                                   ParamController& param_controller)
    : Effect(poles, param_controller) {}

void TestLightsEffect::DoStep() {
  for (auto& pole : poles) {
    pole.ClearGridLights();
  }

  const uint32_t time_per_pole = kTimeStep * gridWidth;

  Pole& pole = poles[(millis() / time_per_pole) % Pole::kNumPoles];
  for (uint8_t y = 0; y < gridHeight; ++y) {
    pole.SetGridLight((millis() / kTimeStep) % gridWidth, y,
                      CRGB(255, 255, 255));
  }

  SetPoleEffect(poles, millis());
}
