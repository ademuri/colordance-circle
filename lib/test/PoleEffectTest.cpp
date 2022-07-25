#include <gtest/gtest.h>

#include "PoleEffect.hpp"

class PoleEffectTest : public ::testing::Test {};

TEST_F(PoleEffectTest, LightsHaveDifferentColors) {
  Poles poles;
  PoleEffect::SetPoleEffect(poles, 0);

  CRGB first(poles[0].get_pole_lights()[0]);
  CRGB second(poles[0].get_pole_lights()[1]);

  ASSERT_NE(first.r, second.r);
  ASSERT_NE(first.g, second.g);
  ASSERT_NE(first.b, second.b);
}

TEST_F(PoleEffectTest, LightsChangeColorOverTime) {
  Poles first_poles;
  PoleEffect::SetPoleEffect(first_poles, 0);

  Poles second_poles;
  PoleEffect::SetPoleEffect(second_poles, 1000);

  CRGB first(first_poles[0].get_pole_lights()[0]);
  CRGB second(second_poles[0].get_pole_lights()[0]);

  ASSERT_NE(first.r, second.r);
  ASSERT_NE(first.g, second.g);
  ASSERT_NE(first.b, second.b);
}

TEST_F(PoleEffectTest, PolesAllHaveSameEffect) {
  Poles poles;
  PoleEffect::SetPoleEffect(poles, 0);

  auto& first_pole = poles[0];

  for (size_t i = 1; i < poles.size(); ++i) {
    auto& other_pole = poles[i];

    for (size_t n = 0; n < kLightsPerPole; ++n) {
      CRGB first_color = first_pole.get_pole_lights()[n];
      CRGB other_color = other_pole.get_pole_lights()[n];

      ASSERT_EQ(first_color.r, other_color.r);
      ASSERT_EQ(first_color.g, other_color.g);
      ASSERT_EQ(first_color.b, other_color.b);
    }
  }
}

TEST_F(PoleEffectTest, LowerEffectIsLowerPower) {
  Poles regular_poles;
  PoleEffect::SetPoleEffect(regular_poles, 0);

  Poles low_power_poles;
  PoleEffect::SetPoleLowerEffect(low_power_poles, 0);

  CRGB regular_first(regular_poles[0].get_pole_lights()[0]);
  CRGB low_power_first(low_power_poles[0].get_pole_lights()[0]);

  ASSERT_EQ(regular_first.r, 255);
  ASSERT_EQ(low_power_first.r, 65);
  ASSERT_EQ(regular_first.g, 143);
  ASSERT_EQ(low_power_first.g, 37);
  ASSERT_EQ(regular_first.b, 143);
  ASSERT_EQ(low_power_first.b, 37);
}
