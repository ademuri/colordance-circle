#pragma once

#include <ColordanceTypes.hpp>
#include <Pole.hpp>

#include <vector>

class FastLedLightController {
 public:
  FastLedLightController();

  void WriteOutLights();

  std::vector<Pole *> const & get_poles() const {
    return poles;
  }

 private:
  static const uint16_t kGridSize = 16;
  static const uint16_t kLedOffset = 1;
  static const uint16_t kNumLeds = 6 * kGridSize + kLedOffset;
  std::vector<Pole*> poles;
  CRGB leds[kNumLeds];
};
