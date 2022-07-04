#include "DummyParamController.hpp"

uint8_t DummyParamController::GetRawParam(Param param) {
  return params[static_cast<uint8_t>(param)];
}

void DummyParamController::SetRawParam(Param param, uint8_t value) {
  params[static_cast<uint8_t>(param)] = value;
}
