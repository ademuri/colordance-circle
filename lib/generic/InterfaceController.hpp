#ifndef INTERFACE_CONTROLLER_HPP_
#define INTERFACE_CONTROLLER_HPP_

#include <queue>
#include <vector>

#include "Effect.hpp"
#include "InterfaceEffect.hpp"
#include "InterfaceEffect1.hpp"
#include "Pole.hpp"

class InterfaceController : public Effect {
 public:
  InterfaceController(std::vector<Pole*> poles,
                      ParamController* paramController);

 protected:
  void DoRun() override;

 private:
  uint32_t GetUpdatedBeat(uint16_t timeSinceLastBeat);
  uint16_t GetBeatsOverTime(uint32_t elapsedTime, uint16_t interval);
  void ResetBeatQueue();

  InterfaceEffect* currentEffect;
  InterfaceEffect1* effect1;

  static const uint16_t MILLIS_PER_RUN_LOOP = 20;

  // Used to track button presses
  uint8_t lastSetBeat = 0;
  uint8_t lastSetShift = 0;

  // Pause
  bool lastLoopWasPaused = false;
  uint32_t pauseStart = 0;
  uint32_t pauseTime = 0;

  // Beat
  static const uint32_t BEAT_RESET_WAIT_TIME = 240000;
  static const uint16_t DEFAULT_MILLIS_PER_BEAT = 750;  // 80bpm
  static const uint16_t MIN_MILLIS_PER_BEAT = 300;
  static const uint16_t MAX_MILLIS_PER_BEAT = 1500;
  static const uint16_t SET_BEAT_TOLERANCE = 200;
  uint32_t lastBeatTime = 0;
  uint32_t nextBeatTime = 750;
  uint32_t lastSetBeatTime = 0;
  uint32_t timeSetForNextBeat = 0;
  uint16_t millisPerBeat = 750;

  // Shift
  static const uint8_t DEFAULT_BEATS_PER_SHIFT = 4;
  static const uint8_t MAX_BEATS_PER_SHIFT = 16;
  bool doShiftOnNextBeat = false;
  uint8_t beatsSinceLastShift = 0;
  uint16_t beatsPerShift = 4;
  uint32_t lastSetShiftTime = 0;
  uint32_t lastShiftTime = 0;

  // Beat tracking
  static const uint8_t BEATS_TO_RECORD = 4;
  std::queue<uint16_t> beatQueue;
  uint16_t beatTrackingTime = 0;
};

#endif