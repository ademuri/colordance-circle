#include <Entropy.h>

#include <ColordanceTypes.hpp>
#include <memory>

#include "Controls.hpp"
#include "Effect.hpp"
#include "LocalButtonController.hpp"
#include "Runner.hpp"
#include "TeensyEnvironmentController.hpp"
#include "TeensyLightController.hpp"
#include "TeensySdLogger.hpp"
#include "interface/InterfaceController.hpp"
#include "serial-param-controller.h"

namespace {

auto light_controller = TeensyLightController();
TeensyEnvironmentController environment_controller;
SerialParamController param_controller;
TeensySdLogger logger{param_controller, environment_controller};
Runner runner(light_controller.get_poles(), param_controller,
              environment_controller, logger);

uint32_t print_at = 0;

}  // namespace

void setup() {
  Serial.begin(115200);

  Serial.println("Brain initializing...");

  // See
  // https://forum.pjrc.com/threads/61974-Teensy4-x-Entropy-library-documentation
  Entropy.Initialize();
  randomSeed(Entropy.random(0, 32767));

  Serial.println("Brain initialization complete");
}

void loop() {
  // if (millis() > print_at) {
  //   Serial.print("Alive: ");
  //   Serial.println(millis());
  //   print_at = millis() + 5000;
  // }
  runner.Step();
  light_controller.WriteOutLights();
}
