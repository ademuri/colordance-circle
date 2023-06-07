#include "FakeLogger.hpp"

#include <cstdio>

char* FakeLogger::GetTimestamp() {
  static constexpr uint32_t kBufferSize = 30;
  static char buffer[kBufferSize];

  snprintf(buffer, kBufferSize, "1970-01-01 00:00:00");
  return buffer;
}
