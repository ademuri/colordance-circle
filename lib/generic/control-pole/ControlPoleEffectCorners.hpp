#ifndef CONTROL_POLE_EFFECT_CORNERS_HPP_
#define CONTROL_POLE_EFFECT_CORNERS_HPP_

#include <vector>

#include "ColordanceTypes.hpp"
#include "ControlPoleEffect.hpp"

class ControlPoleEffectCorners : public ControlPoleEffect {
 public:
  ControlPoleEffectCorners();
  uint8_t GetRotations() override;

 protected:
  void DoSetGrid(std::vector<std::vector<CHSV>> &grid_lights,
                 uint8_t shiftIndex) override;
  uint8_t GetShiftsPerLoop() override;

 private:
  uint8_t GetIndex(uint8_t shiftIndex, uint8_t offset);
};

#endif
