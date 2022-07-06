#include "InterfaceController.hpp"

#include "ColordanceTypes.hpp"
#include "InterfaceEffect.hpp"

InterfaceController::InterfaceController(Poles& poles,
                                         ParamController* paramController)
    : Effect(poles, paramController),
      currentEffect(std::addressof(backAndForth)) {
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
  uint8_t effectNumber = paramController->GetRawParam(Param::kEffect);
  switch (effectNumber) {
    case kHuePolesIndex:
      currentEffect = std::addressof(huePoles);
      break;
    case kBackAndForthIndex:
      currentEffect = std::addressof(backAndForth);
      break;
    case kSlidersIndex:
      currentEffect = std::addressof(sliders);
      break;
    case kSideToSideIndex:
      currentEffect = std::addressof(sideToSide);
  }
  currentEffect->SetOption1(paramController->GetRawParam(Param::kOption1) == 1);
  currentEffect->SetOption2(paramController->GetRawParam(Param::kOption2) == 1);
  currentEffect->SetSlider1(paramController->GetRawParam(Param::kSlider1));
  currentEffect->SetSlider2(paramController->GetRawParam(Param::kSlider2));

  uint32_t systemTime = millis();

  /*
   * Pause
   */
  bool pause = paramController->GetRawParam(Param::kPause) == 1;
  if (pause) {
    if (!lastLoopWasPaused) {
      pauseStart = systemTime;
    }
    lastLoopWasPaused = true;
    return;
  }
  if (lastLoopWasPaused) {
    pauseTime += systemTime - pauseStart;
  }
  lastLoopWasPaused = false;

  // Offset the pause time so unpausing continues smoothly
  uint32_t effectTime = systemTime - pauseTime;

  /*
   * Updates beat timing.
   */
  uint8_t setBeat = paramController->GetRawParam(Param::kBeat);
  bool lastFrameWasBeat = false;  // includes this frame if it lands on the beat

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

  uint32_t timeSinceLastSetBeat = effectTime - lastSetBeatTime;
  uint32_t beatsSinceLastSet = timeSinceLastSetBeat / millisPerBeat;
  if (setBeat == 1 && lastSetBeat != 1) {
    // The beat button was pressed
    if (beatsSinceLastSet < 4) {
      millisPerBeat = GetUpdatedBeat(timeSinceLastSetBeat);
    }
    // If this time is close to the next beat, start beat here
    if (nextBeatTime - effectTime < MILLIS_PER_RUN_LOOP * 4) {
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
    //   if (beatsSinceLastShift > MAX_BEATS_PER_SHIFT) {
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
  uint8_t setShift = paramController->GetRawParam(Param::kShift);
  bool loopShift = true;

  if (lastFrameWasBeat) {
    beatsSinceLastShift++;
  }

  // Good?

  // The shift button was pressed
  if (setShift == 0 && lastSetShift != 0) {
    // The shift will occur on the next beat, or this loop if we just missed it
    uint16_t timeSinceLastShiftSet = effectTime - lastSetShiftTime;
    uint8_t beatsSinceLastShiftSet = timeSinceLastShiftSet / millisPerBeat;
    // Add to the beats if the next beat is close
    if (timeSinceLastShiftSet % millisPerBeat >
        millisPerBeat - SET_BEAT_TOLERANCE) {
      beatsSinceLastShiftSet++;
    }
    if (beatsSinceLastShiftSet <= MAX_BEATS_PER_SHIFT) {
      beatsPerShift = beatsSinceLastShiftSet;
    } else if (beatsSinceLastShift <= MAX_BEATS_PER_SHIFT) {
      beatsPerShift = beatsSinceLastShift;
    } else {
      beatsPerShift = DEFAULT_BEATS_PER_SHIFT;
    }
    if (beatsSinceLastShift > 1 || !loopShift) {
      doShiftOnNextBeat = true;
    }
    lastSetShiftTime = effectTime;
  }
  lastSetShift = setShift;  // Track button state

  if (beatsSinceLastShift == beatsPerShift / 2 && lastFrameWasBeat) {
    currentEffect->Shift(2);
  }
  // Good

  uint32_t timeSinceLastBeat = effectTime - lastBeatTime;
  // This frame is a beat and we're looping, or we set a shift right after a
  // beat
  if ((doShiftOnNextBeat && timeSinceLastBeat < millisPerBeat / 4) ||
      (loopShift && lastFrameWasBeat && beatsSinceLastShift >= beatsPerShift)) {
    currentEffect->Shift(0);  // Shift needs to be done after updating settings
    beatsSinceLastShift = 0;
    doShiftOnNextBeat = false;
    // lastShiftTime = lastBeatTime;
  }

  for (auto& pole : poles) {
    pole.ClearGridLights();
  }
  // Good
  uint16_t interval = nextBeatTime - lastBeatTime;

  currentEffect->SetGrid(poles, timeSinceLastBeat, interval);

  SleepMs(MILLIS_PER_RUN_LOOP);
}

/*
 * Gets the number of beats in a given time frame. Adjusts up if the next beat
 * is very close.
 */
uint16_t InterfaceController::GetBeatsOverTime(uint32_t elapsedTime,
                                               uint16_t interval) {
  uint16_t beatsOverInterval = elapsedTime / interval;
  if (elapsedTime % interval > 3 * interval / 4) {
    beatsOverInterval++;
  }
  return beatsOverInterval;
}

/*
 * Keeps track of a certain amount of beats and returns the average.
 */
uint32_t InterfaceController::GetUpdatedBeat(uint16_t timeSinceLastBeat) {
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
  return beatTrackingTime / beatQueue.size();
}

void InterfaceController::ResetBeatQueue() {
  while (beatQueue.size() > 0) {
    beatQueue.pop();
  }
  beatTrackingTime = 0;
}
