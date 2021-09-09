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
  uint8_t numOfEffects = 5;

  bool previous = paramController->GetRawParam(Param::kPrevious) == 1;
  bool next = paramController->GetRawParam(Param::kNext) == 1;
  bool randomize = paramController->GetRawParam(Param::kRandom) == 1;

  uint8_t effect = (lastEffect + (next != lastNext ? 1 : 0) +
                    (previous != lastPrevious ? numOfEffects - 1 : 0)) %
                   numOfEffects;

  bool effectChanged = lastEffect != effect;
  bool initalize = randomize != lastRandom || effectChanged;

  lastPrevious = previous;
  lastNext = next;
  lastRandom = randomize;
  lastEffect = effect;

  if (initalize) {
    bpm = 80;
    modes[0] = 0;
    modes[1] = 0;
    modes[2] = 0;
    modes[3] = 0;
    hueDistances[0] = 0;
    hueDistances[1] = 0;
    hueDistances[2] = 0;
    hueDistances[3] = 0;
    vals[0] = 255;
    vals[1] = 255;
    vals[2] = 255;
    vals[3] = 255;
    gridLightCount = 4;
    reverse[0] = false;
    reverse[1] = false;
    reverse[2] = false;
    reverse[3] = false;
    staticShiftIndex[0] = 255;
    staticShiftIndex[1] = 255;
    staticShiftIndex[2] = 255;
    staticShiftIndex[3] = 255;
    movementSpeed = 4;  // loops per pole shift
    movementMode = 0;   // still
    beatsPerLoop = 2;
    gridBackForth = false;
    gridSmoothColor = random(2);

    if (effect == 0) {
      // 2 dim poles balance bright pole
      setPoles = 15;  // 0 1 1 1
      modes[0] = 2;
      modes[1] = 4;
      modes[2] = 2;
      modes[3] = 4;
      reverse[0] = false;
      reverse[1] = false;
      reverse[2] = true;
      reverse[3] = true;
      gridBackForth = true;
      gridHueShift = random(1, 15);
      uint8_t gridHueDistance = random(5, 40);
      hueDistances[0] = gridHueDistance;
      hueDistances[1] = gridHueDistance;
      hueDistances[2] = gridHueDistance;
      hueDistances[3] = gridHueDistance;
      uint8_t maxHueSpread = 85;
      uint8_t hueSpread = random(maxHueSpread / 2);
      hues[0] = 255 - hueSpread;
      hues[1] = 128;
      hues[2] = hueSpread;
      hues[3] = 128;
      uint8_t val = (((uint32_t)hueSpread) * 256) / maxHueSpread + 127;
      vals[0] = val;
      vals[2] = val;
      if (val > 220) {
        gridLightCount = 2;
      } else if (val > 180) {
        gridLightCount = 3;
      }
      vals[3] = 0;
      movementSpeed = random(2, 8);
    } else if (effect == 1) {
      // 3 color pole moves through single color poles
      setPoles = 15;  // 1 1 1 1
      modes[0] = 13;
      modes[1] = 4;
      modes[2] = 4;
      modes[3] = 4;
      reverse[0] = true;
      staticShiftIndex[1] = 1;
      staticShiftIndex[2] = 1;
      staticShiftIndex[3] = 1;
      gridHueShift = random(1, 10);
      hues[0] = 85;
      hues[1] = 0;
      hues[2] = 85;
      hues[3] = 170;
      uint8_t val = random(200, 255);
      vals[1] = val;
      vals[2] = val;
      vals[3] = val;
      hueDistances[0] = 85;
      gridLightCount = 1;  // 0 set to 3 below
      movementMode = 5;    // rotate
      movementSpeed = 1;   // loops per pole shift
    } else if (effect == 2) {
      // fade in/out with circle movements
      setPoles = 15;  // 1 1 1 1
      uint8_t mode = random(6, 14);
      if (mode == 13) {
        // Make pinwheel more frequent
        mode = 10;
      } else if (mode >= 11) {
        mode = mode - 11;
      }
      modes[0] = mode;
      modes[1] = mode;
      modes[2] = mode;
      modes[3] = mode;
      gridLightCount = random(2, 5);
      if (mode == 10) {
        gridLightCount = 4;
      }
      hues[0] = 0;
      hues[1] = 128;
      hues[2] = 0;
      hues[3] = 128;
      uint8_t gridHueDistance = random(5, 80);
      hueDistances[0] = gridHueDistance;
      hueDistances[1] = gridHueDistance;
      hueDistances[2] = gridHueDistance;
      hueDistances[3] = gridHueDistance;
      gridHueShift = random(mode < 2 ? 10 : 4, 15);
      beatsPerLoop = random(2, 6);
      movementSpeed = random(2, 6);
    } else if (effect == 3) {
      // 1 light on  all poles fast hue shift
      setPoles = 15;             // 1 1 1 1
      uint8_t mode = random(5);  // 0, 2, 3, 6
      if (mode > 0 && mode < 3) {
        mode += 2;
      } else if (mode > 0) {
        mode = 6;
      }
      modes[0] = mode;
      modes[1] = mode;
      modes[2] = mode;
      modes[3] = mode;
      gridLightCount = 1;
      hues[0] = 0;
      hues[1] = 64;
      hues[2] = 128;
      hues[3] = 192;
      gridHueShift = random(10, 25);
      gridBackForth = random(2) == 0;
      bool shouldReverse = random(2) == 0;
      reverse[0] = shouldReverse;
      reverse[1] = shouldReverse;
      reverse[2] = shouldReverse;
      reverse[3] = shouldReverse;
    } else if (effect == 4) {
      // 4 lights on 1/2 pole fast hue shift
      setPoles = random(1, 4);
      modes[0] = random(0, 5);
      modes[1] = random(0, 5);
      staticShiftIndex[0] = 0;
      staticShiftIndex[1] = 0;
      gridLightCount = 4;
      hueDistances[0] = 64;
      hueDistances[1] = 64;
      if (setPoles == 3) {
        vals[0] = 200;
        vals[1] = 200;
      }
      gridHueShift = random(40, 80);
      beatsPerLoop = 4;
      movementMode = 1;
      movementSpeed = random(2, 5);  // loops per pole shift
    }
  }

  // Timing
  uint32_t millisPerBeat = 60000 / (bpm == 0 ? 80 : bpm);
  uint32_t timer = 0;
  uint16_t frame = 0;
  if (beatsPerLoop == 0) {
    frame = lastFrame;
  } else {
    do {
      SleepMs(10);
      timer = millis() - timerOffset;
      frame = (timer * FRAMES_PER_LOOP / (millisPerBeat * beatsPerLoop)) %
              FRAMES_PER_LOOP;
    } while (frame == lastFrame);
  }
  bool movedPoles = false;
  if (frame < lastFrame) {
    movedPoles = true;
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
    case 5:
      poleOffset = Pole::kNumPoles - movement;
      break;
    default:
      poleOffset = 0;
  }

  // Effects
  if (effect == 0 && movedPoles && movementCount % 4 == 0) {
    uint8_t val1 = vals[1];
    vals[1] = vals[3];
    vals[3] = val1;
  }
  if (effect == 1 && movedPoles) {
    uint8_t hue3 = hues[3];
    hues[3] = hues[2];
    hues[2] = hues[1];
    hues[1] = hue3;
    hues[0] = hues[3];
  }
  if (effect == 2) {
    uint16_t maxVal = 255;
    if (gridLightCount == 3) {
      maxVal = 240;
    } else if (gridLightCount == 4) {
      maxVal = 200;
    }

    uint16_t adjustedFrame =
        (uint16_t)255 *
        (FRAMES_PER_LOOP * (movementCount % movementSpeed) + frame) /
        (FRAMES_PER_LOOP * movementSpeed);

    vals[3] = sin8(adjustedFrame) * maxVal / 255;
    vals[2] = sin8(adjustedFrame + 64) * maxVal / 255;
    vals[1] = sin8(adjustedFrame + 128) * maxVal / 255;
    vals[0] = sin8(adjustedFrame + 192) * maxVal / 255;
  }
  // if (effect == 4 ) {
  //   uint8_t pauseLength = 12;
  //   uint8_t loopLength = pauseLength + 4;
  //   uint16_t adjustedFrame = (millis()/600) % (4*loopLength);
  //   poleOffset = adjustedFrame % loopLength;
  //   poleOffset = poleOffset < pauseLength ? 0 : poleOffset - pauseLength + 1;
  //   poleOffset += adjustedFrame/loopLength;
  //   poleOffset %= 4;
  // }

  // Setting
  for (uint8_t pole = 0; pole < Pole::kNumPoles; pole++) {
    poles[pole]->ClearGridLights();
    if (initalize) {
      controlPoles[pole]->Reset();
    }
    if (setPoles & (1 << pole)) {
      controlPoles[pole]->SetMode(modes[pole]);
      controlPoles[pole]->SetHue(hues[pole]);
      controlPoles[pole]->SetVal(vals[pole]);
      controlPoles[pole]->SetLightCount(gridLightCount);
      controlPoles[pole]->SetHueShift(gridHueShift);
      controlPoles[pole]->SetHueDistance(hueDistances[pole]);
      controlPoles[pole]->SetBackAndForth(gridBackForth);
      controlPoles[pole]->SetSmoothColor(gridSmoothColor == 1);
      controlPoles[pole]->SetReverse(reverse[pole]);
      controlPoles[pole]->SetStaticShiftIndex(staticShiftIndex[pole]);
    }
  }
  if (effect == 1) {
    controlPoles[0]->SetLightCount(3);
  }
  for (uint8_t pole = 0; pole < Pole::kNumPoles; pole++) {
    if (setPoles & (1 << pole)) {
      uint8_t effectivePole = (pole + poleOffset) % Pole::kNumPoles;
      poles[effectivePole]->SetGridLights(
          controlPoles[pole]->GetGrid(frame, lastFrame));
    }
  }

  lastFrame = frame;
}
