#ifndef FLASH_EFFECT_HPP_
#define FLASH_EFFECT_HPP_

#include <vector>
#include "Effect.hpp"
#include "Pole.hpp"

class FlashEffect : public Effect {
 public:
  FlashEffect(std::vector<Pole*> poles, ParamController* paramController);

 protected:
  void DoRun() override;

 private:
  uint32_t timer = 0;
};

#endif
