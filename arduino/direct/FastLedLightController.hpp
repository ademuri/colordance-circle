#ifndef FAST_LED_LIGHT_CONTROLLER_HPP_
#define FAST_LED_LIGHT_CONTROLLER_HPP_

#include <ColordanceTypes.hpp>
#include <LightController.hpp>

class FastLedLightController : public LightController {
 public:
  FastLedLightController();

  void WriteOutLights() override;

 private:
  static const uint16_t kLedPin = WS2812_PIN;
  static const uint16_t kGridSize = 16;
  static const uint16_t kLedOffset = 1;
  static const uint16_t kNumLeds = 6 * kGridSize + kLedOffset;
  CRGB leds[kNumLeds];
};

#endif
