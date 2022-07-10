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

void TeensyEnvironmentController::Step() {
  test_lights_input_.Run();
  battery_median_filter_.Run();
  battery_average_filter_.Run();
}

uint16_t TeensyEnvironmentController::GetBatteryMillivolts() {
  // Use 32 bits to avoid clipping during calculation
  uint32_t battery_raw = battery_average_filter_.GetFilteredValue();
  // Voltage divider is 1200k and 330k resistor, reference voltage is 3.3v, DAC
  // precision is 10 bits -> 1024
  return (uint16_t)(battery_raw * (1200 + 330) * 3.3 * 1000 / 330 / 1024);
}

bool TeensyEnvironmentController::TestLightsPressed() {
  return test_lights_input_.GetFilteredValue();
}