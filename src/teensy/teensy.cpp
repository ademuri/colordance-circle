#include <Entropy.h>
#include <Watchdog_t4.h>

#include <ColordanceTypes.hpp>
#include <memory>

#include "Buttons.hpp"
#include "Controls.hpp"
#include "Effect.hpp"
#include "FakeLogger.hpp"
#include "FakeParamController.hpp"
#include "LocalButtonController.hpp"
#include "Runner.hpp"
#include "TeensyEnvironmentController.hpp"
#include "TeensyLightController.hpp"
#include "TeensySdLogger.hpp"
#include "interface/InterfaceController.hpp"
#include "serial-param-controller.h"

namespace {

Buttons::Bank1 bank1;
Buttons::Bank2 bank2;
auto light_controller = TeensyLightController();
Buttons buttons(bank1, bank2);
TeensyEnvironmentController environment_controller;
// FakeParamController param_controller;
SerialParamController param_controller;
TeensySdLogger logger{param_controller, environment_controller};
Runner runner(light_controller.get_poles(), buttons, param_controller,
              environment_controller, logger);

uint32_t print_at = 0;

WDT_T4<WDT1> watchdog;

}  // namespace

void WatchdogCallback() {
  static constexpr uint32_t kBufferSize = 200;
  static char buffer[kBufferSize];
  Serial.println("Warning: watchdog not fed");
  int ret = snprintf(buffer, kBufferSize, "%10ul, Watchdog warning", millis());
  if (ret > 0) {
    logger.Log(buffer);
  }
}

void setup() {
  Serial.begin(115200);

  Serial.println("Brain initializing...");

  // See
  // https://forum.pjrc.com/threads/61974-Teensy4-x-Entropy-library-documentation
  Entropy.Initialize();
  randomSeed(Entropy.random(0, 32767));

  WDT_timings_t config;
  config.trigger = 5;  /* in seconds, 0->128 */
  config.timeout = 10; /* in seconds, 0->128 */
  config.callback = WatchdogCallback;
  watchdog.begin(config);

  Serial.print("Initializing logger... ");
  if (logger.Begin()) {
    Serial.println("done.");
  } else {
    Serial.println("FAILED.");
  }

  Serial.println("Brain initialization complete");
}

void loop() {
  if (millis() > print_at) {
    Serial.print("Alive: ");
    Serial.println(millis());
    print_at = millis() + 5000;
  }
  runner.Step();
  param_controller.SetRunnerState(runner.State());
  light_controller.WriteOutLights();
  watchdog.feed();
}
