#include "DummyParamController.hpp"
#include "gtest/gtest.h"

TEST(ParamController, scale) {
  DummyParamController pc;

  pc.SetRawParam(Param::kSlider1, 128);

  EXPECT_EQ(pc.GetScaledParam(Param::kSlider1, 0, 128), 64);
}

TEST(ParamController, scale_up) {
  DummyParamController pc;

  pc.SetRawParam(Param::kSlider1, 0);
  EXPECT_EQ(pc.GetScaledParam(Param::kSlider1, -300, 300), -300);

  pc.SetRawParam(Param::kSlider1, 255);
  EXPECT_EQ(pc.GetScaledParam(Param::kSlider1, -300, 300), 300);

  pc.SetRawParam(Param::kSlider1, 128);
  EXPECT_EQ(pc.GetScaledParam(Param::kSlider1, -300, 300), 1);
}

TEST(ParamController, scale_down) {
  DummyParamController pc;

  pc.SetRawParam(Param::kSlider1, 0);
  EXPECT_EQ(pc.GetScaledParam(Param::kSlider1, -64, 64), -64);

  pc.SetRawParam(Param::kSlider1, 255);
  EXPECT_EQ(pc.GetScaledParam(Param::kSlider1, -64, 64), 64);

  pc.SetRawParam(Param::kSlider1, 128);
  EXPECT_EQ(pc.GetScaledParam(Param::kSlider1, -64, 64), 0);
}
