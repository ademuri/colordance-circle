#include "gtest/gtest.h"

#include "DummyParamController.hpp"

TEST(ParamController, scale) {
  DummyParamController pc;

  pc.SetRawParam(Param::kSpeed, 128);

  EXPECT_EQ(pc.GetScaledParam(Param::kSpeed, 0, 128), 64);
}

TEST(ParamController, scale_up) {
  DummyParamController pc;

  pc.SetRawParam(Param::kSpeed, 0);
  EXPECT_EQ(pc.GetScaledParam(Param::kSpeed, -300, 300), -300);

  pc.SetRawParam(Param::kSpeed, 255);
  EXPECT_EQ(pc.GetScaledParam(Param::kSpeed, -300, 300), 300);

  pc.SetRawParam(Param::kSpeed, 128);
  EXPECT_EQ(pc.GetScaledParam(Param::kSpeed, -300, 300), 1);
}

TEST(ParamController, scale_down) {
  DummyParamController pc;

  pc.SetRawParam(Param::kSpeed, 0);
  EXPECT_EQ(pc.GetScaledParam(Param::kSpeed, -64, 64), -64);

  pc.SetRawParam(Param::kSpeed, 255);
  EXPECT_EQ(pc.GetScaledParam(Param::kSpeed, -64, 64), 64);

  pc.SetRawParam(Param::kSpeed, 128);
  EXPECT_EQ(pc.GetScaledParam(Param::kSpeed, -64, 64), 0);
}
