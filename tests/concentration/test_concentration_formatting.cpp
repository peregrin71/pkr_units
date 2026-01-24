#include <gtest/gtest.h>
#include <pkr_units/units/derived/concentration.h>
#include <format>
#include <string>

class SiConcentrationFormattingTest : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(SiConcentrationFormattingTest, format_kilogram_per_cubic_meter_ascii)
{
    kilogram_per_cubic_meter_t conc(1000.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "1000 kg/m^3");
}

TEST_F(SiConcentrationFormattingTest, format_kilogram_per_cubic_meter_wide)
{
    kilogram_per_cubic_meter_t conc(1000.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"1000 kg/m³");
}

TEST_F(SiConcentrationFormattingTest, format_kilogram_per_cubic_meter_utf8)
{
    kilogram_per_cubic_meter_t conc(1000.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "1000 kg/m³");
}

TEST_F(SiConcentrationFormattingTest, format_gram_per_liter_ascii)
{
    gram_per_liter_t conc(50.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "50 g/L");
}

TEST_F(SiConcentrationFormattingTest, format_gram_per_liter_wide)
{
    gram_per_liter_t conc(50.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"50 g/L");
}

TEST_F(SiConcentrationFormattingTest, format_gram_per_liter_utf8)
{
    gram_per_liter_t conc(50.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "50 g/L");
}

TEST_F(SiConcentrationFormattingTest, format_milligram_per_liter_ascii)
{
    milligram_per_liter_t conc(100.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "100 mg/L");
}

TEST_F(SiConcentrationFormattingTest, format_milligram_per_liter_wide)
{
    milligram_per_liter_t conc(100.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"100 mg/L");
}

TEST_F(SiConcentrationFormattingTest, format_milligram_per_liter_utf8)
{
    milligram_per_liter_t conc(100.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "100 mg/L");
}

TEST_F(SiConcentrationFormattingTest, format_microgram_per_liter_ascii)
{
    microgram_per_liter_t conc(10.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "10 µg/L");
}

TEST_F(SiConcentrationFormattingTest, format_microgram_per_liter_wide)
{
    microgram_per_liter_t conc(10.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"10 µg/L");
}

TEST_F(SiConcentrationFormattingTest, format_microgram_per_liter_utf8)
{
    microgram_per_liter_t conc(10.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "10 µg/L");
}

TEST_F(SiConcentrationFormattingTest, format_parts_per_million_ascii)
{
    parts_per_million_t conc(5.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "5 ppm");
}

TEST_F(SiConcentrationFormattingTest, format_parts_per_million_wide)
{
    parts_per_million_t conc(5.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"5 ppm");
}

TEST_F(SiConcentrationFormattingTest, format_parts_per_million_utf8)
{
    parts_per_million_t conc(5.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "5 ppm");
}

TEST_F(SiConcentrationFormattingTest, format_parts_per_billion_ascii)
{
    parts_per_billion_t conc(1.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "1 ppb");
}

TEST_F(SiConcentrationFormattingTest, format_parts_per_billion_wide)
{
    parts_per_billion_t conc(1.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"1 ppb");
}

TEST_F(SiConcentrationFormattingTest, format_parts_per_billion_utf8)
{
    parts_per_billion_t conc(1.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "1 ppb");
}

TEST_F(SiConcentrationFormattingTest, format_molar_ascii)
{
    molar conc(0.5);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "0.5 M");
}

TEST_F(SiConcentrationFormattingTest, format_molar_wide)
{
    molar conc(0.5);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"0.5 M");
}

TEST_F(SiConcentrationFormattingTest, format_molar_utf8)
{
    molar conc(0.5);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "0.5 M");
}

TEST_F(SiConcentrationFormattingTest, format_millimolar_ascii)
{
    millimolar conc(100.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "100 mM");
}

TEST_F(SiConcentrationFormattingTest, format_millimolar_wide)
{
    millimolar conc(100.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"100 mM");
}

TEST_F(SiConcentrationFormattingTest, format_millimolar_utf8)
{
    millimolar conc(100.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "100 mM");
}

TEST_F(SiConcentrationFormattingTest, format_micromolar_ascii)
{
    micromolar conc(50.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "50 µM");
}

TEST_F(SiConcentrationFormattingTest, format_micromolar_wide)
{
    micromolar conc(50.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"50 µM");
}

TEST_F(SiConcentrationFormattingTest, format_micromolar_utf8)
{
    micromolar conc(50.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "50 µM");
}

TEST_F(SiConcentrationFormattingTest, format_nanomolar_ascii)
{
    nanomolar conc(25.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "25 nM");
}

TEST_F(SiConcentrationFormattingTest, format_nanomolar_wide)
{
    nanomolar conc(25.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"25 nM");
}

TEST_F(SiConcentrationFormattingTest, format_nanomolar_utf8)
{
    nanomolar conc(25.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "25 nM");
}

TEST_F(SiConcentrationFormattingTest, format_picomolar_ascii)
{
    picomolar conc(10.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "10 pM");
}

TEST_F(SiConcentrationFormattingTest, format_picomolar_wide)
{
    picomolar conc(10.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"10 pM");
}

TEST_F(SiConcentrationFormattingTest, format_picomolar_utf8)
{
    picomolar conc(10.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "10 pM");
}

TEST_F(SiConcentrationFormattingTest, format_osmole_per_liter_ascii)
{
    osmole_per_liter conc(0.3);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "0.3 Osm/L");
}

TEST_F(SiConcentrationFormattingTest, format_osmole_per_liter_wide)
{
    osmole_per_liter conc(0.3);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"0.3 Osm/L");
}

TEST_F(SiConcentrationFormattingTest, format_osmole_per_liter_utf8)
{
    osmole_per_liter conc(0.3);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "0.3 Osm/L");
}

TEST_F(SiConcentrationFormattingTest, format_milliosmole_per_liter_ascii)
{
    milliosmole_per_liter conc(300.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "300 mOsm/L");
}

TEST_F(SiConcentrationFormattingTest, format_milliosmole_per_liter_wide)
{
    milliosmole_per_liter conc(300.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"300 mOsm/L");
}

TEST_F(SiConcentrationFormattingTest, format_milliosmole_per_liter_utf8)
{
    milliosmole_per_liter conc(300.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "300 mOsm/L");
}

TEST_F(SiConcentrationFormattingTest, format_with_precision)
{
    kilogram_per_cubic_meter_t conc(1000.123456);
    std::string formatted = std::format("{:.2f}", conc);
    EXPECT_EQ(formatted, "1000.12 kg/m^3");
}

TEST_F(SiConcentrationFormattingTest, format_small_values)
{
    microgram_per_liter_t conc(1e-6);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "0.000001 µg/L");
}

TEST_F(SiConcentrationFormattingTest, format_large_values)
{
    kilogram_per_cubic_meter_t conc(1e6);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "1000000 kg/m^3");
}