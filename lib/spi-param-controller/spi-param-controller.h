#ifndef SPI_PARAM_CONTROLLER_H_
#define SPI_PARAM_CONTROLLER_H_

#include "ParamController.hpp"

#include <vector>

class SpiParamController : public ParamController {
  public:
    SpiParamController();

    void Run();

    uint8_t GetRawParam(Param param) override;

  private:
    uint8_t button_mask_high;
    uint8_t button_mask_low;

    std::vector<uint8_t> analog_inputs;

    const uint8_t kNumAnalogInputs = 8;
};

#endif  // SPI_PARAM_CONTROLLER_H_