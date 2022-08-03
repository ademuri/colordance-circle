#pragma once

#include <SD.h>

#include "Logger.hpp"
#include "Timer.hpp"

class TeensySdLogger : public Logger {
 public:
  TeensySdLogger(const ParamController& param_controller,
                 const EnvironmentController& environment_controller);

 protected:
  void Log(const char* message) override;

 private:
  bool sd_init_ = false;
  File log_file_;

  // Used to flush the SD card cache periodically. We will lose up to this
  // interval worth of data when we're powered off.
  Timer sd_flush_timer_{5 * 60 * 1000};
};
