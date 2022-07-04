#include "TeensyLightController.hpp"

const std::array<int, 6> TeensyLightController::kPoleLightIndexes = {6,  9,  5,
                                                                     12, 10, 0};

// const std::array<int, 6> TeensyLightController::kPoleGridIndexes = {7, 8, 4,
// 13, 11, 1};
const std::array<int, 6> TeensyLightController::kPoleGridIndexes = {7,  8,  4,
                                                                    13, 10, 1};

TeensyLightController::TeensyLightController() {
  for (int i = 0; i < kTotalLeds; i++) {
    leds[i] = CHSV(0, 0, 0);
  }

  FastLED.addLeds<kNumLedOutputs, WS2812, /* first pin */ 1, BGR>(
      leds, kLedsPerOutput);
  // FastLED.setBrightness(32);
}

void TeensyLightController::WriteOutLights() {
  for (uint8_t pole_number = 0; pole_number < Pole::kNumPoles; pole_number++) {
    auto & grid_lights = poles[pole_number].get_grid_lights();
    int pole_index = kPoleGridIndexes[pole_number];

    leds[pole_index * kLedsPerOutput + 6] = grid_lights[0][0];
    leds[pole_index * kLedsPerOutput + 7] = grid_lights[0][1];
    leds[pole_index * kLedsPerOutput + 9] = grid_lights[0][2];
    leds[pole_index * kLedsPerOutput + 10] = grid_lights[0][3];

    leds[pole_index * kLedsPerOutput + 5] = grid_lights[1][0];
    leds[pole_index * kLedsPerOutput + 4] = grid_lights[1][1];
    leds[pole_index * kLedsPerOutput + 8] = grid_lights[1][2];
    leds[pole_index * kLedsPerOutput + 11] = grid_lights[1][3];

    leds[pole_index * kLedsPerOutput + 3] = grid_lights[2][0];
    leds[pole_index * kLedsPerOutput + 0] = grid_lights[2][1];
    leds[pole_index * kLedsPerOutput + 12] = grid_lights[2][2];
    leds[pole_index * kLedsPerOutput + 13] = grid_lights[2][3];

    leds[pole_index * kLedsPerOutput + 2] = grid_lights[3][0];
    leds[pole_index * kLedsPerOutput + 1] = grid_lights[3][1];
    leds[pole_index * kLedsPerOutput + 15] = grid_lights[3][2];
    leds[pole_index * kLedsPerOutput + 14] = grid_lights[3][3];
  }
  FastLED.show();
}
