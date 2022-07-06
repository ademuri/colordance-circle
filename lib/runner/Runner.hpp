#pragma once

#include "ParamController.hpp"
#include "interface/InterfaceController.hpp"

class Runner {
 public:
  Runner(Poles poles, ParamController* param_controller);

  void Run();

 private:
  ParamController* const param_controller_;
  InterfaceController interface_controller_;
};