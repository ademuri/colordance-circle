#pragma once

#include "Logger.hpp"

class FakeLogger : public Logger {
 public:
  FakeLogger(const ParamController& param_controller,
             const EnvironmentController& environment_controller)
      : Logger(param_controller, environment_controller) {}

  const char* PreviousMessage() const { return prev_message_; }

  void ResetTimerForTest() { log_timer_.Reset(); }

  void Log(const char* message) override {
    strncpy(prev_message_, message, kLogLineBytes);
  }

 protected:
  char* GetTimestamp() override;

 private:
  char prev_message_[kLogLineBytes] = "";
};
