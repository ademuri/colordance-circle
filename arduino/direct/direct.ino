#include <ColordanceTypes.hpp>

// #include <BrightDarkEffect.hpp>
// #include <ColorCycleEffect.hpp>
// #include <ColorTestEffect.hpp>
#include <ControlledEffect.hpp>
// #include <CrossEffect.hpp>
// #include <Effect.hpp>
// #include <FlashEffect.hpp>
// #include <LightController.hpp>
// #include <MiniCircleEffect.hpp>
// #include <RotateThreeEffect.hpp>
#include "FastLedLightController.hpp"
#include "SerialParamController.hpp"

LightController* light_controller;
Effect* effect;
SerialParamController* paramController;

void setup() {
  Serial.begin(115200);

  paramController = new SerialParamController();
  light_controller = new FastLedLightController();

  // effect = new BrightDarkEffect(light_controller->get_poles(),paramController); 
  // effect = new ColorCycleEffect(light_controller->get_poles(), paramController); 
  // effect = new CrossEffect(light_controller->get_poles(), paramController);
  // effect = new FlashEffect(light_controller->get_poles(), paramController);
  // effect = new MiniCircleEffect(light_controller->get_poles(), paramController); 
  // effect = new RotateThreeEffect(light_controller->get_poles(), paramController);
  effect = new ControlledEffect(light_controller->get_poles(), paramController);
  // effect = new ColorTestEffect(light_controller->get_poles(), paramController);
}

void loop() {
  effect->Run();
  light_controller->WriteOutLights();
  paramController->Tick();
}
