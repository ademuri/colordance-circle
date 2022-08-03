#include "ColordanceTypes.hpp"

#include <assert.h>

#ifdef ARDUINO
// TODO: this is not needed when using certain libraries
// namespace std {
// void __throw_bad_alloc() { Serial.println("Unable to allocate memory"); }

// void __throw_length_error(char const* e) {
//   Serial.print("Length Error :");
//   Serial.println(e);
// }
// }  // namespace std

#else

uint32_t current_time = 0;
bool use_real_millis_ = false;

uint32_t millis() {
  if (use_real_millis_) {
    static const std::chrono::steady_clock::time_point start_time =
        std::chrono::steady_clock::now();

    const std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end_time -
                                                                 start_time)
        .count();
  } else {
    return current_time;
  }
}

void UseRealMillis() { use_real_millis_ = true; }

void SetMillis(uint32_t ms) {
  assert(!use_real_millis_);
  current_time = ms;
}

void AdvanceMillis(uint32_t ms) {
  assert(!use_real_millis_);
  current_time += ms;
}

#endif
