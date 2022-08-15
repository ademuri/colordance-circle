#include "InterfaceParamController.hpp"

InterfaceParamController::InterfaceParamController(
    const ControlsIn& controls_in)
    : controls_in_(controls_in) {}

void InterfaceParamController::Step() {
    ParseControlsIn(controls_in_);
    ParamController::Step();
}

uint8_t InterfaceParamController::GetRawParam(Param param) const {
  return params_[static_cast<uint8_t>(param)];
}