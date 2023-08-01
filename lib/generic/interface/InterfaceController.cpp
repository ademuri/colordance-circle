#include "InterfaceController.hpp"

#include <iostream>

#include "ColordanceTypes.hpp"
#include "InterfaceEffect.hpp"
#include "PoleEffect.hpp"

namespace {

constexpr uint16_t MILLIS_PER_RUN_LOOP = 20;
constexpr uint16_t FRAMES_PER_LOOP = 840;

constexpr uint32_t BEAT_RESET_WAIT_TIME = 240000;
constexpr uint16_t DEFAULT_MILLIS_PER_BEAT = 1000;  // 80bpm
constexpr uint16_t MIN_MILLIS_PER_BEAT = 300;
constexpr uint16_t MAX_MILLIS_PER_BEAT = 1500;
constexpr uint16_t SET_BEAT_TOLERANCE = 200;

constexpr uint8_t DEFAULT_BEATS_PER_SHIFT = 4;
constexpr uint8_t MAX_BEATS_PER_SHIFT = 8;

constexpr uint8_t BEATS_TO_RECORD = 4;


} // namespace

InterfaceController::InterfaceController(Poles& poles, Buttons& buttons,
                                         ParamController& paramController)
    : Effect(poles, buttons, paramController) {
  for (int i = 0; i < 4; i++) {
    beatQueue.push(750);
  }
  beatTrackingTime = 4 * 750;
}

/**
 * Sets the effect parameters from the interface, and handles timing.
 */
void InterfaceController::DoStep() {
  /*
   * Sets the effect
   */
  uint8_t effectNumber = paramController_.GetRawParam(Param::kEffect);
  if (effectNumber >=
      sizeof(interfaceEffects()) / sizeof(interfaceEffects()[0])) {
    effectNumber = 0;
  }

  for (auto effect : interfaceEffects()) {
    effect->SetOption1(paramController_.GetRawParam(Param::kOption1) == 1);
    effect->SetOption2(paramController_.GetRawParam(Param::kOption2) == 1);
    effect->SetSlider1(255 - paramController_.GetRawParam(Param::kSlider1));
    effect->SetSlider2(255 - paramController_.GetRawParam(Param::kSlider2));
  }

  uint32_t systemTime = millis();

  /*
   * Pause
   */
  bool pause = paramController_.GetRawParam(Param::kPause) == 1;
  if (pause) {
    if (!lastLoopWasPaused) {
      pauseStart = systemTime;
    }
    lastLoopWasPaused = true;
    TurnOnPause();
    return;
  }
  if (lastLoopWasPaused) {
    pauseTime += systemTime - pauseStart;
  }
  lastLoopWasPaused = false;

  // Offset the pause time so unpausing continues smoothly
  uint32_t effectTime = systemTime - pauseTime;

  if (effectTime - lastEffectTime > 3000) {
    lastEffectTime = systemTime - MILLIS_PER_RUN_LOOP;
    effectTime = systemTime;
    lastBeatTime = systemTime;
    nextBeatTime = systemTime + millisPerBeat;
  }

  /*
   * Updates beat timing.
   */
  uint8_t setBeat = paramController_.GetRawParam(Param::kBeat);
  bool lastFrameWasBeat = false;  // includes this frame if it lands on the beat
  bool lastFrameWasHalfBeat = false;  // Used for PartialAutomaticShift

  if (effectTime >= nextBeatTime) {
    lastBeatTime = nextBeatTime;
    if (timeSetForNextBeat != 0) {
      nextBeatTime = timeSetForNextBeat;
      timeSetForNextBeat = 0;
    } else {
      nextBeatTime = lastBeatTime + millisPerBeat;
    }
    lastFrameWasBeat = true;
  }
  uint32_t halfBeatTime = lastBeatTime + (nextBeatTime - lastBeatTime) / 2;
  if (effectTime >= halfBeatTime && lastEffectTime < halfBeatTime) {
    lastFrameWasHalfBeat = true;
  }

  uint32_t timeSinceLastSetBeat = effectTime - lastSetBeatTime;
  uint32_t beatsSinceLastSet = timeSinceLastSetBeat / millisPerBeat;
  bool closeToNextBeat = nextBeatTime - effectTime < MILLIS_PER_RUN_LOOP * 4;
  if (setBeat == 1 && lastSetBeat != 1) {
    // The beat button was pressed
    if (beatsSinceLastSet < 4) {
      millisPerBeat = GetUpdatedBeat(timeSinceLastSetBeat);
    }
    if (closeToNextBeat) {
      lastFrameWasBeat = true;
    }
    if (lastFrameWasBeat) {
      lastBeatTime = effectTime;
      nextBeatTime = effectTime + millisPerBeat;
    } else {
      // This will be set after this current beat.
      timeSetForNextBeat = effectTime + 2 * millisPerBeat;
    }
    lastSetBeatTime = effectTime;
    // } else if (effectTime - lastSetBeatTime > BEAT_RESET_WAIT_TIME) {
    //   // A signifanct amount of time has passed since the beat has been set
    //   // Resets to the default beat over BEATS_TO_RECORD # of beats
    //   // Keeping track of the exact beat time does not matter in this
    //   situation
    //   // Also resets the beats per shift unless it has been recently pressed
    //   millisPerBeat = GetUpdatedBeat(DEFAULT_MILLIS_PER_BEAT);
    //   if (beatsSinceAutoShift > MAX_BEATS_PER_SHIFT) {
    //     beatsPerShift = DEFAULT_BEATS_PER_SHIFT;
    //   }
  }
  lastSetBeat = setBeat;  // Track button state

  // Adjust the next beat time if isn't past the last beat due to adjustments
  while (lastBeatTime + MIN_MILLIS_PER_BEAT >= nextBeatTime) {
    nextBeatTime += millisPerBeat;
  }

  /*
   * Handles the shift and updates the beatsPerShift
   */
  uint8_t setShift = paramController_.GetRawParam(Param::kShift);
  // bool loopShift = true;

  if (lastFrameWasBeat) {
    beatsSinceAutoShift++;
    beatsSinceManualShift++;
    beatButtonHue += 57;
  }

  bool doManualShift = false;
  if (setShift != lastSetShift) {  // Shift button pressed
    if (beatsSinceManualShift > 0 || beatsPerShift == 0) {
      /* Automatic beats will stop when the button is pressed once. Then, they
       * will start again when it is pressed shortly after and will continue as
       * unless it is pressed again not roughly in time. */
      if ((beatsPerShift == 0 &&
           beatsSinceManualShift <= MAX_BEATS_PER_SHIFT) ||
          (beatsSinceManualShift > beatsPerShift - 1 &&
           beatsSinceManualShift < beatsPerShift + 2)) {
        beatsPerShift = beatsSinceManualShift % (MAX_BEATS_PER_SHIFT + 1);
        doManualShift = true;
      } else if (beatsSinceManualShift > 1) {
        beatsPerShift = 0;
        doManualShift = true;
      }
    }
    lastSetShift = setShift;  // Track shift button state
  }

  for (auto effect : interfaceEffects()) {
    effect->SetBeatsPerShift(beatsPerShift);
    effect->SetBeatsSinceAutoShift(beatsSinceAutoShift);
  }

  /* Automatic Shifts */
  if (beatsPerShift != 0) {
    if (beatsSinceAutoShift == beatsPerShift / 2 &&
        ((lastFrameWasBeat && beatsPerShift % 2 == 0) ||
         (lastFrameWasHalfBeat && beatsPerShift % 2 == 1))) {
      for (auto effect : interfaceEffects()) {
        effect->AutomaticPartialShift(2);
      }
    }
    if (lastFrameWasBeat && beatsSinceAutoShift >= beatsPerShift) {
      for (auto effect : interfaceEffects()) {
        effect->AutomaticShift(beatsSinceManualShift < 2);
      }
      beatsSinceAutoShift = 0;
    }
  }

  if (doManualShift) {
    for (auto effect : interfaceEffects()) {
      effect->ManualShift(beatsSinceAutoShift < 2);
    }
    beatsSinceManualShift = 0;
  }

  for (auto& pole : poles_) {
    pole.ClearGridLights();
  }
  uint32_t timeSinceLastBeat = effectTime - lastBeatTime;
  uint16_t interval = nextBeatTime - lastBeatTime;

  // Update the grids and set all of the effect buttons
  buttons_.TurnOffAll();
  for (uint8_t i = 0;
       i < sizeof(interfaceEffects()) / sizeof(interfaceEffects()[0]); i++) {
    auto effect = interfaceEffects()[i];
    effect->Update(timeSinceLastBeat, interval);
    effect->SetEffectButton(buttons_, i);
  }

  // Set the current effect grid/buttons & options
  interfaceEffects()[effectNumber]->SetGrid(poles_);
  for (uint8_t i = 6; i < 9; i++) {
    buttons_.SetButton(effectNumber, i, CRGB(100, 100, 100));
  }
  interfaceEffects()[effectNumber]->SetOptionButtons(buttons_);

  uint8_t beatBrightness =
      140 - 140 * (effectTime - lastBeatTime) / millisPerBeat;
  for (int i = 0; i < 15; i++) {
    buttons_.SetButton(Buttons::kHeartButton, i,
                       CRGB(CHSV(beatButtonHue - 30, 255, beatBrightness)));
  }
  for (int i = 7; i < 10; i++) {
    buttons_.SetButton(Buttons::kHeartButton, i,
                       CRGB(CHSV(beatButtonHue, 255, 200)));
  }

  // Set Shift button
  for (int i = 0; i < beatsPerShift && i < 8; i++) {
    uint8_t shiftCountBrightness = 100;
    if (i <= beatsSinceAutoShift) {
      shiftCountBrightness = 255;
    }
    buttons_.SetButton(9, i, CRGB(CHSV(0, 0, shiftCountBrightness)));
  }
  uint8_t shiftBrightness = 50;
  // uint8_t timeSinceLastShift = effectTime - lastShiftTime;
  // if (beatsPerShift > 0) {
  //   shiftBrightness = 255 * timeSinceLastShift / (beatsPerShift *
  //   millisPerBeat);
  // }
  for (int i = 8; i < 12; i++) {
    buttons_.SetButton(9, i, CRGB(CHSV(0, 0, shiftBrightness)));
  }

  // Set Pause button
  for (uint64_t i = 0; i < 4; i++) {
    buttons_.SetButton(11, i, CRGB(CHSV(0, 0, 50)));
  }

  SetPoleLowerEffect(poles_, millis());

  lastEffectTime = effectTime;
  SleepMs(MILLIS_PER_RUN_LOOP);
}

/*
 * Gets the number of beats in a given time frame. Adjusts up if the next beat
 * is very close.
 */
uint16_t InterfaceController::GetBeatsOverTime(uint32_t elapsedTime,
                                               uint16_t interval) {
  return (elapsedTime + interval / 4) / interval;
  ;
}

/*
 * Keeps track of a certain amount of beats and returns the average.
 */
uint16_t InterfaceController::GetUpdatedBeat(uint16_t timeSinceLastBeat) {
  if (timeSinceLastBeat < MIN_MILLIS_PER_BEAT) {
    timeSinceLastBeat = MIN_MILLIS_PER_BEAT;
  } else if (timeSinceLastBeat > MAX_MILLIS_PER_BEAT) {
    timeSinceLastBeat = MAX_MILLIS_PER_BEAT;
  }
  beatTrackingTime += timeSinceLastBeat;
  beatQueue.push(timeSinceLastBeat);
  if ((beatQueue.size() > BEATS_TO_RECORD || timeSinceLastBeat == 0) &&
      beatQueue.size() > 0) {
    beatTrackingTime -= beatQueue.front();
    beatQueue.pop();
  }
  // This shouldn't happen
  if (beatQueue.size() == 0) {
    return DEFAULT_MILLIS_PER_BEAT;
  }
  return beatTrackingTime / beatQueue.size();
}

void InterfaceController::ResetBeatQueue() {
  while (beatQueue.size() > 0) {
    beatQueue.pop();
  }
  beatTrackingTime = 0;
}

void InterfaceController::TurnOnPause() {
  for (uint64_t i = 0; i < 4; i++) {
    buttons_.SetButton(11, i, CRGB(255, 255, 255));
  }
}
