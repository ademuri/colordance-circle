#ifndef ROTATE_THREE_EFFECT_HPP_
#define ROTATE_THREE_EFFECT_HPP_

#include <vector>
#include "Effect.hpp"
#include "Pole.hpp"

class RotateThreeEffect : public Effect {
 public:
  RotateThreeEffect(std::vector<Pole*> poles);

 protected:
  void DoRun() override;

 private:
  uint32_t timer = 0;
};

#endif
