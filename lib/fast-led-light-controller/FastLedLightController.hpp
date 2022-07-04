#pragma once

#include <ColordanceTypes.hpp>
#include <Pole.hpp>

#include <vector>

class FastLedLightController {
 public:
  FastLedLightController();

  void WriteOutLights();

  std::vector<Pole> & get_poles() {
    return poles;
  }

 private:
  static const uint16_t kGridSize = 16;
  static const uint16_t kLedOffset = 1;
  static const uint16_t kNumLeds = 6 * kGridSize + kLedOffset;
  std::vector<Pole> poles = std::vector<Pole>(Pole::kNumPoles);
  CRGB leds[kNumLeds];
};
