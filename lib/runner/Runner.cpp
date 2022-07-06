#include "Runner.hpp"

Runner::Runner(Poles poles, ParamController* param_controller)
    : param_controller_(param_controller), interface_controller_(poles, param_controller) {}

void Runner::Run() {
  param_controller_->Run();
  interface_controller_.Run();
}