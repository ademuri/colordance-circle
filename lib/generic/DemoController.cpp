#include "DemoController.hpp"

#include "ColordanceTypes.hpp"

DemoController::DemoController(std::vector<Pole*> poles,
                               ParamController* paramController)
    : Effect(poles, paramController) {
  for (int i = 0; i < Pole::kNumPoles; i++) {
    ControlPole* pole = new ControlPole(i, FRAMES_PER_LOOP);
    controlPoles.push_back(pole);
  }
}

void DemoController::DoRun() {
  uint8_t effect = 0;

  // MOVEMENT SETTINGS
  uint8_t gridMode = 0;
  uint8_t setPoles = 0;
  uint8_t movementSpeed = 0;
  uint8_t movementMode = 0;
  uint8_t poleHueShift = 0;
  uint8_t beatsPerLoop = 0;
  uint8_t gridLightCount = 0;
  uint8_t gridHueShift = 0;
  uint8_t gridHueDistance = 0;
  uint8_t gridBackForth = 0;
  uint8_t gridSmoothColor = 0;
  uint8_t gridReverse = 0;

  if (effect == 0) {
    gridMode = 6;       // circle
    setPoles = 5;       // 0 1 0 1
    movementSpeed = 4;  // loops per pole shift
    movementMode = 1;   // rotation
    poleHueShift = 255 / 3;
    beatsPerLoop = 2;
    gridLightCount = 3;
    gridHueShift = 2;
    gridHueDistance = 15;
    gridSmoothColor = 0;
  }

  // TIMING
  bool shouldResetBeat = (paramController->GetRawParam(Param::kBeatReset) == 1);

  uint32_t millisPerBeat = 60000 / (bpm == 0 ? 80 : bpm);
  uint32_t timer = 0;
  if (shouldResetBeat != beatHasBeenSet) {
    timerOffset = millis();
    beatHasBeenSet = shouldResetBeat;
  }

  uint16_t frame = 0;
  if (beatsPerLoop == 0) {
    frame = lastFrame;
  } else {
    do {
      SleepMs(10);
      timer = millis() - timerOffset;
      frame = (timer * FRAMES_PER_LOOP / (millisPerBeat * beatsPerLoop)) %
              FRAMES_PER_LOOP;
    } while (frame == lastFrame && shouldResetBeat == beatHasBeenSet);
  }

  // SETTING
  if (effect < 1) {
    if (frame < lastFrame) {
      movementCount++;
    }
    movementSpeed = movementSpeed == 0 ? 1 : movementSpeed;
    movementCount %= Pole::kNumPoles * movementSpeed;
    uint8_t movement = (movementCount / movementSpeed) % Pole::kNumPoles;
    uint8_t poleOffset = 0;
    switch (movementMode) {
      case 1:
      case 2:
        poleOffset = movement;
        break;
      case 3:
        poleOffset = movement % 2 == 0 ? 0 : Pole::kNumPoles / 2;
        break;
      case 4:
        poleOffset = movement % 2 == 0 ? 0 : 1;
        break;
      default:
        poleOffset = 0;
    }

    uint8_t polesOnCount = 0;
    for (int i = 0; i < Pole::kNumPoles; i++) {
      poles[i]->ClearGridLights();
      controlPoles[i]->SetMode(gridMode);
      if (setPoles & (1 << i)) {
        controlPoles[i]->SetHue(polesOnCount++ * poleHueShift);
        controlPoles[i]->SetLightCount(gridLightCount == 0 ? 1
                                                           : gridLightCount);
        controlPoles[i]->SetHueShift(gridHueShift);
        controlPoles[i]->SetHueDistance(gridHueDistance);
        controlPoles[i]->SetBackAndForth(gridBackForth);
        controlPoles[i]->SetSmoothColor(gridSmoothColor == 1);
        controlPoles[i]->SetReverse(gridReverse == 1);
      }
    }
    for (uint8_t pole = 0; pole < Pole::kNumPoles; pole++) {
      if (setPoles & (1 << pole)) {
        uint8_t effectivePole = (pole + poleOffset) % Pole::kNumPoles;
        poles[effectivePole]->SetGridLights(
            controlPoles[pole]->GetGrid(frame, lastFrame));
      }
    }
  }

  lastFrame = frame;
}
