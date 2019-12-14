#ifndef PARAM_CONTROLLER_HPP_
#define PARAM_CONTROLLER_HPP_

#include "ColordanceTypes.hpp"

enum class Param {
  kMode,
  kEffectIndex,

  // Sentinel value, used for sizing. Needs to be the last param.
  kLastParam,
};

class ParamController {
 public:
  ParamController();

  virtual uint8_t GetRawParam(Param param) = 0;
};

#endif  // PARAM_CONTROLLER_HPP_
