#pragma once

#include "ColordanceTypes.hpp"
#include "ControlPoleEffect.hpp"
#include "Grid.hpp"

class ControlPoleEffectDiverge : public ControlPoleEffect {
 public:
  ControlPoleEffectDiverge();
  uint8_t GetRotations() override;

 protected:
  void DoSetGrid(Grid<CHSV>& grid_lights,
                 uint8_t shiftIndex) override;
  uint8_t GetShiftsPerLoop() override;
};
