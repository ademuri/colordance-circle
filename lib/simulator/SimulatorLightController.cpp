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

    auto& pole_lights = poles[pole_number].get_pole_lights();
    for (std::size_t n = 0; n < kLightsPerPole; n++) {
      leds[kGridLights + pole_number * kLightsPerPole + n] = pole_lights[n];
    }
  }
}

void SimulatorLightController::SetLedPositions() {
  const LedSize led_size = GetLedSize();

  // Grid lights
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

  // Pole lights
  const int y_offset =
      kLedSpacing + gridHeight * (led_size.frame_size + kLedSpacing);
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    const int x_position =
        kLedSpacing +
        pole * ((led_size.frame_size + kLedSpacing) * gridWidth + kPoleSpacing);
    for (int n = 0; n < kLightsPerPole; n++) {
      const int index = kGridLights + pole * kLightsPerPole + n;
      const int y_position = y_offset + n * (led_size.frame_size + kLedSpacing);
      led_locations_[index] = {x_position, y_position};
    }
  }
}

SDL_Point SimulatorLightController::GetInitialSize() {
  const LedSize led_size = GetLedSize();
  const int x_size =
      Pole::kNumPoles *
      (gridWidth * (led_size.frame_size + kLedSpacing) + kPoleSpacing);
  const int y_size = gridHeight * (led_size.frame_size + kLedSpacing) +
                     kLedSpacing +
                     kLightsPerPole * (led_size.frame_size + kLedSpacing);
  return {x_size, y_size};
}

SDL_Point SimulatorLightController::GetInitialPosition() { return {0, 0}; }

LedSize SimulatorLightController::GetLedSize() {
  return {kLedPixels, kLedFramePixels};
}