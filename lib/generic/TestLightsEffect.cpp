#include "TestLightsEffect.hpp"

#include "PoleEffect.hpp"

TestLightsEffect::TestLightsEffect(Poles& poles, Buttons& buttons,
                                   ParamController& param_controller)
    : Effect(poles, buttons, param_controller) {}

void TestLightsEffect::DoStep() {
  for (auto& pole : poles_) {
    pole.ClearGridLights();
  }

  const uint32_t time_per_pole = kTimeStep * gridWidth;

  Pole& pole = poles_[(millis() / time_per_pole) % Pole::kNumPoles];
  for (uint8_t y = 0; y < gridHeight; ++y) {
    pole.SetGridLight((millis() / kTimeStep) % gridWidth, y,
                      CRGB(255, 255, 255));
  }

  SetPoleEffect(poles_, millis());
  for (uint8_t i = 0; i < 14; i++) {
    for (uint8_t j = 0; j < 15; j++) {
      buttons_.SetButton(i, j, CHSV(millis() / 10, 255, 255));
    }
  }
}
