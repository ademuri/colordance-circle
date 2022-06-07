#ifndef DUMMY_PARAM_CONTROLLER_HPP_
#define DUMMY_PARAM_CONTROLLER_HPP_

#include <vector>

#include "ColordanceTypes.hpp"
#include "ParamController.hpp"

class DummyParamController : public ParamController {
 public:
  DummyParamController();

  uint8_t GetRawParam(Param param) override;

  void SetRawParam(Param param, uint8_t value);

 private:
  // TODO: It is unclear what this is trying to do. It currently constructs an
  // empty vector.
  std::vector<uint8_t> params =
      std::vector<uint8_t>(static_cast<uint8_t>(Param::kLastParam), 0);
};

#endif  // PARAM_CONTROLLER_HPP_
