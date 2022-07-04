#include <Entropy.h>

#include <ColordanceTypes.hpp>
#include <memory>

#include "Controls.hpp"
#include "Effect.hpp"
#include "LocalButtonController.hpp"
#include "TeensyLightController.hpp"
#include "interface/InterfaceController.hpp"
#include "spi-param-controller.h"

TeensyLightController* light_controller;
Effect* effect;
SpiParamController* param_controller;

void setup() {
  Serial.begin(115200);

  Serial.println("Brain initializing...");
  param_controller = new SpiParamController();
  light_controller = new TeensyLightController();
  effect =
      new InterfaceController(light_controller->get_poles(), param_controller);

  // See
  // https://forum.pjrc.com/threads/61974-Teensy4-x-Entropy-library-documentation
  Entropy.Initialize();
  randomSeed(Entropy.random(0, 32767));

  Serial.println("Brain initialization complete");
}

uint32_t print_at = 0;

void loop() {
  if (millis() > print_at) {
    Serial.print("Alive: ");
    Serial.println(millis());
    print_at = millis() + 5000;
  }
  param_controller->Run();

  effect->Run();
  light_controller->WriteOutLights();

  // for (Pole* pole : light_controller->get_poles()) {
  //   for (int i = 0; i < 4; i++) {
  //     pole->ClearGridLights();
  //     for (int j = 0; j < 4; j++) {
  //       pole->SetGridLight(i, j, CHSV(0, 0, 128));
  //     }
  //     light_controller->WriteOutLights();
  //     delay(200);
  //   }
  //   pole->ClearGridLights();
  // }
  // Serial.println(param_controller->controls_in.button_mask);
}
