#include <gtest/gtest.h>

#include "Buttons.hpp"
#include "Effect.hpp"
#include "FakeEnvironmentController.hpp"
#include "FakeLogger.hpp"
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

    case RunnerState::TEST_LIGHTS:
      out << "TEST_LIGHTS";
      break;
  }
  return out;
}

class RunnerTest : public PolesTest {
 protected:
  Buttons::Bank1 bank1;
  Buttons::Bank2 bank2;
  Buttons buttons{bank1, bank2};
  FakeParamController param_controller{};
  FakeEnvironmentController environment_controller{};
  FakeLogger logger{param_controller, environment_controller};
  Runner runner{poles, buttons, param_controller, environment_controller,
                logger};

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
    ASSERT_LE(GetTotalLightCount(), 3) << "millis: " << millis;
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
  ASSERT_LE(GetTotalLightCount(), 3);

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

TEST_F(RunnerTest, TestLightsButton) {
  runner.Step();
  ASSERT_EQ(runner.State(), RunnerState::NORMAL);

  AdvanceMillis(1000);
  environment_controller.SetTestLights(true);
  runner.Step();
  runner.Step();
  ASSERT_EQ(runner.State(), RunnerState::TEST_LIGHTS);
  ASSERT_EQ(GetTotalLightCount(), 4);
  ASSERT_EQ(GetPolesOn(), 1);

  environment_controller.SetTestLights(false);
  for (uint32_t n = 0; n < Runner::kTestLightsDuration; n += 100) {
    AdvanceMillis(100);
    runner.Step();
    ASSERT_EQ(runner.State(), RunnerState::TEST_LIGHTS);
    ASSERT_EQ(GetTotalLightCount(), 4);
    ASSERT_EQ(GetPolesOn(), 1);
  }

  AdvanceMillis(100);
  runner.Step();
  ASSERT_EQ(runner.State(), RunnerState::NORMAL);
  EXPECT_GE(GetPolesOn(), 2);

  AdvanceMillis(Runner::kIdleTimeout * 2);
  runner.Step();
  runner.Step();
  ASSERT_EQ(runner.State(), RunnerState::IDLE);
  ASSERT_EQ(GetTotalLightCount(), 2);
  ASSERT_EQ(GetPolesOn(), 2);

  AdvanceMillis(1000);
  environment_controller.SetTestLights(true);
  runner.Step();
  runner.Step();
  ASSERT_EQ(runner.State(), RunnerState::TEST_LIGHTS);
  ASSERT_EQ(GetTotalLightCount(), 4);
  ASSERT_EQ(GetPolesOn(), 1);
}

TEST_F(RunnerTest, DetectsMotion) {
  param_controller.SetRawParam(Param::kSlider1, 1);
  runner.Step();
  ASSERT_EQ(runner.State(), RunnerState::NORMAL);

  AdvanceMillis(Runner::kIdleTimeout + 100);
  runner.Step();
  ASSERT_EQ(runner.State(), RunnerState::IDLE);

  AdvanceMillis(100);
  environment_controller.SetMotionDetected(true);
  runner.Step();
  ASSERT_EQ(runner.State(), RunnerState::NORMAL);

  environment_controller.SetMotionDetected(false);
  AdvanceMillis(Runner::kIdleTimeout - 100);
  runner.Step();
  ASSERT_EQ(runner.State(), RunnerState::NORMAL);

  environment_controller.SetMotionDetected(true);
  AdvanceMillis(2000);
  runner.Step();
  ASSERT_EQ(runner.State(), RunnerState::NORMAL);
}