#ifndef EFFECT_HPP_
#define EFFECT_HPP_

#include <vector>
#include "Pole.hpp"

class Effect {
 public:
  Effect(std::vector<Pole*> poles);

  /* Runs this effect. */
  void Run();

 protected:
  /*
   * Internal method that contains the actual code for the effect. This code
   * can call SleepMs to delay execution of the effect (without blocking the
   * main loop).
   */
  virtual void DoRun() = 0;

  const std::vector<Pole*> poles;
};

#endif
