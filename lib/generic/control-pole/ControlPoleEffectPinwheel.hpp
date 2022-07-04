#pragma once

#include "ColordanceTypes.hpp"
#include "ControlPoleEffect.hpp"
#include "Grid.hpp"

class ControlPoleEffectPinwheel : public ControlPoleEffect {
 public:
  ControlPoleEffectPinwheel();
  uint8_t GetRotations() override;

 protected:
  void DoSetGrid(Grid<CHSV>& grid_lights, uint8_t shiftIndex) override;
  uint8_t GetShiftsPerLoop() override;

 private:
  uint8_t GetBigSquare(uint8_t shiftIndex);
  uint8_t GetLittleSquare(uint8_t shiftIndex);
};
