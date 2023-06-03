#pragma once

#include <array>

#include "ColordanceTypes.hpp"

class Buttons {
 public:
  static constexpr int kMaxLedsPerStrip = 15;
  static constexpr int kStripsPerBank1 = 12;
  static constexpr int kStripsPerBank2 = 4;

  using Bank1 = std::array<CRGB, kMaxLedsPerStrip * kStripsPerBank1>;
  using Bank2 = std::array<CRGB, kMaxLedsPerStrip * kStripsPerBank2>;

  Buttons(Bank1& bank1, Bank2& bank2);

  void SetButton(uint8_t button_index, const uint8_t led_index,
                 const CRGB& rgb);
  void TurnOffAll();

  static constexpr uint8_t kHeartButton = 10;

 private:
  CRGB* getStripBank1(const int index);
  CRGB* getStripBank2(const int index);

  Bank1& bank1_;
  Bank2& bank2_;
};