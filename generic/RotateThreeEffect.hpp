#ifndef ROTATE_THREE_EFFECT_HPP_
#define ROTATE_THREE_EFFECT_HPP_

#include <vector>
#include "Effect.hpp"
#include "Pole.hpp"

class RotateThreeEffect : public Effect {
 public:
  RotateThreeEffect(std::vector<Pole*> poles, ParamController* paramController);

 protected:
  void DoRun() override;

 private:
  uint32_t timer = 0;
  // 0 to 3, controls up-down or left-right and same direction or alternating
  // directions.
  uint8_t mode = 2;

  uint8_t num_poles_on = 2;
};

#endif
