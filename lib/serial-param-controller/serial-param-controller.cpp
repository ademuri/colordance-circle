#include "serial-param-controller.h"

#include <EasyTransfer.h>
#include <SPI.h>

SerialParamController::SerialParamController() {
  Serial6.begin(kSerialBaud);
  transfer_in_.begin(details(controls_in), &Serial6);
  transfer_out_.begin(details(controls_out), &Serial6);
}

void SerialParamController::Step() {
  transfer_in_.receiveData();
  transfer_out_.sendData();

  // Effects 0-6

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

  ParamController::Step();
}

uint8_t SerialParamController::GetRawParam(Param param) const {
  return params_[static_cast<uint8_t>(param)];
}