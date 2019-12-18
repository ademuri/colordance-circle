#ifndef SERIAL_PARAM_CONTROLLER_HPP_
#define SERIAL_PARAM_CONTROLLER_HPP_

#include "ParamController.hpp"

class SerialParamController : public ParamController {
 public:
  SerialParamController();

  void Tick();

  uint8_t GetRawParam(Param param);

 private:
  uint8_t mode;
  uint8_t effect_index;
};

#endif  // SERIAL_PARAM_CONTROLLER_HPP_
