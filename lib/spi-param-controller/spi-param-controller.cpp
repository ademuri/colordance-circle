#include "spi-param-controller.h"

#include <SPI.h>

SpiParamController::SpiParamController() {
  for (int i = 0; i < kNumAnalogInputs; i++) {
    analog_inputs.emplace_back(0);
  }
}

void SpiParamController::Run() {
  // TODO: the SPI peripheral library doesn't seem to have settings, are these
  // correct?
  SPI1.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(38, LOW);

  button_mask_high = SPI1.transfer(0);
  button_mask_low = SPI1.transfer(0);

  for (int i = 0; i < kNumAnalogInputs; i++) {
    analog_inputs[i] = SPI1.transfer(0);
  }

  digitalWrite(38, HIGH);
  SPI1.endTransaction();
}

uint8_t GetRawParam(Param param) {
  // TODO: map raw inputs to Params
  return 0;
}