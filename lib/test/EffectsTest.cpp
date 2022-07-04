#include <array>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <interface/InterfaceController.hpp>

#include "DummyParamController.hpp"
#include "Effect.hpp"
#include "Pole.hpp"
#include "gtest/gtest.h"

constexpr auto effect_names = std::array{"HuePoles", "BackAndForth",
                                               "Sliders", "SideToSide"};
// Effect index starts at this value.
constexpr uint8_t kEffectOffset = 3;

class EffectsTest : public ::testing::Test {
  protected:
  Poles poles{};
  DummyParamController param_controller;
  InterfaceController controller{poles, std::addressof(param_controller)};
};

TEST_F(EffectsTest, power_consumption) {
  constexpr uint32_t kStepMs = 10;
  constexpr uint32_t kRunCycles = 2 * 60 * 1000 / kStepMs;

  // Approximate power consumption, in watts (not yet verified with hardware)
  constexpr float kRedPower = 2.0;
  constexpr float kGreenPower = 2.7;
  constexpr float kBluePower = 2.7;

  uint32_t time = 0;
  for (uint8_t effect_index = 0; effect_index < effect_names.size();
       effect_index++) {
    const std::string_view effect_name = effect_names[effect_index];
    float max_power = 0;
    float max_pole_power = 0;
    float power_sum = 0;
    for (uint32_t cycle = 0; cycle < kRunCycles; cycle++) {
      time += kStepMs;
      SetMillis(time);
      param_controller.SetRawParam(Param::kEffect,
                                    effect_index + kEffectOffset);
      controller.Run();

      float instantaneous_power = 0;
      for (Pole & pole : poles) {
        float instantaneous_pole_power = 0;
        auto & grid_lights = pole.get_grid_lights();
        for (uint row = 0; row < grid_lights.size(); row++) {
          for (uint col = 0; col < grid_lights[row].size(); col++) {
            CRGB rgb = grid_lights[row][col];
            float light_power =
                (rgb.r * kRedPower + rgb.g * kGreenPower + rgb.b * kBluePower) /
                255;
            power_sum += light_power;
            instantaneous_power += light_power;
            instantaneous_pole_power += light_power;
          }
        }
        max_pole_power = std::max(max_pole_power, instantaneous_pole_power);
      }
      max_power = std::max(instantaneous_power, max_power);
    }

    float average_power = power_sum / kRunCycles;
    std::cout << "Power report for " << effect_name << ":\n";
    printf("  Average power:    %5.1f W\n", average_power);
    printf("  Peak power:       %5.1f W\n", max_power);
    printf("  Peak pole power:  %5.1f W\n\n", max_pole_power);

    // 4A average power limit
    EXPECT_LT(average_power, 48.0) << effect_name;
    // 6A max peak power
    EXPECT_LT(max_power, 72.0) << effect_name;
    // 3A max per pole
    EXPECT_LT(max_pole_power, 36.0) << effect_name;

    // Clear all lights
    for (Pole & pole : poles) {
      pole.ClearGridLights();
    }
  }
}

TEST_F(EffectsTest, InvalidParams) {
  constexpr uint32_t kStepMs = 10;
  // 15 seconds should be enough to detect badness
  constexpr uint32_t kCycles = 15 * 1000 / kStepMs;

  constexpr auto kParams = std::array{
      Param::kBeat,    Param::kLoopShift, Param::kShift,   Param::kPause,
      Param::kEffect,  Param::kOption1,   Param::kOption1, Param::kOption2,
      Param::kSlider1, Param::kSlider2};

  uint32_t time = 0;

  for (Param param : kParams) {
    std::cout << "Testing param " << static_cast<uint32_t>(param) << "\n";
    for (uint16_t value = 0; value < 256; value++) {
      param_controller.SetRawParam(param, value);
      for (uint32_t cycle = 0; cycle < kCycles; cycle++) {
        controller.Run();
        time += kStepMs;
        SetMillis(time);
      }
    }
  }
}

TEST_F(EffectsTest, StableForAllEffects) {
  uint32_t time = 0;
  for (uint8_t effect_index = 0; effect_index < effect_names.size();
       effect_index++) {
    std::cout << "Testing effect '" << effect_names[effect_index]
              << "' for stability...\n";
    param_controller.SetRawParam(Param::kEffect, effect_index + kEffectOffset);
    for (uint32_t cycle = 0; cycle < 12 * 60 * 60 * 100; cycle++) {
      controller.Run();
      time += 10;
      SetMillis(time);
    }
  }
}

class ParamTest : public EffectsTest,
                  public ::testing::WithParamInterface<
                      std::tuple<uint8_t, uint8_t, uint8_t, uint8_t, uint8_t>> {
};

const std::vector<uint8_t> kEffects = {3, 4, 5, 6};
const std::vector<uint8_t> kOptions = {0, 1};
const std::vector<uint8_t> kSliders = {0, 1, 64, 128, 192, 254, 255};

TEST_P(ParamTest, StableForAllParams) {
  uint32_t time = 0;
  for (uint8_t effect_index = 0; effect_index < effect_names.size();
       effect_index++) {
    param_controller.SetRawParam(Param::kEffect, std::get<0>(GetParam()));
    param_controller.SetRawParam(Param::kOption1, std::get<1>(GetParam()));
    param_controller.SetRawParam(Param::kOption2, std::get<2>(GetParam()));
    param_controller.SetRawParam(Param::kSlider1, std::get<3>(GetParam()));
    param_controller.SetRawParam(Param::kSlider2, std::get<4>(GetParam()));
    for (uint32_t cycle = 0; cycle < 10 * 60 * 100; cycle++) {
      controller.Run();
      time += 10;
      SetMillis(time);
    }
  }
}

INSTANTIATE_TEST_CASE_P(ParamTests, ParamTest,
                        ::testing::Combine(::testing::ValuesIn(kEffects),
                                           ::testing::ValuesIn(kOptions),
                                           ::testing::ValuesIn(kOptions),
                                           ::testing::ValuesIn(kSliders),
                                           ::testing::ValuesIn(kSliders)));