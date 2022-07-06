#pragma once

#include "ParamController.hpp"
#include "interface/InterfaceController.hpp"

class Runner {
 public:
  Runner(Poles poles, ParamController& param_controller);

  // Runs one iteration. Non-blocking.
  void Step();

 private:
  ParamController& param_controller_;
  InterfaceController interface_controller_;
};