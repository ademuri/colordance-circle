#include "FastLedLightController.hpp"

FastLedLightController::FastLedLightController() {
  constexpr uint16_t ledPin = WS2812_PIN;
  FastLED.addLeds<NEOPIXEL, ledPin>(leds, kNumLeds);
  FastLED.setDither(0);
  FastLED.showColor(CRGB(0, 0, 0));
  FastLED.setMaxRefreshRate(200);
}

void FastLedLightController::WriteOutLights() {
  for (uint8_t pole_index = 0; pole_index < Pole::kNumPoles; pole_index++) {
    auto const& grid_lights = poles[pole_index].get_grid_lights();
    leds[kLedOffset + pole_index * kGridSize + 0] =
        Pole::ClampCRGBForDisplay(grid_lights[0][0]);
    leds[kLedOffset + pole_index * kGridSize + 1] =
        Pole::ClampCRGBForDisplay(grid_lights[0][1]);
    leds[kLedOffset + pole_index * kGridSize + 2] =
        Pole::ClampCRGBForDisplay(grid_lights[0][2]);
    leds[kLedOffset + pole_index * kGridSize + 3] =
        Pole::ClampCRGBForDisplay(grid_lights[0][3]);

    leds[kLedOffset + pole_index * kGridSize + 7] =
        Pole::ClampCRGBForDisplay(grid_lights[1][0]);
    leds[kLedOffset + pole_index * kGridSize + 6] =
        Pole::ClampCRGBForDisplay(grid_lights[1][1]);
    leds[kLedOffset + pole_index * kGridSize + 5] =
        Pole::ClampCRGBForDisplay(grid_lights[1][2]);
    leds[kLedOffset + pole_index * kGridSize + 4] =
        Pole::ClampCRGBForDisplay(grid_lights[1][3]);

    leds[kLedOffset + pole_index * kGridSize + 8] =
        Pole::ClampCRGBForDisplay(grid_lights[2][0]);
    leds[kLedOffset + pole_index * kGridSize + 9] =
        Pole::ClampCRGBForDisplay(grid_lights[2][1]);
    leds[kLedOffset + pole_index * kGridSize + 10] =
        Pole::ClampCRGBForDisplay(grid_lights[2][2]);
    leds[kLedOffset + pole_index * kGridSize + 11] =
        Pole::ClampCRGBForDisplay(grid_lights[2][3]);

    leds[kLedOffset + pole_index * kGridSize + 15] =
        Pole::ClampCRGBForDisplay(grid_lights[3][0]);
    leds[kLedOffset + pole_index * kGridSize + 14] =
        Pole::ClampCRGBForDisplay(grid_lights[3][1]);
    leds[kLedOffset + pole_index * kGridSize + 13] =
        Pole::ClampCRGBForDisplay(grid_lights[3][2]);
    leds[kLedOffset + pole_index * kGridSize + 12] =
        Pole::ClampCRGBForDisplay(grid_lights[3][3]);
  }
  FastLED.show();
}
