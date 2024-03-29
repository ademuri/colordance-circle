#pragma once

#include <ColordanceTypes.hpp>
#include <Pole.hpp>
#include <array>

class TeensyLightController {
 public:
  TeensyLightController();

  void WriteOutLights();

  Poles& get_poles() { return poles; }

 private:
  // The number of LED output pins
  static constexpr int kNumLedOutputs = 14;
  // TODO: make this bigger when pole LEDs are added
  static constexpr int kLedsPerOutput = 45;

  static constexpr int kTotalLeds = kNumLedOutputs * kLedsPerOutput;

  Poles poles{};

  CRGB leds[kTotalLeds];

  // FastLED pin order:
  // 0 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
  // 1,0,24,25,19,18,14,15,17,16,22,23,20,21,26,27

  // Map from pole number (position in array) to the index for that pole's main
  // light in the LED array
  // Pins: 15, 17, 19, 21, 22, 0
  static const std::array<int, 6> kGridLightIndexes;

  // Map from pole number (position in array) to the index for that pole's pole
  // lights in the LED array
  // Pins: 14, 16, 18, 20, 23, 1
  static const std::array<int, 6> kPoleLightIndexes;

  static constexpr int kPodiumIndex = 3;
  static constexpr int kControlPanelIndex = 2;
};
