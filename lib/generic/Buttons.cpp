#include "Buttons.hpp"

#ifndef ARDUINO
#include <cstdio>
#endif

Buttons::Buttons(Bank1& bank1, Bank2& bank2) : bank1_(bank1), bank2_(bank2) {}

// TODO: Change index to enum
void Buttons::SetButton(uint8_t button_index, const uint8_t led_index,
                        const CRGB& rgb) {
  CRGB* button = nullptr;
  switch (button_index) {
    case 0:  // Effect 1
      button = getStripBank1(0);
      break;

    case 1:  // Effect 2
      button = getStripBank1(11);
      break;

    case 2:  // Effect 3
      button = getStripBank1(8);
      break;

    case 3:  // Effect 4
      button = getStripBank2(1);
      break;

    case 4:  // Effect 5
      button = getStripBank1(1);
      break;

    case 5:  // Effect 6
      button = getStripBank1(10);
      break;

    case 6:  // Effect 7
      button = getStripBank1(9);
      break;

    case 7:  // Option 1
      button = getStripBank1(2);
      break;

    case 8:  // Option 2
      button = getStripBank2(0);
      break;

    case 9:  // Shift
      button = getStripBank1(4);
      break;

    case 10:  // Beat
      button = getStripBank1(7);
      break;

    case 11:  // Pause
      button = getStripBank1(3);
      break;

    case 12:  // Slider 1
      button = getStripBank2(3);
      break;

    case 13:  // Slider 2
      button = getStripBank1(5);
      break;

    default:
#ifdef ARDUINO
      button = getStripBank1(0);
#else
      fprintf(stderr,
              "Invalid call to Buttons::SetButton(button_index: %u, led_index: "
              "%u, rgb: (%u, %u, %u))\n",
              button_index, led_index, rgb.r, rgb.g, rgb.b);
#endif
      break;
  }

  button[led_index] = rgb;
}

CRGB* Buttons::getStripBank1(const int index) {
  return &bank1_[index * kMaxLedsPerStrip];
}

CRGB* Buttons::getStripBank2(const int index) {
  return &bank2_[index * kMaxLedsPerStrip];
}

void Buttons::TurnOffAll() {
  for (uint16_t i = 0; i < sizeof(bank1_) / sizeof(bank1_[0]); i++) {
    bank1_[i] = CRGB(0, 0, 0);
  }
  for (uint16_t i = 0; i < sizeof(bank2_) / sizeof(bank2_[0]); i++) {
    bank2_[i] = CRGB(0, 0, 0);
  }
  // for (int i=0; i<16; i++) {
  //   bank1_[i] = CRGB(255, 0, 0);
  // }
}