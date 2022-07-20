#pragma once

#include <vector>

#include "ParamController.hpp"

// Reads params over stdin, from the Processing controller.
class StdinParamController : public ParamController {
 public:
  void Step() override;

  uint8_t GetRawParam(Param param) const override;
};
