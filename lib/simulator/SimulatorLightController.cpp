#include "SimulatorLightController.hpp"

#include <math.h>

#include <chrono>
#include <cstdio>
#include <map>
#include <utility>
#include <vector>

SimulatorLightController::SimulatorLightController() { Init(); }

SimulatorLightController::~SimulatorLightController() { Close(); }

void SimulatorLightController::WriteOutLights() {
  for (uint8_t pole_number = 0; pole_number < Pole::kNumPoles; pole_number++) {
    auto& grid_lights = poles[pole_number].get_grid_lights();

    for (std::size_t n = 0; n < gridWidth * gridHeight; n++) {
      leds[pole_number * kLedsPerOutput + n] =
          grid_lights[n / gridHeight][n % gridWidth];
    }
  }
}

void SimulatorLightController::SetLedPositions() {
  const LedSize led_size = GetLedSize();
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    for (int y = 0; y < gridHeight; y++) {
      for (int x = 0; x < gridWidth; x++) {
        const uint16_t index =
            pole * gridWidth * gridHeight + y * gridHeight + x;
        leds[index] = CRGB(0, 0, 0);
        const int x_position =
            kLedSpacing +
            pole * ((led_size.frame_size + kLedSpacing) * gridWidth +
                    kPoleSpacing) +
            x * (led_size.frame_size + kLedSpacing);
        const int y_position =
            kLedSpacing + y * (led_size.frame_size + kLedSpacing);
        led_locations_[index] = {x_position, y_position};
      }
    }
  }
}

SDL_Point SimulatorLightController::GetInitialSize() {
  const LedSize led_size = GetLedSize();
  return {Pole::kNumPoles *
              (gridWidth * (led_size.frame_size + kLedSpacing) + kPoleSpacing),
          gridHeight * (led_size.frame_size + kLedSpacing) + kLedSpacing};
}

SDL_Point SimulatorLightController::GetInitialPosition() { return {0, 0}; }

LedSize SimulatorLightController::GetLedSize() {
  return {kLedPixels, kLedFramePixels};
}