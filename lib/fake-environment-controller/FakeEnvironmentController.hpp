#pragma once

#include <ColordanceTypes.hpp>

#include "EnvironmentController.hpp"

class FakeEnvironmentController : public EnvironmentController {
 public:
  void Step() override {}

  uint16_t GetBatteryMillivolts() const override { return battery_millivolts_; }
  void SetBatteryMillivolts(uint16_t batter_millivolts) {
    battery_millivolts_ = batter_millivolts;
  }

  bool TestLightsPressed() const override { return test_lights_; }
  void SetTestLights(bool test_lights) { test_lights_ = test_lights; }

  bool MotionDetected() const override { return motion_detected_; }
  void SetMotionDetected(bool motion_detected) {
    motion_detected_ = motion_detected;
  }

 private:
  uint16_t battery_millivolts_ = 1300;
  bool test_lights_ = false;
  bool motion_detected_ = false;
};
