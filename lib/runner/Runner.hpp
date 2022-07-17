#pragma once

#include "EnvironmentController.hpp"
#include "IdleEffect.hpp"
#include "LowPowerEffect.hpp"
#include "ParamController.hpp"
#include "Timer.hpp"
#include "interface/InterfaceController.hpp"

enum class RunnerState {
  LOW_POWER,
  IDLE,
  NORMAL,
};

class Runner {
 public:
  Runner(Poles& poles, ParamController& param_controller,
         EnvironmentController& environment_controller);

  // Runs one iteration. Non-blocking.
  void Step();

  RunnerState State();

  // How long to wait to go to idle mode after the last user interaction.
  static constexpr uint32_t kIdleTimeout = 5 * 60 * 1000;

 private:
  ParamController& param_controller_;
  EnvironmentController& environment_controller_;
  InterfaceController interface_controller_;
  LowPowerEffect low_power_effect_;
  IdleEffect idle_effect_;

  RunnerState state_ = RunnerState::NORMAL;

  static constexpr uint16_t kBatteryLowThresholdMillivolts = 1170;
  // Once the battery drops below the threshold, it must exceed the threshold by
  // this amount before we consider the battery OK.
  static constexpr uint16_t kBatteryDeadBandMillivolts = 30;

  Timer idle_timer_ = Timer(kIdleTimeout);
};