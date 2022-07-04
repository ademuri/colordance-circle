#pragma once

#include <vector>

#include "ColordanceTypes.hpp"
#include "ControlPoleEffect.hpp"

class ControlPoleEffectCircle : public ControlPoleEffect {
 public:
  ControlPoleEffectCircle();
  uint8_t GetRotations() override;

 protected:
  void DoSetGrid(Grid<CHSV>& grid_lights,
                 uint8_t shiftIndex) override;
  uint8_t GetShiftsPerLoop() override;

 private:
  uint8_t GetIndex(uint8_t shiftIndex);
};
