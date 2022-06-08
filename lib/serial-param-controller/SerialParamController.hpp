#pragma once

#include <vector>

#include "ParamController.hpp"

class SerialParamController : public ParamController {
 public:
  SerialParamController();

  void Tick();

  uint8_t GetRawParam(Param param);

 private:
  // TODO: It is unclear what this is trying to do. It currently constructs an
  // empty vector.
  std::vector<uint8_t> params =
      std::vector<uint8_t>(static_cast<uint8_t>(Param::kLastParam), 0);
};
