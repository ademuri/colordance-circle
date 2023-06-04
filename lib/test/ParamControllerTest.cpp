#include <gtest/gtest.h>

#include <map>

#include "FakeParamController.hpp"
#include "ParamController.hpp"

const std::map<Param, std::string_view> kButtonParams = {
    {Param::kBeat, "Beat"},       {Param::kShift, "Shift"},
    {Param::kPause, "Pause"},     {Param::kOption1, "Option1"},
    {Param::kOption2, "Option2"},
};

TEST(ParamControllerTest, ParsesButtons) {
  FakeParamController controller;
  ControlsIn controls_in;

  controls_in.button_mask = 0;
  controller.ParseControlsIn(controls_in);
  for (const auto& param : kButtonParams) {
    EXPECT_EQ(controller.GetRawParam(param.first), 0) << param.second;
  }

  controls_in.button_mask = 0xFFFF;
  controller.ParseControlsIn(controls_in);
  for (const auto& param : kButtonParams) {
    EXPECT_EQ(controller.GetRawParam(param.first), 1) << param.second;
  }

  for (uint8_t i = 0; i < 16; i++) {
    controls_in.button_mask = 1 << i;
    controller.ParseControlsIn(controls_in);
    uint8_t on = 0;
    for (const auto& param : kButtonParams) {
      if (controller.GetRawParam(param.first)) {
        on++;
      }
    }
    EXPECT_LE(on, 1);
  }
}

TEST(ParamControllerTest, ParsesSliders) {
  FakeParamController controller;
  ControlsIn controls_in;

  controls_in.analog_inputs[0] = 94;
  controller.ParseControlsIn(controls_in);
  EXPECT_EQ(controller.GetRawParam(Param::kSlider1), 94);
  EXPECT_EQ(controller.GetRawParam(Param::kSlider2), 0);

  controls_in.analog_inputs[0] = 0;
  controls_in.analog_inputs[1] = 135;
  controller.ParseControlsIn(controls_in);
  EXPECT_EQ(controller.GetRawParam(Param::kSlider1), 0);
  EXPECT_EQ(controller.GetRawParam(Param::kSlider2), 135);
}

TEST(ParamControllerTest, ParsesEffect) {
  FakeParamController controller;
  ControlsIn controls_in;

  controls_in.button_mask = 0b1;
  controller.ParseControlsIn(controls_in);
  EXPECT_EQ(controller.GetRawParam(Param::kEffect), 0);

  controls_in.button_mask = 0b10;
  controller.ParseControlsIn(controls_in);
  EXPECT_EQ(controller.GetRawParam(Param::kEffect), 1);

  controls_in.button_mask = 0b1000000;
  controller.ParseControlsIn(controls_in);
  EXPECT_EQ(controller.GetRawParam(Param::kEffect), 6);

  controls_in.button_mask = 0;
  controller.ParseControlsIn(controls_in);
  EXPECT_EQ(controller.GetRawParam(Param::kEffect), 6);
}

TEST(ParamControllerTest, GetScaledParam) {
  FakeParamController controller;
  ControlsIn controls_in;

  controls_in.analog_inputs[0] = 127;
  controller.ParseControlsIn(controls_in);
  ASSERT_EQ(controller.GetRawParam(Param::kSlider1), 127);

  EXPECT_EQ(controller.GetScaledParam(Param::kSlider1, 0, 128), 63);
  EXPECT_EQ(controller.GetScaledParam(Param::kSlider1, 128, 255), 191);
}
