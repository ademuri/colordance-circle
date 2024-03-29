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

  // Writes out the log message.
  virtual void Log(const char* message) { UNUSED(message); }

 protected:
  virtual char* GetTimestamp() = 0;

  Timer log_timer_{kLogIntervalMillis};

 private:
  const ParamController& param_controller_;
  const EnvironmentController& environment_controller_;

  bool motion_detected_ = false;
  bool param_changed_ = false;
};
