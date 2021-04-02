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
      case 'a':
        params[static_cast<uint8_t>(Param::kBeatReset)] =
            in.substring(2).toInt();
        break;

      case 'b':
        params[static_cast<uint8_t>(Param::kBpm)] = in.substring(2).toInt();
        break;

      case 'c':
        params[static_cast<uint8_t>(Param::kGridLightCount)] =
            in.substring(2).toInt();
        break;

      case 'd':
        params[static_cast<uint8_t>(Param::kGridHueDistance)] =
            in.substring(2).toInt();
        break;

      case 'e':
        params[static_cast<uint8_t>(Param::kGridSpeed)] =
            in.substring(2).toInt();
        break;

      case 'f':
        params[static_cast<uint8_t>(Param::kGridBackForth)] =
            in.substring(2).toInt();
        break;

      case 'g':
        params[static_cast<uint8_t>(Param::kGridMode)] =
            in.substring(2).toInt();
        break;

      case 'h':
        params[static_cast<uint8_t>(Param::kPollHueShift)] =
            in.substring(2).toInt();
        break;

      case 'i':
        params[static_cast<uint8_t>(Param::kGridHueShift)] =
            in.substring(2).toInt();
        break;

      case 'l':
        params[static_cast<uint8_t>(Param::kBalanceColor)] =
            in.substring(2).toInt();
        break;

      case 'm':
        params[static_cast<uint8_t>(Param::kMovementMode)] =
            in.substring(2).toInt();
        break;

      case 'o':
        params[static_cast<uint8_t>(Param::kGridSmoothColor)] =
            in.substring(2).toInt();
        break;

      case 'p':
        params[static_cast<uint8_t>(Param::kActivePoles)] =
            in.substring(2).toInt();
        break;

      case 'r':
        params[static_cast<uint8_t>(Param::kGridReverse)] =
            in.substring(2).toInt();
        break;

      case 's':
        params[static_cast<uint8_t>(Param::kMovementSpeed)] =
            in.substring(2).toInt();
        break;

      case 'u':
        params[static_cast<uint8_t>(Param::kPause)] = in.substring(2).toInt();
        break;

      default:
        break;
    }
  }
}

uint8_t SerialParamController::GetRawParam(Param param) {
  return params[static_cast<uint8_t>(param)];
}
