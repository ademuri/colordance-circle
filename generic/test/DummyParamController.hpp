#ifndef DUMMY_PARAM_CONTROLLER_HPP_
#define DUMMY_PARAM_CONTROLLER_HPP_

#include "ColordanceTypes.hpp"
#include "ParamController.hpp"

class DummyParamController : public ParamController {
 public:
  DummyParamController();

  uint8_t GetMode() override;
  uint8_t GetEffectIndex() override;
};

#endif  // PARAM_CONTROLLER_HPP_
