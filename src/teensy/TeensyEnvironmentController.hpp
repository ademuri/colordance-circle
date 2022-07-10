#pragma once

#include <exponential-moving-average-filter.h>
#include <median-filter.h>

#include "EnvironmentController.hpp"

class TeensyEnvironmentController : public EnvironmentController {
 public:
  TeensyEnvironmentController();

  void Step() override;
  uint16_t GetBatteryMillivolts() override;
  bool TestLightsPressed() override;

 private:
  static constexpr int kBatteryPin = 41;
  static constexpr int kTestLightsPin = 9;

  MedianFilter<uint8_t, uint8_t, 201> test_lights_input_;
  MedianFilter<uint16_t, uint16_t, 5> battery_median_filter_;
  ExponentialMovingAverageFilter<uint16_t> battery_average_filter_;
  // val = (previous * 3 + current) / 4
  static constexpr uint8_t kBatteryFilterAlpha = 96;
};