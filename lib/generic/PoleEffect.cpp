#include "PoleEffect.hpp"

#include <FastLED.h>

CHSV GetColor(uint8_t n, long timeMs) {
  // How slowly each wave should propagate across the pole. The units are
  // somewhat arbitrary so these may be considered magic numbers.
  uint16_t hue_speed = -300;
  uint16_t brightness_speed = 200;

  // Number of effect cycles per pole at any given time.
  uint8_t hue_freq = 3;
  uint8_t brightness_freq = 5;

  // Map to [0, 255]
  uint8_t hue =
      ((n + timeMs / hue_speed) * (uint32_t)255 * hue_freq) / kLightsPerPole;
  uint8_t value =
      ((n + timeMs / brightness_speed) * (uint32_t)255 * brightness_freq) /
      kLightsPerPole;

  // Hue automatically wraps around with integer overflow, the cos of the value
  // is necessary to create the waves.
  return CHSV(hue, 64, cos8(value));
}

void SetPoleEffect(Poles& poles, long timeMs) {
  for (auto& pole : poles) {
    pole.ClearPoleLights();

    for (uint8_t i = 0; i < kLightsPerPole; ++i) {
      CHSV color = GetColor(i, timeMs);
      pole.SetPoleLight(i, color);
    }
  }
}

void SetPoleLowerEffect(Poles& poles, long timeMs) {
  for (auto& pole : poles) {
    pole.ClearPoleLights();

    for (uint8_t i = 0; i < kLightsPerPole; ++i) {
      CHSV color = GetColor(i, timeMs);
      // Linear falloff as we approach the bottom of the pole.
      uint16_t light_pos = ((uint16_t)i * 255) / kLightsPerPole;
      color.v = (color.v * light_pos) / 255;

      // Map from [0, 256) to [128, 256) to make things a little brighter.
      color.v /= 2;
      color.v += 128;
      
      pole.SetPoleLight(i, color);
    }
  }
}
