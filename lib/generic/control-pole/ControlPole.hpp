#ifndef CONTROL_POLE_HPP_
#define CONTROL_POLE_HPP_

#include <vector>

#include "ControlPoleEffect.hpp"
#include "ControlPoleEffectCircle.hpp"
#include "ControlPoleEffectCross.hpp"
#include "ControlPoleEffectDiverge.hpp"
#include "ControlPoleEffectLine.hpp"
#include "ControlPoleEffectPinwheel.hpp"

class ControlPole {
 public:
  ControlPole(uint16_t framesPerLoop);
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
  void SetReverse(bool reverse);
  void ResetFade();
  void FadeIn(uint16_t fadeFrames);
  void FadeOut(uint16_t fadeFrames);
  uint32_t GetTimerShiftOffset();
  std::vector<std::vector<CHSV>> GetGrid(uint16_t frame, uint16_t lastFrame);

 private:
  uint8_t GetUpdatedHueShift(uint16_t framesSinceLast);

  ControlPoleEffect* currentEffect;
  ControlPoleEffect* effects[5];

  uint16_t fadeInFrames = 0;
  uint16_t fadeOutFrames = 0;
  uint16_t fadeOutFramesLeft = 0;
  uint16_t fadeInFramesLeft = 0;

  uint8_t lastMode = 0;

  uint8_t baseHue = 0;
  uint8_t hueShift = 5;
  uint8_t currentHueShift = 0;
  uint16_t hueShiftRemainder = 0;
  bool smoothColor = true;

  uint8_t baseVal = 255;

  bool goBackwards = false;
  bool backAndForth = false;
  bool reverse = false;

  const uint16_t FRAMES_PER_LOOP;
};

#endif
