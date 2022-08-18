#pragma once

#include "ColordanceTypes.hpp"
#include "Controls.hpp"
#include "ParamController.hpp"

class InterfaceParamController : public ParamController {
 public:
  InterfaceParamController(const ControlsIn& controls_in);

  void Step() override;

  uint8_t GetRawParam(Param param) const override;

 private:
  const ControlsIn& controls_in_;
};
