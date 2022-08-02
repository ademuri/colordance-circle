#include "ModelLightController.hpp"

ModelLightController::ModelLightController() {
  constexpr uint16_t ledPin = WS2812_PIN;
  FastLED.addLeds<1, WS2812, /*first pin*/ ledPin, GRB>(leds, kNumLeds);
  FastLED.setDither(0);
  FastLED.showColor(CRGB(0, 0, 0));
  FastLED.setMaxRefreshRate(200);
}

void ModelLightController::WriteOutLights() {
  for (uint8_t pole_index = 0; pole_index < Pole::kNumPoles; pole_index++) {
    auto const& grid_lights = poles[pole_index].get_grid_lights();
    leds[pole_index * kGridSize + 0] = grid_lights[0][0];
    leds[pole_index * kGridSize + 1] = grid_lights[0][1];
    leds[pole_index * kGridSize + 2] = grid_lights[0][2];
    leds[pole_index * kGridSize + 3] = grid_lights[0][3];

    leds[pole_index * kGridSize + 7] = grid_lights[1][0];
    leds[pole_index * kGridSize + 6] = grid_lights[1][1];
    leds[pole_index * kGridSize + 5] = grid_lights[1][2];
    leds[pole_index * kGridSize + 4] = grid_lights[1][3];

    leds[pole_index * kGridSize + 8] = grid_lights[2][0];
    leds[pole_index * kGridSize + 9] = grid_lights[2][1];
    leds[pole_index * kGridSize + 10] = grid_lights[2][2];
    leds[pole_index * kGridSize + 11] = grid_lights[2][3];

    leds[pole_index * kGridSize + 15] = grid_lights[3][0];
    leds[pole_index * kGridSize + 14] = grid_lights[3][1];
    leds[pole_index * kGridSize + 13] = grid_lights[3][2];
    leds[pole_index * kGridSize + 12] = grid_lights[3][3];
  }
  FastLED.show();
}
