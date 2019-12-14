#include "ColorCycleEffect.hpp"
#include "ColordanceTypes.hpp"

ColorCycleEffect::ColorCycleEffect(std::vector<Pole*> poles,
                                   ParamController* paramController)
    : Effect(poles, paramController) {}

void ColorCycleEffect::DoRun() {
  mode = paramController->GetRawParam(Param::kMode);

  if (mode == 0) {
    // Each pole has RGB
    for (uint16_t pole = 0; pole < 6; pole++) {
      for (uint16_t i = 0; i < 3; i++) {
        poles[pole]->SetGridLight(
            0, i, CHSV((uint8_t)(255 / 3 * i + timer), 255, 200));
      }
    }
  } else if (mode == 1) {
    // Each pole has a single color
    for (uint16_t pole = 0; pole < 6; pole++) {
      poles[pole]->SetGridLight(
          0, 0, CHSV((uint8_t)(255 / 3 * pole + timer), 255, 255));
      poles[pole]->SetGridLight(
          0, 2, CHSV((uint8_t)(255 / 3 * pole + timer), 255, 255));
    }
  } else if (mode == 2) {
    // Two evenly-spaced colors per pole
    for (uint16_t pole = 0; pole < 6; pole++) {
      poles[pole]->SetGridLight(
          0, 0, CHSV((uint8_t)(255 / 3 * pole + timer), 255, 255));
      poles[pole]->SetGridLight(
          0, 2, CHSV((uint8_t)(255 / 3 * (pole + 1) + timer), 255, 255));
    }
  } else if (mode == 3) {
    // Two colors per pole, closer together
    for (uint16_t pole = 0; pole < 6; pole++) {
      poles[pole]->SetGridLight(
          0, 0, CHSV((uint8_t)(255 / 3 * pole + timer), 255, 255));
      poles[pole]->SetGridLight(
          0, 2, CHSV((uint8_t)(255 / 3 * pole + timer + 30), 255, 255));
    }
  } else if (mode == 4) {
    // Two colors per pole, far apart
    for (uint16_t pole = 0; pole < 6; pole++) {
      poles[pole]->SetGridLight(
          0, 0, CHSV((uint8_t)(255 / 3 * pole + timer), 255, 255));
      poles[pole]->SetGridLight(
          0, 2, CHSV((uint8_t)(255 / 3 * pole + timer + 128), 255, 255));
    }
  } else if (mode == 5) {
    // One color per pole, fade in between them
    for (uint16_t pole = 0; pole < 6; pole++) {
      CHSV hsv = CHSV(pole * 256 / 6, 255, sin8(pole * 256 / 3 + timer / 5));
      poles[pole]->SetGridLight(0, 0, hsv);
      poles[pole]->SetGridLight(0, 1, hsv);
      poles[pole]->SetGridLight(0, 2, hsv);
      poles[pole]->SetGridLight(0, 3, hsv);
    }
  } else if (mode == 6) {
    // One color per pole, fade in between them
    for (uint16_t pole = 0; pole < 3; pole++) {
      for (uint16_t i = 0; i < 4; i++) {
        poles[pole * 2]->SetGridLight(
            i, i,
            CHSV(i * 256 / 4 + timer / 3, 255,
                 sin8(i * 256 / 4 + timer / 2 + pole * 256 / 3)));
      }
    }
  } else {
    // Three poles, each has rgb
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        CHSV hsv = {(uint8_t)(255 / 3 * i + timer * 3), 255, 150};
        CRGB rgb = hsv;
        poles[j * 2]->SetGridLight(i, i, rgb);
      }
    }
  }

  timer++;
  SleepMs(10);
}
