#include "Effect.hpp"
#include "ColordanceTypes.hpp"

Effect::Effect(std::vector<Pole*> poles) : poles(poles) {}

void Effect::Run() {
  if (millis() > sleep_until_ms) {
    DoRun();
  }
}

void Effect::SleepMs(uint32_t ms_to_sleep) {
  if (ms_to_sleep == 0) {
    sleep_until_ms = 0;
  } else {
    sleep_until_ms = millis() + ms_to_sleep;
  }
}
