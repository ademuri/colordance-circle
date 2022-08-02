#ifndef SPI_PARAM_CONTROLLER_H_
#define SPI_PARAM_CONTROLLER_H_

#include <EasyTransfer.h>

#include <vector>

#include "Controls.hpp"
#include "ParamController.hpp"

// Reads from the physical (real) interface over a serial (UART) port.
class SerialParamController : public ParamController {
 public:
  SerialParamController();

  void Step() override;

  uint8_t GetRawParam(Param param) const override;

  ControlsIn controls_in = {};
  ControlsOut controls_out = {};

 private:
  // Prints the param values to the serial console.
  void DumpParams();

  static constexpr bool kDumpParams = false;

  EasyTransfer transfer_in_;
  EasyTransfer transfer_out_;

  uint8_t effect_ = 0;
  static constexpr int kLedPin = 13;
};

#endif  // SPI_PARAM_CONTROLLER_H_