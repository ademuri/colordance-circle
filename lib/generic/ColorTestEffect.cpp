#include "ColorTestEffect.hpp"

#include "ColordanceTypes.hpp"

ColorTestEffect::ColorTestEffect(std::vector<Pole*> poles,
                                 ParamController* paramController)
    : Effect(poles, paramController) {}

void ColorTestEffect::DoRun() {
  for (int i = 0; i < 4; i++) {
    poles[0]->SetGridLight(i, 0,
                           CHSV((uint8_t)(255 / 4 * i + timer), 255, 255));
  }

  timer++;
  SleepMs(10);
}
