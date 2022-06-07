#ifndef HELPER_POLE_HPP_
#define HELPER_POLE_HPP_

#include <vector>

#include "ColordanceTypes.hpp"
#include "Pole.hpp"

// enum class Mode {
//   kCircle,
//   kCross,
//   kDiverge,
//   kLine,
//   kPinwheel
// };

class HelperPole {
 public:
  HelperPole(uint16_t framesPerLoop);

  void SetHue(uint8_t hue);
  void SetSat(uint8_t sat);
  void SetVal(uint8_t val);
  void SetLightCount(uint8_t lightCount);
  void SetHueShift(uint8_t hueShift);
  void SetHueDistance(uint8_t hueDistance);
  void SetBackAndForth(bool backAndForth);
  void SetSmoothColor(bool smoothColor);
  void SetReverse(bool reverse);
  void ResetFade();
  void FadeIn(uint16_t fadeFrames);
  void FadeOut(uint16_t fadeFrames);

  void Reset();

  std::vector<std::vector<CHSV>> const & GetGrid(uint16_t frame, uint16_t lastFrame,
                                         bool multiply);

 private:
  void SetStaticSmallSquare(uint8_t shiftIndex);
  void TurnOffAll();
  void SetGrid(uint8_t shiftIndex, bool multiply);
  std::vector<std::vector<CHSV>> grid_lights;

  uint8_t GetUpdatedHueShift(uint16_t framesSinceLast);
  uint16_t GetFramesPerShift(uint16_t framesPerLoop, bool backAndForth);
  uint8_t GetAdjustedShiftsPerLoop(bool backAndForth);

  uint8_t AdjustedBrightness(uint8_t baseVal, uint8_t lightsOn,
                             uint8_t maxLights);
  uint8_t GetHueDistance(uint8_t hueDistance, uint8_t lightIndex,
                         uint8_t minLights);

  uint16_t fadeInFrames = 0;
  uint16_t fadeOutFrames = 0;
  uint16_t fadeOutFramesLeft = 0;
  uint16_t fadeInFramesLeft = 0;

  uint8_t lastMode = 0;

  uint8_t lightCount = 4;

  uint8_t hueDistance = 0;
  uint8_t hueShift = 5;
  uint8_t currentHueShift = 0;
  uint16_t hueShiftRemainder = 0;
  bool smoothColor = true;

  uint8_t baseHue = 0;
  uint8_t baseSat = 255;
  uint8_t baseVal = 255;

  uint8_t currentHue = 0;
  uint8_t currentVal = 255;
  uint8_t currentSat = 255;

  bool goBackwards = false;
  bool backAndForth = false;
  bool reverse = false;

  const uint16_t FRAMES_PER_LOOP;
};

#endif
