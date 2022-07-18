#pragma once

#include <exponential-moving-average-filter.h>
#include <median-filter.h>

#include <vector>

#include "EnvironmentController.hpp"

constexpr std::array<int, 2> kMotionSensorPins = {2, 3};

class TeensyEnvironmentController : public EnvironmentController {
 public:
  TeensyEnvironmentController();

  void Step() override;
  uint16_t GetBatteryMillivolts() const override;
  bool TestLightsPressed() const override;
  bool MotionDetected() const override;

 private:
  static constexpr int kBatteryPin = 41;
  static constexpr int kTestLightsPin = 9;

  MedianFilter<uint8_t, uint8_t, 201> test_lights_input_;
  MedianFilter<uint16_t, uint16_t, 5> battery_median_filter_;
  ExponentialMovingAverageFilter<uint16_t> battery_average_filter_;
  // val = (previous * 3 + current) / 4
  static constexpr uint8_t kBatteryFilterAlpha = 96;

  std::vector<MedianFilter<uint8_t, uint8_t, 5>> motion_sensor_filters_;
};