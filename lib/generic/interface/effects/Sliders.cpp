#include "Sliders.hpp"

#include "ColordanceTypes.hpp"

Sliders::Sliders(std::vector<HelperPole *> helperPoles)
    : InterfaceEffect(helperPoles) {
  hueLeft = 0;
  hueRight = 127;
  pole_left = helperPoles[0];
  pole_right = helperPoles[1];
  pole_left->SetHue(0);
  pole_right->SetHue(127);
}

bool Sliders::ContinuousShift() { return true; }

void Sliders::DoSetGrid(std::vector<Pole *> poles, uint16_t frame) {
  // if (mode == 0) {
  //   SetMode0(poles, count);
  // } else {
  //   SetMode1(poles);
  // }

  poles[leftIndex]->SetGridLights(pole_left->GetGrid(frame, lastFrame, false));
  poles[rightIndex]->SetGridLights(
      pole_right->GetGrid(frame, lastFrame, false));

  lastFrame = frame;
}

// void Sliders::SetMode0(std::vector<Pole *> poles, uint8_t position) {
//   uint8_t adjustedPosition = 3 - position - 1;
//   uint8_t sat =
//       position % 3 == adjustedPosition % 3 && rightIndex == leftIndex ? 0 :
//       255;

//   pole_left->GetGrid()
//   UpdateGrid(pole_left, position, hueLeft, sat);
//   UpdateGrid(pole_right, adjustedPosition, hueRight, sat);
//   if (rightIndex == leftIndex) {
//     UpdateGrid(pole_left, adjustedPosition, hueRight, sat);
//     UpdateGrid(pole_right, position, hueLeft, sat);
//   } else {
//     poles[rightIndex]->SetGridLights(swap ? pole_left : pole_right);
//   }
//   poles[leftIndex]->SetGridLights(swap ? pole_right : pole_left);

//   helperPole->GetGrid
// }

// void Sliders::SetMode1(std::vector<Pole *> poles) {
//   uint8_t sat = 255;
//   if (rightIndex == leftIndex) {
//     UpdateGrid(pole_left, 0, swap ? hueLeft : hueRight, sat);
//     UpdateGrid(pole_left, 1, swap ? hueRight : hueLeft, sat);
//     poles[leftIndex]->SetGridLights(pole_left);
//   } else {
//     UpdateGrid(pole_left, swap ? 1 : 0, swap ? hueLeft : hueRight, sat);
//     UpdateGrid(pole_right, swap ? 0 : 1, swap ? hueRight : hueLeft, sat);
//     poles[leftIndex]->SetGridLights(pole_left);
//     poles[rightIndex]->SetGridLights(pole_right);
//   }
// }

// void Sliders::UpdateGrid(std::vector<std::vector<CHSV>> &pole, uint8_t
// position,
//                          uint8_t hue, uint8_t sat) {
//   const CHSV color = CHSV(hue, sat, 255);
//   if (mode == 0) {
//     position = position % 3;
//     pole[0][position] = color;
//     pole[3 - position][0] = color;
//     pole[3][3 - position] = color;
//     pole[position][3] = color;
//   } else if (mode == 1) {
//     position = position % 2;
//     pole[position][position] = color;
//     pole[3 - position][3 - position] = color;
//     pole[position][3 - position] = color;
//     pole[3 - position][position] = color;
//   }
// }

// void Sliders::TurnOffAll(std::vector<std::vector<CHSV>> &pole) {
//   for (int x = 0; x < 4; x++) {
//     for (int y = 0; y < 4; y++) {
//       pole[x][y].val = 0;
//     }
//   }
// }

void Sliders::UpdateOption1() {
  mode++;
  // mode %= kNumModes;
}

/**
 * Cycle hues.
 */
void Sliders::UpdateOption2() { smoothHue = !smoothHue; }

/**
 * Change the fade.
 */
void Sliders::UpdateSlider1(uint8_t val) { leftIndex = val / 43; }

/**
 * Chages the hue distance
 */
void Sliders::UpdateSlider2(uint8_t val) { rightIndex = val / 43; }

void Sliders::DoShift(uint8_t shiftPosition) {
  if (shiftPosition == 0) {
    swap = !swap;
  }
}

void Sliders::Reset() {}