#include <Entropy.h>

#include <ColordanceTypes.hpp>
#include <memory>

#include "Controls.hpp"
#include "Effect.hpp"
#include "FakeParamController.hpp"
#include "LocalButtonController.hpp"
#include "ModelLightController.hpp"
#include "Runner.hpp"
#include "TeensyEnvironmentController.hpp"
#include "TeensySdLogger.hpp"
#include "interface/InterfaceController.hpp"
#include "serial-param-controller.h"

namespace {

auto light_controller = ModelLightController();
TeensyEnvironmentController environment_controller;
SerialParamController param_controller;
TeensySdLogger* logger;
Runner* runner;

uint32_t print_at = 0;

}  // namespace

void setup() {
  Serial.begin(115200);

  Serial.println("Brain initializing...");

  logger = new TeensySdLogger(param_controller, environment_controller);
  runner = new Runner(light_controller.get_poles(), param_controller,
                      environment_controller, *logger);

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
  runner->Step();
  light_controller.WriteOutLights();
}
