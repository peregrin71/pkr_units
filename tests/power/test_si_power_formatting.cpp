#include <gtest/gtest.h>
#include <pkr_units/si_units_formatting.h>
#include <format>
#include <sstream>
#include <pkr_units/units/derived/mechanical/power.h>

using namespace ::testing;

class SiPowerFormattingTest : public Test
{
};

// ============================================================================
// Basic Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(SiPowerFormattingTest, watt_ascii_formatting)
{
    pkr::units::watt W{1000.0};
    std::string result = std::format("{}", W);
    ASSERT_EQ(result, "1000 W");
}

TEST_F(SiPowerFormattingTest, watt_ascii_with_precision)
{
    pkr::units::watt W{123.456};
    std::string result = std::format("{:.2f}", W);
    ASSERT_EQ(result, "123.46 W");
}

TEST_F(SiPowerFormattingTest, kilowatt_ascii_formatting)
{
    pkr::units::kilowatt kW{1.5};
    std::string result = std::format("{}", kW);
    ASSERT_EQ(result, "1.5 kW");
}

TEST_F(SiPowerFormattingTest, megawatt_ascii_formatting)
{
    pkr::units::megawatt MW{0.5};
    std::string result = std::format("{}", MW);
    ASSERT_EQ(result, "0.5 MW");
}

TEST_F(SiPowerFormattingTest, milliwatt_ascii_formatting)
{
    pkr::units::milliwatt mW{500.0};
    std::string result = std::format("{}", mW);
    ASSERT_EQ(result, "500 mW");
}

TEST_F(SiPowerFormattingTest, microwatt_ascii_formatting)
{
    pkr::units::microwatt uW{0.5};
    std::string result = std::format("{}", uW);
    ASSERT_EQ(result, "0.5 uW");
}

TEST_F(SiPowerFormattingTest, horsepower_ascii_formatting)
{
    pkr::units::horsepower hp{1.0};
    std::string result = std::format("{}", hp);
    ASSERT_EQ(result, "1 hp");
}