#include "InterfaceEffect.hpp"

#include "ColordanceTypes.hpp"

InterfaceEffect::InterfaceEffect(std::vector<Pole*> poles) {}

void InterfaceEffect::SetOption1(bool on) { option1 = on; }

void InterfaceEffect::SetOption2(bool on) { option2 = on; }

void InterfaceEffect::SetSlider1(uint8_t val) { slider1 = val; }

void InterfaceEffect::SetSlider2(uint8_t val) { slider2 = val; }

void InterfaceEffect::SetShift(bool doShift) { shift = doShift; }

void InterfaceEffect::Run(uint16_t timeSinceLastBeat, uint16_t millisPerBeat) {}