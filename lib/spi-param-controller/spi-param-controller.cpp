#include "spi-param-controller.h"

#include <EasyTransfer.h>
#include <SPI.h>

SpiParamController::SpiParamController() {
  Serial2.begin(kSerialBaud);
  transfer_in_.begin(details(controls_in), &Serial2);
  transfer_out_.begin(details(controls_out), &Serial2);
}

void SpiParamController::Run() {
  transfer_in_.receiveData();
  transfer_out_.sendData();
  
  // Effects 0-6
  
  for(uint8_t i = 0; i < 7; i++) {
    if((controls_in.button_mask & (1<<i)) != 0) {
      effect = i;
    }
  }
  params[static_cast<uint8_t>(Param::kEffect)] = effect;

  //Beat 7
  if((controls_in.button_mask & (1<<7)) != 0) {
    params[static_cast<uint8_t>(Param::kBeat)] = 1;
  } else {
    params[static_cast<uint8_t>(Param::kBeat)] = 0;
  }

  //Timing 8
  if((controls_in.button_mask & (1<<8)) != 0) {
    params[static_cast<uint8_t>(Param::kShift)] = 1;
  } else {
    params[static_cast<uint8_t>(Param::kShift)] = 0;
  }

  //Pause 9
  if((controls_in.button_mask & (1<<9)) != 0) {
    params[static_cast<uint8_t>(Param::kPause)] = 1;
  } else {
    params[static_cast<uint8_t>(Param::kPause)] = 0;
  }

  //Option 1 = 10
  if((controls_in.button_mask & (1<<10)) != 0) {
    params[static_cast<uint8_t>(Param::kOption1)] = 1;
  } else {
    params[static_cast<uint8_t>(Param::kOption1)] = 0;
  }

  //Option 2 = 11
  if((controls_in.button_mask & (1<<11)) != 0) {
    params[static_cast<uint8_t>(Param::kOption2)] = 1;
  } else {
    params[static_cast<uint8_t>(Param::kOption2)] = 0;
  }

  params[static_cast<uint8_t>(Param::kSlider1)] = controls_in.analog_inputs[0];
  params[static_cast<uint8_t>(Param::kSlider2)] = controls_in.analog_inputs[1 ];

  params[static_cast<uint8_t>(Param::kLoopShift)] = 1;

}

uint8_t SpiParamController::GetRawParam(Param param) {
  return params[static_cast<uint8_t>(param)];
}