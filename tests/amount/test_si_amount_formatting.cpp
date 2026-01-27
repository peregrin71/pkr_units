#include <gtest/gtest.h>
#include <pkr_units/si_units_formatting.h>
#include <format>
#include <sstream>
#include <pkr_units/units/base/amount.h>

using namespace ::testing;

class SiAmountFormattingTest : public Test
{
};

/*
// ============================================================================
// Basic Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(SiAmountFormattingTest, mole_ascii_formatting)
{
    pkr::units::mole_t mol{5.0};
    std::string result = std::format("{}", mol);
    ASSERT_EQ(result, "5 mol");
}

TEST_F(SiAmountFormattingTest, mole_ascii_with_precision)
{
    pkr::units::mole_t mol{2.5};
    std::string result = std::format("{:.2f}", mol);
    ASSERT_EQ(result, "2.50 mol");
}

TEST_F(SiAmountFormattingTest, millimole_ascii_formatting)
{
    pkr::units::millimole_t mmol{1500.0};
    std::string result = std::format("{}", mmol);
    ASSERT_EQ(result, "1500 mmol");
}

TEST_F(SiAmountFormattingTest, micromole_ascii_formatting)
{
    pkr::units::micromole_t umol{0.5};
    std::string result = std::format("{}", umol);
    ASSERT_EQ(result, "0.5 umol"); // ASCII fallback: "u" instead of "μ"
}

TEST_F(SiAmountFormattingTest, nanomole_ascii_formatting)
{
    pkr::units::nanomole_t nmol{100.0};
    std::string result = std::format("{}", nmol);
    ASSERT_EQ(result, "100 nmol");
}

TEST_F(SiAmountFormattingTest, kilomole_ascii_formatting)
{
    pkr::units::kilomole_t kmol{2.5};
    std::string result = std::format("{}", kmol);
    ASSERT_EQ(result, "2.5 kmol");
}
*/
