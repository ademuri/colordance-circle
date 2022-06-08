#pragma once

#include <vector>

#include "ColordanceTypes.hpp"
#include "ControlPoleEffect.hpp"

class ControlPoleEffectPinwheel : public ControlPoleEffect {
 public:
  ControlPoleEffectPinwheel();
  uint8_t GetRotations() override;

 protected:
  void DoSetGrid(std::vector<std::vector<CHSV>>& grid_lights,
                 uint8_t shiftIndex) override;
  uint8_t GetShiftsPerLoop() override;

 private:
  uint8_t GetBigSquare(uint8_t shiftIndex);
  uint8_t GetLittleSquare(uint8_t shiftIndex);
};
