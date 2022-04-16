#include "SerialParamController.hpp"

SerialParamController::SerialParamController() {
  for (uint8_t i = 0; i < static_cast<uint8_t>(Param::kLastParam); i++) {
    params.push_back(0);
  }
}

void SerialParamController::Tick() {
  if (Serial.available() > 0) {
    String in = Serial.readStringUntil('\n');
    switch (in.charAt(0)) {
      case 'b':
        params[static_cast<uint8_t>(Param::kBeat)] = in.substring(2).toInt();
        break;
      case 'l':
        params[static_cast<uint8_t>(Param::kLoopShift)] =
            in.substring(2).toInt();
        break;
      case 'p':
        params[static_cast<uint8_t>(Param::kPause)] = in.substring(2).toInt();
        break;
      case 's':
        params[static_cast<uint8_t>(Param::kShift)] = in.substring(2).toInt();
        break;

      default:
        break;
    }
  }
}

uint8_t SerialParamController::GetRawParam(Param param) {
  return params[static_cast<uint8_t>(param)];
}
