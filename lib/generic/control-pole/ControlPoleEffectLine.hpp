#pragma once

#include <vector>

#include "ColordanceTypes.hpp"
#include "ControlPoleEffect.hpp"

class ControlPoleEffectLine : public ControlPoleEffect {
 public:
  ControlPoleEffectLine();
  uint8_t GetRotations() override;

 protected:
  void DoSetGrid(Grid<CHSV>& grid_lights,
                 uint8_t shiftIndex) override;
  uint8_t GetShiftsPerLoop() override;
};
