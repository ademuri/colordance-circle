#include <ColordanceTypes.hpp>
#include "FastLedLightController.hpp"
#include <LightController.hpp>
#include <Effect.hpp>
#include <BrightDarkEffect.hpp>
#include <CrossEffect.hpp>
#include <ColorCycleEffect.hpp>
#include <RotateThreeEffect.hpp>
#include <MiniCircleEffect.hpp>
#include "SerialParamController.hpp"

LightController* light_controller;
Effect* effect;
SerialParamController* paramController;

void setup() {
  Serial.begin(115200);

  paramController = new SerialParamController();
  light_controller = new FastLedLightController();

  //effect = new BrightDarkEffect(light_controller->get_poles(), paramController);
  effect = new ColorCycleEffect(light_controller->get_poles(), paramController);
  //effect = new CrossEffect(light_controller->get_poles(), paramController); 
  //effect = new MiniCircleEffect(light_controller->get_poles(), paramController); 
  //effect = new RotateThreeEffect(light_controller->get_poles(), paramController); 
}

void loop() {
  effect->Run();
  light_controller->WriteOutLights();
  paramController->Tick();
}
