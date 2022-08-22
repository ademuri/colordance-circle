#include "StdinParamController.hpp"

#include <iostream>
#include <string>

void StdinParamController::Step() {
  std::string input = "";
  // Note: this blocks on user input. But, non-blocking input is not
  // platform-independent. We work around this by making the controller spam
  // newlines. Sorry, mom.
  std::getline(std::cin, input);
  if (input.length() >= 4 && input[1] == ':') {
    uint8_t val = std::stoi(&input[2]);
    switch (input[0]) {
      case 'b':
        params_[static_cast<uint8_t>(Param::kBeat)] = val;
        break;
      case 'l':
        params_[static_cast<uint8_t>(Param::kLoopShift)] = val;
        break;
      case 'e':
        params_[static_cast<uint8_t>(Param::kEffect)] = val;
        break;
      case 'p':
        params_[static_cast<uint8_t>(Param::kPause)] = val;
        break;
      case 's':
        params_[static_cast<uint8_t>(Param::kShift)] = val;
        break;
      case 'v':
        params_[static_cast<uint8_t>(Param::kSlider1)] = val;
        break;
      case 'w':
        params_[static_cast<uint8_t>(Param::kSlider2)] = val;
        break;
      case 'x':
        params_[static_cast<uint8_t>(Param::kOption1)] = val;
        break;
      case 'y':
        params_[static_cast<uint8_t>(Param::kOption2)] = val;
        break;
      default:
        break;
    }
  }
  ParamController::Step();
}

uint8_t StdinParamController::GetRawParam(Param param) const {
  return params_[static_cast<uint8_t>(param)];
}
