#include "ParamController.hpp"

ParamController::ParamController() {}

int16_t ParamController::GetScaledParam(Param param, int16_t min, int16_t max) {
  const int16_t original = GetRawParam(param);

  return min + ((max - min) * original) / 255;
}
