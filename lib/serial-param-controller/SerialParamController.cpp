#include "SerialParamController.hpp"

void SerialParamController::Run() {
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
      case 'e':
        params[static_cast<uint8_t>(Param::kEffect)] = in.substring(2).toInt();
        break;
      case 'p':
        params[static_cast<uint8_t>(Param::kPause)] = in.substring(2).toInt();
        break;
      case 's':
        params[static_cast<uint8_t>(Param::kShift)] = in.substring(2).toInt();
        break;
      case 'v':
        params[static_cast<uint8_t>(Param::kSlider1)] = in.substring(2).toInt();
        break;
      case 'w':
        params[static_cast<uint8_t>(Param::kSlider2)] = in.substring(2).toInt();
      case 'x':
        params[static_cast<uint8_t>(Param::kOption1)] = in.substring(2).toInt();
      case 'y':
        params[static_cast<uint8_t>(Param::kOption2)] = in.substring(2).toInt();
      default:
        break;
    }
  }
}

uint8_t SerialParamController::GetRawParam(Param param) {
  return params[static_cast<uint8_t>(param)];
}
