#include "MiniLightController.hpp"

void MiniLightController::Begin() {
#ifdef ARDUINO

  // These have to be listed out because the data pin is in the template
  FastLED.addLeds<WS2812, /* data pin */ 16, RGB>(leds[0].data(), kLedsPerPole);
  FastLED.addLeds<WS2812, /* data pin */ 17, RGB>(leds[1].data(), kLedsPerPole);
  FastLED.addLeds<WS2812, /* data pin */ 18, RGB>(leds[2].data(), kLedsPerPole);
  FastLED.addLeds<WS2812, /* data pin */ 19, RGB>(leds[3].data(), kLedsPerPole);
  FastLED.addLeds<WS2812, /* data pin */ 20, RGB>(leds[4].data(), kLedsPerPole);
  FastLED.addLeds<WS2812, /* data pin */ 21, RGB>(leds[5].data(), kLedsPerPole);

  // TODO: set this lower if there are glitches
  FastLED.setMaxRefreshRate(50);
  FastLED.clear(/*writeData=*/true);
#endif
}

void MiniLightController::WriteOutLights() {
  for (uint8_t pole = 0; pole < Pole::kNumPoles; pole++) {
    for (uint8_t x = 0; x < 4; x++) {
      for (uint8_t y = 0; y < 4; y++) {
        for (uint16_t led_index : GridLightToNativeLedIndices(x, y)) {
          leds[pole][led_index] = poles[pole].get_grid_lights()[y][x];
        }
      }
    }
  }

#ifdef ARDUINO
  FastLED.show();
#endif
}

// static
uint16_t MiniLightController::NativeToBoardLedIndex(const uint16_t i) {
  if ((i / 16) % 2 == 0) {
    return i;
  }

  const uint16_t row = i / 16;
  const uint16_t offset = i % 16;

  return (row * 16) + (15 - offset);
}

// static
MiniLightController::LedIndices
MiniLightController::GridLightToNativeLedIndices(uint16_t x, uint16_t y) {
  MiniLightController::LedIndices indices;
  uint8_t index = 0;
  for (uint8_t row = 0; row < 4; row++) {
    for (uint8_t col = 0; col < 4; col++) {
      indices[index++] = (y * 4 + row) * 16 + col + x * 4;
    }
  }

  return indices;
}
