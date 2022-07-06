#pragma once

#include <vector>

#include "ParamController.hpp"

class SerialParamController : public ParamController {
 public:
  void Run() override;

  uint8_t GetRawParam(Param param) override;

 private:
  std::vector<uint8_t> params =
      std::vector<uint8_t>(static_cast<std::size_t>(Param::kLastParam));
};
