#include "InterfaceController.hpp"

#include "ColordanceTypes.hpp"

InterfaceController::InterfaceController(std::vector<Pole*> poles,
                                         ParamController* paramController)
    : Effect(poles, paramController) {
  for (int i = 0; i < 4; i++) {
    beatQueue.push(750);
  }
  beatTrackingTime = 4 * 750;
}

void InterfaceController::DoRun() {
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

  uint32_t timeSinceLastSetBeat = effectTime - lastSetBeatTime;
  uint32_t beatsSinceLastSet = timeSinceLastSetBeat / millisPerBeat;
  if (lastSetBeat != setBeat) {
    // The beat button was pressed
    lastSetBeat = setBeat;  // For button toggeling
    if (beatsSinceLastSet < 4) {
      millisPerBeat = GetUpdatedBeat(timeSinceLastSetBeat);
    }
    lastSetBeatTime = effectTime;
  } else if (effectTime - lastSetBeatTime > BEAT_RESET_WAIT_TIME) {
    // A signifanct amount of time has passed since the beat has been set
    // Resets to the default beat over BEATS_TO_RECORD # of beats
    millisPerBeat = GetUpdatedBeat(DEFAULT_MILLIS_PER_BEAT);
    beatResetCount++;
    if (beatResetCount == BEATS_TO_RECORD) {
      lastSetBeatTime = effectTime;
      beatResetCount = 0;
    }
  } else if (beatsSinceLastSet > 4) {
    // Remove oldest beat from tracking but keeps millisPerBeat
    GetUpdatedBeat(0);
  }
  if (millisPerBeat < MIN_MILLIS_PER_BEAT) {
    millisPerBeat = MIN_MILLIS_PER_BEAT;
  }

  /*
   * Handles the shift and updates the beatsPerShift
   */
  uint8_t setShift = paramController->GetRawParam(Param::kShift);
  bool loopShift = paramController->GetRawParam(Param::kLoopShift) == 1;

  uint16_t beatsSinceLastShift =
      GetBeatsOverTime(effectTime - lastShiftTime, millisPerBeat);
  if (lastSetShift != setShift) {
    // The shift button was pressed
    // The shift will occur on the next beat, or this loop if we just missed it
    doShiftOnNextBeat = true;

    uint16_t beatsSinceLastShiftSet =
        GetBeatsOverTime(effectTime - lastSetShiftTime, millisPerBeat);
    if (beatsSinceLastShiftSet > 0 &&
        beatsSinceLastShiftSet <= MAX_BEATS_PER_SHIFT) {
      beatsPerShift = beatsSinceLastShiftSet;
    } else if (beatsSinceLastShift > 0 &&
               beatsSinceLastShift <= MAX_BEATS_PER_SHIFT) {
      beatsPerShift = beatsSinceLastShift;
    } else {
      beatsPerShift = DEFAULT_BEATS_PER_SHIFT;
    }

    lastSetShift = setShift;
    lastSetShiftTime = effectTime;
  }

  uint32_t lastBeatTime = lastSetBeatTime + beatsSinceLastSet * millisPerBeat;
  uint32_t timeSinceLastBeat = effectTime - lastBeatTime;
  bool lastFrameWasBeat =
      lastTimeSinceLastBeat > timeSinceLastBeat &&
      lastTimeSinceLastBeat - timeSinceLastBeat > millisPerBeat / 2;

  bool doShiftNow = false;
  if (doShiftOnNextBeat && timeSinceLastBeat < millisPerBeat / 4) {
    // Shift when shift button is press
    doShiftNow = true;
    doShiftOnNextBeat = false;
  } else if (loopShift && lastFrameWasBeat &&
             beatsSinceLastShift == beatsPerShift) {
    // Shift when we are looping
    doShiftNow = true;
  }
  if (doShiftNow) {
    lastShiftTime = effectTime;
  }

  /*
   * Sets the effect
   * The frame of this given beat is timeSinceLastBeat / millisPerBeat
   * The effect should not be updated if this frame is now before the previous
   * do to timing changes.
   */
  bool lastFrameWasSmaller = lastTimeSinceLastBeat * millisPerBeat <
                             timeSinceLastBeat * lastMillisPerBeat;
  if (lastFrameWasBeat || lastFrameWasSmaller) {
    // InterfaceEffect* effect = new InterfaceEffect(poles);
    // InterfaceEffect effect =
    // GetEffect(paramController->GetRawParam(Param::kEffect));
    // effect->SetOption1(paramController->GetRawParam(Param::kOption1) == 1);
    // effect->SetOption1(paramController->GetRawParam(Param::kOption2) == 1);
    // effect->SetSlider1(paramController->GetRawParam(Param::kSlider1));
    // effect->SetSlider2(paramController->GetRawParam(Param::kSlider2));
    // effect->SetShift(doShiftNow);

    if (doShiftNow) {
      shiftI++;
    }
    poles[0]->SetGridLight(
        shiftI % 4, 1,
        CHSV(0, 255, 255 - 255 * timeSinceLastBeat / millisPerBeat));
    poles[0]->SetGridLight((shiftI + 4 - 1) % 4, 1, CHSV(0, 255, 0));
  }
  lastTimeSinceLastBeat = timeSinceLastBeat;
  lastMillisPerBeat = millisPerBeat;

  SleepMs(20);
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
  beatTrackingTime += timeSinceLastBeat;
  if (timeSinceLastBeat != 0) {
    beatQueue.push(timeSinceLastBeat);
  }
  if ((beatQueue.size() > BEATS_TO_RECORD || timeSinceLastBeat == 0) &&
      beatQueue.size() > 0) {
    beatTrackingTime -= beatQueue.front();
    beatQueue.pop();
  }
  return beatTrackingTime / beatQueue.size();
}
