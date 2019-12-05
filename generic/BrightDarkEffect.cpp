#include "BrightDarkEffect.hpp"
#include "ColordanceTypes.hpp"

BrightDarkEffect::BrightDarkEffect(std::vector<Pole *> poles) : Effect(poles) {}

void BrightDarkEffect::DoRun() {
  if (mode == 0) {
    SetPole(poles[0], CHSV(timer, 255, 255));
    SetPole(poles[2], CHSV(timer + 255 / 3, 255, 150));
    SetPole(poles[4], CHSV(timer + 255 * 2 / 3, 255, 150));
  } else if (mode == 1) {
    SetPole(poles[0], CHSV(230, 255, 255));
    SetPole(poles[2], CHSV(timer, 255, 180));
    SetPole(poles[4], CHSV(timer, 255, 180));
  }

  timer++;
  SleepMs(10);
}

void BrightDarkEffect::SetPole(Pole *pole, CRGB rgb) {
  pole->SetGridLight(0, 0, rgb);
  pole->SetGridLight(0, 1, rgb);
  pole->SetGridLight(0, 2, rgb);
}
