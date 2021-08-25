#ifndef EFFECT_COLOR_PICKUP_HPP_
#define EFFECT_COLOR_PICKUP_HPP_

#include <vector>

#include "Effect.hpp"
#include "Pole.hpp"

class EffectColorPickup : public Effect {
 public:
  EffectColorPickup(std::vector<Pole*> poles, ParamController* paramController);

 protected:
  void DoRun() override;

 private:
  uint32_t timer = 0;
  void setMergedSquare(uint8_t pole, uint8_t hue1, uint8_t hue2);
  void setSquare(uint8_t pole, uint8_t hue);
  void setLine(uint8_t pole, uint8_t x, uint8_t hue);
};

#endif
