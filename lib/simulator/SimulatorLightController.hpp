#pragma once

#include <fast-led-simulator.h>

#include <chrono>
#include <map>
#include <vector>

#include "Pole.hpp"

/*
 * Interface class for controlling the output lights.
 */
class SimulatorLightController : private FastLEDSimulator<96> {
 public:
  SimulatorLightController();
  ~SimulatorLightController();

  using FastLEDSimulator<96>::Run;

  void WriteOutLights();

  void SetLedPositions() override;

  SDL_Point GetInitialSize() override;
  SDL_Point GetInitialPosition() override;
  LedSize GetLedSize() override;
  Poles poles;

 private:
  static constexpr int kLedPixels = 20;
  static constexpr int kLedFramePixels = 24;
  static constexpr int kLedSpacing = 8;
  static constexpr int kPoleSpacing = 40;
  static constexpr int kLedsPerOutput = 16;
};
