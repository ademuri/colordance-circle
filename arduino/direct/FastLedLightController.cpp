#include "FastLedLightController.hpp"

FastLedLightController::FastLedLightController() {
  FastLED.addLeds<NEOPIXEL, kLedPin>(leds, kNumLeds);
  FastLED.setDither(0);
  FastLED.showColor(CRGB(0, 0, 0));

  for (uint8_t pole_index = 0; pole_index < Pole::kNumPoles; pole_index++) {
    poles.push_back(new Pole());
  }
}

void FastLedLightController::WriteOutLights() {
  for (uint8_t pole_index = 0; pole_index < Pole::kNumPoles; pole_index++) {
    Pole* pole = poles[pole_index];
    leds[kLedOffset + pole_index * kGridSize] = pole->get_grid_lights()[0][0];
    leds[kLedOffset + pole_index * kGridSize + 1] =
        pole->get_grid_lights()[0][1];
    leds[kLedOffset + pole_index * kGridSize + 2] =
        pole->get_grid_lights()[0][2];
    leds[kLedOffset + pole_index * kGridSize + 3] =
        pole->get_grid_lights()[0][3];

    leds[kLedOffset + pole_index * kGridSize + 7] =
        pole->get_grid_lights()[1][0];
    leds[kLedOffset + pole_index * kGridSize + 6] =
        pole->get_grid_lights()[1][1];
    leds[kLedOffset + pole_index * kGridSize + 5] =
        pole->get_grid_lights()[1][2];
    leds[kLedOffset + pole_index * kGridSize + 4] =
        pole->get_grid_lights()[1][3];

    leds[kLedOffset + pole_index * kGridSize + 8] =
        pole->get_grid_lights()[2][0];
    leds[kLedOffset + pole_index * kGridSize + 9] =
        pole->get_grid_lights()[2][1];
    leds[kLedOffset + pole_index * kGridSize + 10] =
        pole->get_grid_lights()[2][2];
    leds[kLedOffset + pole_index * kGridSize + 11] =
        pole->get_grid_lights()[2][3];

    leds[kLedOffset + pole_index * kGridSize + 15] =
        pole->get_grid_lights()[3][0];
    leds[kLedOffset + pole_index * kGridSize + 14] =
        pole->get_grid_lights()[3][1];
    leds[kLedOffset + pole_index * kGridSize + 13] =
        pole->get_grid_lights()[3][2];
    leds[kLedOffset + pole_index * kGridSize + 12] =
        pole->get_grid_lights()[3][3];
  }

  //  for (uint8_t pole_index = 0; pole_index < Pole::kNumPoles; pole_index++) {
  //   Pole* pole = poles[pole_index];
  //   leds[kLedOffset + pole_index * kGridSize + 6] =
  //       pole->get_grid_lights()[0][0];
  //   leds[kLedOffset + pole_index * kGridSize + 7] =
  //       pole->get_grid_lights()[0][1];
  //   leds[kLedOffset + pole_index * kGridSize + 9] =
  //       pole->get_grid_lights()[0][2];
  //   leds[kLedOffset + pole_index * kGridSize + 10] =
  //       pole->get_grid_lights()[0][3];

  //   leds[kLedOffset + pole_index * kGridSize + 5] =
  //       pole->get_grid_lights()[1][0];
  //   leds[kLedOffset + pole_index * kGridSize + 4] =
  //       pole->get_grid_lights()[1][1];
  //   leds[kLedOffset + pole_index * kGridSize + 8] =
  //       pole->get_grid_lights()[1][2];
  //   leds[kLedOffset + pole_index * kGridSize + 11] =
  //       pole->get_grid_lights()[1][3];

  //   leds[kLedOffset + pole_index * kGridSize + 3] =
  //       pole->get_grid_lights()[2][0];
  //   leds[kLedOffset + pole_index * kGridSize + 0] =
  //       pole->get_grid_lights()[2][1];
  //   leds[kLedOffset + pole_index * kGridSize + 12] =
  //       pole->get_grid_lights()[2][2];
  //   leds[kLedOffset + pole_index * kGridSize + 13] =
  //       pole->get_grid_lights()[2][3];

  //   leds[kLedOffset + pole_index * kGridSize + 2] =
  //       pole->get_grid_lights()[3][0];
  //   leds[kLedOffset + pole_index * kGridSize + 1] =
  //       pole->get_grid_lights()[3][1];
  //   leds[kLedOffset + pole_index * kGridSize + 15] =
  //       pole->get_grid_lights()[3][2];
  //   leds[kLedOffset + pole_index * kGridSize + 14] =
  //       pole->get_grid_lights()[3][3];
  // }
  FastLED.show();
}
