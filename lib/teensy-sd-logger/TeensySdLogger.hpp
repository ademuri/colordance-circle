#pragma once

#include <SD.h>

#include "Logger.hpp"

class TeensySdLogger : public Logger {
 public:
  TeensySdLogger(const ParamController& param_controller,
                 const EnvironmentController& environment_controller);

 protected:
  void Log(const char* message) override;

 private:
  bool sd_init_ = false;
  File log_file_;
};
