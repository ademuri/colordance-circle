#include <gtest/gtest.h>

#include "Buttons.hpp"
#include "Effect.hpp"
#include "FakeEnvironmentController.hpp"
#include "FakeLogger.hpp"
#include "FakeParamController.hpp"
#include "Pole.hpp"
#include "Runner.hpp"

class LoggerTest : public ::testing::Test {
 protected:
  Poles poles{};
  Buttons::Bank1 bank1;
  Buttons::Bank2 bank2;
  Buttons buttons{bank1, bank2};
  FakeParamController param_controller{};
  FakeEnvironmentController environment_controller{};
  FakeLogger logger{param_controller, environment_controller};
  Runner runner{poles, buttons, param_controller, environment_controller,
                logger};

  void SetUp() override { environment_controller.SetBatteryMillivolts(1200); }
};

TEST_F(LoggerTest, Logs) {
  SetMillis(0);
  logger.ResetTimerForTest();
  ASSERT_STREQ(logger.PreviousMessage(), "");
  runner.Step();
  AdvanceMillis(kLogIntervalMillis + 100);
  runner.Step();
  EXPECT_STREQ(logger.PreviousMessage(), "        10, 0, 0, 0, 0, 1200, 0");

  AdvanceMillis(kLogIntervalMillis + 100);
  param_controller.SetRawParam(Param::kEffect, 2);
  param_controller.SetRawParam(Param::kSlider1, 3);
  param_controller.SetRawParam(Param::kSlider2, 4);
  environment_controller.SetBatteryMillivolts(1210);
  runner.Step();
  EXPECT_STREQ(logger.PreviousMessage(), "        20, 2, 3, 4, 1, 1210, 0");

  AdvanceMillis(kLogIntervalMillis + 100);
  environment_controller.SetMotionDetected(true);
  runner.Step();
  EXPECT_STREQ(logger.PreviousMessage(), "        30, 2, 3, 4, 0, 1210, 1");
}
