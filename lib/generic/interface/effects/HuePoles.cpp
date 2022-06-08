#include "HuePoles.hpp"

#include "ColordanceTypes.hpp"

HuePoles::HuePoles() : InterfaceEffect() {}

bool HuePoles::ContinuousShift() { return true; }

void HuePoles::DoSetGrid(std::vector<Pole*>& poles, uint16_t frame) {}

/**
 * Change the mode (grid animation).
 */
void HuePoles::UpdateOption1() {}

void HuePoles::UpdateOption2() {}

/**
 * Change the number of poles on.
 */
void HuePoles::UpdateSlider1(uint8_t val) {}

void HuePoles::UpdateHues() {}

/**
 * Chages the hue distance
 */
void HuePoles::UpdateSlider2(uint8_t val) {}

void HuePoles::DoShift(uint8_t shiftPosition) {}

void HuePoles::ResetEffect() { poleOffset = 0; }