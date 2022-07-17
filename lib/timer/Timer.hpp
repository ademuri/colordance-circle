#pragma once

#include "ColordanceTypes.hpp"

class Timer {
 public:
  Timer(uint32_t duration);

  void Reset() {
    started_ = true;
    expires_ = millis() + duration_;
  }
  bool Expired() { return started_ && millis() > expires_; }
  bool Active() { return started_ && millis() <= expires_; }

 protected:
  uint32_t duration_;
  uint32_t expires_ = 0;
  bool started_ = false;
};
