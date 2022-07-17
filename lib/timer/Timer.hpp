#pragma once

#include "ColordanceTypes.hpp"

class Timer {
 public:
  Timer(uint32_t duration);

  void Reset() { expires_ = millis() + duration_; }
  bool Expired() { return expires_ > 0 && millis() > expires_; }

 protected:
  uint32_t duration_;
  uint32_t expires_ = 0;
};
