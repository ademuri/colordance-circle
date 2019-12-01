#ifndef COLORDANCE_TYPES_HPP_
#define COLORDANCE_TYPES_HPP_

#ifdef ARDUINO

#include <FastLED.h>

// Arduino.h, automatically included by the IDE, defines min and max macros
// (which it shouldn't). Apparently FastLED depends on them, so don't undef
// them until FastLED has been included.
#undef max
#undef min

#else
#include <chrono>

#include "FakeFastLED/colorutils.h"
#include "FakeFastLED/hsv2rgb.h"
#include "FakeFastLED/pixeltypes.h"

// Replace the Arduino millis() function. Note that this counts from the first
// call of this function.
uint32_t millis();

void UseRealMillis();
void SetMillis(uint32_t ms);
void AdvanceMillis(uint32_t ms);

#endif

#endif
