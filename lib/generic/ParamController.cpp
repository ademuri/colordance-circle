#include "ParamController.hpp"

ParamController::ParamController() {}

int16_t ParamController::GetScaledParam(Param param, int16_t min,
                                        int16_t max) const {
  const int16_t original = GetRawParam(param);

  return min + ((max - min) * original) / 255;
}

void ParamController::Step() {
  param_changed_ = false;
  for (size_t i = 0; i < params_.size(); ++i) {
    if (prev_params_[i] != params_[i]) {
      param_changed_ = true;
    }
  }
  prev_params_ = params_;
}

bool ParamController::ParamChanged() const { return param_changed_; }