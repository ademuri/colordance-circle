#ifndef CONTROLS_H_
#define CONTROLS_H_

#include "ColordanceTypes.hpp"

static const uint32_t kSerialBaud = 115200;

enum class RunnerState {
  LOW_POWER,
  IDLE,
  TEST_LIGHTS,
  NORMAL,
};

struct ControlsIn {
  uint16_t button_mask = 0;
  static const uint8_t kAnalogInputSize = 6;
  uint8_t analog_inputs[kAnalogInputSize] = {0};
  bool alive = false;
};

struct ControlsOut {
  RunnerState runner_state = RunnerState::NORMAL;
};

#endif  // CONTROLS_H_