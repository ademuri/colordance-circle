#include <gtest/gtest.h>

#include "Effect.hpp"
#include "FakeEnvironmentController.hpp"
#include "FakeParamController.hpp"
#include "Pole.hpp"
#include "PolesTest.hpp"
#include "Runner.hpp"

std::ostream &operator<<(std::ostream &out, RunnerState state) {
  switch (state) {
    case RunnerState::LOW_POWER:
      out << "LOW_POWER";
      break;

    case RunnerState::IDLE:
      out << "IDLE";
      break;

    case RunnerState::NORMAL:
      out << "NORMAL";
      break;
  }
  return out;
}

class RunnerTest : public PolesTest {
 protected:
  FakeParamController param_controller{};
  FakeEnvironmentController environment_controller{};
  Runner runner{poles, param_controller, environment_controller};

  void SetUp() override {
    SetMillis(0);
    environment_controller.SetBatteryMillivolts(1210);
  }
};

TEST_F(RunnerTest, ChecksBatteryVoltage) {
  environment_controller.SetBatteryMillivolts(1200);
  runner.Step();
  EXPECT_EQ(runner.State(), RunnerState::NORMAL);

  AdvanceMillis(100);
  runner.Step();
  EXPECT_LE(4, GetPolesOn());
  EXPECT_EQ(runner.State(), RunnerState::NORMAL);

  AdvanceMillis(100);
  environment_controller.SetBatteryMillivolts(1100);
  runner.Step();
  EXPECT_EQ(2, GetPolesOn());
  EXPECT_EQ(runner.State(), RunnerState::LOW_POWER);

  AdvanceMillis(100);
  environment_controller.SetBatteryMillivolts(1230);
  runner.Step();
  EXPECT_LE(4, GetPolesOn());
  EXPECT_EQ(runner.State(), RunnerState::NORMAL);
}

TEST_F(RunnerTest, BatteryVoltageCheckHasHysteresis) {
  environment_controller.SetBatteryMillivolts(1180);
  runner.Step();

  AdvanceMillis(100);
  runner.Step();
  EXPECT_LE(4, GetPolesOn());

  AdvanceMillis(100);
  environment_controller.SetBatteryMillivolts(1160);
  runner.Step();
  EXPECT_EQ(2, GetPolesOn());
  EXPECT_EQ(runner.State(), RunnerState::LOW_POWER);

  AdvanceMillis(100);
  environment_controller.SetBatteryMillivolts(1190);
  runner.Step();
  EXPECT_EQ(2, GetPolesOn());
  EXPECT_EQ(runner.State(), RunnerState::LOW_POWER);

  AdvanceMillis(100);
  environment_controller.SetBatteryMillivolts(1210);
  runner.Step();
  EXPECT_LE(4, GetPolesOn());
  EXPECT_EQ(runner.State(), RunnerState::NORMAL);

  AdvanceMillis(100);
  environment_controller.SetBatteryMillivolts(1180);
  runner.Step();
  EXPECT_LE(4, GetPolesOn());
  EXPECT_EQ(runner.State(), RunnerState::NORMAL);
}

TEST_F(RunnerTest, GoesToIdleMode) {
  param_controller.SetRawParam(Param::kEffect,
                               InterfaceController::kSlidersIndex);
  param_controller.SetRawParam(Param::kSlider1, 0);
  param_controller.SetRawParam(Param::kSlider2, 255);
  runner.Step();
  ASSERT_EQ(runner.State(), RunnerState::NORMAL);

  uint32_t millis;
  for (millis = 1000; millis <= Runner::kIdleTimeout; millis += 1000) {
    SetMillis(millis);
    runner.Step();
    ASSERT_EQ(runner.State(), RunnerState::NORMAL) << "millis: " << millis;
    ASSERT_EQ(GetTotalLightCount(), 8) << "millis: " << millis;
  }

  for (; millis <= Runner::kIdleTimeout * 3; millis += 1000) {
    SetMillis(millis);
    runner.Step();
    ASSERT_EQ(runner.State(), RunnerState::IDLE) << "millis: " << millis;
    ASSERT_EQ(GetTotalLightCount(), 4) << "millis: " << millis;
  }

  param_controller.SetRawParam(Param::kSlider1, 1);
  runner.Step();
  runner.Step();
  EXPECT_EQ(runner.State(), RunnerState::NORMAL);
}

TEST_F(RunnerTest, LowBatteryTakesPreferenceOverIdleMode) {
  param_controller.SetRawParam(Param::kSlider1, 1);
  runner.Step();
  ASSERT_EQ(runner.State(), RunnerState::NORMAL);

  uint32_t millis;
  for (millis = 1000; millis <= Runner::kIdleTimeout + 1000; millis += 1000) {
    SetMillis(millis);
    runner.Step();
  }

  ASSERT_EQ(runner.State(), RunnerState::IDLE);
  ASSERT_EQ(GetTotalLightCount(), 4);

  environment_controller.SetBatteryMillivolts(1160);
  runner.Step();
  EXPECT_EQ(runner.State(), RunnerState::LOW_POWER);
  ASSERT_EQ(GetTotalLightCount(), 2);

  param_controller.SetRawParam(Param::kSlider1, 2);
  runner.Step();
  runner.Step();
  EXPECT_EQ(runner.State(), RunnerState::LOW_POWER);
  ASSERT_EQ(GetTotalLightCount(), 2);

  environment_controller.SetBatteryMillivolts(1230);
  runner.Step();
  EXPECT_EQ(runner.State(), RunnerState::NORMAL);
}
