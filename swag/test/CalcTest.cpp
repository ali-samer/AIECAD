#include <swag/Calc.hpp>
#include <swag/portability/GTest.hpp>

TEST(Calc, AddsWithinBounds) {
	EXPECT_EQ(swag::clamp_add(2, 3, 0, 10), 5);
}

TEST(Calc, ClampsLow) {
	EXPECT_EQ(swag::clamp_add(-100, 10, 0, 50), 0);
}

TEST(Calc, ClampsHigh) {
	EXPECT_NE(swag::clamp_add(100, 100, 0, 150), 250);
}