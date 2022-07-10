#include "LowPowerEffect.hpp"

LowPowerEffect::LowPowerEffect(Poles& poles, ParamController* paramController)
    : Effect(poles, paramController) {}

void LowPowerEffect::DoStep() {
  for (auto& pole : poles) {
    pole.ClearGridLights();
  }

  // Turn on dim lights on two poles
  auto& pole1 = poles[1];
  uint8_t pole2_index = Pole::kNumPoles == 2 ? 0 : Pole::kNumPoles - 1;
  auto& pole2 = poles[pole2_index];

  // Red LEDs have lower power consumption
  const CRGB rgb = CRGB(96, 0, 0);
  pole1.SetGridLight(0, 0, rgb);
  pole2.SetGridLight(0, 0, rgb);
}