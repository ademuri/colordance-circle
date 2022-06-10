#include <Entropy.h>

#include <ColordanceTypes.hpp>
#include <memory>

#include "Controls.hpp"
#include "Effect.hpp"
#include "LocalButtonController.hpp"
#include "TeensyLightController.hpp"
#include "interface/InterfaceController.hpp"
#include "spi-param-controller.h"

LightController* light_controller;
Effect* effect;
SpiParamController* param_controller;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Brain initializing...");
  param_controller = new SpiParamController();
  light_controller = new TeensyLightController();
  effect = new InterfaceController(light_controller->get_poles(),
                                   param_controller);

  // See
  // https://forum.pjrc.com/threads/61974-Teensy4-x-Entropy-library-documentation
  Entropy.Initialize();
  randomSeed(Entropy.random(0, 32767));

  Serial.println("Brain initialization complete");
}

void loop() {
  param_controller->Run();
  effect->Run();
  light_controller->WriteOutLights();
  Serial.println(param_controller->controls_in.button_mask);
}
