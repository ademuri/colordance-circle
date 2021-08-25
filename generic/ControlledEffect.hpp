#ifndef CONTROLLED_EFFECT_HPP_
#define CONTROLLED_EFFECT_HPP_

#include <vector>

#include "ControlPole.hpp"
#include "Effect.hpp"
#include "Pole.hpp"

class ControlledEffect : public Effect {
 public:
  ControlledEffect(std::vector<Pole*> poles, ParamController* paramController);

 protected:
  void DoRun() override;

 private:
  uint8_t GetNumberOfPolesOn(uint8_t polesBitMap);

  std::vector<ControlPole*> controlPoles;
  ControlPole* standardPole;
  uint8_t lastMovementMode = 0;
  uint8_t movementMode = 0;
  uint8_t movementSpeed = 1;
  uint8_t movementCount = 0;
  uint8_t poleHueShift = 40;
  uint8_t poleOffset = 0;
  uint8_t fadeTimer = 10;
  uint8_t setPoles = 1;
  uint8_t poleFrame = 0;

  uint32_t timerOffset = 0;

  uint8_t bpm = 80;
  static const uint16_t FRAMES_PER_LOOP = 840;  // lcm(shiftsPerLoop of effects
  uint16_t lastFrame = 0;
  bool beatSet = false;
};

#endif
