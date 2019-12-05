#include <ColordanceTypes.hpp>
#include "FastLedLightController.hpp"
#include <LightController.hpp>
#include <Effect.hpp>
#include <ColorCycleEffect.hpp>
#include <RotateThreeEffect.hpp>

LightController* light_controller;
Effect* effect;

void setup() {
  Serial.begin(115200);

  light_controller = new FastLedLightController();
  effect = new RotateThreeEffect(light_controller->get_poles()); 
}

void loop() {
  effect->Run();
  light_controller->WriteOutLights();
}