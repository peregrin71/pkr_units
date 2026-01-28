#include <gtest/gtest.h>
#include <pkr_units/si_units_formatting.h>
#include <format>
#include <sstream>
#include <pkr_units/units/imperial/mechanical/pressure.h>

using namespace ::testing;

class ImperialPressureFormattingTest : public Test
{
};

/*
// ============================================================================
// Basic Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(ImperialPressureFormattingTest, psi_ascii_formatting)
{
    pkr::units::psi_t psi{14.7};
    std::string result = std::format("{}", psi);
    ASSERT_EQ(result, "14.7 psi");
}
*/
