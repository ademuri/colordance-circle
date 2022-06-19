#include <EasyTransfer.h>
#include <FastLED.h>
#include <debounce-filter.h>
#include <median-filter.h>

#include <vector>

#include "Controls.hpp"

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
const int kAnalog2 = 20;
const int kAnalog3 = 40;
const int kAnalog4 = 41;
const int kAnalog5 = 26;
const int kAnalog6 = 21;
const int kAnalog7 = 39;
const int kAnalog8 = 27;

const std::vector<int> ANALOG_INPUT_PINS = {
    kAnalog1, kAnalog3, kAnalog4, kAnalog5, kAnalog7, kAnalog8,
};

const std::vector<int> PCB_ORDER_INPUT_PINS = {
    kButton1, kButton5,  kButton9,  kAnalog1,
    kButton2, kButton6,  kButton10, /* No analog 2, */ kButton3,
    kButton7, kButton11, kAnalog3,  kButton4,
    kButton8, kButton12, kAnalog4,
};

std::vector<MedianFilter<uint16_t, uint16_t, 3>> analog_inputs;
std::vector<uint16_t> prev_analog_inputs;

EasyTransfer brain_out;
EasyTransfer brain_in;
ControlsIn brain_out_data;
ControlsOut brain_in_data;

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

uint8_t effect_last_pressed = 0;

// LED strips matching the order of the buttons, then the analog inputs, based
// on their positions on the PCB.
// clang-format off
std::vector<CRGB*> strips = {
    // getStrip(bank1,  0), getStrip(bank1, 11), getStrip(bank1,  8), getStrip(bank2,  1),
    // getStrip(bank1,  1), getStrip(bank1, 10), getStrip(bank1,  9), getStrip(bank1,  2),
    // getStrip(bank2,  0), getStrip(bank1,  4), getStrip(bank1,  7), getStrip(bank1,  3),
    // getStrip(bank2,  3), getStrip(bank1,  5), getStrip(bank1,  6), getStrip(bank2,  2),

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

void setup() {
  Serial.begin(115200);
  Serial.println("Booting...");

  for (auto button_pin : BUTTON_PINS) {
    pinMode(button_pin, INPUT_PULLUP);
    // buttons.push_back(DebounceFilter(
    //     filter_functions::ForInvertedDigitalReadDynamic(button_pin)));
    // button_rose.push_back(false);
  }

  for (auto analog_pin : ANALOG_INPUT_PINS) {
    pinMode(analog_pin, INPUT);
    analog_inputs.push_back(MedianFilter<uint16_t, uint16_t, 3>(
        filter_functions::ForAnalogReadDynamic(analog_pin)));
    prev_analog_inputs.push_back(analogRead(analog_pin));
  }

  // Controls only use 8 bits of resolution
  analogReadResolution(8);

  Serial.println("Pins initialized");

  FastLED.addLeds<kStripsPerBank1, WS2812, kBank1FirstPin, GRB>(
      bank1, kMaxLedsPerStrip);
  FastLED.addLeds<kStripsPerBank2, WS2812, kBank2FirstPin, GRB>(
      bank2, kMaxLedsPerStrip);
  FastLED.showColor(CRGB::Black);
  // colordance-brain power supply can source 1A at 5V. Leave lots of margin for
  // its load (the RS422 is power-hungry).
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);

  Serial.println("FastLED initialized");
  delay(100);

  if (kDebugFlashAtBoot) {
    // Quickly flash all of the controls R, G, B. This facilitates checking that
    // all LEDS work on startup.
    FastLED.showColor(CRGB(255, 0, 0));
    delay(250);
    FastLED.showColor(CRGB(0, 255, 0));
    delay(250);
    FastLED.showColor(CRGB(0, 0, 255));
    delay(250);
    FastLED.showColor(CRGB::Black);
  }

  Serial.println("Local assets initialized. Beginning serial communication...");

  Serial5.begin(kSerialBaud);
  brain_out.begin(details(brain_out_data), &Serial5);
  brain_in.begin(details(brain_in_data), &Serial5);
}

void readControls() {
  brain_out_data.button_mask = 0;
  bool effect_pressed = false;

  for (uint8_t button_index = 0; button_index < BUTTON_PINS.size();
       button_index++) {
    uint8_t val = !digitalRead(BUTTON_PINS[button_index]) << button_index;
    if (val && !effect_pressed) {
      effect_last_pressed = button_index;
      effect_pressed = true;
    }
    brain_out_data.button_mask |= val;

    for (uint8_t i = 0; i < kMaxLedsPerStrip; i++) {
      if (button_index >= 3 && button_index <= 6) {
        // Effect buttons
        if (i < 6) {
          strips[button_index][i] =
              CHSV((button_index - 3) * 256 / 4, 255, 255);
        } else {
          if (effect_last_pressed == button_index) {
            strips[button_index][i] = CHSV(0, 0, 255);
          } else {
            strips[button_index][i] = CHSV(0, 0, 0);
          }
        }
      } else if (button_index == 7) {
        // Heart
        strips[button_index][i] = CHSV(millis() / 10, val ? 0 : 255, 255);
      } else {
        strips[button_index][i] = CHSV(val ? 100 : 0, 0, 128);
      }
    }
  }

  for (uint8_t i = 0;
       i < ANALOG_INPUT_PINS.size() && i < ControlsIn::kAnalogInputSize; i++) {
    analog_inputs[i].Run();
    brain_out_data.analog_inputs[i] = analog_inputs[i].GetFilteredValue();
  }

  FastLED.show();
}

void debugControls() {
  for (uint8_t input_index = 0; input_index < 16; input_index++) {
    CRGB color;
    if ((input_index % 4) < 3) {
      bool button_pressed = !digitalRead(PCB_ORDER_INPUT_PINS[input_index]);
      color = button_pressed ? CRGB(0, 255, 255) : CRGB(255, 0, 0);
    } else {
      uint16_t input = analogRead(PCB_ORDER_INPUT_PINS[input_index]);
      color = CHSV(HUE_RED, 255 - input, input);
    }
    for (uint8_t light_index = 0; light_index < kMaxLedsPerStrip;
         light_index++) {
      strips[input_index][light_index] = color;
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

  brain_out.sendData();
  brain_in.receiveData();
  // for (int i = 0; i < 6; i++) {
  //   Serial.print(brain_out_data.analog_inputs[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();
}
