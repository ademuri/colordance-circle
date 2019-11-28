#ifndef LIGHT_CONTROLLER_HPP_
#define LIGHT_CONTROLLER_HPP_

#include <ColordanceTypes.hpp>
#include <vector>
#include "Pole.hpp"

class LightController {
 public:
  LightController();

  /* Writes the light values from the poles to the output device. */
  virtual void WriteOutLights() = 0;

  std::vector<Pole*> get_poles();

 protected:
  std::vector<Pole*> poles;
};

#endif
