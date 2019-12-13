#include "SerialParamController.hpp"

SerialParamController::SerialParamController() {}

void SerialParamController::Tick() {
  if (Serial.available() > 0) {
    String in = Serial.readStringUntil('\n');
    switch (in.charAt(0)) {
      case 'm':
        mode = in.substring(2).toInt();
        Serial.print("m: ");
        Serial.println(mode);
        break;

      case 'e':
        effect_index = in.substring(2).toInt();
        Serial.print("e: ");
        Serial.println(effect_index);
        break;

      default:
        Serial.print("Invalid: ");
        Serial.println(in);
        break;
    }
  }
}

uint8_t SerialParamController::GetMode() { return mode; }

uint8_t SerialParamController::GetEffectIndex() { return effect_index; }
