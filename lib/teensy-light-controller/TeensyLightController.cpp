#include "TeensyLightController.hpp"

TeensyLightController::TeensyLightController() {
  FastLED.addLeds</* numStrips */ 14, WS2812, /* first pin */ 1, RGB>(
      leds, kLedsPerOutput);
}

void TeensyLightController::WriteOutLights() {
  for (uint8_t pole_number = 0; pole_number < Pole::kNumPoles; pole_number++) {
    Pole* pole = poles[pole_number];
    int pole_index = kPoleGridIndexes[pole_number];

    leds[pole_index * kLedsPerOutput + 6] = pole->get_grid_lights()[0][0];
    leds[pole_index * kLedsPerOutput + 7] = pole->get_grid_lights()[0][1];
    leds[pole_index * kLedsPerOutput + 9] = pole->get_grid_lights()[0][2];
    leds[pole_index * kLedsPerOutput + 10] = pole->get_grid_lights()[0][3];

    leds[pole_index * kLedsPerOutput + 5] = pole->get_grid_lights()[1][0];
    leds[pole_index * kLedsPerOutput + 4] = pole->get_grid_lights()[1][1];
    leds[pole_index * kLedsPerOutput + 8] = pole->get_grid_lights()[1][2];
    leds[pole_index * kLedsPerOutput + 11] = pole->get_grid_lights()[1][3];

    leds[pole_index * kLedsPerOutput + 3] = pole->get_grid_lights()[2][0];
    leds[pole_index * kLedsPerOutput + 0] = pole->get_grid_lights()[2][1];
    leds[pole_index * kLedsPerOutput + 12] = pole->get_grid_lights()[2][2];
    leds[pole_index * kLedsPerOutput + 13] = pole->get_grid_lights()[2][3];

    leds[pole_index * kLedsPerOutput + 2] = pole->get_grid_lights()[3][0];
    leds[pole_index * kLedsPerOutput + 1] = pole->get_grid_lights()[3][1];
    leds[pole_index * kLedsPerOutput + 15] = pole->get_grid_lights()[3][2];
    leds[pole_index * kLedsPerOutput + 14] = pole->get_grid_lights()[3][3];
  }
  FastLED.show();
}