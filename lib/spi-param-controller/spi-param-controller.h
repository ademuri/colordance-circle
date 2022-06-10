#ifndef SPI_PARAM_CONTROLLER_H_
#define SPI_PARAM_CONTROLLER_H_

#include <vector>
#include <EasyTransfer.h>

#include "Controls.hpp"
#include "ParamController.hpp"

class SpiParamController : public ParamController {
 public:
  SpiParamController();

  void Run();

  uint8_t GetRawParam(Param param) override;

  ControlsIn controls_in = {};
  ControlsOut controls_out = {};

 private:
  EasyTransfer transfer_in_;
  EasyTransfer transfer_out_;
};

#endif  // SPI_PARAM_CONTROLLER_H_