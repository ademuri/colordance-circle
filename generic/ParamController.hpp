#ifndef PARAM_CONTROLLER_HPP_
#define PARAM_CONTROLLER_HPP_

#include "ColordanceTypes.hpp"

class ParamController {
 public:
  ParamController();

  virtual uint8_t GetMode() = 0;
  virtual uint8_t GetEffectIndex() = 0;
};

#endif  // PARAM_CONTROLLER_HPP_
