#include "Timer.hpp"

#ifndef ARDUINO
#include <assert.h>
#endif

Timer::Timer(uint32_t duration) : duration_(duration) {
#ifndef ARDUINO
  assert(duration > 0);
#endif
}