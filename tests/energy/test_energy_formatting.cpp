#include <gtest/gtest.h>
#include <format>
#include <sstream>
#include <pkr_units/units/derived/mechanical/energy.h>

using namespace ::testing;

class EnergyFormattingTest : public Test
{
};

/*
// ============================================================================
// Basic Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(EnergyFormattingTest, joule_ascii_formatting)
{
    pkr::units::joule_t energy{1000.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "1000 J");
}

TEST_F(EnergyFormattingTest, joule_ascii_with_precision)
{
    pkr::units::joule_t energy{1234.56789};
    std::string result = std::format("{:.2f}", energy);
    ASSERT_EQ(result, "1234.57 J");
}

TEST_F(EnergyFormattingTest, kilojoule_ascii_formatting)
{
    pkr::units::kilojoule_t energy{5.5};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "5.5 kJ");
}

TEST_F(EnergyFormattingTest, megajoule_ascii_formatting)
{
    pkr::units::megajoule_t energy{2.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "2 MJ");
}

TEST_F(EnergyFormattingTest, gigajoule_ascii_formatting)
{
    pkr::units::gigajoule_t energy{1.5};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "1.5 GJ");
}

TEST_F(EnergyFormattingTest, millijoule_ascii_formatting)
{
    pkr::units::millijoule_t energy{500.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "500 mJ");
}

TEST_F(EnergyFormattingTest, microjoule_ascii_formatting)
{
    pkr::units::microjoule_t energy{1000.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "1000 uJ");
}

TEST_F(EnergyFormattingTest, calorie_ascii_formatting)
{
    pkr::units::calorie_t energy{100.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "100 cal");
}

TEST_F(EnergyFormattingTest, kilocalorie_ascii_formatting)
{
    pkr::units::kilocalorie_t energy{0.5};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "0.5 kcal");
}

TEST_F(EnergyFormattingTest, watthour_ascii_formatting)
{
    pkr::units::watt_hour_t energy{100.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "100 Wh");
}

TEST_F(EnergyFormattingTest, kilowatthour_ascii_formatting)
{
    pkr::units::kilowatt_hour_t energy{10.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "10 kWh");
}

TEST_F(EnergyFormattingTest, electronvolt_ascii_formatting)
{
    pkr::units::electronvolt_t energy{1e6};
    std::string result = std::format("{:.1e}", energy);
    ASSERT_EQ(result, "1.0e+06 eV");
}

TEST_F(EnergyFormattingTest, kiloelectronvolt_ascii_formatting)
{
    pkr::units::kiloelectronvolt_t energy{1e3};
    std::string result = std::format("{:.1e}", energy);
    ASSERT_EQ(result, "1.0e+03 keV");
}

TEST_F(EnergyFormattingTest, megaelectronvolt_ascii_formatting)
{
    pkr::units::megaelectronvolt_t energy{1.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "1 MeV");
}

TEST_F(EnergyFormattingTest, gigaelectronvolt_ascii_formatting)
{
    pkr::units::gigaelectronvolt_t energy{1.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "1 GeV");
}

// ============================================================================
// Wide Character Formatting Tests
// ============================================================================

TEST_F(EnergyFormattingTest, joule_wide_formatting)
{
    pkr::units::joule_t energy{1000.0};
    std::wstring result = std::format(L"{}", energy);
    ASSERT_EQ(result, L"1000 J");
}

TEST_F(EnergyFormattingTest, microjoule_wide_formatting)
{
    pkr::units::microjoule_t energy{1000.0};
    std::wstring result = std::format(L"{}", energy);
    ASSERT_EQ(result, L"1000 \u00b5J");
}

// ============================================================================
// UTF-8 Formatting Tests
// ============================================================================

TEST_F(EnergyFormattingTest, joule_utf8_formatting)
{
    pkr::units::joule_t energy{1000.0};
    std::u8string result = std::format(u8"{}", energy);
    ASSERT_EQ(result, u8"1000 J");
}

TEST_F(EnergyFormattingTest, microjoule_utf8_formatting)
{
    pkr::units::microjoule_t energy{1000.0};
    std::u8string result = std::format(u8"{}", energy);
    ASSERT_EQ(result, u8"1000 \u00b5J");
}

// ============================================================================
// Edge Cases and Special Values
// ============================================================================

TEST_F(EnergyFormattingTest, zero_energy_formatting)
{
    pkr::units::joule_t energy{0.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "0 J");
}

TEST_F(EnergyFormattingTest, negative_energy_formatting)
{
    pkr::units::joule_t energy{-500.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "-500 J");
}

TEST_F(EnergyFormattingTest, very_small_energy)
{
    pkr::units::electronvolt_t energy{1e-20};
    std::string result = std::format("{:.2e}", energy);
    ASSERT_EQ(result, "1.00e-20 eV");
}

TEST_F(EnergyFormattingTest, very_large_energy)
{
    pkr::units::gigajoule_t energy{1e9};
    std::string result = std::format("{:.1e}", energy);
    ASSERT_EQ(result, "1.0e+09 GJ");
}

TEST_F(EnergyFormattingTest, default_precision)
{
    pkr::units::joule_t energy{3.141592653589793};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "3.14159 J");
}

TEST_F(EnergyFormattingTest, value_preservation)
{
    pkr::units::joule_t energy{123.456};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "123.456 J");
}
*/
