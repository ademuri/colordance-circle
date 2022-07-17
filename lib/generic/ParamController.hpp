#pragma once

#include <vector>

#include "ColordanceTypes.hpp"

enum class Param {
  kBeat,
  kLoopShift,
  kShift,
  kPause,
  kEffect,
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
  virtual ~ParamController(){};

  virtual uint8_t GetRawParam(Param param) = 0;

  virtual int16_t GetScaledParam(Param param, int16_t min, int16_t max);

  // Perform periodic work
  virtual void Step(){};

 protected:
  std::vector<uint8_t> params_ =
      std::vector<uint8_t>(static_cast<std::size_t>(Param::kLastParam));
};
