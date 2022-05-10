#include <FastLED.h>
#include <SPISlave_T4.h>

#include <vector>

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

const std::vector<int> buttons = {
    kButton1, kButton2, kButton3,  kButton4,  kButton5,  kButton6,  kButton7,
    kButton8, kButton9, kButton10, kButton11, kButton12, kButton13, kButton14,
};

// Analog inputs
const int kAnalog1 = 38;
const int kAnalog2 = 30;
const int kAnalog3 = 40;
const int kAnalog4 = 41;
const int kAnalog5 = 26;
const int kAnalog6 = 21;
const int kAnalog7 = 39;
const int kAnalog8 = 27;

const std::vector<int> analog_inputs = {
    kAnalog1, kAnalog2, kAnalog3, kAnalog4,
    kAnalog5, kAnalog6, kAnalog7, kAnalog8,
};

// FastLED Teensy 4.1 parallel output pin strings:
// [1, 0, 24, 25, 19, 18, 14, 15, 17, 16, 22, 23,] 20, 21, 26, 27
// 10, 12, 11, 13, [6, 9, 32, 8, 7]
// 37, 36, 35, 34, 39, 38, 28, 31, 30

const int kMaxLedsPerStrip = 15;
const int kStripsPerBank1 = 12;
const int kStripsPerBank2 = 4;

const int kBank1FirstPin = 1;
const int kBank2FirstPin = 6;

CRGB bank1[kMaxLedsPerStrip * kStripsPerBank1];
CRGB bank2[kMaxLedsPerStrip * kStripsPerBank2];

SPISlave_T4<&SPI, SPI_8_BITS> spi_out;

void setup() {
  Serial.begin(115200);
  Serial.println("Booting...");

  for (auto button_pin : buttons) {
    pinMode(button_pin, INPUT_PULLUP);
  }

  for (auto analog_pin : analog_inputs) {
    pinMode(analog_pin, INPUT);
  }

  FastLED.addLeds<kStripsPerBank1, WS2812, kBank1FirstPin, RGB>(
      bank1, kStripsPerBank1);
  FastLED.addLeds<kStripsPerBank2, WS2812, kBank2FirstPin, RGB>(
      bank2, kStripsPerBank2);

  Serial.println("Local assets initialized. Beginning SPI communication...");

  spi_out.begin();
  spi_out.onReceive(onReceive);

  Serial.println("SPI started successfully");
}

void loop() {
  // TODO: read sensors
  // TODO: output LEDs
}

void onReceive() {
  // TODO: send sensor data
  // Note: SPI is full-duplex. The controller (colordance-brain) writes out one byte at a time, and the peripheral (us) simultaneously writes data back.
  while (spi_out.active()) {
    if (spi_out.available()) {
      spi_out.pushr(0);
      Serial.print(spi_out.popr());
    }
  }
  Serial.println();
}
