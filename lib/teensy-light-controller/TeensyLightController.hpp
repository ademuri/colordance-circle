#pragma once

#include <ColordanceTypes.hpp>
#include <LightController.hpp>
#include <array>

class TeensyLightController : public LightController {
 public:
  TeensyLightController();

  void WriteOutLights() override;

 private:
  // The number of LED output pins
  static constexpr int kNumLedOutputs = 14;
  // TODO: make this bigger when pole LEDs are added
  static constexpr int kLedsPerOutput = 16;

  static constexpr int kTotalLeds = kNumLedOutputs * kLedsPerOutput;

  CRGB leds[kTotalLeds];

  // FastLED pin order:
  // 1,0,24,25,19,18,14,15,17,16,22,23,20,21,26,27

  // Map from pole number (position in array) to the index for that pole's main
  // light in the LED array
  // Pins: 14, 16, 18, 20, 22, 1
  static const std::array<int, 6> kPoleGridIndexes;

  // Map from pole number (position in array) to the index for that pole's pole
  // lights in the LED array
  // Pins: 15, 17, 19, 21, 23, 0
  static constexpr std::array<int, 6> kPoleLightIndexes = {7,  8,  4,
                                                                  13, 11, 1};

  static constexpr int kPodiumIndex = 3;
  static constexpr int kControlPanelIndex = 2;
};
