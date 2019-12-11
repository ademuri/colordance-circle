#include <ColordanceTypes.hpp>
#include "FastLedLightController.hpp"
#include <LightController.hpp>
#include <Effect.hpp>
#include <BrightDarkEffect.hpp>
#include <CrossEffect.hpp>
#include <ColorCycleEffect.hpp>
#include <RotateThreeEffect.hpp>
#include <MiniCircleEffect.hpp>

LightController* light_controller;
Effect* effect;

void setup() {
  Serial.begin(115200);

  light_controller = new FastLedLightController();
  effect = new BrightDarkEffect(light_controller->get_poles()); 
  //effect = new ColorCycleEffect(light_controller->get_poles()); 
  //effect = new CrossEffect(light_controller->get_poles()); 
  //effect = new MiniCircleEffect(light_controller->get_poles()); 
  //effect = new RotateThreeEffect(light_controller->get_poles()); 
}

void loop() {
  effect->Run();
  light_controller->WriteOutLights();

  // This gives FastLED time to do temporal dithering (smoothing out low
  // values).
  FastLED.delay(1);
}
