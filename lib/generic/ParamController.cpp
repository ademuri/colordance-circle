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

void ParamController::ParseControlsIn(const ControlsIn& controls_in) {
  for (uint8_t i = 0; i < 7; i++) {
    if ((controls_in.button_mask & (1 << i)) != 0) {
      effect_ = i;
    }
  }
  params_[static_cast<uint8_t>(Param::kEffect)] = effect_;

  // Beat 7
  if ((controls_in.button_mask & (1 << 7)) != 0) {
    params_[static_cast<uint8_t>(Param::kBeat)] = 1;
  } else {
    params_[static_cast<uint8_t>(Param::kBeat)] = 0;
  }

  // Timing 8
  if ((controls_in.button_mask & (1 << 8)) != 0) {
    params_[static_cast<uint8_t>(Param::kShift)] = 1;
  } else {
    params_[static_cast<uint8_t>(Param::kShift)] = 0;
  }

  // Pause 9
  if ((controls_in.button_mask & (1 << 9)) != 0) {
    params_[static_cast<uint8_t>(Param::kPause)] = 1;
  } else {
    params_[static_cast<uint8_t>(Param::kPause)] = 0;
  }

  // Option 1 = 10
  if ((controls_in.button_mask & (1 << 10)) != 0) {
    params_[static_cast<uint8_t>(Param::kOption1)] = 1;
  } else {
    params_[static_cast<uint8_t>(Param::kOption1)] = 0;
  }

  // Option 2 = 11
  if ((controls_in.button_mask & (1 << 11)) != 0) {
    params_[static_cast<uint8_t>(Param::kOption2)] = 1;
  } else {
    params_[static_cast<uint8_t>(Param::kOption2)] = 0;
  }

  params_[static_cast<uint8_t>(Param::kSlider1)] = controls_in.analog_inputs[0];
  params_[static_cast<uint8_t>(Param::kSlider2)] = controls_in.analog_inputs[1];

  params_[static_cast<uint8_t>(Param::kLoopShift)] = 1;
}
