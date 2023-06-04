#pragma once

#include <array>

#include "ColordanceTypes.hpp"
#include "Controls.hpp"

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

using Params = std::array<uint8_t, static_cast<std::size_t>(Param::kLastParam)>;

class ParamController {
 public:
  ParamController();
  virtual ~ParamController(){};

  virtual uint8_t GetRawParam(Param param) const = 0;

  virtual int16_t GetScaledParam(Param param, int16_t min, int16_t max) const;

  // Whether a param changed in the most recent call to Step.
  bool ParamChanged() const;

  // Perform periodic work
  virtual void Step();

  // Visible for testing
  void ParseControlsIn(const ControlsIn& in);

 protected:
  Params params_ =
      std::array<uint8_t, static_cast<std::size_t>(Param::kLastParam)>();
  bool param_changed_ = false;
  uint8_t effect_ = 0;

 private:
  Params prev_params_ =
      std::array<uint8_t, static_cast<std::size_t>(Param::kLastParam)>();
};
