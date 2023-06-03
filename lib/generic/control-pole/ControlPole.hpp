#pragma once

#include "ColordanceTypes.hpp"
#include "ControlPoleEffect.hpp"
#include "ControlPoleEffectCircle.hpp"
#include "ControlPoleEffectCorners.hpp"
#include "ControlPoleEffectCross.hpp"
#include "ControlPoleEffectDiverge.hpp"
#include "ControlPoleEffectLine.hpp"
#include "ControlPoleEffectPinwheel.hpp"
#include "ControlPoleEffectSmallSquare.hpp"
#include "Grid.hpp"

enum class Mode {
  // Line is first to make testing easier
  kLine,
  kCircle,
  kCorners,
  kCross,
  kDiverge,
  kPinwheel,
  kSmallSquare,
};

enum class Speed {
  kStill,
  kHalf,
  kDefault,
  kDouble,
  kOffset,
};

class ControlPole {
 public:
  ControlPole(uint16_t framesPerLoop);
  void SetHue(uint8_t hue);
  void IncrementHue(uint8_t hue);
  void SetSat(uint8_t sat);
  void SetVal(uint8_t val);
  void SetMode(Mode mode);
  void SetRotation(uint8_t rotation);
  void SetShiftSpeed(Speed speed);
  void SetShiftOffset(uint8_t offset);
  void SetLightCount(uint8_t lightCount);
  void SetHueShift(uint8_t hueShift);
  void SetHueDistance(uint8_t hueDistance);
  void SetBackAndForth(bool backAndForth);
  void SetSmoothColor(bool smoothColor);
  void SetReverse(bool reverse);
  void SetGridFade(uint8_t fadeFrames);
  void ResetFade();
  void FadeIn(uint16_t fadeFrames);
  void FadeOut(uint16_t fadeFrames);
  void TurnOffAll();
  uint8_t GetHue();
  uint8_t GetHueDistance();
  CHSV GetHSV();
  uint32_t GetTimerShiftOffset();
  uint8_t GetShiftsPerLoop();
  uint8_t GetLastShiftIndex();
  uint8_t UpdateGrid(uint16_t frame, uint16_t lastFrame, bool multiply);
  Grid<CHSV> const& GetGrid();

 private:
  uint8_t GetUpdatedHueShift(uint16_t framesSinceLast);

  ControlPoleEffectCircle effectCircle;
  ControlPoleEffectCorners effectCorners;
  ControlPoleEffectCross effectCross;
  ControlPoleEffectDiverge effectDiverge;
  ControlPoleEffectLine effectLine;
  ControlPoleEffectPinwheel effectPinwheel;
  ControlPoleEffectSmallSquare effectSmallSquare;
  ControlPoleEffect* currentEffect = std::addressof(effectLine);

  Grid<CHSV> grid_lights;

  uint8_t gridFadeFrames = 0;

  uint16_t fadeInFrames = 0;
  uint16_t fadeOutFrames = 0;
  uint16_t fadeOutFramesLeft = 0;
  uint16_t fadeInFramesLeft = 0;

  Mode mode = Mode::kLine;
  Mode lastMode = Mode::kLine;

  uint8_t baseHue = 0;
  uint8_t hueDistance = 0;
  uint8_t hueShift = 5;
  uint8_t currentHueShift = 0;
  uint16_t hueShiftRemainder = 0;
  bool smoothColor = true;

  uint8_t baseVal = 255;
  uint8_t baseSat = 255;

  uint8_t hue = 0;
  uint8_t actualHue = 0;

  uint8_t lightCount = 4;

  Speed speed = Speed::kDefault;
  bool didFirstHalf = false;

  uint8_t shiftOffset = 0;
  uint8_t lastShiftIndex = 0;
  uint8_t lastEffectiveShiftIndex = 0;

  bool goBackwards = false;
  bool backAndForth = false;
  bool reverse = false;

  uint16_t framesPerLoop;

  bool firstLoop = true;
};
