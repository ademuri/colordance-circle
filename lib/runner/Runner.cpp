#include "Runner.hpp"

Runner::Runner(Poles& poles, ParamController& param_controller,
               EnvironmentController& environment_controller, Logger& logger)
    : param_controller_(param_controller),
      environment_controller_(environment_controller),
      logger_(logger),
      interface_controller_(poles, param_controller),
      low_power_effect_(poles, param_controller),
      idle_effect_(poles, param_controller),
      test_lights_effect_(poles, param_controller) {
  idle_timer_.Reset();
}

void Runner::Step() {
  environment_controller_.Step();
  if (environment_controller_.TestLightsPressed()) {
    test_lights_timer_.Reset();
  }

  bool battery_low = false;
  if (state_ == RunnerState::LOW_POWER) {
    battery_low = environment_controller_.GetBatteryMillivolts() <
                  (kBatteryLowThresholdMillivolts + kBatteryDeadBandMillivolts);
  } else {
    battery_low = environment_controller_.GetBatteryMillivolts() <
                  kBatteryLowThresholdMillivolts;
  }

  param_controller_.Step();
  if (param_controller_.ParamChanged() ||
      environment_controller_.MotionDetected()) {
    idle_timer_.Reset();
  }

  if (battery_low) {
    state_ = RunnerState::LOW_POWER;
  } else {
    if (test_lights_timer_.Active()) {
      state_ = RunnerState::TEST_LIGHTS;
    } else if (idle_timer_.Expired()) {
      state_ = RunnerState::IDLE;
    } else {
      state_ = RunnerState::NORMAL;
    }
  }

  switch (state_) {
    case RunnerState::LOW_POWER:
      low_power_effect_.Step();
      break;

    case RunnerState::IDLE:
      idle_effect_.Step();
      break;

    case RunnerState::NORMAL:
      interface_controller_.Step();
      break;

    case RunnerState::TEST_LIGHTS:
      test_lights_effect_.Step();
      break;
  }

  logger_.Step();
}

RunnerState Runner::State() { return state_; }
