#include "Types.hpp"

uint32_t millis() {
  static const std::chrono::steady_clock::time_point start_time =
      std::chrono::steady_clock::now();

  const std::chrono::steady_clock::time_point end_time =
      std::chrono::steady_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(end_time -
                                                               start_time)
      .count();
}
