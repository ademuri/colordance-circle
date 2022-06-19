#include "LocalButtonController.hpp"

LocalButtonController::LocalButtonController() {
  pinMode(kNextPin, INPUT_PULLUP);
  pinMode(kRandomPin, INPUT_PULLUP);
}

bool LocalButtonController::Next() {
  if (!digitalRead(kNextPin)) {
    if (!nextOn) {
      Serial.println("next on");
      nextOn = true;
      return true;
    }
  } else {
    nextOn = false;
  }

  return false;
}

bool LocalButtonController::Random() {
  if (!digitalRead(kRandomPin)) {
    if (!randomOn) {
      Serial.println("random on");
      randomOn = true;
      return true;
    }
  } else {
    randomOn = false;
  }

  return false;
}