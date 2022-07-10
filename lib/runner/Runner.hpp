#pragma once

#include "EnvironmentController.hpp"
#include "LowPowerEffect.hpp"
#include "ParamController.hpp"
#include "interface/InterfaceController.hpp"

class Runner {
 public:
  Runner(Poles& poles, ParamController& param_controller,
         EnvironmentController& environment_controller);

  // Runs one iteration. Non-blocking.
  void Step();

 private:
  ParamController& param_controller_;
  EnvironmentController& environment_controller_;
  InterfaceController interface_controller_;
  LowPowerEffect low_power_effect_;

  static constexpr uint16_t kBatteryLowThresholdMillivolts = 1170;
};