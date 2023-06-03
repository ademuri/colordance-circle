#include <EasyTransfer.h>
#include <FastLED.h>
#include <Watchdog_t4.h>
#include <debounce-filter.h>
#include <median-filter.h>
#include <quantization-filter.h>

#include <vector>

#include "Controls.hpp"
#include "IdleEffect.hpp"
#include "InterfaceParamController.hpp"
#include "LowPowerEffect.hpp"
#include "Pole.hpp"
#include "TestLightsEffect.hpp"
#include "interface/InterfaceController.hpp"

// Behavior flags
constexpr bool kDebugFlashAtBoot = true;

enum class RunType {
  NORMAL,
  DEBUG_LIGHTS,
  DEBUG_CONTROLS,
};

const constexpr RunType run_mode = RunType::NORMAL;

// Buttons
const int kEffect1 = 2;
const int kEffect2 = 3;
const int kEffect3 = 10;
const int kEffect4 = 11;
const int kEffect5 = 5;
const int kEffect6 = 4;
const int kEffect7 = 30;
const int kOption1 = 31;
const int kOption2 = 33;
const int kShift = 7;
const int kBeat = 35;
const int kPause = 36;
const int kButton13 = 37;
const int kButton14 = 34;

const std::vector<int> BUTTON_PINS = {
    kEffect1, kEffect2, kEffect3, kEffect4, kEffect5, kEffect6,  kEffect7,
    kOption1, kOption2, kShift,   kBeat,    kPause,   kButton13, kButton14,
};

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
    kAnalog1, kAnalog2, kAnalog3, kAnalog4, kAnalog5, kAnalog7, kAnalog8,
};

const std::vector<int> PCB_ORDER_INPUT_PINS = {
    kEffect1, kEffect5, kOption2, kAnalog1, kEffect2, kEffect6,
    kShift,   kAnalog2, kEffect3, kEffect7, kBeat,    kAnalog3,
    kEffect4, kOption1, kPause,   kAnalog4,
};

constexpr int kLed = 13;

std::vector<QuantizationFilter<uint16_t>> analog_inputs;
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
The # on the right is the index in PCB_ORDER_INPUT_PINS starting at 1
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

Buttons::Bank1 bank1;
Buttons::Bank2 bank2;
Poles poles;
Buttons buttons(bank1, bank2);
InterfaceParamController param_controller{brain_out_data};
InterfaceController interface_controller{poles, buttons, param_controller};
IdleEffect idle_effect{poles, buttons, param_controller};
LowPowerEffect low_power_effect{poles, buttons, param_controller};
TestLightsEffect test_lights_effect{poles, buttons, param_controller};

uint8_t effect_last_pressed = 0;

WDT_T4<WDT1> watchdog;

void WatchdogCallback() { Serial.println("Warning: watchdog not fed"); }

void setup() {
  pinMode(kLed, OUTPUT);
  digitalWrite(kLed, HIGH);

  Serial.begin(115200);
  // while(!Serial) {}
  Serial.println("Booting...");
  pinMode(13, OUTPUT);

  for (auto button_pin : BUTTON_PINS) {
    pinMode(button_pin, INPUT_PULLUP);
  }

  for (auto analog_pin : ANALOG_INPUT_PINS) {
    pinMode(analog_pin, INPUT);
    analog_inputs.push_back(QuantizationFilter<uint16_t>(
        filter_functions::ForAnalogReadDynamic(analog_pin), /*bucket_size=*/4,
        /*hysteresis=*/4));
    prev_analog_inputs.push_back(analogRead(analog_pin));
  }

  analogReadResolution(10);

  Serial.println("Pins initialized");

  FastLED.addLeds<kStripsPerBank1, WS2812, kBank1FirstPin, GRB>(
      bank1.data(), kMaxLedsPerStrip);
  FastLED.addLeds<kStripsPerBank2, WS2812, kBank2FirstPin, GRB>(
      bank2.data(), kMaxLedsPerStrip);
  FastLED.showColor(CRGB::Black);
  // colordance-brain power supply can source 1A at 5V. Leave lots of margin for
  // its load (the RS422 is power-hungry).
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
  FastLED.setMaxRefreshRate(50);

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

  // Sets speed for serial port and brain communication
  // decrease this if flaky
  Serial7.begin(kSerialBaud);
  brain_out.begin(details(brain_out_data), &Serial7);
  brain_in.begin(details(brain_in_data), &Serial7);

  digitalWrite(kLed, LOW);

  WDT_timings_t config;
  config.trigger = 5;  /* in seconds, 0->128 */
  config.timeout = 10; /* in seconds, 0->128 */
  config.callback = WatchdogCallback;
  watchdog.begin(config);
}

void readControls() {
  brain_out_data.alive = (millis() / 500) % 2;
  brain_out_data.button_mask = 0;
  bool effect_pressed = false;

  for (uint8_t button_index = 0; button_index < BUTTON_PINS.size();
       button_index++) {
    uint16_t val = !digitalRead(BUTTON_PINS[button_index]) << button_index;
    if (val && !effect_pressed) {
      effect_last_pressed = button_index;
      effect_pressed = true;
    }
    brain_out_data.button_mask |= val;
  }

  for (uint8_t i = 0;
       i < ANALOG_INPUT_PINS.size() && i < ControlsIn::kAnalogInputSize; i++) {
    analog_inputs[i].Run();
    brain_out_data.analog_inputs[i] = analog_inputs[i].GetFilteredValue() / 4;
  }
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
      // TODO: write to the buttons
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
      break;

    case RunType::DEBUG_CONTROLS:
      debugControls();
      break;

    case RunType::DEBUG_LIGHTS:
      debugLights();
      break;
  }

  // Wait to receive data before sending, so that we don't interrupt the brain
  // while its writing out LEDs.
  if (brain_in.receiveData()) {
    digitalWrite(kLed, (millis() / 500) % 2);
    brain_out.sendData();

    // Run the main effect here on the interface - we keep this in sync with the
    // one on the brain, so that this one can output to the buttons.
    switch (brain_in_data.runner_state) {
      case RunnerState::NORMAL:
        interface_controller.Step();
        param_controller.Step();
        break;

      case RunnerState::IDLE:
        idle_effect.Step();
        break;

      case RunnerState::LOW_POWER:
        low_power_effect.Step();
        break;

      case RunnerState::TEST_LIGHTS:
        test_lights_effect.Step();
        break;
    }
    FastLED.show();
  }
  digitalWrite(13, brain_in_data.alive);
  watchdog.feed();
  // for (int i = 0; i < 6; i++) {
  //   Serial.print(brain_out_data.analog_inputs[i] / 4);
  //   Serial.print(" ");
  // }
  // Serial.println();
}
