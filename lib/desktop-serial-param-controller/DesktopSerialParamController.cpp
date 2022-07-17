#include "DesktopSerialParamController.hpp"

void DesktopSerialParamController::Step() {
  if (Serial.available() > 0) {
    String in = Serial.readStringUntil('\n');
    switch (in.charAt(0)) {
      case 'b':
        params_[static_cast<uint8_t>(Param::kBeat)] = in.substring(2).toInt();
        break;
      case 'l':
        params_[static_cast<uint8_t>(Param::kLoopShift)] =
            in.substring(2).toInt();
        break;
      case 'e':
        params_[static_cast<uint8_t>(Param::kEffect)] = in.substring(2).toInt();
        break;
      case 'p':
        params_[static_cast<uint8_t>(Param::kPause)] = in.substring(2).toInt();
        break;
      case 's':
        params_[static_cast<uint8_t>(Param::kShift)] = in.substring(2).toInt();
        break;
      case 'v':
        params_[static_cast<uint8_t>(Param::kSlider1)] =
            in.substring(2).toInt();
        break;
      case 'w':
        params_[static_cast<uint8_t>(Param::kSlider2)] =
            in.substring(2).toInt();
      case 'x':
        params_[static_cast<uint8_t>(Param::kOption1)] =
            in.substring(2).toInt();
      case 'y':
        params_[static_cast<uint8_t>(Param::kOption2)] =
            in.substring(2).toInt();
      default:
        break;
    }
  }

  ParamController::Step();
}

uint8_t DesktopSerialParamController::GetRawParam(Param param) {
  return params_[static_cast<uint8_t>(param)];
}
