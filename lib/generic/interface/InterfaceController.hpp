#pragma once

#include <memory>
#include <queue>

#include "Buttons.hpp"
#include "Effect.hpp"
#include "Pole.hpp"
#include "interface/InterfaceEffect.hpp"
#include "interface/effects/BackAndForth.hpp"
#include "interface/effects/HuePoles.hpp"
#include "interface/effects/MovingPole.hpp"
#include "interface/effects/Random.hpp"
#include "interface/effects/SideToSide.hpp"
#include "interface/effects/Sliders.hpp"
#include "interface/effects/Split.hpp"

class InterfaceController : public Effect {
 public:
  InterfaceController(Poles& poles, Buttons& buttons,
                      ParamController& paramController);

  enum EffectIndex {
    kBackAndForth,
    kHuePoles,
    kSideToSide,
    kSliders,
    kMovingPole,
    kSplit,
    kRandom,
  };

 protected:
  void DoStep() override;

 private:
  uint16_t GetUpdatedBeat(uint16_t timeSinceLastBeat);
  uint16_t GetBeatsOverTime(uint32_t elapsedTime, uint16_t interval);
  bool HandleShiftButton(uint8_t beatsSinceLastSet);
  void ResetBeatQueue();
  void TurnOnPause();

  auto interfaceEffects() {
    return std::array<InterfaceEffect*, 7>{
        std::addressof(backAndForth), std::addressof(huePoles),
        std::addressof(sideToSide),   std::addressof(sliders),
        std::addressof(movingPole),   std::addressof(split),
        std::addressof(random)};
  }

  // std::array<InterfaceEffect, 5> interfaceEffects;
  BackAndForth backAndForth;
  HuePoles huePoles;
  SideToSide sideToSide;
  Sliders sliders;
  Split split;
  MovingPole movingPole;
  Random random;

  uint32_t lastEffectTime = 0;

  // Used to track button presses
  uint8_t lastSetBeat = 0;
  uint8_t lastSetShift = 0;

  // Pause
  bool lastLoopWasPaused = false;
  uint32_t pauseStart = 0;
  uint32_t pauseTime = 0;

  // Beat
  uint32_t lastBeatTime = 0;
  uint32_t nextBeatTime = 750;
  uint32_t lastSetBeatTime = 0;
  uint32_t timeSetForNextBeat = 0;
  uint16_t millisPerBeat = 750;

  // Shift
  bool doShiftOnNextBeat = false;
  uint8_t beatsSinceAutoShift = 0;
  uint8_t beatsSinceManualShift = 0;
  uint16_t beatsPerShift = 4;
  uint32_t lastSetShiftTime = 0;
  uint32_t lastShiftTime = 0;

  // Beat tracking
  std::queue<uint16_t> beatQueue;
  uint16_t beatTrackingTime = 0;

  uint8_t beatButtonHue = 0;
};
