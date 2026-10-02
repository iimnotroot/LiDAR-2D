#include "LookUpTable.hpp"
#include <cmath>
#include <gtest/gtest.h>

TEST(LookUpTableTest, CosZero) {
    LookUpTable<1440> lut;
    EXPECT_EQ(lut.cos(0.0f), std::cos(0.0f));
}

TEST(LookUpTableTest, SinZero) {
    LookUpTable<1440> lut;
    EXPECT_EQ(lut.sin(0.0f), std::sin(0.0f));
}