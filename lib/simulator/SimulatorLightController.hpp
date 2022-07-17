#pragma once

#include <fast-led-simulator.h>

#include <chrono>
#include <map>
#include <vector>

#include "Pole.hpp"

static constexpr size_t kGridLights = Pole::kNumPoles * gridWidth * gridHeight;
static constexpr size_t kPoleLights = Pole::kNumPoles * kLightsPerPole;
static constexpr size_t kTotalLights = kGridLights + kPoleLights;

/*
 * Interface class for controlling the output lights.
 */
class SimulatorLightController : private FastLEDSimulator<kTotalLights> {
 public:
  SimulatorLightController();
  ~SimulatorLightController();

  using FastLEDSimulator<kTotalLights>::Run;

  void WriteOutLights();

  void SetLedPositions() override;

  SDL_Point GetInitialSize() override;
  SDL_Point GetInitialPosition() override;
  Poles poles;

 private:
  static constexpr int kGridLedPixels = 20;
  static constexpr int kGridLedFramePixels = 24;
  static constexpr int kGridLedSpacing = 8;

  static constexpr int kPoleLedPixels = 4;
  static constexpr int kPoleLedFramePixels = 6;
  static constexpr int kPoleLedSpacing = 2;

  static constexpr int kPoleSpacing = 40;
  static constexpr int kLedsPerOutput = 16;
};
