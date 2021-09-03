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

  // Map from pole number (position in vector) to the index for that pole's main
  // light in the LED array
  const std::vector<int> kPoleGridIndexes = {7, 9, 5, 13, 10, 0};

  // Map from pole number (position in vector) to the index for that pole's pole
  // lights in the LED array
  const std::vector<int> kPoleLightIndexes = {6, 8, 4, 12, 11, 1};

  static const int kPodiumIndex = 3;
  static const int kControlPanelIndex = 2;
};