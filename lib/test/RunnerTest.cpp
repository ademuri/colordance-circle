#include <gtest/gtest.h>

#include "DummyParamController.hpp"
#include "Effect.hpp"
#include "FakeEnvironmentController.hpp"
#include "Pole.hpp"
#include "PolesTest.hpp"
#include "Runner.hpp"

class RunnerTest : public PolesTest {
 protected:
  DummyParamController param_controller{};
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
  environment_controller.SetBatteryMillivolts(1200);
  runner.Step();
  EXPECT_LE(4, GetPolesOn());
}