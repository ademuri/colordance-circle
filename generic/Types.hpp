#ifndef TYPES_HPP_
#define TYPES_HPP_

#ifdef ARDUINO

#else
#include <chrono>

#include "FakeFastLED/colorutils.h"
#include "FakeFastLED/hsv2rgb.h"
#include "FakeFastLED/pixeltypes.h"

// Replace the Arduino millis() function. Note that this counts from the first
// call of this function.
uint32_t millis();

#endif

#endif
