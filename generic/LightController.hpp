#ifndef LIGHT_CONTROLLER_HPP_
#define LIGHT_CONTROLLER_HPP_

#include <vector>
#include "Pole.hpp"

class LightController {
 public:
  LightController();

  virtual void WriteOutLights() = 0;

  std::vector<Pole*> get_poles();

 protected:
  std::vector<Pole*> poles;
};

#endif
