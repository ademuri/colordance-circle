#ifndef DEMO_CONTROLLER_HPP_
#define DEMO_CONTROLLER_HPP_

#include <vector>

#include "ControlPole.hpp"
#include "Effect.hpp"
#include "Pole.hpp"

class DemoController : public Effect {
 public:
  DemoController(std::vector<Pole*> poles, ParamController* paramController);

 protected:
  void DoRun() override;

 private:
  std::vector<ControlPole*> controlPoles;
  uint16_t movementCount = 0;

  uint32_t timerOffset = 0;

  uint8_t bpm = 80;
  static const uint16_t FRAMES_PER_LOOP = 840;  // lcm(shiftsPerLoop of effects)
  uint16_t lastFrame = 0;
  bool beatHasBeenSet = false;
};

#endif