#ifndef PARAM_CONTROLLER_HPP_
#define PARAM_CONTROLLER_HPP_

#include "ColordanceTypes.hpp"

enum class Param {
  kBeat,
  kLoopShift,
  kShift,
  kPause,
  kOption1,
  kOption2,
  kSlider1,
  kSlider2,
  // Sentinel value, used for sizing. Needs to be the last param.
  kLastParam,
};

class ParamController {
 public:
  ParamController();

  virtual uint8_t GetRawParam(Param param) = 0;

  virtual int16_t GetScaledParam(Param param, int16_t min, int16_t max);
};

#endif  // PARAM_CONTROLLER_HPP_
