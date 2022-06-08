#ifndef CONTROL_POLE_HPP_
#define CONTROL_POLE_HPP_

#include <vector>

#include "ColordanceTypes.hpp"
#include "ControlPoleEffect.hpp"
#include "ControlPoleEffectCircle.hpp"
#include "ControlPoleEffectCross.hpp"
#include "ControlPoleEffectDiverge.hpp"
#include "ControlPoleEffectLine.hpp"
#include "ControlPoleEffectPinwheel.hpp"

enum class Mode {
  kCircle,
  kCross,
  kDiverge,
  kLine,
  kPinwheel,
  kSmallSquare,
  kCorners
};

class ControlPole {
 public:
  ControlPole(uint16_t framesPerLoop);
  void SetHue(uint8_t hue);
  void SetSat(uint8_t sat);
  void SetVal(uint8_t val);
  void SetMode(Mode mode);
  void SetRotation(uint8_t rotation);
  void SetLightCount(uint8_t lightCount);
  void SetHueShift(uint8_t hueShift);
  void SetHueDistance(uint8_t hueDistance);
  void SetBackAndForth(bool backAndForth);
  void SetSmoothColor(bool smoothColor);
  void SetReverse(bool reverse);
  void ResetFade();
  void FadeIn(uint16_t fadeFrames);
  void FadeOut(uint16_t fadeFrames);
  void TurnOffAll();
  uint32_t GetTimerShiftOffset();
  std::vector<std::vector<CHSV>> const& GetGrid(uint16_t frame,
                                                uint16_t lastFrame,
                                                bool multiply);

 private:
  uint8_t GetUpdatedHueShift(uint16_t framesSinceLast);

  ControlPoleEffectCross effectCross;
  ControlPoleEffectLine effectLine;
  ControlPoleEffectCircle effectCircle;
  ControlPoleEffectDiverge effectDiverge;
  ControlPoleEffectPinwheel effectPinwheel;
  ControlPoleEffect* currentEffect;

  std::vector<std::vector<CHSV>> grid_lights;

  uint16_t fadeInFrames = 0;
  uint16_t fadeOutFrames = 0;
  uint16_t fadeOutFramesLeft = 0;
  uint16_t fadeInFramesLeft = 0;

  Mode mode;
  Mode lastMode;

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
