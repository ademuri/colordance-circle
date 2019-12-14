#ifndef BRIGHT_DARK_EFFECT_HPP_
#define BRIGHT_DARK_EFFECT_HPP_

#include <vector>
#include "Effect.hpp"
#include "Pole.hpp"

class BrightDarkEffect : public Effect {
 public:
  BrightDarkEffect(std::vector<Pole *> poles, ParamController *paramController);

 protected:
  void DoRun() override;

 private:
  void SetPole(Pole *pole, CRGB rgb);

  uint32_t timer = 0;
  uint8_t mode = 1;
};

#endif
