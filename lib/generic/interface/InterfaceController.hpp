#pragma once

#include <memory>
#include <queue>

#include "Buttons.hpp"
#include "Effect.hpp"
#include "Pole.hpp"
#include "interface/InterfaceEffect.hpp"
#include "interface/effects/BackAndForth.hpp"
#include "interface/effects/HuePoles.hpp"
#include "interface/effects/SideToSide.hpp"
#include "interface/effects/Sliders.hpp"
#include "interface/effects/Split.hpp"
#include "interface/effects/Sticky.hpp"

class InterfaceController : public Effect {
 public:
  InterfaceController(Poles& poles, Buttons& buttons,
                      ParamController& paramController);

 protected:
  void DoStep() override;

 private:
  uint16_t GetUpdatedBeat(uint16_t timeSinceLastBeat);
  uint16_t GetBeatsOverTime(uint32_t elapsedTime, uint16_t interval);
  bool HandleShiftButton(uint8_t beatsSinceLastSet);
  void ResetBeatQueue();
  void TurnOnPause();

  auto interfaceEffects() {
    return std::array<InterfaceEffect*, 6>{
        std::addressof(backAndForth), std::addressof(huePoles),
        std::addressof(sideToSide),   std::addressof(sliders),
        std::addressof(sticky),       std::addressof(split)};
  }

  // std::array<InterfaceEffect, 5> interfaceEffects;
  BackAndForth backAndForth;
  HuePoles huePoles;
  SideToSide sideToSide;
  Sliders sliders;
  Split split;
  Sticky sticky;

  const uint16_t MILLIS_PER_RUN_LOOP = 20;
  const uint16_t FRAMES_PER_LOOP = 840;

  uint32_t lastEffectTime = 0;

  // Used to track button presses
  uint8_t lastSetBeat = 0;
  uint8_t lastSetShift = 0;

  // Pause
  bool lastLoopWasPaused = false;
  uint32_t pauseStart = 0;
  uint32_t pauseTime = 0;

  // Beat
  const uint32_t BEAT_RESET_WAIT_TIME = 240000;
  const uint16_t DEFAULT_MILLIS_PER_BEAT = 1000;  // 80bpm
  const uint16_t MIN_MILLIS_PER_BEAT = 300;
  const uint16_t MAX_MILLIS_PER_BEAT = 1500;
  const uint16_t SET_BEAT_TOLERANCE = 200;
  uint32_t lastBeatTime = 0;
  uint32_t nextBeatTime = 750;
  uint32_t lastSetBeatTime = 0;
  uint32_t timeSetForNextBeat = 0;
  uint16_t millisPerBeat = 750;

  // Shift
  const uint8_t DEFAULT_BEATS_PER_SHIFT = 4;
  const uint8_t MAX_BEATS_PER_SHIFT = 8;
  bool doShiftOnNextBeat = false;
  uint8_t beatsSinceAutoShift = 0;
  uint8_t beatsSinceManualShift = 0;
  uint16_t beatsPerShift = 4;
  uint32_t lastSetShiftTime = 0;
  uint32_t lastShiftTime = 0;

  // Beat tracking
  const uint8_t BEATS_TO_RECORD = 4;
  std::queue<uint16_t> beatQueue;
  uint16_t beatTrackingTime = 0;

  uint8_t beatButtonHue = 0;
};
