#include "CrossEffect.hpp"
#include "ColordanceTypes.hpp"

CrossEffect::CrossEffect(std::vector<Pole*> poles,
                         ParamController* paramController)
    : Effect(poles, paramController) {}

void CrossEffect::DoRun() {
  static uint8_t hue_base = 0;
  static uint8_t pole_offset = 0;
  static int8_t light_offset = 0;

  for (int pole = 0; pole < 3; pole++) {
    for (int i = 0; i < 4; i++) {
      poles[pole * 2 + pole_offset]->SetGridLight(light_offset, light_offset,
                                                  CRGB(0, 0, 0));
      poles[pole * 2 + pole_offset]->SetGridLight(
          light_offset, 3 - light_offset, CRGB(0, 0, 0));
    }
  }

  timer++;
  if (pole_offset == 0) {
    light_offset++;
  } else {
    light_offset--;
  }

  if (light_offset >= 4) {
    light_offset = 3;
    hue_base += 10;
    pole_offset = (pole_offset + 1) % 2;
  } else if (light_offset < 0) {
    light_offset = 0;
    hue_base += 10;
    pole_offset = (pole_offset + 1) % 2;
  }

  for (int pole = 0; pole < 3; pole++) {
    for (int i = 0; i < 4; i++) {
      poles[pole * 2 + pole_offset]->SetGridLight(
          light_offset, light_offset,
          CHSV(hue_base + 255 / 5 * pole, 255, 255));
      poles[pole * 2 + pole_offset]->SetGridLight(
          light_offset, 3 - light_offset,
          CHSV(hue_base + 255 / 5 * pole + 30, 255, 255));
    }
  }
  SleepMs(150);
}
