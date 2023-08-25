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
