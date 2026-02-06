#include <gtest/gtest.h>
#include <format>
#include <sstream>
#include <pkr_units/units/derived/mechanical/energy.h>
#include <pkr_units/format/si.h>

using namespace ::testing;

class EnergyFormattingTest : public Test
{
};

// ============================================================================
// Basic Formatting Tests - char (ASCII) - double
// ============================================================================

TEST_F(EnergyFormattingTest, joule_ascii_formatting_double)
{
    pkr::units::joule_t<double> energy{1000.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "1000 J");
}

TEST_F(EnergyFormattingTest, joule_ascii_formatting_float)
{
    pkr::units::joule_t<float> energy{1000.0f};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "1000 J");
}

TEST_F(EnergyFormattingTest, joule_ascii_precision_double)
{
    pkr::units::joule_t<double> energy{1234.56789};
    std::string result = std::format("{:.2f}", energy);
    ASSERT_EQ(result, "1234.57 J");
}

TEST_F(EnergyFormattingTest, joule_ascii_precision_float)
{
    pkr::units::joule_t<float> energy{1234.56789f};
    std::string result = std::format("{:.2f}", energy);
    ASSERT_EQ(result, "1234.57 J");
}

TEST_F(EnergyFormattingTest, kilojoule_ascii_formatting_double)
{
    pkr::units::kilojoule_t<double> energy{5.5};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "5.5 kJ");
}

TEST_F(EnergyFormattingTest, kilojoule_ascii_formatting_float)
{
    pkr::units::kilojoule_t<float> energy{5.5f};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "5.5 kJ");
}

TEST_F(EnergyFormattingTest, megajoule_ascii_formatting_double)
{
    pkr::units::megajoule_t<double> energy{2.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "2 MJ");
}

TEST_F(EnergyFormattingTest, megajoule_ascii_formatting_float)
{
    pkr::units::megajoule_t<float> energy{2.0f};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "2 MJ");
}

TEST_F(EnergyFormattingTest, gigajoule_ascii_formatting_double)
{
    pkr::units::gigajoule_t<double> energy{1.5};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "1.5 GJ");
}

TEST_F(EnergyFormattingTest, gigajoule_ascii_formatting_float)
{
    pkr::units::gigajoule_t<float> energy{1.5f};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "1.5 GJ");
}

TEST_F(EnergyFormattingTest, millijoule_ascii_formatting_double)
{
    pkr::units::millijoule_t<double> energy{500.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "500 mJ");
}

TEST_F(EnergyFormattingTest, millijoule_ascii_formatting_float)
{
    pkr::units::millijoule_t<float> energy{500.0f};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "500 mJ");
}

TEST_F(EnergyFormattingTest, microjoule_ascii_formatting_double)
{
    pkr::units::microjoule_t<double> energy{1000.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "1000 uJ");
}

TEST_F(EnergyFormattingTest, microjoule_ascii_formatting_float)
{
    pkr::units::microjoule_t<float> energy{1000.0f};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "1000 uJ");
}

TEST_F(EnergyFormattingTest, calorie_ascii_formatting_double)
{
    pkr::units::calorie_t<double> energy{100.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "100 cal");
}

TEST_F(EnergyFormattingTest, calorie_ascii_formatting_float)
{
    pkr::units::calorie_t<float> energy{100.0f};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "100 cal");
}

TEST_F(EnergyFormattingTest, kilocalorie_ascii_formatting_double)
{
    pkr::units::kilocalorie_t<double> energy{0.5};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "0.5 kcal");
}

TEST_F(EnergyFormattingTest, kilocalorie_ascii_formatting_float)
{
    pkr::units::kilocalorie_t<float> energy{0.5f};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "0.5 kcal");
}

TEST_F(EnergyFormattingTest, watthour_ascii_formatting_double)
{
    pkr::units::watt_hour_t<double> energy{100.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "100 Wh");
}

TEST_F(EnergyFormattingTest, watthour_ascii_formatting_float)
{
    pkr::units::watt_hour_t<float> energy{100.0f};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "100 Wh");
}

TEST_F(EnergyFormattingTest, kilowatthour_ascii_formatting_double)
{
    pkr::units::kilowatt_hour_t<double> energy{10.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "10 kWh");
}

TEST_F(EnergyFormattingTest, kilowatthour_ascii_formatting_float)
{
    pkr::units::kilowatt_hour_t<float> energy{10.0f};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "10 kWh");
}

TEST_F(EnergyFormattingTest, electronvolt_ascii_formatting_double)
{
    pkr::units::electronvolt_t<double> energy{1e6};
    std::string result = std::format("{:.1e}", energy);
    ASSERT_EQ(result, "1.0e+06 eV");
}

TEST_F(EnergyFormattingTest, electronvolt_ascii_formatting_float)
{
    pkr::units::electronvolt_t<float> energy{1e6f};
    std::string result = std::format("{:.1e}", energy);
    ASSERT_EQ(result, "1.0e+06 eV");
}

// ============================================================================
// Wide Character Formatting Tests - wchar_t - double
// ============================================================================

TEST_F(EnergyFormattingTest, joule_wide_formatting_double)
{
    pkr::units::joule_t<double> energy{1000.0};
    std::wstring result = std::format(L"{}", energy);
    ASSERT_EQ(result, L"1000 J");
}

TEST_F(EnergyFormattingTest, joule_wide_formatting_float)
{
    pkr::units::joule_t<float> energy{1000.0f};
    std::wstring result = std::format(L"{}", energy);
    ASSERT_EQ(result, L"1000 J");
}

TEST_F(EnergyFormattingTest, joule_wide_precision_double)
{
    pkr::units::joule_t<double> energy{1234.56789};
    std::wstring result = std::format(L"{:.2f}", energy);
    ASSERT_EQ(result, L"1234.57 J");
}

TEST_F(EnergyFormattingTest, joule_wide_precision_float)
{
    pkr::units::joule_t<float> energy{1234.56789f};
    std::wstring result = std::format(L"{:.2f}", energy);
    ASSERT_EQ(result, L"1234.57 J");
}

TEST_F(EnergyFormattingTest, kilocalorie_wide_formatting_double)
{
    pkr::units::kilocalorie_t<double> energy{0.5};
    std::wstring result = std::format(L"{}", energy);
    ASSERT_EQ(result, L"0.5 kcal");
}

TEST_F(EnergyFormattingTest, kilocalorie_wide_formatting_float)
{
    pkr::units::kilocalorie_t<float> energy{0.5f};
    std::wstring result = std::format(L"{}", energy);
    ASSERT_EQ(result, L"0.5 kcal");
}

// ============================================================================
// Edge Cases and Special Values
// ============================================================================

TEST_F(EnergyFormattingTest, zero_energy_formatting_double)
{
    pkr::units::joule_t<double> energy{0.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "0 J");
}

TEST_F(EnergyFormattingTest, zero_energy_formatting_float)
{
    pkr::units::joule_t<float> energy{0.0f};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "0 J");
}

TEST_F(EnergyFormattingTest, negative_energy_formatting_double)
{
    pkr::units::joule_t<double> energy{-500.0};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "-500 J");
}

TEST_F(EnergyFormattingTest, negative_energy_formatting_float)
{
    pkr::units::joule_t<float> energy{-500.0f};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "-500 J");
}

TEST_F(EnergyFormattingTest, very_small_energy_double)
{
    pkr::units::electronvolt_t<double> energy{1e-20};
    std::string result = std::format("{:.2e}", energy);
    ASSERT_EQ(result, "1.00e-20 eV");
}

TEST_F(EnergyFormattingTest, very_small_energy_float)
{
    pkr::units::electronvolt_t<float> energy{1e-20f};
    std::string result = std::format("{:.2e}", energy);
    ASSERT_EQ(result, "1.00e-20 eV");
}

TEST_F(EnergyFormattingTest, very_large_energy_double)
{
    pkr::units::gigajoule_t<double> energy{1e9};
    std::string result = std::format("{:.1e}", energy);
    ASSERT_EQ(result, "1.0e+09 GJ");
}

TEST_F(EnergyFormattingTest, very_large_energy_float)
{
    pkr::units::gigajoule_t<float> energy{1e9f};
    std::string result = std::format("{:.1e}", energy);
    ASSERT_EQ(result, "1.0e+09 GJ");
}

TEST_F(EnergyFormattingTest, default_precision_double)
{
    pkr::units::joule_t<double> energy{3.141592653589793};
    std::string result = std::format("{}", energy);
    std::string expected = std::format("{}", 3.141592653589793) + " J";
    ASSERT_EQ(result, expected);
}

TEST_F(EnergyFormattingTest, default_precision_float)
{
    pkr::units::joule_t<float> energy{3.141592653589793f};
    std::string result = std::format("{}", energy);
    std::string expected = std::format("{}", 3.141592653589793f) + " J";
    ASSERT_EQ(result, expected);
}

TEST_F(EnergyFormattingTest, value_preservation_double)
{
    pkr::units::joule_t<double> energy{123.456};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "123.456 J");
}

TEST_F(EnergyFormattingTest, value_preservation_float)
{
    pkr::units::joule_t<float> energy{123.456f};
    std::string result = std::format("{}", energy);
    ASSERT_EQ(result, "123.456 J");
}
