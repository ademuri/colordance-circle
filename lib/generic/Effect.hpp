#ifndef EFFECT_HPP_
#define EFFECT_HPP_

#include <memory>
#include <vector>

#include "ParamController.hpp"
#include "Pole.hpp"

class Effect {
 public:
  Effect(std::vector<Pole*> poles, std::unique_ptr<ParamController> paramController);

  /* Runs this effect. */
  void Run();

 protected:
  /*
   * Internal method that contains the actual code for the effect. This code
   * can call SleepMs to delay execution of the effect (without blocking the
   * main loop).
   */
  virtual void DoRun() = 0;

  /*
   * Delays execution of this effect for the specified milliseconds, or 0 to
   * disable.
   */
  void SleepMs(uint32_t ms_to_sleep);

  std::vector<Pole*> poles;
  std::unique_ptr<ParamController> paramController;

 private:
  uint32_t sleep_until_ms = 0;
};

#endif
