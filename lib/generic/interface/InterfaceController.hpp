#pragma once

#include <memory>
#include <queue>

#include "Effect.hpp"
#include "Pole.hpp"
#include "interface/InterfaceEffect.hpp"
#include "interface/effects/BackAndForth.hpp"
#include "interface/effects/HuePoles.hpp"
#include "interface/effects/SideToSide.hpp"
#include "interface/effects/Sliders.hpp"

class InterfaceController : public Effect {
 public:
  InterfaceController(Poles& poles, ParamController* paramController);

  // Effect indices
  static constexpr uint8_t kHuePolesIndex = 3;
  static constexpr uint8_t kBackAndForthIndex = 4;
  static constexpr uint8_t kSlidersIndex = 5;
  static constexpr uint8_t kSideToSideIndex = 6;

 protected:
  void DoRun() override;

 private:
  uint32_t GetUpdatedBeat(uint16_t timeSinceLastBeat);
  uint16_t GetBeatsOverTime(uint32_t elapsedTime, uint16_t interval);
  void ResetBeatQueue();

  BackAndForth backAndForth;
  Sliders sliders;
  SideToSide sideToSide;
  HuePoles huePoles;
  InterfaceEffect* currentEffect;

  const uint16_t MILLIS_PER_RUN_LOOP = 20;
  const uint16_t FRAMES_PER_LOOP = 840;

  // Used to track button presses
  uint8_t lastSetBeat = 0;
  uint8_t lastSetShift = 0;

  // Pause
  bool lastLoopWasPaused = false;
  uint32_t pauseStart = 0;
  uint32_t pauseTime = 0;

  // Beat
  const uint32_t BEAT_RESET_WAIT_TIME = 240000;
  const uint16_t DEFAULT_MILLIS_PER_BEAT = 750;  // 80bpm
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
  const uint8_t MAX_BEATS_PER_SHIFT = 16;
  bool doShiftOnNextBeat = false;
  uint8_t beatsSinceLastShift = 0;
  uint16_t beatsPerShift = 4;
  uint32_t lastSetShiftTime = 0;
  uint32_t lastShiftTime = 0;

  // Beat tracking
  const uint8_t BEATS_TO_RECORD = 4;
  std::queue<uint16_t> beatQueue;
  uint16_t beatTrackingTime = 0;
};
