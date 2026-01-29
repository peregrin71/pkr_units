#include <gtest/gtest.h>

#include <format>
#include <pkr_units/si_units_formatting.h>
#include <pkr_units/units/dimensionless/ratio.h>
#include <pkr_units/units/dimensionless/decibel.h>

using namespace ::testing;

class DimensionlessFormattingTest : public Test
{
};

TEST_F(DimensionlessFormattingTest, RatioFormatting)
{
    pkr::units::ratio_t ratio{0.5};
    std::string result = std::format("{}", ratio);
    EXPECT_EQ(result, "0.5 ratio");
}

TEST_F(DimensionlessFormattingTest, PercentageFormatting)
{
    pkr::units::percentage_t percent{25.0};
    std::string result = std::format("{}", percent);
    EXPECT_EQ(result, "25 %");
}

TEST_F(DimensionlessFormattingTest, DecibelPowerFormatting)
{
    pkr::units::decibel_power_t db{10.0};
    std::string result = std::format("{}", db);
    EXPECT_EQ(result, "10 dB");
}

TEST_F(DimensionlessFormattingTest, DecibelAmplitudeFormatting)
{
    pkr::units::decibel_amplitude_t db{20.0};
    std::string result = std::format("{}", db);
    EXPECT_EQ(result, "20 dB");
}
