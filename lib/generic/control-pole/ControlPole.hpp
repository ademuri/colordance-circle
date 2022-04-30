#ifndef CONTROL_POLE_HPP_
#define CONTROL_POLE_HPP_

#include <vector>

#include "ControlPoleEffect.hpp"
#include "ControlPoleEffectCircle.hpp"
#include "ControlPoleEffectCross.hpp"
#include "ControlPoleEffectDiverge.hpp"
#include "ControlPoleEffectLine.hpp"
#include "ControlPoleEffectTwinkle.hpp"

class ControlPole {
 public:
  ControlPole(uint8_t index, uint16_t framesPerLoop);
  void SetHue(uint8_t hue);
  void SetSat(uint8_t sat);
  void SetVal(uint8_t val);
  void SetMode(uint8_t mode);
  void SetLightCount(uint8_t lightCount);
  void SetSpeed(uint8_t speed);
  void SetHueShift(uint8_t hueShift);
  void SetHueDistance(uint8_t hueDistance);
  void SetBackAndForth(bool backAndForth);
  void SetSmoothColor(bool smoothColor);
  void SetReverse(bool flash);
  uint32_t GetTimerShiftOffset();
  std::vector<std::vector<CHSV>> GetGrid(uint16_t frame, uint16_t lastFrame);

 private:
  ControlPoleEffect* currentEffect;
  ControlPoleEffect* effects[5];
  uint8_t index;
  uint32_t fadeTimer;
  uint8_t lastMode = 0;
};

#endif
