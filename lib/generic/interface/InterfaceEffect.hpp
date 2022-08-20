#pragma once

#include "Buttons.hpp"
#include "ColordanceTypes.hpp"
#include "Pole.hpp"
#include "control-pole/ControlPole.hpp"

class InterfaceEffect {
 public:
  InterfaceEffect();

  void SetOption1(bool pressed);
  void SetOption2(bool pressed);
  void SetSlider1(uint8_t val);
  void SetSlider2(uint8_t val);

  void SetBeatsPerShift(uint8_t beats);
  void SetBeatsSinceAutoShift(uint8_t beats);

  void AutomaticShift(bool didManual);
  void AutomaticPartialShift(uint8_t shiftFraction);
  void ManualShift(bool didAutomatic);
  void Update(uint16_t timeSinceLastBeat, uint16_t millisPerBeat);
  void SetGrid(Poles &poles);
  void SetEffectButton(Buttons buttons);

  void Reset();

 protected:
  virtual void DoUpdate(uint16_t frame, uint16_t lastFrame) = 0;
  virtual void DoSetGrid(Poles &poles) = 0;
  virtual void DoSetEffectButton(Buttons buttons) = 0;
  virtual void UpdateOption1() = 0;
  virtual void UpdateOption2() = 0;
  virtual void UpdateSlider1(uint8_t val) = 0;
  virtual void UpdateSlider2(uint8_t val) = 0;
  virtual void DoAutomaticShift(bool didManual) = 0;
  virtual void DoAutomaticPartialShift(uint8_t shiftFraction) = 0;
  virtual void DoManualShift(bool didAutomatic) = 0;
  virtual void InitializeEffect(){};

  const uint16_t FRAMES_PER_LOOP = 840;

  bool option1WasPressed = false;
  bool option2WasPressed = false;

  uint8_t beatsPerShift = 0;
  uint8_t beatsSinceAutoShift = 0;

  uint32_t lastTimeSinceLastBeat = 0;

  uint16_t lastFrame = 0;

 private:
  const uint16_t WAIT_TIME_TO_START_OVER = 8000;  // time effect was off
};
