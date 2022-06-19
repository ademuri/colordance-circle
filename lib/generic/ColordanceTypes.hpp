#pragma once

#define UNUSED(x) (void)(x)

#ifdef ARDUINO

#include <FastLED.h>

// Arduino.h, automatically included by the IDE, defines min and max macros
// (which it shouldn't). Apparently FastLED depends on them, so don't undef
// them until FastLED has been included.
#undef max
#undef min

#else
#include <chrono>

// Ignore warnings for FakeFastLED
#pragma GCC diagnostic push

#pragma GCC diagnostic ignored "-Wpedantic"

#include <FastLED.h>
//#include "../third_party/FakeFastLED/colorutils.h"
//#include "colorutils.h"
//#include "../third_party/FakeFastLED/hsv2rgb.h"
//#include "../third_party/FakeFastLED/pixeltypes.h"

#pragma GCC diagnostic pop

// Replace the Arduino millis() function. Note that this counts from the first
// call of this function.
uint32_t millis();

void UseRealMillis();
void SetMillis(uint32_t ms);
void AdvanceMillis(uint32_t ms);

#endif
