#ifndef ARDUINO
#include <assert.h>

#include <iostream>
#endif

#include "Logger.hpp"

Logger::Logger(const ParamController& param_controller,
               const EnvironmentController& environment_controller)
    : param_controller_(param_controller),
      environment_controller_(environment_controller) {
  log_timer_.Reset();
}

void Logger::Step() {
  if (environment_controller_.MotionDetected()) {
    motion_detected_ = true;
  }
  if (param_controller_.ParamChanged()) {
    param_changed_ = true;
  }

  if (!log_timer_.Expired()) {
    return;
  }
  static char line[kLogLineBytes];
  int ret = snprintf(
      line, kLogLineBytes, "%10u, %d, %d, %d, %d, %04d, %d",
      // TODO: switch to real-time clock
      millis() / 1000, param_controller_.GetRawParam(Param::kEffect),
      param_controller_.GetRawParam(Param::kSlider1),
      param_controller_.GetRawParam(Param::kSlider2), param_changed_,
      environment_controller_.GetBatteryMillivolts(), motion_detected_);

#ifndef ARDUINO
  if (ret <= 0) {
    std::cout << "Logger: call to snprintf failed: " << ret << "\n";
  }
  assert(ret > 0);
  if (ret >= (int)kLogLineBytes) {
    std::cout << "Logger: buffer size was too small: " << ret << "\n";
  }
  assert(ret < (int)kLogLineBytes);
#endif

  if (ret > 0) {
    Log(line);
  }

  log_timer_.Reset();
  motion_detected_ = false;
  param_changed_ = false;
}