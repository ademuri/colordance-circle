#pragma once

#include <ColordanceTypes.hpp>
#include <LightController.hpp>
#include <vector>

class TeensyLightController : public LightController {
 public:
  TeensyLightController();

  void WriteOutLights() override;

 private:
  // The number of LED output pins
  static const int kNumLedOutputs = 14;
  // TODO: make this bigger when pole LEDs are added
  static const int kLedsPerOutput = 16;

  static const int kTotalLeds = kNumLedOutputs * kLedsPerOutput;

  CRGB leds[kTotalLeds];

  // FastLED pin order:
  // 1,0,24,25,19,18,14,15,17,16,22,23,20,21,26,27

  // Map from pole number (position in vector) to the index for that pole's main
  // light in the LED array
  // Pins: 14, 16, 18, 20, 22, 1
  const std::vector<int> kPoleGridIndexes = {6, 9, 5, 12, 10, 0};

  // Map from pole number (position in vector) to the index for that pole's pole
  // lights in the LED array
  // Pins: 15, 17, 19, 21, 23, 0
  const std::vector<int> kPoleLightIndexes = {7, 8, 4, 13, 11, 1};

  static const int kPodiumIndex = 3;
  static const int kControlPanelIndex = 2;
};