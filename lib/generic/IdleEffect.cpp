#include "IdleEffect.hpp"

IdleEffect::IdleEffect(Poles& poles, ParamController& paramController)
    : Effect(poles, paramController) {}

void IdleEffect::DoStep() {
  for (auto& pole : poles) {
    pole.ClearGridLights();
  }

  uint8_t hue = millis() / 10;
  uint8_t angle = millis() / 7;
  poles[0].SetGridLight(0, 0, CHSV(hue, 255, Brightness(angle)));
  poles[1].SetGridLight(0, 0, CHSV(hue + 64, 255, Brightness(angle + 64)));
  poles[Pole::kNumPoles - 1].SetGridLight(
      3, 0, CHSV(hue + 128, 255, Brightness(angle + 128)));
  poles[Pole::kNumPoles - 2].SetGridLight(
      3, 0, CHSV(hue + 192, 255, Brightness(angle + 192)));
}

// static
uint8_t IdleEffect::Brightness(uint8_t angle) {
  uint8_t val = sin8(angle);
  if (val < 96) {
    val = 0;
  }
  return val;
}