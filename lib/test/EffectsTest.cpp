#include <gtest/gtest.h>

#include <array>
#include <cstdio>
#include <interface/InterfaceController.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Effect.hpp"
#include "FakeParamController.hpp"
#include "Pole.hpp"
#include "PolesTest.hpp"

constexpr auto effect_names =
    std::array{"HuePoles", "BackAndForth", "Sliders", "SideToSide"};
// Effect index starts at this value.
constexpr uint8_t kEffectOffset = 3;

class EffectsTest : public PolesTest {
 protected:
  FakeParamController param_controller;
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
      controller.Step();

      float instantaneous_power = 0;
      for (Pole& pole : poles) {
        float instantaneous_pole_power = 0;
        auto& grid_lights = pole.get_grid_lights();
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
    for (Pole& pole : poles) {
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
        controller.Step();
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
      controller.Step();
      time += 10;
      SetMillis(time);
    }
  }
}

TEST_F(EffectsTest, HuePolesTest) {
  uint32_t time = 0;
  SetMillis(time);
  param_controller.SetRawParam(Param::kEffect,
                               InterfaceController::kHuePolesIndex);
  controller.Step();

  // Behavior for HuePoles is that 2 lights are on on each pole
  for (int i = 0; i < 60 * 100; i++) {
    time += 10;
    SetMillis(time);
    controller.Step();
    ASSERT_EQ(GetTotalLightCount(), 12) << "time " << time;
    for (uint8_t pole = 0; pole < Pole::kNumPoles; ++pole) {
      EXPECT_EQ(GetLightCount(poles[pole]), 2)
          << "time " << time << ", pole " << pole;
    }
  }
}

TEST_F(EffectsTest, BackAndForthTest) {
  uint32_t time = 0;
  SetMillis(time);
  param_controller.SetRawParam(Param::kEffect,
                               InterfaceController::kBackAndForthIndex);
  controller.Step();

  for (uint32_t i = 0; i < 60 * 100; i++) {
    time += 10;
    SetMillis(time);
    controller.Step();
    ASSERT_EQ(GetTotalLightCount(), 8) << "time " << time;
    EXPECT_EQ(GetPolesOn(), 2) << "time " << time;
  }
}

TEST_F(EffectsTest, SlidersTest) {
  uint32_t time = 0;
  SetMillis(time);
  param_controller.SetRawParam(Param::kEffect,
                               InterfaceController::kSlidersIndex);
  controller.Step();

  // Each slider controls the pole position of 4 lights - the default is that
  // both lights are on the same pole
  for (uint8_t pole1 = 0; pole1 < Pole::kNumPoles; ++pole1) {
    param_controller.SetRawParam(
        Param::kSlider1, (uint16_t)(pole1 + 1) * 255 / Pole::kNumPoles - 2);
    for (uint8_t pole2 = 0; pole2 < Pole::kNumPoles; ++pole2) {
      param_controller.SetRawParam(
          Param::kSlider2, (uint16_t)(pole2 + 1) * 255 / Pole::kNumPoles - 2);
      for (uint32_t i = 0; i < 10 * 100; i++) {
        std::stringstream trace;
        trace << "pole1: " << std::to_string(pole1)
              << ", pole2: " << std::to_string(pole2)
              << ", time: " << std::to_string(time);
        SCOPED_TRACE(trace.str());
        time += 100;
        SetMillis(time);
        controller.Step();
        ASSERT_EQ(GetTotalLightCount(), 8);
        EXPECT_EQ(GetPolesOn(), pole1 == pole2 ? 1 : 2);
      }
    }
  }
}

TEST_F(EffectsTest, SideToSideTest) {
  uint32_t time = 0;
  SetMillis(time);
  param_controller.SetRawParam(Param::kEffect,
                               InterfaceController::kSideToSideIndex);
  controller.Step();

  // Only 1 pole on by default
  for (uint8_t poles_on = 1; poles_on <= 5; ++poles_on) {
    uint8_t slider1 = std::min(((uint16_t)(poles_on - 1) * 255) / 4 + 8, 255);
    param_controller.SetRawParam(Param::kSlider1, slider1);
    uint16_t max_lights_on = 0;
    uint8_t max_poles_on = 0;
    for (uint32_t i = 0; i < 60 * 100; i++) {
      time += 10;
      SetMillis(time);
      controller.Step();
      // Note: the lights fade in and out
      ASSERT_GE(GetTotalLightCount(), 0) << "time " << time;
      ASSERT_GE(GetPolesOn(), poles_on - 1) << "time " << time;
      max_lights_on = std::max(max_lights_on, GetTotalLightCount());
      max_poles_on = std::max(max_poles_on, GetPolesOn());
    }
    EXPECT_GE(max_lights_on, (poles_on - 1) * 4);
    EXPECT_EQ(max_poles_on, poles_on);
  }
}

class ParamTest : public EffectsTest,
                  public ::testing::WithParamInterface<
                      std::tuple<uint8_t, uint8_t, uint8_t, uint8_t, uint8_t>> {
};

const std::vector<uint8_t> kEffects = {InterfaceController::kHuePolesIndex,
                                       InterfaceController::kBackAndForthIndex,
                                       InterfaceController::kSlidersIndex,
                                       InterfaceController::kSideToSideIndex};
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
      controller.Step();
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