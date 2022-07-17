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
  // Grid lights
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    for (int y = 0; y < gridHeight; y++) {
      for (int x = 0; x < gridWidth; x++) {
        const uint16_t index =
            pole * gridWidth * gridHeight + y * gridHeight + x;
        leds[index] = CRGB(0, 0, 0);
        const int x_position =
            kGridLedSpacing +
            pole * ((kGridLedFramePixels + kGridLedSpacing) * gridWidth +
                    kPoleSpacing) +
            x * (kGridLedFramePixels + kGridLedSpacing);
        const int y_position =
            kGridLedSpacing + y * (kGridLedFramePixels + kGridLedSpacing);
        led_layout_[index].location = {x_position, y_position};
        led_layout_[index].frame_size = kGridLedFramePixels;
        led_layout_[index].led_size = kGridLedPixels;
      }
    }
  }

  // Pole lights
  const int y_offset =
      kGridLedSpacing + gridHeight * (kGridLedFramePixels + kGridLedSpacing);
  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    const int x_pole_center = kGridLedFramePixels * 2 + kGridLedSpacing * 1.5 -
                              kPoleLedFramePixels / 2;
    const int x_position =
        kGridLedSpacing +
        pole * ((kGridLedFramePixels + kGridLedSpacing) * gridWidth +
                kPoleSpacing) +
        x_pole_center;
    for (int n = 0; n < kLightsPerPole; n++) {
      const int index = kGridLights + pole * kLightsPerPole + n;
      const int y_position =
          y_offset + n * (kPoleLedFramePixels + kPoleLedSpacing);
      led_layout_[index].location = {x_position, y_position};
      led_layout_[index].frame_size = kPoleLedFramePixels;
      led_layout_[index].led_size = kPoleLedPixels;
    }
  }
}

SDL_Point SimulatorLightController::GetInitialSize() {
  const int x_size =
      Pole::kNumPoles *
      (gridWidth * (kGridLedFramePixels + kGridLedSpacing) + kPoleSpacing);
  const int y_size =
      gridHeight * (kGridLedFramePixels + kGridLedSpacing) + kGridLedSpacing +
      (kLightsPerPole + 1) * (kPoleLedFramePixels + kPoleLedSpacing);
  return {x_size, y_size};
}

SDL_Point SimulatorLightController::GetInitialPosition() { return {0, 0}; }
