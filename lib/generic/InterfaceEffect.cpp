#include "InterfaceEffect.hpp"

#include "ColordanceTypes.hpp"

InterfaceEffect::InterfaceEffect() {}

void InterfaceEffect::SetOption1(bool pressed) {
  if (option1WasPressed && !pressed) {
    UpdateOption1();
  }
  option1WasPressed = pressed;
}

void InterfaceEffect::SetOption2(bool pressed) {
  if (option2WasPressed && !pressed) {
    UpdateOption2();
  }
  option2WasPressed = pressed;
}

void InterfaceEffect::SetSlider1(uint8_t val) { UpdateSlider1(val); }

void InterfaceEffect::SetSlider2(uint8_t val) { UpdateSlider2(val); }

void InterfaceEffect::Shift() { DoShift(); };

void InterfaceEffect::SetGrid(std::vector<Pole*> poles,
                              uint16_t timeSinceLastBeat,
                              uint16_t millisPerBeat) {
  if (lastTimeSinceLastBeat + WAIT_TIME_TO_START_OVER < timeSinceLastBeat) {
    Reset();
  }

  DoSetGrid(poles, FRAMES_PER_LOOP * timeSinceLastBeat / millisPerBeat);
  lastTimeSinceLastBeat = timeSinceLastBeat;
}
