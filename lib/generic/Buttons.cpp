#include "Buttons.hpp"

Buttons::Buttons(Bank1& bank1, Bank2& bank2) : bank1_(bank1), bank2_(bank2) {}

void Buttons::SetEffectButton(uint8_t button_index, const CRGB& rgb) {
  CRGB* button = nullptr;
  switch (button_index) {
    case 0:
      button = getStripBank1(0);
      break;

    case 1:
      button = getStripBank1(11);
      break;

    case 2:
      button = getStripBank1(8);
      break;

    case 3:
      button = getStripBank2(1);
      break;

    case 4:
      button = getStripBank1(1);
      break;

    case 5:
      button = getStripBank1(10);
      break;

    case 6:
      button = getStripBank1(9);
      break;

    case 7:
      button = getStripBank1(2);
      break;

    default:
#ifdef ARDUINO
      button = getStripBank1(0);
#endif
      break;
  }

  button[button_index] = rgb;
}

CRGB* Buttons::getStripBank1(const int index) {
  return &bank1_[index * kMaxLedsPerStrip];
}

CRGB* Buttons::getStripBank2(const int index) {
  return &bank2_[index * kMaxLedsPerStrip];
}