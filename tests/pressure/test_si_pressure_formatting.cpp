#include <gtest/gtest.h>
#include <pkr_units/si_units_formatting.h>
#include <format>
#include <sstream>
#include <pkr_units/units/derived/mechanical/pressure.h>

using namespace ::testing;

class SiPressureFormattingTest : public Test
{
};

// ============================================================================
// Basic Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(SiPressureFormattingTest, pascal_ascii_formatting)
{
    pkr::units::pascal_t Pa{101325.0};
    std::string result = std::format("{}", Pa);
    ASSERT_EQ(result, "101325 Pa");
}

TEST_F(SiPressureFormattingTest, pascal_ascii_with_precision)
{
    pkr::units::pascal_t Pa{1013.25};
    std::string result = std::format("{:.2f}", Pa);
    ASSERT_EQ(result, "1013.25 Pa");
}

TEST_F(SiPressureFormattingTest, hectopascal_ascii_formatting)
{
    pkr::units::hectopascal_t hPa{1013.0};
    std::string result = std::format("{}", hPa);
    ASSERT_EQ(result, "1013 hPa");
}

TEST_F(SiPressureFormattingTest, kilopascal_ascii_formatting)
{
    pkr::units::kilopascal_t kPa{101.325};
    std::string result = std::format("{}", kPa);
    ASSERT_EQ(result, "101.325 kPa");
}

TEST_F(SiPressureFormattingTest, megapascal_ascii_formatting)
{
    pkr::units::megapascal_t MPa{0.101325};
    std::string result = std::format("{}", MPa);
    ASSERT_EQ(result, "0.101325 MPa");
}

TEST_F(SiPressureFormattingTest, bar_ascii_formatting)
{
    pkr::units::bar_t bar{1.0};
    std::string result = std::format("{}", bar);
    ASSERT_EQ(result, "1 bar");
}

TEST_F(SiPressureFormattingTest, atmosphere_ascii_formatting)
{
    pkr::units::atmosphere_t atm{1.0};
    std::string result = std::format("{}", atm);
    ASSERT_EQ(result, "1 atm");
}

TEST_F(SiPressureFormattingTest, psi_ascii_formatting)
{
    pkr::units::psi_t psi{14.7};
    std::string result = std::format("{}", psi);
    ASSERT_EQ(result, "14.7 psi");
}