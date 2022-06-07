#include <interface/InterfaceController.hpp>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>

#include "DummyParamController.hpp"
#include "Effect.hpp"
#include "Pole.hpp"
#include "gtest/gtest.h"

std::vector<Pole*> CreatePoles() {
  std::vector<Pole*> poles;
  for (int i = 0; i < 6; i++) {
    poles.push_back(new Pole());
  }
  return poles;
}

struct NamedEffect {
  std::string name;
  Effect * effect;
};

std::vector<NamedEffect> CreateEffects(std::vector<Pole*> poles) {
  DummyParamController* paramController = new DummyParamController();
  return {
      {"Interface", new InterfaceController(poles, paramController)},
  };
}

TEST(Effects, stable) {
  auto const effects = CreateEffects(CreatePoles());

  for (auto const & element : effects) {
    std::cout << "Testing effect '" << element.name << "' for stability...\n";

    for (uint32_t time = 0; time < 12 * 60 * 60 * 1000; time += 10) {
      element.effect->Run();
      SetMillis(time);
    }
  }
}

TEST(Effects, power_consumption) {
  const uint32_t kRunTimeMs = 2 * 60 * 1000;
  const uint32_t kStepMs = 10;

  // Approximate power consumption, in watts (not yet verified with hardware)
  const float kRedPower = 2.0;
  const float kGreenPower = 2.7;
  const float kBluePower = 2.7;

  std::vector<Pole*> poles = CreatePoles();
  auto const effects = CreateEffects(poles);

  for (auto const & element : effects) {
    float max_power = 0;
    float power_sum = 0;
    for (uint32_t time = 0; time < kRunTimeMs; time += kStepMs) {
      SetMillis(time);
      element.effect->Run();

      float instantaneous_power = 0;
      for (Pole* pole : poles) {
        for (uint row = 0; row < pole->get_grid_lights().size(); row++) {
          for (uint col = 0; col < pole->get_grid_lights()[row].size(); col++) {
            CRGB rgb = pole->get_grid_lights()[row][col];
            float light_power =
                (rgb.r * kRedPower + rgb.g * kGreenPower + rgb.b * kBluePower) /
                255;
            power_sum += light_power;
            instantaneous_power += light_power;
          }
        }
      }
      if (instantaneous_power > max_power) {
        max_power = instantaneous_power;
      }
    }

    float average_power = power_sum / (kRunTimeMs / kStepMs);
    printf("Power report for '%s':\n", element.name.c_str());
    printf("  Average power:  %5.1f W\n", average_power);
    printf("  Max power:      %5.1f W\n\n", max_power);

    // TODO: decide on appropriate values for these
    EXPECT_LT(average_power, 60.0) << element.name;
    EXPECT_LT(max_power, 120.0) << element.name;

    // Clear all lights
    for (Pole* pole : poles) {
      for (uint row = 0; row < pole->get_grid_lights().size(); row++) {
        for (uint col = 0; col < pole->get_grid_lights()[row].size(); col++) {
          pole->SetGridLight(row, col, CRGB(0, 0, 0));
        }
      }
    }
  }
}
