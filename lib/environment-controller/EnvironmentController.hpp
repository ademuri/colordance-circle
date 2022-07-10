#pragma once

#include <ColordanceTypes.hpp>

// Reads environmental inputs such as battery voltage and motion sensors.
class EnvironmentController {
 public:
  EnvironmentController(){};

  virtual void Step() = 0;

  // Returns the system battery voltage, in millivolts.
  virtual uint16_t GetBatteryMillivolts() = 0;

  // Returns true when the onboard "test lights" button is pressed.
  virtual bool TestLightsPressed() = 0;
};