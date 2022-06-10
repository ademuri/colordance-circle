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
std::unique_ptr<SpiParamController> param_controller;

void setup() {
  Serial.begin(115200);

  param_controller = std::make_unique<SpiParamController>();
  light_controller = new TeensyLightController();
  effect = new InterfaceController(light_controller->get_poles(),
                                   std::move(param_controller));

  // See
  // https://forum.pjrc.com/threads/61974-Teensy4-x-Entropy-library-documentation
  Entropy.Initialize();
  randomSeed(Entropy.random(0, 32767));
}

void loop() {
  param_controller->Run();
  effect->Run();
  light_controller->WriteOutLights();
}
