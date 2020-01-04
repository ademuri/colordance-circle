#include "BrightDarkEffect.hpp"
#include "ColordanceTypes.hpp"

BrightDarkEffect::BrightDarkEffect(std::vector<Pole *> poles,
                                   ParamController *paramController)
    : Effect(poles, paramController) {}

void BrightDarkEffect::DoRun() {
  if (mode == 0) {
    SetPole(poles[0], CHSV(timer, 255, 255));
    SetPole(poles[2], CHSV(timer + 255 / 3, 255, 150));
    SetPole(poles[4], CHSV(timer + 255 * 2 / 3, 255, 150));
  } else if (mode == 1) {
    SetPole(poles[0], CHSV(230, 255, 255));
    SetPole(poles[2], CHSV(timer, 255, 180));
    SetPole(poles[4], CHSV(timer, 255, 180));
  } else if (mode == 2) {
    uint16_t foo = timer >> 2;
    SetPole(poles[(0 + foo) % 6], CHSV(255, 0, ((foo & 0x1) * 255)));
    SetPole(poles[(3 + foo) % 6], CHSV(255, 0, ((foo & 0x2) ? 255 : 0)));
    SetPole(poles[(1 + foo) % 6], CHSV(255, 0, ((foo & 0x4) ? 255 : 0)));
    SetPole(poles[(4 + foo) % 6], CHSV(255, 0, ((foo & 0x8) ? 255 : 0)));
    SetPole(poles[(2 + foo) % 6], CHSV(255, 0, ((foo & 0x10) ? 255 : 0)));
    SetPole(poles[(5 + foo) % 6], CHSV(255, 0, ((foo & 0x20) ? 255 : 0)));
  } else if (mode == 4) {
    uint16_t offset = -timer >> 3;

    for (uint8_t i = 0; i < Pole::kNumPoles; ++i) {
      poles[i]->ClearGridLights();
    }

    poles[(0 + offset) % 6]->SetGridLight(0, 0, CHSV(255, 255, 128));
    poles[(0 + offset) % 6]->SetGridLight(0, 1, CHSV(255, 255, 128));
    poles[(0 + offset) % 6]->SetGridLight(0, 2, CHSV(255, 255, 128));
    poles[(0 + offset) % 6]->SetGridLight(0, 3, CHSV(255, 255, 128));
    poles[(0 + offset) % 6]->SetGridLight(1, 0, CHSV(255, 255, 128));
    poles[(0 + offset) % 6]->SetGridLight(1, 2, CHSV(255, 255, 128));
    poles[(0 + offset) % 6]->SetGridLight(2, 0, CHSV(255, 255, 128));

    poles[(1 + offset) % 6]->SetGridLight(0, 0, CHSV(64, 255, 128));
    poles[(1 + offset) % 6]->SetGridLight(0, 1, CHSV(64, 255, 128));
    poles[(1 + offset) % 6]->SetGridLight(0, 2, CHSV(64, 255, 128));
    poles[(1 + offset) % 6]->SetGridLight(0, 3, CHSV(64, 255, 128));
    poles[(1 + offset) % 6]->SetGridLight(1, 3, CHSV(64, 255, 128));
    poles[(1 + offset) % 6]->SetGridLight(2, 0, CHSV(64, 255, 128));
    poles[(1 + offset) % 6]->SetGridLight(2, 1, CHSV(64, 255, 128));
    poles[(1 + offset) % 6]->SetGridLight(2, 2, CHSV(64, 255, 128));
    poles[(1 + offset) % 6]->SetGridLight(2, 3, CHSV(64, 255, 128));

    poles[(2 + offset) % 6]->SetGridLight(0, 1, CHSV(96, 255, 128));
    poles[(2 + offset) % 6]->SetGridLight(0, 2, CHSV(96, 255, 128));
    poles[(2 + offset) % 6]->SetGridLight(1, 0, CHSV(96, 255, 128));
    poles[(2 + offset) % 6]->SetGridLight(2, 0, CHSV(96, 255, 128));
    poles[(2 + offset) % 6]->SetGridLight(1, 3, CHSV(96, 255, 128));
    poles[(2 + offset) % 6]->SetGridLight(2, 3, CHSV(96, 255, 128));

    poles[(3 + offset) % 6]->SetGridLight(0, 0, CHSV(160, 255, 128));
    poles[(3 + offset) % 6]->SetGridLight(0, 1, CHSV(160, 255, 128));
    poles[(3 + offset) % 6]->SetGridLight(0, 2, CHSV(160, 255, 128));
    poles[(3 + offset) % 6]->SetGridLight(0, 3, CHSV(160, 255, 128));
    poles[(3 + offset) % 6]->SetGridLight(1, 1, CHSV(160, 255, 128));
    poles[(3 + offset) % 6]->SetGridLight(1, 2, CHSV(160, 255, 128));
    poles[(3 + offset) % 6]->SetGridLight(2, 0, CHSV(160, 255, 128));
    poles[(3 + offset) % 6]->SetGridLight(2, 3, CHSV(160, 255, 128));
  }

  timer++;
  SleepMs(10);
}

void BrightDarkEffect::SetPole(Pole *pole, CRGB rgb) {
  pole->SetGridLight(0, 0, rgb);
  pole->SetGridLight(0, 1, rgb);
  pole->SetGridLight(0, 2, rgb);
}
