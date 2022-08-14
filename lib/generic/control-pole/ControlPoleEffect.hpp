#pragma once

#include "ColordanceTypes.hpp"
#include "Grid.hpp"

class ControlPoleEffect {
 public:
  ControlPoleEffect();

  void SetGrid(Grid<CHSV>& grid_lights, uint8_t shiftIndex);

  void SetHue(uint8_t hue);
  void SetBaseSat(uint8_t sat);
  void SetBaseVal(uint8_t val);

  void SetLightCount(uint8_t lightCount);
  void SetHueDistance(uint8_t hueDistance);

  virtual uint8_t GetRotations() = 0;
  void SetRotation(uint8_t rotate);

  uint8_t GetShiftIndex(uint16_t frame, uint16_t lastFrame);
  uint8_t AdjustShiftIndex(uint8_t shiftIndex);

  uint16_t GetFramesPerShift(uint16_t framesPerLoop, bool backAndForth);
  uint8_t GetAdjustedShiftsPerLoop(bool backAndForth);

 protected:
  virtual void DoSetGrid(Grid<CHSV>& grid_lights, uint8_t shiftIndex) = 0;
  virtual uint8_t GetShiftsPerLoop() = 0;

  uint8_t AdjustedBrightness(uint8_t baseVal, uint8_t lightsOn,
                             uint8_t maxLights);
  uint8_t GetHueDistance(uint8_t hueDistance, uint8_t lightIndex,
                         uint8_t minLights);

  uint8_t baseSat = 255;
  uint8_t baseVal = 255;

  uint8_t currentHue = 0;

  uint8_t lightCount = 4;

  uint8_t hueDistance = 10;
  bool backAndForth = false;
  bool smoothColor = true;

  uint8_t rotation = 0;
  bool reverse = false;
  bool goBackwards = false;
};
