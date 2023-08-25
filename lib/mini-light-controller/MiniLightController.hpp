#pragma once

#include <ColordanceTypes.hpp>
#include <array>

#include "Pole.hpp"

class MiniLightController {
 public:
  void Begin();

  void WriteOutLights();

  Poles& get_poles() { return poles; }

 private:
  Poles poles{};

  static constexpr uint32_t kNumLeds = 16 * 16;
  std::array<CRGB, kNumLeds> leds;
};
