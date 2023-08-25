#include <gtest/gtest.h>

#include <ColordanceTypes.hpp>

#include "MiniLightController.hpp"

TEST(MiniLightControllerTest, NativeToBoardLedIndex) {
  EXPECT_EQ(MiniLightController::NativeToBoardLedIndex(0), 0);
  EXPECT_EQ(MiniLightController::NativeToBoardLedIndex(1), 1);
  EXPECT_EQ(MiniLightController::NativeToBoardLedIndex(15), 15);
  EXPECT_EQ(MiniLightController::NativeToBoardLedIndex(16), 31);
  EXPECT_EQ(MiniLightController::NativeToBoardLedIndex(17), 30);
  EXPECT_EQ(MiniLightController::NativeToBoardLedIndex(30), 17);
  EXPECT_EQ(MiniLightController::NativeToBoardLedIndex(31), 16);
}

TEST(MiniLightControllerTest, GridLightToNativeLedIndices) {
  MiniLightController::LedIndices expected{
      0, 1, 2, 3, 16, 17, 18, 19, 32, 33, 34, 35, 48, 49, 50, 51,
  };
  EXPECT_EQ(MiniLightController::GridLightToNativeLedIndices(0, 0), expected);

  expected = MiniLightController::LedIndices{
      64, 65, 66, 67, 80, 81, 82, 83, 96, 97, 98, 99, 112, 113, 114, 115,
  };
  EXPECT_EQ(MiniLightController::GridLightToNativeLedIndices(0, 1), expected);

  expected = MiniLightController::LedIndices{
      4, 5, 6, 7, 20, 21, 22, 23, 36, 37, 38, 39, 52, 53, 54, 55,
  };
  EXPECT_EQ(MiniLightController::GridLightToNativeLedIndices(1, 0), expected);
}
