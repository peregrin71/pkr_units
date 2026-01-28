#include <gtest/gtest.h>
#include <pkr_units/si_units_formatting.h>
#include <format>
#include <pkr_units/units/derived/area/area_units.h>

using namespace ::testing;

class SiAreaFormattingTest : public Test
{
};

// ============================================================================
// Area Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(SiAreaFormattingTest, square_meter_ascii_formatting)
{
    pkr::units::square_meter_t area{5.0};
    std::string result = std::format("{}", area);
    ASSERT_EQ(result, "5 m^2");
}

TEST_F(SiAreaFormattingTest, square_kilometer_ascii_formatting)
{
    pkr::units::square_kilometer_t area{1.25};
    std::string result = std::format("{}", area);
    ASSERT_EQ(result, "1.25 km^2");
}

TEST_F(SiAreaFormattingTest, square_centimeter_ascii_formatting)
{
    pkr::units::square_centimeter_t area{100.0};
    std::string result = std::format("{}", area);
    ASSERT_EQ(result, "100 cm^2");
}

TEST_F(SiAreaFormattingTest, square_millimeter_ascii_formatting)
{
    pkr::units::square_millimeter_t area{2500.0};
    std::string result = std::format("{}", area);
    ASSERT_EQ(result, "2500 mm^2");
}

// ============================================================================
// Wide Character Formatting Tests - wchar_t
// ============================================================================

TEST_F(SiAreaFormattingTest, square_meter_wide_formatting)
{
    pkr::units::square_meter_t area{5.0};
    std::wstring result = std::format(L"{}", area);
    std::wstring expected = std::wstring(L"5 ") + std::wstring(pkr::units::square_meter_t::w_symbol);
    ASSERT_EQ(result, expected);
}

TEST_F(SiAreaFormattingTest, square_kilometer_wide_formatting)
{
    pkr::units::square_kilometer_t area{1.25};
    std::wstring result = std::format(L"{}", area);
    std::wstring expected = std::wstring(L"1.25 ") + std::wstring(pkr::units::square_kilometer_t::w_symbol);
    ASSERT_EQ(result, expected);
}
