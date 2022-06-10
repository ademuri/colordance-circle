#include "spi-param-controller.h"

#include <EasyTransfer.h>
#include <SPI.h>

SpiParamController::SpiParamController() {
  Serial2.begin(kSerialBaud);
  transfer_in_.begin(details(controls_in), &Serial2);
  transfer_out_.begin(details(controls_out), &Serial2);
}

void SpiParamController::Run() {
  controls_out.test++;
  transfer_in_.receiveData();
  transfer_out_.sendData();
}

uint8_t GetRawParam(Param param) {
  // TODO: map raw inputs to Params
  return 0;
}