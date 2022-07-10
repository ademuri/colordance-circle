#include <ColordanceTypes.hpp>
#include <interface/InterfaceController.hpp>

#include "FakeEnvironmentController.hpp"
#include "FastLedLightController.hpp"
#include "Runner.hpp"
#include "SerialParamController.hpp"

namespace {

auto light_controller = FastLedLightController();
SerialParamController param_controller;
FakeEnvironmentController environment_controller;
Runner runner(light_controller.get_poles(), param_controller,
              environment_controller);

}  // namespace

void setup() { Serial.begin(115200); }

void loop() {
  runner.Step();
  light_controller.WriteOutLights();
}
