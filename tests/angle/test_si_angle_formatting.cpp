#include <gtest/gtest.h>
#include <pkr_units/si_units_formatting.h>
#include <format>
#include <sstream>
#include <pkr_units/units/base/angle.h>

using namespace ::testing;

class SiAngleFormattingTest : public Test
{
};

// ============================================================================
// Basic Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(SiAngleFormattingTest, radian_ascii_formatting)
{
    pkr::units::radian_t rad{3.14159};
    std::string result = std::format("{}", rad);
    ASSERT_EQ(result, "3.14159 rad");
}

TEST_F(SiAngleFormattingTest, radian_ascii_with_precision)
{
    pkr::units::radian_t rad{1.5708};
    std::string result = std::format("{:.2f}", rad);
    ASSERT_EQ(result, "1.57 rad");
}

TEST_F(SiAngleFormattingTest, degree_ascii_formatting)
{
    pkr::units::degree_t deg{90.0};
    std::string result = std::format("{}", deg);
    ASSERT_EQ(result, "90 deg");
}

TEST_F(SiAngleFormattingTest, gradian_ascii_formatting)
{
    pkr::units::gradian_t grad{100.0};
    std::string result = std::format("{}", grad);
    ASSERT_EQ(result, "100 grad");
}