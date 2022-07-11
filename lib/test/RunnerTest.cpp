#include <gtest/gtest.h>

#include "Effect.hpp"
#include "FakeEnvironmentController.hpp"
#include "FakeParamController.hpp"
#include "Pole.hpp"
#include "PolesTest.hpp"
#include "Runner.hpp"

class RunnerTest : public PolesTest {
 protected:
  FakeParamController param_controller{};
  FakeEnvironmentController environment_controller{};
  Runner runner{poles, param_controller, environment_controller};
};

TEST_F(RunnerTest, ChecksBatteryVoltage) {
  environment_controller.SetBatteryMillivolts(1200);
  runner.Step();
  SetMillis(100);
  runner.Step();
  EXPECT_LE(4, GetPolesOn());

  AdvanceMillis(100);
  environment_controller.SetBatteryMillivolts(1100);
  runner.Step();
  EXPECT_EQ(2, GetPolesOn());

  AdvanceMillis(100);
  environment_controller.SetBatteryMillivolts(1230);
  runner.Step();
  EXPECT_LE(4, GetPolesOn());
}

TEST_F(RunnerTest, BatteryVoltageCheckHasHysteresis) {
  environment_controller.SetBatteryMillivolts(1180);
  runner.Step();
  SetMillis(100);
  runner.Step();
  EXPECT_LE(4, GetPolesOn());

  AdvanceMillis(100);
  environment_controller.SetBatteryMillivolts(1160);
  runner.Step();
  EXPECT_EQ(2, GetPolesOn());

  AdvanceMillis(100);
  environment_controller.SetBatteryMillivolts(1190);
  runner.Step();
  EXPECT_EQ(2, GetPolesOn());

  AdvanceMillis(100);
  environment_controller.SetBatteryMillivolts(1210);
  runner.Step();
  EXPECT_LE(4, GetPolesOn());

  AdvanceMillis(100);
  environment_controller.SetBatteryMillivolts(1180);
  runner.Step();
  EXPECT_LE(4, GetPolesOn());
}