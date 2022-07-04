#include <ColordanceTypes.hpp>
#include <interface/InterfaceController.hpp>

#include "FastLedLightController.hpp"
#include "SerialParamController.hpp"

auto light_controller = FastLedLightController();
Effect* effect;
SerialParamController* paramController;

void setup() {
  Serial.begin(115200);

  paramController = new SerialParamController();

  effect = new InterfaceController(
      light_controller.get_poles(),
      paramController);
}

void loop() {
  effect->Run();
  light_controller.WriteOutLights();
  paramController->Tick();
}
