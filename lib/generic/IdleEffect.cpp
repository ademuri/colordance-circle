#include "IdleEffect.hpp"

IdleEffect::IdleEffect(Poles& poles, ParamController& paramController)
    : Effect(poles, paramController) {}

void IdleEffect::DoStep() {
  for (auto& pole : poles) {
    pole.ClearGridLights();
  }

  uint8_t hue = millis() / 10;
  poles[0].SetGridLight(0, 0, CHSV(hue, 255, 255));
  poles[1].SetGridLight(0, 0, CHSV(hue + 64, 255, 255));
  poles[Pole::kNumPoles - 1].SetGridLight(0, 0, CHSV(hue + 128, 255, 255));
  poles[Pole::kNumPoles - 2].SetGridLight(0, 0, CHSV(hue + 192, 255, 255));
}