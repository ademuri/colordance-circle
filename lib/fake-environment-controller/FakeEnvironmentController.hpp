#pragma once

#include <ColordanceTypes.hpp>

#include "EnvironmentController.hpp"

class FakeEnvironmentController : public EnvironmentController {
 public:
  void Step() override {}

  uint16_t GetBatteryMillivolts() override { return battery_millivolts_; }
  void SetBatteryMillivolts(uint16_t batter_millivolts) {
    battery_millivolts_ = batter_millivolts;
  }

  bool TestLightsPressed() override { return test_lights_; }
  void SetTestLights(bool test_lights) { test_lights_ = test_lights; }

 private:
  uint16_t battery_millivolts_ = 0;
  bool test_lights_ = false;
};
