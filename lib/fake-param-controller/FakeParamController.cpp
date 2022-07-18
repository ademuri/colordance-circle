#include "FakeParamController.hpp"

uint8_t FakeParamController::GetRawParam(Param param) const {
  return params_[static_cast<uint8_t>(param)];
}

void FakeParamController::SetRawParam(Param param, uint8_t value) {
  params_[static_cast<uint8_t>(param)] = value;
}
