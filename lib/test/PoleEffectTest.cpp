#include <gtest/gtest.h>

#include "PoleEffect.hpp"

class PoleEffectTest : public ::testing::Test {};

TEST_F(PoleEffectTest, LightsHaveDifferentColors) {
  Poles poles;
  SetPoleEffect(poles, 0);

  CRGB first(poles[0].get_pole_lights()[0]);
  CRGB second(poles[0].get_pole_lights()[1]);

  EXPECT_NE(first.r, second.r);
  EXPECT_NE(first.g, second.g);
  EXPECT_NE(first.b, second.b);
}

TEST_F(PoleEffectTest, LightsChangeColorOverTime) {
  Poles first_poles;
  SetPoleEffect(first_poles, 0);

  Poles second_poles;
  SetPoleEffect(second_poles, 1000);

  CRGB first(first_poles[0].get_pole_lights()[0]);
  CRGB second(second_poles[0].get_pole_lights()[0]);

  EXPECT_NE(first.r, second.r);
  EXPECT_NE(first.g, second.g);
  EXPECT_NE(first.b, second.b);
}

TEST_F(PoleEffectTest, PolesAllHaveSameEffect) {
  Poles poles;
  SetPoleEffect(poles, 0);

  auto& first_pole = poles[0];

  for (size_t i = 1; i < poles.size(); ++i) {
    auto& other_pole = poles[i];

    for (size_t n = 0; n < kLightsPerPole; ++n) {
      CRGB first_color = first_pole.get_pole_lights()[n];
      CRGB other_color = other_pole.get_pole_lights()[n];

      EXPECT_EQ(first_color.r, other_color.r);
      EXPECT_EQ(first_color.g, other_color.g);
      EXPECT_EQ(first_color.b, other_color.b);
    }
  }
}

TEST_F(PoleEffectTest, LowerEffectIsLowerPower) {
  Poles regular_poles;
  SetPoleEffect(regular_poles, 0);

  Poles low_power_poles;
  SetPoleLowerEffect(low_power_poles, 0);

  CRGB regular_first(regular_poles[0].get_pole_lights()[0]);
  CRGB low_power_first(low_power_poles[0].get_pole_lights()[0]);
  CRGB low_power_lower(
      low_power_poles[0].get_pole_lights()[kLightsPerPole * 0.25]);

  EXPECT_EQ(regular_first.r, 255);
  EXPECT_EQ(low_power_first.r, 0);
  EXPECT_EQ(low_power_lower.r, 5);
  EXPECT_EQ(regular_first.g, 143);
  EXPECT_EQ(low_power_first.g, 0);
  EXPECT_EQ(low_power_lower.g, 4);
  EXPECT_EQ(regular_first.b, 143);
  EXPECT_EQ(low_power_first.b, 0);
  EXPECT_EQ(low_power_lower.b, 6);
}
