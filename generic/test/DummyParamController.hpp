#ifndef DUMMY_PARAM_CONTROLLER_HPP_
#define DUMMY_PARAM_CONTROLLER_HPP_

#include "ColordanceTypes.hpp"
#include "ParamController.hpp"

#include <vector>

class DummyParamController : public ParamController {
 public:
  DummyParamController();

  uint8_t GetRawParam(Param param) override;

  void SetRawParam(Param param, uint8_t value);

 private:
  std::vector<uint8_t> params =
      std::vector<uint8_t>(static_cast<uint8_t>(Param::kLastParam), 0);
};

#endif  // PARAM_CONTROLLER_HPP_
