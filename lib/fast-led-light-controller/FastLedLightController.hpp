#pragma once

#include <ColordanceTypes.hpp>
#include <Pole.hpp>

class FastLedLightController {
 public:
  FastLedLightController();

  void WriteOutLights();

  Poles & get_poles() {
    return poles;
  }

 private:
  static const uint16_t kGridSize = 16;
  static const uint16_t kLedOffset = 1;
  static const uint16_t kNumLeds = 6 * kGridSize + kLedOffset;
  Poles poles{};
  CRGB leds[kNumLeds];
};
