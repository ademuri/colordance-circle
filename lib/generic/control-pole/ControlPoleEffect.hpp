#ifndef CONTROL_POLE_EFFECT_HPP_
#define CONTROL_POLE_EFFECT_HPP_

#include <vector>

#include "ColordanceTypes.hpp"

class ControlPoleEffect {
 public:
  ControlPoleEffect(uint16_t framesPerLoop);

  void TurnOffAll();
  void PrepareFrame(uint16_t frame, uint16_t lastFrame);
  void SetGrid();

  CHSV GetLight(uint8_t x, uint8_t y);
  std::vector<std::vector<CHSV>> GetGrid();

  void SetBaseHue(uint8_t hue);
  void SetBaseSat(uint8_t sat);
  void SetBaseVal(uint8_t val);

  void SetLightCount(uint8_t lightCount);
  void SetSpeed(uint8_t speed);
  void SetHueShift(uint8_t hueShift);
  void SetHueDistance(uint8_t hueDistance);

  void SetBackAndForth(bool backAndForth);
  void SetSmoothColor(bool smoothColor);

  void SetReverse(bool reverse);
  void SetRotation(uint8_t rotate);

  uint8_t GetShiftIndex(uint16_t frame, uint16_t lastFrame);
  uint8_t AdjustShiftIndex(uint8_t shiftIndex);

  uint32_t GetTimerShiftOffset();
  void ResetTimerShiftOffset();

  uint16_t GetFramesPerShift();

  static const uint8_t kGridWidth = 4;
  static const uint8_t kGridHeight = 4;

 protected:
  std::vector<std::vector<CHSV>> grid_lights;

  virtual void DoSetGrid(uint8_t shiftIndex) = 0;
  virtual uint8_t GetShiftsPerLoop() = 0;

  uint8_t AdjustedBrightness(uint8_t baseVal, uint8_t lightsOn,
                             uint8_t maxLights);
  uint8_t GetHueDistance(uint8_t hueDistance, uint8_t lightIndex,
                         uint8_t minLights);
  uint8_t GetAdjustedShiftsPerLoop();

  uint8_t shiftIndex = 0;

  uint32_t timerShiftOffset = 0;

  uint8_t lastShiftIndex = 0;
  uint16_t lastMillisPerShift = 0;
  uint8_t lastShiftsPerLoop = 0;

  uint8_t baseHue = 0;
  uint8_t baseSat = 255;
  uint8_t baseVal = 255;

  uint8_t currentHue = 0;
  uint8_t currentHueShift = 0;
  uint16_t hueShiftRemainder = 0;

  uint8_t lightCount = 4;

  uint8_t speed = 4;
  uint8_t hueShift = 5;
  uint8_t hueDistance = 10;
  bool backAndForth = false;
  bool smoothColor = true;

  uint8_t rotation = 0;
  bool reverse = false;
  bool goBackwards = false;

  const uint16_t FRAMES_PER_LOOP;
};

#endif
