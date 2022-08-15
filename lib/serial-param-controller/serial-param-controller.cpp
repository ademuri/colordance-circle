#include "serial-param-controller.h"

#include <EasyTransfer.h>
#include <SPI.h>

SerialParamController::SerialParamController() {
  Serial6.begin(kSerialBaud);
  transfer_in_.begin(details(controls_in), &Serial6);
  transfer_out_.begin(details(controls_out), &Serial6);
  pinMode(kLedPin, OUTPUT);
}

void SerialParamController::Step() {
  static uint32_t print_at = 0;
  transfer_out_.sendData();
  // Briefly wait, to make sure that the interface has sent data before we call
  // `receiveData`
  delay(3);
  if (!transfer_in_.receiveData()) {
    return;
  }

  // Blink the onboard LED to show that communication is working
  digitalWrite(kLedPin, controls_in.alive);

  if (kDumpParams && millis() > print_at) {
    DumpParams();
    print_at = millis() + 500;
  }

  ParseControlsIn(controls_in);
  ParamController::Step();
}

void SerialParamController::SetRunnerState(RunnerState state) {
  controls_out.runner_state = state;
}

uint8_t SerialParamController::GetRawParam(Param param) const {
  return params_[static_cast<uint8_t>(param)];
}

void SerialParamController::DumpParams() {
  Serial.print("buttons: ");
  for (int8_t n = 12; n >= 0; --n) {
    Serial.print((controls_in.button_mask >> n) & 1);
  }
  Serial.println();
  Serial.print("analog: ");
  for (uint8_t n = 0; n < controls_in.kAnalogInputSize; n++) {
    // Manual padding
    if (controls_in.analog_inputs[n] < 10) {
      Serial.print(" ");
    }
    if (controls_in.analog_inputs[n] < 100) {
      Serial.print(" ");
    }
    Serial.print(controls_in.analog_inputs[n]);
    Serial.print(" ");
  }
  Serial.println("\n");
}
