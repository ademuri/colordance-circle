#include "PoleEffect.hpp"

#include <FastLED.h>

void PoleEffect::SetPoleEffect(Poles& poles, long t) {
  for (auto& pole : poles) {
    pole.ClearPoleLights();

    for (uint8_t i = 0; i < kLightsPerPole; ++i) {
      CHSV color = GetColor(i, t);
      pole.SetPoleLight(i, color);
    }
  }
}

void PoleEffect::SetPoleLowerEffect(Poles& poles, long t) {
  for (auto& pole : poles) {
    pole.ClearPoleLights();

    for (uint8_t i = 0; i < kLightsPerPole; ++i) {
      CHSV color = GetColor(i, t);
      // Light index from [0, 256)
      uint16_t amount = ((uint16_t)i * 255) / kLightsPerPole;
      color.v = (color.v * amount) / 255;
      color.v /= 2;
      color.v += 128;
      pole.SetPoleLight(i, color);
    }
  }
}

CHSV PoleEffect::GetColor(uint8_t n, long t) {
  // Map to [0, 255]
  uint8_t hue = ((n + t / -300) * (uint32_t)255 * 3) / kLightsPerPole;
  uint8_t value = ((n + t / 200) * (uint32_t)255 * 5) / kLightsPerPole;

  return CHSV(hue, 64, cos8(value));
}
