#include "MiniLightController.hpp"

void MiniLightController::Begin() {
  FastLED.addLeds<WS2812, RGB>(leds.data(), leds.size());
  // TODO: set this lower if there are glitches
  FastLED.setMaxRefreshRate(50);
  FastLED.clear(/*writeData=*/true);
}

void MiniLightController::WriteOutLights() {
  // TODO: copy from the poles to `leds`
  FastLED.show();
}