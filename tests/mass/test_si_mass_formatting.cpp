#include <gtest/gtest.h>
#include <pkr_units/si_units_formatting.h>
#include <format>
#include <sstream>
#include <pkr_units/units/base/mass.h>

using namespace ::testing;

class SiMassFormattingTest : public Test
{
};

/*
// ============================================================================
// Basic Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(SiMassFormattingTest, kilogram_ascii_formatting)
{
    pkr::units::kilogram_t kg{5.0};
    std::string result = std::format("{}", kg);
    ASSERT_EQ(result, "5 kg");
}

TEST_F(SiMassFormattingTest, kilogram_ascii_with_precision)
{
    pkr::units::kilogram_t kg{5.123456};
    std::string result = std::format("{:.2f}", kg);
    ASSERT_EQ(result, "5.12 kg");
}

TEST_F(SiMassFormattingTest, gram_ascii_formatting)
{
    pkr::units::gram_t g{2500.0};
    std::string result = std::format("{}", g);
    ASSERT_EQ(result, "2500 g");
}

TEST_F(SiMassFormattingTest, milligram_ascii_formatting)
{
    pkr::units::milligram_t mg{1500.0};
    std::string result = std::format("{}", mg);
    ASSERT_EQ(result, "1500 mg");
}

TEST_F(SiMassFormattingTest, microgram_ascii_formatting)
{
    pkr::units::microgram_t ug{0.5};
    std::string result = std::format("{}", ug);
    ASSERT_EQ(result, "0.5 ug"); // ASCII fallback: "u" instead of "μ"
}

TEST_F(SiMassFormattingTest, nanogram_ascii_formatting)
{
    pkr::units::nanogram_t ng{100.0};
    std::string result = std::format("{}", ng);
    ASSERT_EQ(result, "100 ng");
}

TEST_F(SiMassFormattingTest, picogram_ascii_formatting)
{
    pkr::units::picogram_t pg{500.0};
    std::string result = std::format("{}", pg);
    ASSERT_EQ(result, "500 pg");
}

TEST_F(SiMassFormattingTest, megagram_ascii_formatting)
{
    pkr::units::megagram_t Mg{2.5};
    std::string result = std::format("{}", Mg);
    ASSERT_EQ(result, "2.5 Mg");
}
*/
