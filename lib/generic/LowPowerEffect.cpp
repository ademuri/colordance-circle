#include "LowPowerEffect.hpp"

#include "PoleEffect.hpp"

LowPowerEffect::LowPowerEffect(Poles& poles, Buttons& buttons,
                               ParamController& paramController)
    : Effect(poles, buttons, paramController) {}

void LowPowerEffect::DoStep() {
  for (auto& pole : poles_) {
    pole.ClearGridLights();
  }

  // Turn on dim lights on two poles
  auto& pole1 = poles_[1];
  uint8_t pole2_index = Pole::kNumPoles == 2 ? 0 : Pole::kNumPoles - 1;
  auto& pole2 = poles_[pole2_index];

  // Red LEDs have lower power consumption
  const CRGB rgb = CRGB(96, 0, 0);
  pole1.SetGridLight(0, 0, rgb);
  pole2.SetGridLight(0, 0, rgb);

  SetPoleLowerEffect(poles_, millis());
}