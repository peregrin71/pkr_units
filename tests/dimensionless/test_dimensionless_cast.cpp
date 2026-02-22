#include <gtest/gtest.h>
#include <stdexcept>

#include <pkr_units/impl/cast/unit_cast.h>
#include <pkr_units/units/dimensionless/ratio.h>
#include <pkr_units/units/dimensionless/percentage.h>
#include <pkr_units/units/dimensionless/decibel_cast.h>

using namespace ::testing;

class DimensionlessCastTest : public Test
{
};

TEST_F(DimensionlessCastTest, RatioToPercentage)
{
    pkr::units::ratio_t<double> ratio{0.5};
    auto percent = pkr::units::unit_cast<pkr::units::percentage_t<double>>(ratio);
    EXPECT_DOUBLE_EQ(percent.value(), 50.0);
}

TEST_F(DimensionlessCastTest, PercentageToRatio)
{
    pkr::units::percentage_t<double> percent{25.0};
    auto ratio = pkr::units::unit_cast<pkr::units::ratio_t<double>>(percent);
    EXPECT_DOUBLE_EQ(ratio.value(), 0.25);
}
