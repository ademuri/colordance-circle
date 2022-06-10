#ifndef CONTROLS_H_
#define CONTROLS_H_

#include <ColordanceTypes.hpp>

static const uint32_t kSerialBaud = 115200;

struct ControlsIn {
  uint16_t button_mask;
  static const uint8_t kAnalogInputSize = 8;
  uint8_t analog_inputs[kAnalogInputSize];
};

struct ControlsOut {
  uint8_t test;
  // TODO
};

#endif  // CONTROLS_H_