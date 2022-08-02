#pragma once

#include <ColordanceTypes.hpp>
#include <Pole.hpp>

// For the scale model, which uses prefab 4x4 arrays of standard WS2812B LEDs.
class ModelLightController {
 public:
  ModelLightController();

  void WriteOutLights();

  Poles& get_poles() { return poles; }

 private:
  static const uint16_t kGridSize = 16;
  static const uint16_t kNumLeds = 6 * kGridSize;
  Poles poles{};
  CRGB leds[kNumLeds];
};
