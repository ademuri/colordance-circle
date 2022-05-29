#ifndef INTERFACE_EFFECT_HPP_
#define INTERFACE_EFFECT_HPP_

#include <vector>

#include "ColordanceTypes.hpp"
#include "Pole.hpp"

class InterfaceEffect {
 public:
  InterfaceEffect();

  void SetOption1(bool pressed);
  void SetOption2(bool pressed);
  void SetSlider1(uint8_t val);
  void SetSlider2(uint8_t val);

  void Shift(uint8_t shiftPosition);
  void SetGrid(std::vector<Pole*> poles, uint16_t timeSinceLastBeat,
               uint16_t millisPerBeat);

 protected:
  virtual void DoSetGrid(std::vector<Pole*> poles, uint16_t frame) = 0;
  virtual void UpdateOption1() = 0;
  virtual void UpdateOption2() = 0;
  virtual void UpdateSlider1(uint8_t val) = 0;
  virtual void UpdateSlider2(uint8_t val) = 0;
  virtual void DoShift(uint8_t shiftPosition) = 0;
  virtual void Reset() = 0;

  const uint16_t FRAMES_PER_LOOP = 840;

  bool option1WasPressed = false;
  bool option2WasPressed = false;
  uint8_t slider1 = 0;
  uint8_t slider2 = 0;

  uint32_t lastTimeSinceLastBeat = 0;

 private:
  const uint8_t WAIT_TIME_TO_START_OVER = 200;  // time effect was off
};

#endif
