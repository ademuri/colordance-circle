#ifndef CROSS_EFFECT_HPP_
#define CROSS_EFFECT_HPP_

#include <vector>
#include "Effect.hpp"
#include "Pole.hpp"

class CrossEffect : public Effect {
 public:
  CrossEffect(std::vector<Pole*> poles, ParamController* paramController);

 protected:
  void DoRun() override;

 private:
  uint32_t timer = 0;
};

#endif
