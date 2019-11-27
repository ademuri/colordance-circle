#include "RotateThreeEffect.hpp"
#include "Types.hpp"

RotateThreeEffect::RotateThreeEffect(std::vector<Pole*> poles)
    : Effect(poles) {}

void RotateThreeEffect::DoRun() {
  static uint8_t hue_base = 0;
  static uint8_t pole_offset = 0;
  static uint8_t light_offset = 0;

  for (int pole = 0; pole < 3; pole++) {
    for (int i = 0; i < 3; i++) {
      poles[pole * 2 + pole_offset]->SetGridLight(light_offset, i,
                                                  CRGB(0, 0, 0));
    }
  }

  timer++;
  light_offset++;
  if (light_offset >= 3) {
    light_offset = 0;
    pole_offset = (pole_offset + 1) % 2;
  }
  hue_base += 10;

  for (int pole = 0; pole < 3; pole++) {
    for (int i = 0; i < 3; i++) {
      poles[pole * 2 + pole_offset]->SetGridLight(
          light_offset, i, CHSV(hue_base + 255 / 3 * pole, 255, 150));
    }
  }
  SleepMs(100);
}
