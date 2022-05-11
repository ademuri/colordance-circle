#include <FastLED.h>
#include <SPISlave_T4.h>
#include <debounce-filter.h>
#include <median-filter.h>

#include <vector>

#include "debug.h"

// Behavior flags
const constexpr bool kDebugFlashAtBoot = true;

enum class RunType {
  NORMAL,
  DEBUG_LIGHTS,
  DEBUG_CONTROLS,
};

const constexpr RunType run_mode = RunType::NORMAL;

// Buttons
const int kButton1 = 2;
const int kButton2 = 3;
const int kButton3 = 28;
const int kButton4 = 29;
const int kButton5 = 5;
const int kButton6 = 4;
const int kButton7 = 30;
const int kButton8 = 31;
const int kButton9 = 33;
const int kButton10 = 7;
const int kButton11 = 35;
const int kButton12 = 36;
const int kButton13 = 37;
const int kButton14 = 34;

const std::vector<int> BUTTON_PINS = {
    kButton1, kButton2, kButton3,  kButton4,  kButton5,  kButton6,  kButton7,
    kButton8, kButton9, kButton10, kButton11, kButton12, kButton13, kButton14,
};

std::vector<DebounceFilter> buttons;
std::vector<bool> button_rose;

// Analog inputs
const int kAnalog1 = 38;
const int kAnalog2 = 30;
const int kAnalog3 = 40;
const int kAnalog4 = 41;
const int kAnalog5 = 26;
const int kAnalog6 = 21;
const int kAnalog7 = 39;
const int kAnalog8 = 27;

const std::vector<int> ANALOG_INPUT_PINS = {
    kAnalog1, kAnalog2, kAnalog3, kAnalog4,
    kAnalog5, kAnalog6, kAnalog7, kAnalog8,
};

std::vector<MedianFilter<uint16_t, uint16_t, 3>> analog_inputs;
std::vector<uint16_t> prev_analog_inputs;

// FastLED Teensy 4.1 parallel output pin strings:
// [1, 0, 24, 25, 19, 18, 14, 15, 17, 16, 22, 23,] 20, 21, 26, 27
// 10, 12, 11, 13, [6, 9, 32, 8,] 7
// 37, 36, 35, 34, 39, 38, 28, 31, 30

/*
Index  LED_number
Bank 1:
 0  1
 1  2
 2 14
 3 15
 4  7
 5  8
 6 12
 7 11
 8  9
 9 10
10  6
11  5

Bank 2:
0  3
1 13
2 16
3  4
*/

const int kMaxLedsPerStrip = 15;
const int kStripsPerBank1 = 12;
const int kStripsPerBank2 = 4;

const int kBank1FirstPin = 1;
const int kBank2FirstPin = 6;

CRGB bank1[kMaxLedsPerStrip * kStripsPerBank1];
CRGB bank2[kMaxLedsPerStrip * kStripsPerBank2];

CRGB* getStrip(CRGB* const bank, const int index) {
  return &bank[index * kMaxLedsPerStrip];
}

// LED strips matching the order of the buttons, then the analog inputs, based
// on their positions on the PCB.
// clang-format off
std::vector<CRGB*> strips = {
    getStrip(bank1,  0), getStrip(bank1, 11), getStrip(bank1,  8), getStrip(bank2,  1),
    getStrip(bank1,  1), getStrip(bank1, 10), getStrip(bank1,  9), getStrip(bank1,  2),
    getStrip(bank2,  0), getStrip(bank1,  4), getStrip(bank1,  7), getStrip(bank1,  3),
    getStrip(bank2,  3), getStrip(bank1,  5), getStrip(bank1,  6), getStrip(bank2,  2),

    // Original, in LED_1, LED_2, etc. order
    /*
    getStrip(bank1, 0), getStrip(bank1, 1),  getStrip(bank2, 0),
    getStrip(bank2, 3), getStrip(bank1, 11), getStrip(bank1, 10),
    getStrip(bank1, 4), getStrip(bank1, 5),  getStrip(bank1, 8),
    getStrip(bank1, 9), getStrip(bank1, 7),  getStrip(bank1, 6),
    getStrip(bank2, 1), getStrip(bank1, 2),  getStrip(bank1, 3),
    getStrip(bank2, 2),
    */
};
// clang-format on

SPISlave_T4<&SPI, SPI_8_BITS> spi_out;

// Writes out the button bitmask and analog input values to SPI
void onReceive() {
  if (!spi_out.active()) {
    debug_printf("onReceive called, but received 0 bytes");
    return;
  }
  uint8_t buttons_bitmask = 0;
  for (uint8_t button_index = 0; button_index < 8; button_index++) {
    buttons_bitmask |= button_rose[button_index] << 7 - button_index;
  }
  spi_out.pushr(buttons_bitmask);

  if (!spi_out.active()) {
    debug_printf("onReceive called, but only received 1 bytes");
    return;
  }
  for (uint8_t button_index = 8; button_index < buttons.size();
       button_index++) {
    buttons_bitmask |= button_rose[button_index] << 16 - button_index;
  }
  spi_out.pushr(buttons_bitmask);

  for (uint8_t i = 0; i < analog_inputs.size(); i++) {
    if (!spi_out.active()) {
      debug_printf("onReceive called, but only received %u bytes", i + 2);
      return;
    }
    spi_out.pushr(analog_inputs[i].GetFilteredValue());
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Booting...");

  for (auto button_pin : BUTTON_PINS) {
    pinMode(button_pin, INPUT_PULLUP);
    buttons.push_back(DebounceFilter(
        filter_functions::ForInvertedDigitalReadDynamic(button_pin)));
    button_rose.push_back(false);
  }

  for (auto analog_pin : ANALOG_INPUT_PINS) {
    pinMode(analog_pin, INPUT);
    analog_inputs.push_back(MedianFilter<uint16_t, uint16_t, 3>(
        filter_functions::ForAnalogReadDynamic(analog_pin)));
    prev_analog_inputs.push_back(analogRead(analog_pin));
  }

  // Controls only use 8 bits of resolution
  analogReadResolution(8);

  FastLED.addLeds<kStripsPerBank1, WS2812, kBank1FirstPin, RGB>(
      bank1, kStripsPerBank1);
  FastLED.addLeds<kStripsPerBank2, WS2812, kBank2FirstPin, RGB>(
      bank2, kStripsPerBank2);
  FastLED.clear();
  // colordance-brain power supply can source 1A at 5V. Leave lots of margin for
  // its load (the RS422 is power-hungry).
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);

  if (kDebugFlashAtBoot) {
    // Quickly flash all of the controls R, G, B. This facilitates checking that
    // all LEDS work on startup.
    FastLED.showColor(CRGB(255, 0, 0));
    FastLED.delay(1000);
    FastLED.showColor(CRGB(0, 255, 0));
    FastLED.delay(1000);
    FastLED.showColor(CRGB(0, 0, 255));
    FastLED.delay(1000);
  }

  Serial.println("Local assets initialized. Beginning SPI communication...");

  spi_out.begin();
  spi_out.onReceive(onReceive);

  Serial.println("SPI started successfully");
}

void readControls() {
  for (uint8_t button_index = 0; button_index < buttons.size();
       button_index++) {
    buttons[button_index].Run();
    if (buttons[button_index].Rose()) {
      button_rose[button_index] = true;
    }
  }

  for (auto filter : analog_inputs) {
    filter.Run();
  }
}

void debugControls() {
  // Buttons
  for (uint8_t button_index = 0; button_index < BUTTON_PINS.size();
       button_index++) {
    CRGB color = digitalRead(BUTTON_PINS[button_index])
                     ? CHSV(HUE_RED, 255, 16)
                     : CHSV(HUE_BLUE, 255, 255);
    for (int light_index = 0; light_index < kMaxLedsPerStrip; light_index++) {
      strips[button_index][light_index] = color;
    }
  }

  // Analog inputs
  for (uint8_t analog_index = 0; analog_index < ANALOG_INPUT_PINS.size();
       analog_index++) {
    uint16_t input = analogRead(ANALOG_INPUT_PINS[analog_index]);
    // Range from dark red to bright white
    CHSV color = CHSV(HUE_RED, 255 - input, input);
    for (int light_index = 0; light_index < kMaxLedsPerStrip; light_index++) {
      strips[analog_index + BUTTON_PINS.size()][light_index] = color;
    }
  }

  FastLED.show();
  delay(10);
}

// Flash the lights RED, GREEN, BLUE
void debugLights() {
  CRGB color = CRGB(255, 0, 0);
  if ((millis() / 1000) % 3 == 1) {
    color = CRGB(0, 255, 0);
  } else if ((millis() / 1000) % 3 == 2) {
    color = CRGB(0, 0, 255);
  }
  FastLED.showColor(color);
  delay(10);
}

void loop() {
  switch (run_mode) {
    case RunType::NORMAL:
      readControls();
      // TODO: output LEDs
      break;

    case RunType::DEBUG_CONTROLS:
      debugControls();
      break;

    case RunType::DEBUG_LIGHTS:
      debugLights();
      break;
  }
}
