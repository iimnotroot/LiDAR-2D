#include "LookUpTable.hpp"
#include <cmath>
#include <gtest/gtest.h>

constexpr float DEG_TO_RAD = M_PI / 180.0f;
constexpr float DEG_TO_INDEX = 1440.0f / 360.0f;
constexpr float TOLERANCE = 1e-4f;

TEST(LookUpTableTest, CosZero) {
    LookUpTable<1440> lut;
    for (size_t i = 0; i < 1440; ++i ) {
        float deg_value = static_cast<float>(i) / (DEG_TO_INDEX);
        float rad_value = deg_value * DEG_TO_RAD;

        EXPECT_NEAR(lut.cos(deg_value), std::cos(rad_value), TOLERANCE);
    }
    
}

TEST(LookUpTableTest, SinZero) {
    LookUpTable<1440> lut;
    for (size_t i = 0; i < 1440; ++i ) {
        float deg_value = static_cast<float>(i) / (DEG_TO_INDEX);
        float rad_value = deg_value * DEG_TO_RAD;
        
        EXPECT_NEAR(lut.sin(deg_value), std::sin(rad_value), TOLERANCE);
    }
}