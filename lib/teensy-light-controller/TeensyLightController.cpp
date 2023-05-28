#include "TeensyLightController.hpp"

const std::array<int, 6> TeensyLightController::kPoleLightIndexes = {7,  8,  4,
                                                                     13, 10, 1};

const std::array<int, 6> TeensyLightController::kGridLightIndexes = {6,  9,  5,
                                                                     12, 11, 0};

TeensyLightController::TeensyLightController() {
  for (int i = 0; i < kTotalLeds; i++) {
    leds[i] = CHSV(0, 0, 0);
  }

  FastLED.addLeds<kNumLedOutputs, WS2812, /* first pin */ 1, BGR>(
      leds, kLedsPerOutput);
  // TODO: tune this value
  FastLED.setMaxRefreshRate(200);
  // FastLED.setBrightness(32);
}

void TeensyLightController::WriteOutLights() {
  for (uint8_t pole_number = 0; pole_number < Pole::kNumPoles; pole_number++) {
    auto& grid_lights = poles[pole_number].get_grid_lights();
    int pole_index = kGridLightIndexes[pole_number];

    leds[pole_index * kLedsPerOutput + 6] =
        Pole::ClampCRGBForDisplay(grid_lights[0][0]);
    leds[pole_index * kLedsPerOutput + 7] =
        Pole::ClampCRGBForDisplay(grid_lights[0][1]);
    leds[pole_index * kLedsPerOutput + 9] =
        Pole::ClampCRGBForDisplay(grid_lights[0][2]);
    leds[pole_index * kLedsPerOutput + 10] =
        Pole::ClampCRGBForDisplay(grid_lights[0][3]);

    leds[pole_index * kLedsPerOutput + 5] =
        Pole::ClampCRGBForDisplay(grid_lights[1][0]);
    leds[pole_index * kLedsPerOutput + 4] =
        Pole::ClampCRGBForDisplay(grid_lights[1][1]);
    leds[pole_index * kLedsPerOutput + 8] =
        Pole::ClampCRGBForDisplay(grid_lights[1][2]);
    leds[pole_index * kLedsPerOutput + 11] =
        Pole::ClampCRGBForDisplay(grid_lights[1][3]);

    leds[pole_index * kLedsPerOutput + 3] =
        Pole::ClampCRGBForDisplay(grid_lights[2][0]);
    leds[pole_index * kLedsPerOutput + 0] =
        Pole::ClampCRGBForDisplay(grid_lights[2][1]);
    leds[pole_index * kLedsPerOutput + 12] =
        Pole::ClampCRGBForDisplay(grid_lights[2][2]);
    leds[pole_index * kLedsPerOutput + 13] =
        Pole::ClampCRGBForDisplay(grid_lights[2][3]);

    leds[pole_index * kLedsPerOutput + 2] =
        Pole::ClampCRGBForDisplay(grid_lights[3][0]);
    leds[pole_index * kLedsPerOutput + 1] =
        Pole::ClampCRGBForDisplay(grid_lights[3][1]);
    leds[pole_index * kLedsPerOutput + 15] =
        Pole::ClampCRGBForDisplay(grid_lights[3][2]);
    leds[pole_index * kLedsPerOutput + 14] =
        Pole::ClampCRGBForDisplay(grid_lights[3][3]);
  }
  FastLED.show();
}
