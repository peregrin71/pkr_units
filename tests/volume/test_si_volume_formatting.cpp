#include <gtest/gtest.h>
#include <pkr_units/si_units_formatting.h>
#include <format>
#include <pkr_units/units/derived/volume/volume_units.h>

using namespace ::testing;

class SiVolumeFormattingTest : public Test
{
};

// ============================================================================
// Volume Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(SiVolumeFormattingTest, cubic_meter_ascii_formatting)
{
    pkr::units::cubic_meter_t volume{2.0};
    std::string result = std::format("{}", volume);
    ASSERT_EQ(result, "2 m^3");
}

TEST_F(SiVolumeFormattingTest, cubic_kilometer_ascii_formatting)
{
    pkr::units::cubic_kilometer_t volume{0.5};
    std::string result = std::format("{}", volume);
    ASSERT_EQ(result, "0.5 km^3");
}

TEST_F(SiVolumeFormattingTest, cubic_centimeter_ascii_formatting)
{
    pkr::units::cubic_centimeter_t volume{10.0};
    std::string result = std::format("{}", volume);
    ASSERT_EQ(result, "10 cm^3");
}

TEST_F(SiVolumeFormattingTest, cubic_millimeter_ascii_formatting)
{
    pkr::units::cubic_millimeter_t volume{7.0};
    std::string result = std::format("{}", volume);
    ASSERT_EQ(result, "7 mm^3");
}

TEST_F(SiVolumeFormattingTest, liter_ascii_formatting)
{
    pkr::units::liter_t volume{1.5};
    std::string result = std::format("{}", volume);
    ASSERT_EQ(result, "1.5 L");
}

TEST_F(SiVolumeFormattingTest, milliliter_ascii_formatting)
{
    pkr::units::milliliter_t volume{250.0};
    std::string result = std::format("{}", volume);
    ASSERT_EQ(result, "250 mL");
}

// ============================================================================
// Wide Character Formatting Tests - wchar_t
// ============================================================================

TEST_F(SiVolumeFormattingTest, cubic_meter_wide_formatting)
{
    pkr::units::cubic_meter_t volume{2.0};
    std::wstring result = std::format(L"{}", volume);
    std::wstring expected = std::wstring(L"2 ") + std::wstring(pkr::units::cubic_meter_t::w_symbol);
    ASSERT_EQ(result, expected);
}

TEST_F(SiVolumeFormattingTest, liter_wide_formatting)
{
    pkr::units::liter_t volume{1.5};
    std::wstring result = std::format(L"{}", volume);
    std::wstring expected = std::wstring(L"1.5 ") + std::wstring(pkr::units::liter_t::w_symbol);
    ASSERT_EQ(result, expected);
}
