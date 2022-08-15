#include "Effect.hpp"

#include "ColordanceTypes.hpp"

Effect::Effect(Poles& poles, Buttons& buttons, ParamController& paramController)
    : poles_(poles), buttons_(buttons), paramController_(paramController) {}

void Effect::Step() {
  if (millis() > sleep_until_ms) {
    DoStep();
  }
}

void Effect::SleepMs(uint32_t ms_to_sleep) {
  if (ms_to_sleep == 0) {
    sleep_until_ms = 0;
  } else {
    sleep_until_ms = millis() + ms_to_sleep;
  }
}
