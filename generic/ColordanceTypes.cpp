#include "ColordanceTypes.hpp"

#ifdef ARDUINO
namespace std {
void __throw_bad_alloc() { Serial.println("Unable to allocate memory"); }

void __throw_length_error(char const* e) {
  Serial.print("Length Error :");
  Serial.println(e);
}
}  // namespace std

#else
uint32_t millis() {
  static const std::chrono::steady_clock::time_point start_time =
      std::chrono::steady_clock::now();

  const std::chrono::steady_clock::time_point end_time =
      std::chrono::steady_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(end_time -
                                                               start_time)
      .count();
}
#endif
