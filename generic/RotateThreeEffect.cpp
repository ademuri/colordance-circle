#include "RotateThreeEffect.hpp"
#include "ColordanceTypes.hpp"

RotateThreeEffect::RotateThreeEffect(std::vector<Pole*> poles)
    : Effect(poles) {}

void RotateThreeEffect::DoRun() {
  static uint8_t hue_base = 0;
  static uint8_t pole_offset = 0;
  static uint8_t light_offset = 0;

  for (int pole = 0; pole < 3; pole++) {
    for (int i = 0; i < 4; i++) {
      poles[pole * 2 + pole_offset]->SetGridLight(light_offset, i,
                                                  CRGB(0, 0, 0));
    }
  }

  timer++;
  light_offset++;
  if (light_offset >= 4) {
    light_offset = 0;
    pole_offset = (pole_offset + 1) % 2;
  }
  hue_base += 10;

  for (int pole = 0; pole < 3; pole++) {
    for (int i = 0; i < 4; i++) {
      poles[pole * 2 + pole_offset]->SetGridLight(
          light_offset, i, CHSV(hue_base + 255 / 3 * pole + i * 12, 255, 255));
    }
  }
  SleepMs(100);
}
