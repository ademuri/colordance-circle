#include "TeensyEnvironmentController.hpp"

TeensyEnvironmentController::TeensyEnvironmentController()
    : test_lights_input_(
          filter_functions::ForInvertedDigitalRead<kTestLightsPin>()),
      battery_median_filter_(filter_functions::ForAnalogRead<kBatteryPin>()),
      battery_average_filter_(
          [this]() { return battery_median_filter_.GetFilteredValue(); },
          kBatteryFilterAlpha) {
  pinMode(kBatteryPin, INPUT);
  test_lights_input_.SetMinRunInterval(10);
}

void TeensyEnvironmentController::Run() { test_lights_input_.Run(); }

uint16_t TeensyEnvironmentController::GetBatteryMillivolts() {}

bool TeensyEnvironmentController::TestLightsPressed() {
  return test_lights_input_.GetFilteredValue();
}