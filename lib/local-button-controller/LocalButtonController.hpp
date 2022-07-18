#pragma once

#include "ColordanceTypes.hpp"
#include "ParamController.hpp"

class LocalButtonController : public ParamController {
 public:
  LocalButtonController();

  uint8_t GetRawParam(Param param) const override { return 0; };

  bool Random();
  bool Next();

 private:
  const int kRandomPin = 2;
  const int kNextPin = 3;

  bool randomOn = false;
  bool nextOn = false;

  bool randomInit = false;
};
