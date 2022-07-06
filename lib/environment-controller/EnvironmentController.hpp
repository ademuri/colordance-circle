#pragma once

#include <ColordanceTypes.hpp>

class EnvironmentController {
 public:
  EnvironmentController(){};

  virtual void Run() = 0;

  // Returns the system battery voltage, in millivolts.
  virtual uint16_t GetBatteryMillivolts() = 0;

  // Returns true when the onboard "test lights" button is pressed.
  virtual bool TestLightsPressed() = 0;
};