#include "FakeParamController.hpp"

uint8_t FakeParamController::GetRawParam(Param param) {
  return params[static_cast<uint8_t>(param)];
}

void FakeParamController::SetRawParam(Param param, uint8_t value) {
  params[static_cast<uint8_t>(param)] = value;
}
