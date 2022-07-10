#include "Runner.hpp"

Runner::Runner(Poles poles, ParamController& param_controller,
               EnvironmentController& environment_controller)
    : param_controller_(param_controller),
      environment_controller_(environment_controller),
      interface_controller_(poles, &param_controller),
      low_power_effect_(poles, &param_controller) {}

void Runner::Step() {
  environment_controller_.Step();
  if (environment_controller_.GetBatteryMillivolts() <
      kBatteryLowThresholdMillivolts) {
    low_power_effect_.Step();
  } else {
    // Battery voltage OK
    param_controller_.Step();
    interface_controller_.Step();
  }
}