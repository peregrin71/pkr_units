#include <gtest/gtest.h>

#include <format>
#include <pkr_units/format/si.h>
#include <pkr_units/units/dimensionless/ratio.h>
#include <pkr_units/units/dimensionless/percentage.h>
#include <pkr_units/units/dimensionless/decibel.h>

using namespace ::testing;

class DimensionlessFormattingTest : public Test
{
};

TEST_F(DimensionlessFormattingTest, RatioFormatting)
{
    pkr::units::ratio_t<double> ratio{0.5};
    std::string result = std::format("{}", ratio);
    EXPECT_EQ(result, "0.5 ratio");
}

TEST_F(DimensionlessFormattingTest, PercentageFormatting)
{
    pkr::units::percentage_t<double> percent{25.0};
    std::string result = std::format("{}", percent);
    EXPECT_EQ(result, "25 %");
}

TEST_F(DimensionlessFormattingTest, DecibelPowerFormatting)
{
    pkr::units::decibel_power_t<double> db{10.0};
    std::string result = std::format("{}", db);
    EXPECT_EQ(result, "10 dB");
}

TEST_F(DimensionlessFormattingTest, DecibelPowerWideFormatting)
{
    pkr::units::decibel_power_t<double> db{10.0};
    std::wstring result = std::format(L"{}", db);
    EXPECT_EQ(result, L"10 dB");
}

TEST_F(DimensionlessFormattingTest, DecibelAmplitudeFormatting)
{
    pkr::units::decibel_amplitude_t<double> db{20.0};
    std::string result = std::format("{}", db);
    EXPECT_EQ(result, "20 dB");
}

TEST_F(DimensionlessFormattingTest, DecibelAmplitudeWideFormatting)
{
    pkr::units::decibel_amplitude_t<double> db{20.0};
    std::wstring result = std::format(L"{}", db);
    EXPECT_EQ(result, L"20 dB");
}
