#pragma once

#include <ColordanceTypes.hpp>
#include <LightController.hpp>

class FastLedLightController : public LightController {
 public:
  FastLedLightController();

  void WriteOutLights() override;

 private:
  static const uint16_t kGridSize = 16;
  static const uint16_t kLedOffset = 1;
  static const uint16_t kNumLeds = 6 * kGridSize + kLedOffset;
  CRGB leds[kNumLeds];
};
