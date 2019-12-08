#ifndef MINI_CIRCLE_EFFECT_HPP_
#define MINI_CIRCLE_EFFECT_HPP_

#include <vector>
#include "Effect.hpp"
#include "Pole.hpp"

class MiniCircleEffect : public Effect {
 public:
  MiniCircleEffect(std::vector<Pole*> poles);

 protected:
  void DoRun() override;

 private:
  uint16_t LineToCircle(uint16_t line);

  uint32_t timer = 0;
  uint8_t circle_offset = 3;
};

#endif
