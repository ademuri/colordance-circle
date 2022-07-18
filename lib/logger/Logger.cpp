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
  if (!log_timer_.Expired()) {
    return;
  }
  static char line[kLogLineBytes];
  size_t ret = snprintf(line, kLogLineBytes, "%d\n",
                        param_controller_.GetRawParam(Param::kEffect));

#ifndef ARDUINO
  if (ret <= 0) {
    std::cout << "Logger: call to snprintf failed: " << ret << "\n";
  }
  assert(ret > 0);
  if (ret >= kLogLineBytes) {
    std::cout << "Logger: buffer size was too small: " << ret << "\n";
  }
  assert(ret < kLogLineBytes);
#endif

  if (ret > 0) {
    Log(line);
  }

  log_timer_.Reset();
}