#include "ColorCycleEffect.hpp"
#include "ColordanceTypes.hpp"

ColorCycleEffect::ColorCycleEffect(std::vector<Pole*> poles) : Effect(poles) {}

void ColorCycleEffect::DoRun() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      CHSV hsv = {255 / 3 * i + timer * 3, 255, 150};
      CRGB rgb = hsv;
      poles[j * 2]->SetGridLight(i, i, rgb);
    }
  }
  timer++;
  SleepMs(10);
}
