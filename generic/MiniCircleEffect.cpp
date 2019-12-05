#include "MiniCircleEffect.hpp"
#include "ColordanceTypes.hpp"

MiniCircleEffect::MiniCircleEffect(std::vector<Pole*> poles) : Effect(poles) {}

void MiniCircleEffect::DoRun() {
  for (uint16_t pole = 0; pole < 6; pole++) {
    poles[pole]->SetGridLight(LineToCircle(timer), LineToCircle(timer + 1),
                              CHSV(0, 255, 0));
    poles[pole]->SetGridLight(LineToCircle(timer + 1), LineToCircle(timer + 2),
                              CHSV(0, 255, 0));
  }

  timer++;

  for (uint16_t pole = 0; pole < 6; pole++) {
    poles[pole]->SetGridLight(LineToCircle(timer), LineToCircle(timer + 1),
                              CHSV(timer * 5, 255, 255));
    poles[pole]->SetGridLight(LineToCircle(timer + 1), LineToCircle(timer + 2),
                              CHSV(timer * 5 + 120, 255, 255));
  }

  SleepMs(100);
}

uint16_t MiniCircleEffect::LineToCircle(uint16_t line) {
  uint16_t circle = line % 4;
  if (circle == 3) {
    circle = 1;
  }
  return circle;
}
