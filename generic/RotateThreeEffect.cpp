#include "RotateThreeEffect.hpp"
#include "ColordanceTypes.hpp"

RotateThreeEffect::RotateThreeEffect(std::vector<Pole*> poles)
    : Effect(poles) {}

void RotateThreeEffect::DoRun() {
  static uint8_t hue_base = 0;
  static uint8_t pole_offset = 0;
  static int8_t light_offset = 0;

  for (int pole = 0; pole < num_poles_on; pole++) {
    for (int i = 0; i < 4; i++) {
      if (mode / 2 == 0) {
        poles[pole * (poles.size() / num_poles_on) + pole_offset]->SetGridLight(
            light_offset, i, CRGB(0, 0, 0));
      } else {
        poles[pole * (poles.size() / num_poles_on) + pole_offset]->SetGridLight(
            i, light_offset, CRGB(0, 0, 0));
      }
    }
  }

  timer++;
  if (mode % 2 == 0) {
    light_offset++;
  } else {
    if (pole_offset % 2 == 0) {
      light_offset++;
    } else {
      light_offset--;
    }
  }

  if (light_offset >= 4) {
    if (mode % 2 == 0) {
      light_offset = 0;
    } else {
      light_offset = 3;
    }
    pole_offset = (pole_offset + 1) % (poles.size() / num_poles_on);
  }
  if (light_offset < 0) {
    light_offset = 0;
    pole_offset = (pole_offset + 1) % (poles.size() / num_poles_on);
  }
  hue_base += 10;

  for (int pole = 0; pole < num_poles_on; pole++) {
    for (int i = 0; i < 4; i++) {
      if (mode / 2 == 0) {
        poles[pole * (poles.size() / num_poles_on) + pole_offset]->SetGridLight(
            light_offset, i,
            CHSV(hue_base + 255 / 3 * pole + i * 12, 255, 255));
      } else {
        poles[pole * (poles.size() / num_poles_on) + pole_offset]->SetGridLight(
            i, light_offset,
            CHSV(hue_base + 255 / 3 * pole + i * 12, 255, 255));
      }
    }
  }
  SleepMs(100);
}
