#include "ControlledEffect.hpp"

#include "ColordanceTypes.hpp"

ControlledEffect::ControlledEffect(std::vector<Pole*> poles,
                                   ParamController* paramController)
    : Effect(poles, paramController) {
  for (int i = 0; i < Pole::kNumPoles; i++) {
    ControlPole* pole = new ControlPole(i, FRAMES_PER_LOOP);
    controlPoles.push_back(pole);
  }
}

void ControlledEffect::DoRun() {
  uint8_t pause = paramController->GetRawParam(Param::kPause);
  if (Pole::kNumPoles == 0 || pause) return;

  lastMovementMode = movementMode;
  uint8_t lastMovementSpeed = movementSpeed;
  movementMode = paramController->GetRawParam(Param::kMovementMode);
  movementSpeed = paramController->GetRawParam(Param::kMovementSpeed);
  poleHueShift = paramController->GetRawParam(Param::kPollHueShift);
  setPoles = paramController->GetRawParam(Param::kActivePoles);

  uint8_t balanceColor = paramController->GetRawParam(Param::kBalanceColor);

  uint8_t gridMode = paramController->GetRawParam(Param::kGridMode);
  uint8_t gridLightCount = paramController->GetRawParam(Param::kGridLightCount);
  uint8_t gridSpeed = paramController->GetRawParam(Param::kGridSpeed);
  uint8_t gridHueShift = paramController->GetRawParam(Param::kGridHueShift);
  uint8_t gridHueDistance =
      paramController->GetRawParam(Param::kGridHueDistance);
  uint8_t gridBackForth = paramController->GetRawParam(Param::kGridBackForth);
  uint8_t gridSmoothColor =
      paramController->GetRawParam(Param::kGridSmoothColor);
  uint8_t gridReverse = paramController->GetRawParam(Param::kGridReverse);
  bpm = paramController->GetRawParam(Param::kBpm);

  uint8_t numberOfPolesOn = GetNumberOfPolesOn(setPoles);

  // uint8_t poleHueShiftOffest = poleHueShift;
  if (balanceColor == 1) {
    poleHueShift = 255 / numberOfPolesOn;
  }

  uint8_t polesOnCount = 0;
  for (int i = 0; i < Pole::kNumPoles; i++) {
    poles[i]->ClearGridLights();
    controlPoles[i]->SetMode(gridMode);
    if (setPoles & (1 << i)) {
      controlPoles[i]->SetHue(polesOnCount++ * poleHueShift);
      controlPoles[i]->SetLightCount(gridLightCount == 0 ? 1 : gridLightCount);
      controlPoles[i]->SetHueShift(gridHueShift);
      controlPoles[i]->SetHueDistance(gridHueDistance);
      controlPoles[i]->SetBackAndForth(gridBackForth);
      controlPoles[i]->SetSmoothColor(gridSmoothColor == 1);
      controlPoles[i]->SetReverse(gridReverse == 1);
    }
  }

  bool resetBeat = (paramController->GetRawParam(Param::kBeatReset) == 1);

  uint32_t millisPerBeat = 60000 / (bpm == 0 ? 80 : bpm);
  uint8_t beatsPerLoop = gridSpeed == 0 ? 1 : gridSpeed;
  uint32_t timer = 0;
  if (resetBeat != beatSet) {
    timerOffset = millis();
    beatSet = resetBeat;
  }

  uint16_t frame = 0;
  do {
    SleepMs(10);
    timer = millis() - timerOffset;
    frame = (timer * FRAMES_PER_LOOP / (millisPerBeat * beatsPerLoop)) %
            FRAMES_PER_LOOP;
    // frame = (timer * loopsPerBeat / millisPerBeat) % FRAMES_PER_LOOP;
  } while (frame == lastFrame && resetBeat == beatSet);

  if (frame < lastFrame) {
    movementCount++;
  }
  movementSpeed = movementSpeed == 0 ? 1 : movementSpeed;
  movementCount %= 6 * movementSpeed;
  uint8_t movement = (movementCount / movementSpeed) % 6;
  switch (movementMode) {
    case 1:
    case 2:
      poleOffset = movement;
      break;
    case 3:
      poleOffset = movement % 2 == 0 ? 0 : 3;
      break;
    case 4:
      poleOffset = movement % 2 == 0 ? 0 : 1;
      break;
    default:
      poleOffset = 0;
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

uint8_t ControlledEffect::GetNumberOfPolesOn(uint8_t polesBitMap) {
  uint8_t count = 0;
  while (polesBitMap != 0) {
    count += polesBitMap & 1;
    polesBitMap >>= 1;
  }
  return count;
}
