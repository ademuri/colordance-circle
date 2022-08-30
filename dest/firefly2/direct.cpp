#include <ColordanceTypes.hpp>
#include <interface/InterfaceController.hpp>

#include "Buttons.hpp"
#include "DesktopSerialParamController.hpp"
#include "FakeEnvironmentController.hpp"
#include "FakeLogger.hpp"
#include "FastLedLightController.hpp"
#include "Runner.hpp"

namespace {

Buttons::Bank1 bank1;
Buttons::Bank2 bank2;
auto light_controller = FastLedLightController();
Buttons buttons(bank1, bank2);
DesktopSerialParamController param_controller;
FakeEnvironmentController environment_controller;
FakeLogger logger{param_controller, environment_controller};
Runner runner(light_controller.get_poles(), buttons, param_controller,
              environment_controller, logger);

}  // namespace

void setup() { Serial.begin(115200); }

void loop() {
  runner.Step();
  light_controller.WriteOutLights();
}
