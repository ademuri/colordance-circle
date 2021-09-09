#ifndef DEMO_CONTROLLER_HPP_
#define DEMO_CONTROLLER_HPP_

#include <vector>

#include "ControlPole.hpp"
#include "Effect.hpp"
#include "Pole.hpp"
#include "LocalButtonController.hpp"

class DemoController : public Effect {
 public:
  DemoController(std::vector<Pole*> poles, LocalButtonController* paramController);

 protected:
  void DoRun() override;

 private:
  std::vector<ControlPole*> controlPoles;
  uint16_t movementCount = 0;

  uint32_t timerOffset = 0;

  uint8_t bpm = 80;
  static const uint16_t FRAMES_PER_LOOP = 840;  // lcm(shiftsPerLoop of effects)
  uint16_t lastFrame = 0;

  uint8_t lastEffect = 0;

  bool lastPrevious = false;
  bool lastNext = false;
  bool lastRandom = false;

  uint8_t setPoles = 0;
  uint8_t movementSpeed = 0;
  uint8_t movementMode = 0;
  uint8_t beatsPerLoop = 0;
  uint8_t gridHueShift = 0;
  uint8_t gridBackForth = 0;
  uint8_t gridSmoothColor = 0;
  bool reverse[4];
  uint8_t staticShiftIndex[4] = {255, 255, 255, 255};
  uint8_t modes[4];
  uint8_t gridLightCount = 1;
  uint8_t hues[4];
  uint8_t hueDistances[4];
  uint8_t vals[4] = {255, 255, 255, 255};

  long randomAt = 0;
  uint8_t effect = 0;
};

#endif