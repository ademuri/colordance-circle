#ifndef CONTROL_POLE_EFFECT_LINE_HPP_
#define CONTROL_POLE_EFFECT_LINE_HPP_

#include <vector>

#include "ColordanceTypes.hpp"
#include "ControlPoleEffect.hpp"

class ControlPoleEffectLine : public ControlPoleEffect {
 public:
  ControlPoleEffectLine();
  uint8_t GetRotations() override;

 protected:
  void DoSetGrid(std::vector<std::vector<CHSV>>& grid_lights,
                 uint8_t shiftIndex) override;
  uint8_t GetShiftsPerLoop() override;
};

#endif
