#pragma once

#include <ColordanceTypes.hpp>
#include <array>

#include "Pole.hpp"

class MiniLightController {
 public:
  void Begin();

  void WriteOutLights();

  Poles& get_poles() { return poles; }

  // Translates from native ordering (first row is 0-15, second row is 16-31,
  // etc.) to board ordering (first row is 0-15, second row is 31-16, etc.).
  static uint16_t NativeToBoardLedIndex(uint16_t i);

  using LedIndices = std::array<uint16_t, 16>;
  static LedIndices GridLightToNativeLedIndices(uint16_t x, uint16_t y);

 private:
  Poles poles{};

  static constexpr uint32_t kLedsPerPole = 16 * 16;
  std::array<std::array<CRGB, kLedsPerPole>, Pole::kNumPoles> leds;
};
