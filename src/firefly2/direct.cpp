#include <ColordanceTypes.hpp>
#include <interface/InterfaceController.hpp>

#include "FastLedLightController.hpp"
#include "SerialParamController.hpp"
#include "Runner.hpp"

namespace {

auto light_controller = FastLedLightController();
SerialParamController param_controller;
Runner runner(light_controller.get_poles(), &param_controller);

}  // namespace

void setup() {
  Serial.begin(115200);
}

void loop() {
  runner.Run();
  light_controller.WriteOutLights();
}
