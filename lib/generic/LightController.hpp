#pragma once

#include <ColordanceTypes.hpp>
#include <vector>

#include "Pole.hpp"

class LightController {
 public:
  /* Writes the light values from the poles to the output device. */
  virtual void WriteOutLights() = 0;

  std::vector<Pole*> const& get_poles() const { return poles; }

 protected:
  std::vector<Pole*> poles;
};
