#ifndef COLOR_CYCLE_EFFECT_HPP_
#define COLOR_CYCLE_EFFECT_HPP_

#include <vector>
#include "Effect.hpp"
#include "Pole.hpp"

class ColorCycleEffect : public Effect {
 public:
  ColorCycleEffect(std::vector<Pole*> poles, ParamController* paramController);

 protected:
  void DoRun() override;

 private:
  uint32_t timer = 0;
  uint8_t mode = 6;
};

#endif
