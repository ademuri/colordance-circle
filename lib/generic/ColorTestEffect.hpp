#ifndef COLOR_TEST_EFFECT_HPP_
#define COLOR_TEST_EFFECT_HPP_

#include <vector>

#include "Effect.hpp"
#include "Pole.hpp"

class ColorTestEffect : public Effect {
 public:
  ColorTestEffect(std::vector<Pole*> poles, ParamController* paramController);

 protected:
  void DoRun() override;

 private:
  uint32_t timer = 0;
};

#endif
