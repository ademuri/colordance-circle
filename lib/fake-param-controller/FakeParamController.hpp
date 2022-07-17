#pragma once

#include <vector>

#include "ColordanceTypes.hpp"
#include "ParamController.hpp"

class FakeParamController : public ParamController {
 public:
  uint8_t GetRawParam(Param param) override;

  void SetRawParam(Param param, uint8_t value);
};
