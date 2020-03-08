#include "FlashEffect.hpp"
#include "ColordanceTypes.hpp"

FlashEffect::FlashEffect(std::vector<Pole*> poles,
                         ParamController* paramController)
    : Effect(poles, paramController) {}

void SetLights(Pole* pole, const CHSV& color) {
  pole->SetGridLight(1, 1, color);
  pole->SetGridLight(1, 2, color);
  pole->SetGridLight(2, 1, color);
  pole->SetGridLight(2, 2, color);
}

void FlashEffect::DoRun() {
  static uint8_t hue_base = 0;
  static uint8_t pole_offset = 0;
  static int8_t light_offset = 0;

  uint8_t num_poles = poles.size();

  static CHSV off(0, 0, 0);
  for (auto pole : poles) {
    SetLights(pole, off);
  }

  uint8_t step = timer >> 7;
  uint8_t period = timer & 127;

  uint8_t pole = (step * 2) % num_poles;
  uint8_t inv_pole = (pole + num_poles / 2) % num_poles;

  uint32_t brightness = (127 - period) * 2;

  uint8_t hue = (timer >> 6) % 256;
  uint8_t inv_hue = hue + ((uint32_t)128);

  SetLights(poles[pole], CHSV(hue, 255, brightness));
  SetLights(poles[inv_pole], CHSV(inv_hue, 255, brightness));

  timer++;
  SleepMs(5);
}
