#include <Arduino.h>

#include <ColordanceTypes.hpp>

#include "Buttons.hpp"
#include "Effect.hpp"
#include "FakeParamController.hpp"
#include "MiniLightController.hpp"
#include "interface/InterfaceController.hpp"

Buttons::Bank1 bank1;
Buttons::Bank2 bank2;
Buttons buttons{bank1, bank2};

MiniLightController light_controller;
FakeParamController param_controller;

InterfaceController interface_controller{light_controller.get_poles(), buttons,
                                         param_controller};

void setup() { light_controller.Begin(); }

void loop() {
  interface_controller.Step();
  light_controller.WriteOutLights();
}
