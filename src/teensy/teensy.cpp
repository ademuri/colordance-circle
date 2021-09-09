#include <ColordanceTypes.hpp>
#include <DemoController.hpp>

#include "LocalButtonController.hpp"
#include "TeensyLightController.hpp"

LightController* light_controller;
Effect* effect;
// TODO: possibly replace this
LocalButtonController* param_controller;

void setup() {
  Serial.begin(115200);

  param_controller = new LocalButtonController();
  light_controller = new TeensyLightController();
  effect = new DemoController(light_controller->get_poles(), param_controller);
}

void loop() {
  effect->Run();
  light_controller->WriteOutLights();
  //param_controller->Tick();
}
