#include <gtest/gtest.h>
#include <format>
#include <sstream>
#include <pkr_units/units/derived/mechanical/force.h>
#include <pkr_units/si_formatting.h>

using namespace ::testing;

class ForceFormattingTest : public Test
{
};

// ============================================================================
// Basic Formatting Tests - char (ASCII)
// ============================================================================

/*
TEST_F(ForceFormattingTest, newton_ascii_formatting)
{
    pkr::units::newton_t force{100.0};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "100 N");
}

TEST_F(ForceFormattingTest, newton_ascii_with_precision)
{
    pkr::units::newton_t force{123.456789};
    std::string result = std::format("{:.2f}", force);
    ASSERT_EQ(result, "123.46 N");
}

TEST_F(ForceFormattingTest, kilonewton_ascii_formatting)
{
    pkr::units::kilonewton_t force{5.5};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "5.5 kN");
}

TEST_F(ForceFormattingTest, meganewton_ascii_formatting)
{
    pkr::units::meganewton_t force{2.0};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "2 MN");
}

TEST_F(ForceFormattingTest, millinewton_ascii_formatting)
{
    pkr::units::millinewton_t force{500.0};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "500 mN");
}

TEST_F(ForceFormattingTest, micronewton_ascii_formatting)
{
    pkr::units::micronewton_t force{1000.0};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "1000 uN");
}

TEST_F(ForceFormattingTest, nanonewton_ascii_formatting)
{
    pkr::units::nanonewton_t force{5000000.0};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "5000000 nN");
}

// ============================================================================
// Wide Character Formatting Tests
// ============================================================================

TEST_F(ForceFormattingTest, newton_wide_formatting)
{
    pkr::units::newton_t force{100.0};
    std::wstring result = std::format(L"{}", force);
    ASSERT_EQ(result, L"100 N");
}

TEST_F(ForceFormattingTest, micronewton_wide_formatting)
{
    pkr::units::micronewton_t force{1000.0};
    std::wstring result = std::format(L"{}", force);
    ASSERT_EQ(result, L"1000 \u00b5N");
}

// ============================================================================
// Edge Cases and Special Values
// ============================================================================

TEST_F(ForceFormattingTest, zero_force_formatting)
{
    pkr::units::newton_t force{0.0};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "0 N");
}

TEST_F(ForceFormattingTest, negative_force_formatting)
{
    pkr::units::newton_t force{-50.0};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "-50 N");
}

TEST_F(ForceFormattingTest, very_small_force)
{
    pkr::units::nanonewton_t force{1e-12};
    std::string result = std::format("{:.2e}", force);
    ASSERT_EQ(result, "1.00e-12 nN");
}

TEST_F(ForceFormattingTest, very_large_force)
{
    pkr::units::meganewton_t force{1e6};
    std::string result = std::format("{:.1e}", force);
    ASSERT_EQ(result, "1.0e+06 MN");
}

TEST_F(ForceFormattingTest, default_precision)
{
    pkr::units::newton_t force{3.141592653589793};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "3.14159 N");
}

TEST_F(ForceFormattingTest, value_preservation)
{
    pkr::units::newton_t force{123.456};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "123.456 N");
}
*/
