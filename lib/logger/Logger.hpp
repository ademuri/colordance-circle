#pragma once

#include "ColordanceTypes.hpp"
#include "EnvironmentController.hpp"
#include "ParamController.hpp"
#include "Timer.hpp"

// Size of the string buffer for each log line.
static constexpr size_t kLogLineBytes = 500;

// Period for writing log messages.
static constexpr uint32_t kLogIntervalMillis = 10 * 1000;

class Logger {
 public:
  Logger(const ParamController& param_controller,
         const EnvironmentController& environment_controller);

  // Performs non-blocking work. Writes to logs periodically.
  void Step();

 protected:
  // Writes out the log message.
  virtual void Log(const char* message) { UNUSED(message); }

 private:
  const ParamController& param_controller_;
  const EnvironmentController& environment_controller_;

  Timer log_timer_{kLogIntervalMillis};
};
