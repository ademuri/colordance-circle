#pragma once

#include <vector>

#include "ColordanceTypes.hpp"
#include "ControlPoleEffect.hpp"

class ControlPoleEffectDiverge : public ControlPoleEffect {
 public:
  ControlPoleEffectDiverge();
  uint8_t GetRotations() override;

 protected:
  void DoSetGrid(std::vector<std::vector<CHSV>>& grid_lights,
                 uint8_t shiftIndex) override;
  uint8_t GetShiftsPerLoop() override;
};
