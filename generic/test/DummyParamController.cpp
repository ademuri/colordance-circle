#include "DummyParamController.hpp"

DummyParamController::DummyParamController() : ParamController() {}

uint8_t DummyParamController::GetRawParam(Param param) {
  // Ignore unused
  (void)param;
  return 0;
}
