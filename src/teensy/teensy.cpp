#include <ColordanceTypes.hpp>
#include <DemoController.hpp>

#include "SerialParamController.hpp"
#include "TeensyLightController.hpp"

LightController* light_controller;
Effect* effect;
// TODO: possibly replace this
SerialParamController* param_controller;

void setup() {
  Serial.begin(115200);

  param_controller = new SerialParamController();
  light_controller = new TeensyLightController();
  effect = new DemoController(light_controller->get_poles(), param_controller);
}

void loop() {
  effect->Run();
  light_controller->WriteOutLights();
  param_controller->Tick();
}
