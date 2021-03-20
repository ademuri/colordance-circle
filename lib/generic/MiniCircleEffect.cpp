#include "MiniCircleEffect.hpp"

#include "ColordanceTypes.hpp"

MiniCircleEffect::MiniCircleEffect(std::vector<Pole*> poles,
                                   ParamController* paramController)
    : Effect(poles, paramController) {}

void MiniCircleEffect::DoRun() {
  for (uint16_t pole = 0; pole < 6; pole++) {
    poles[pole]->SetGridLight(LineToCircle(timer), LineToCircle(timer + 2),
                              CHSV(0, 255, 0));
    poles[pole]->SetGridLight(LineToCircle(timer + circle_offset),
                              LineToCircle(timer + circle_offset + 2),
                              CHSV(0, 255, 0));
  }

  timer++;

  for (uint16_t pole = 0; pole < 3; pole++) {
    poles[pole * 2]->SetGridLight(LineToCircle(timer), LineToCircle(timer + 2),
                                  CHSV(pole * 255 / 3 + timer * 5, 255, 255));
    poles[pole * 2]->SetGridLight(
        LineToCircle(timer + circle_offset),
        LineToCircle(timer + circle_offset + 2),
        CHSV(pole * 255 / 3 + timer * 5 + 30, 255, 255));
  }

  SleepMs(paramController->GetRawParam(Param::kSpeed) + 10);
}

uint16_t MiniCircleEffect::LineToCircle(uint16_t line) {
  // 0 1 2 3 3 2 1 0
  uint16_t circle = line % 8;
  if (circle > 3) {
    circle = 7 - circle;
  }
  return circle;
}
