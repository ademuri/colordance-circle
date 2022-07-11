#define SIMULATOR

#include <cmath>
#include <interface/InterfaceController.hpp>
#include <iostream>

#include "FakeParamController.hpp"
#include "SimulatorLightController.hpp"

int main() {
  SimulatorLightController light_controller;

  auto param_controller = FakeParamController();
  auto effect = InterfaceController(light_controller.poles, param_controller);

  const std::chrono::steady_clock::time_point start_time =
      std::chrono::steady_clock::now();

  while (light_controller.Run()) {
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