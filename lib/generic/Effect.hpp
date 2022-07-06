#pragma once

#include <memory>

#include "ParamController.hpp"
#include "Pole.hpp"

class Effect {
 public:
  Effect(Poles& poles, ParamController* paramController);
  virtual ~Effect() {}

  /* Runs one iteration of this effect. Non-blocking. */
  void Step();

 protected:
  /*
   * Internal method that contains the actual code for the effect. This code
   * can call SleepMs to delay execution of the effect (without blocking the
   * main loop).
   */
  virtual void DoStep() = 0;

  /*
   * Delays execution of this effect for the specified milliseconds, or 0 to
   * disable.
   */
  void SleepMs(uint32_t ms_to_sleep);

  Poles& poles;
  ParamController* paramController;

 private:
  uint32_t sleep_until_ms = 0;
};
