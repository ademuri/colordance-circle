#pragma once

#include "Pole.hpp"

class PoleEffect {
 public:
  static void SetPoleEffect(Poles& poles, long t);
  static void SetPoleLowerEffect(Poles& poles, long t);

 private:
  static CHSV GetColor(uint8_t n, long t);
};
