#include <ColordanceTypes.hpp>
#include <interface/InterfaceController.hpp>

#include "FastLedLightController.hpp"
#include "SerialParamController.hpp"

LightController* light_controller;
Effect* effect;
SerialParamController* paramController;

void setup() {
  Serial.begin(115200);

  paramController = new SerialParamController();
  light_controller = new FastLedLightController();

  effect = new InterfaceController(
      light_controller->get_poles(),
      std::unique_ptr<SerialParamController>(paramController));
}

void loop() {
  effect->Run();
  light_controller->WriteOutLights();
  paramController->Tick();
}
