#ifndef SERIAL_PARAM_CONTROLLER_HPP_
#define SERIAL_PARAM_CONTROLLER_HPP_

#include <vector>

#include "ParamController.hpp"

class SerialParamController : public ParamController {
 public:
  SerialParamController();

  void Tick();

  uint8_t GetRawParam(Param param);

 private:
  std::vector<uint8_t> params =
      std::vector<uint8_t>(static_cast<uint8_t>(Param::kLastParam), 0);
};

#endif  // SERIAL_PARAM_CONTROLLER_HPP_
