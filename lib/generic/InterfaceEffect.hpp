#ifndef INTERFACE_EFFECT_HPP_
#define INTERFACE_EFFECT_HPP_

#include <vector>

#include "ColordanceTypes.hpp"
#include "Pole.hpp"

class InterfaceEffect {
 public:
  InterfaceEffect(std::vector<Pole*> poles);

  void SetOption1(bool on);
  void SetOption2(bool on);
  void SetSlider1(uint8_t val);
  void SetSlider2(uint8_t val);
  void SetShift(bool doShift);

 protected:
  uint16_t timeSinceLastBeat = 0;
  uint16_t millisPerBeat = 0;

  bool option1 = false;
  bool option2 = false;
  uint8_t slider1 = 0;
  uint8_t slider2 = 0;

  bool shift = false;
};

#endif
