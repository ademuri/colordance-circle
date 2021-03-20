#include "RotateThreeEffect.hpp"

#include "ColordanceTypes.hpp"

RotateThreeEffect::RotateThreeEffect(std::vector<Pole*> poles,
                                     ParamController* paramController)
    : Effect(poles, paramController) {}

void RotateThreeEffect::DoRun() {
  static uint8_t hue_base = 0;
  static uint8_t pole_offset = 0;
  static int8_t light_offset = 0;

  for (int pole = 0; pole < Pole::kNumPoles; pole++) {
    poles[pole]->ClearGridLights();
    /*for (int i = 0; i < 4; i++) {
      if (mode / 2 == 0) {
        poles[pole * (poles.size() / num_poles_on) + pole_offset]->SetGridLight(
            light_offset, i, CRGB(0, 0, 0));
      } else {
        poles[pole * (poles.size() / num_poles_on) + pole_offset]->SetGridLight(
            i, light_offset, CRGB(0, 0, 0));
      }
    }*/
  }

  for (uint16_t pole = 0; pole < 6; pole++) {
    for (uint16_t i = 0; i < 4; i++) {
      uint16_t amount = pole * 256 / 6 + timer;
      amount = sin8(amount);
      if (amount > 128) {
        amount -= 128;
        amount *= 2;
        // poles[pole]->SetGridLight(i, 0, CHSV(35, 255, amount));
        poles[pole]->SetGridLight(i, 0, CHSV(96, 255, amount / 2));
      } else {
        amount = 128 - amount;
        amount *= 2;
        // poles[pole]->SetGridLight(i, 0, CHSV(140, 128, amount));
        poles[pole]->SetGridLight(i, 0, CHSV(224, 255, amount));
      }
    }
  }

  timer++;
  /*if (mode % 2 == 0) {
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
  }*/
  SleepMs(10);
}
