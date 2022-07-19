#include <gtest/gtest.h>

#include "Effect.hpp"
#include "FakeEnvironmentController.hpp"
#include "FakeLogger.hpp"
#include "FakeParamController.hpp"
#include "Pole.hpp"
#include "Runner.hpp"

class LoggerTest : public ::testing::Test {
 protected:
  Poles poles{};
  FakeParamController param_controller{};
  FakeEnvironmentController environment_controller{};
  FakeLogger logger{param_controller, environment_controller};
  Runner runner{poles, param_controller, environment_controller, logger};

  void SetUp() override { environment_controller.SetBatteryMillivolts(1200); }
};

TEST_F(LoggerTest, Logs) {
  ASSERT_STREQ(logger.PreviousMessage(), "");
  runner.Step();
  AdvanceMillis(kLogIntervalMillis + 100);
  runner.Step();
  ASSERT_STREQ(logger.PreviousMessage(), "0, 0, 0, 0, 1200, 0\n");

  AdvanceMillis(kLogIntervalMillis + 100);
  param_controller.SetRawParam(Param::kEffect, 2);
  param_controller.SetRawParam(Param::kSlider1, 3);
  param_controller.SetRawParam(Param::kSlider2, 4);
  environment_controller.SetBatteryMillivolts(1210);
  runner.Step();
  ASSERT_STREQ(logger.PreviousMessage(), "2, 3, 4, 1, 1210, 0\n");

  AdvanceMillis(kLogIntervalMillis + 100);
  environment_controller.SetMotionDetected(true);
  runner.Step();
  ASSERT_STREQ(logger.PreviousMessage(), "2, 3, 4, 0, 1210, 1\n");
}
