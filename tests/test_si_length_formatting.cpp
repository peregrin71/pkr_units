// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#include <gtest/gtest.h>
#include <units/impl/length.h>
#include <units/formatting/si_unit_formatting.h>
#include <format>

namespace test
{

using namespace ::testing;

class SiLengthFormattingTest : public Test
{
};

// ============================================================================
// Formatting Tests
// ============================================================================

TEST_F(SiLengthFormattingTest, format_meter)
{
    si::meter m{5.0};
    auto formatted = std::format("{}", m);
    ASSERT_FALSE(formatted.empty());
    // Should contain "5" and "m"
    ASSERT_NE(formatted.find("5"), std::string::npos);
    ASSERT_NE(formatted.find("m"), std::string::npos);
}

TEST_F(SiLengthFormattingTest, format_kilometer)
{
    si::kilometer km{2.5};
    auto formatted = std::format("{}", km);
    ASSERT_FALSE(formatted.empty());
    ASSERT_NE(formatted.find("2.5"), std::string::npos);
}

TEST_F(SiLengthFormattingTest, format_millimeter)
{
    si::millimeter mm{1500.0};
    auto formatted = std::format("{}", mm);
    ASSERT_FALSE(formatted.empty());
    ASSERT_NE(formatted.find("1500"), std::string::npos);
}

TEST_F(SiLengthFormattingTest, format_with_precision)
{
    si::meter m{3.14159};
    auto formatted = std::format("{:.2f}", m);
    ASSERT_EQ(formatted, "3.14 m");
}

TEST_F(SiLengthFormattingTest, format_area_with_exponent)
{
    si::meter m1{5.0};
    si::meter m2{3.0};
    auto area = m1 * m2;
    auto formatted = std::format("{}", area);
    ASSERT_FALSE(formatted.empty());
    // Should contain the area value
    ASSERT_NE(formatted.find("15"), std::string::npos);
}

// ============================================================================
// Special Imperial Unit Formatting Tests (feet/inches)
// ============================================================================

TEST_F(SiLengthFormattingTest, format_feet_whole_number)
{
    si::foot ft{5.0};
    auto formatted = std::format("{}", ft);
    ASSERT_EQ(formatted, "5'");
}

TEST_F(SiLengthFormattingTest, format_feet_with_half_inch)
{
    si::foot ft{5.5};
    auto formatted = std::format("{}", ft);
    ASSERT_EQ(formatted, "5'6\"");
}

TEST_F(SiLengthFormattingTest, format_feet_quarter_foot)
{
    si::foot ft{5.25};
    auto formatted = std::format("{}", ft);
    ASSERT_EQ(formatted, "5'3\"");
}

TEST_F(SiLengthFormattingTest, format_feet_less_than_one)
{
    si::foot ft{0.5};
    auto formatted = std::format("{}", ft);
    ASSERT_EQ(formatted, "0'6\"");
}

TEST_F(SiLengthFormattingTest, format_feet_less_than_one_to_inches)
{
    si::foot ft{0.5};
    auto formatted = std::format("{}", si::si_cast<si::inch>(ft));
    ASSERT_EQ(formatted, "6\"");
}

TEST_F(SiLengthFormattingTest, format_feet_rounding_to_next_foot)
{
    si::foot ft{5.9999};
    auto formatted = std::format("{}", ft);
    ASSERT_EQ(formatted, "6'");
}

TEST_F(SiLengthFormattingTest, format_feet_one_foot_one_inch)
{
    si::foot ft{1.08333333};  // 1 foot + 1 inch
    auto formatted = std::format("{}", ft);
    ASSERT_EQ(formatted, "1'1\"");
}

} // namespace test
