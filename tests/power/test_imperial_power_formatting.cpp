#include <gtest/gtest.h>
#include <pkr_units/si_units_formatting.h>
#include <format>
#include <sstream>
#include <pkr_units/units/imperial/mechanical/power.h>

using namespace ::testing;

class ImperialPowerFormattingTest : public Test
{
};

/*
// ============================================================================
// Basic Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(ImperialPowerFormattingTest, horsepower_ascii_formatting)
{
    pkr::units::horsepower_t hp{1.0};
    std::string result = std::format("{}", hp);
    ASSERT_EQ(result, "1 hp");
}
*/
