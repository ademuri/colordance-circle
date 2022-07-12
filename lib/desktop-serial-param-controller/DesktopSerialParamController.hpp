#pragma once

#include <vector>

#include "ParamController.hpp"

// Reads params over `Serial` (typically USB serial). Works with the Processing
// interface.
class DesktopSerialParamController : public ParamController {
 public:
  void Step() override;

  uint8_t GetRawParam(Param param) override;

 private:
  std::vector<uint8_t> params =
      std::vector<uint8_t>(static_cast<std::size_t>(Param::kLastParam));
};
