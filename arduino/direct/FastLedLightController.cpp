#include "FastLedLightController.hpp"

FastLedLightController::FastLedLightController() {
  FastLED.addLeds<NEOPIXEL, kLedPin>(leds, kNumLeds);
  FastLED.showColor(CRGB(0, 0, 0));
}

void FastLedLightController::WriteOutLights() { FastLED.show(); }
