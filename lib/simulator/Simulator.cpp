#define SIMULATOR

#include <cmath>
#include <iostream>

#include "Buttons.hpp"
#include "FakeParamController.hpp"
#include "SimulatorLightController.hpp"
#include "StdinParamController.hpp"
#include "TestLightsEffect.hpp"
#include "interface/InterfaceController.hpp"

int main() {
  SimulatorLightController light_controller;

  Buttons::Bank1 bank1;
  Buttons::Bank2 bank2;
  Buttons buttons{bank1, bank2};
  auto param_controller = StdinParamController();
  auto effect =
      InterfaceController(light_controller.poles, buttons, param_controller);

  const std::chrono::steady_clock::time_point start_time =
      std::chrono::steady_clock::now();

  while (light_controller.Run()) {
    param_controller.Step();
    effect.Step();
    light_controller.WriteOutLights();
    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();
    SetMillis(std::chrono::duration_cast<std::chrono::milliseconds>(end_time -
                                                                    start_time)
                  .count());
  }
  return 0;
}