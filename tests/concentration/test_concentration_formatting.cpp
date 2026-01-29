#include <gtest/gtest.h>
#include <pkr_units/units/derived/concentration.h>
#include <pkr_units/si_units_formatting.h>
#include <format>
#include <string>

class SiConcentrationFormattingTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(SiConcentrationFormattingTest, mole_per_cubic_meter_ascii_formatting)
{
    pkr::units::mole_per_cubic_meter_concentration_t conc(1000.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "1000 mol/m^3");
}

TEST_F(SiConcentrationFormattingTest, mole_per_cubic_meter_wide_formatting)
{
    pkr::units::mole_per_cubic_meter_concentration_t conc(1000.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"1000 mol·m⁻³");
}

TEST_F(SiConcentrationFormattingTest, mole_per_liter_ascii_formatting)
{
    pkr::units::mole_per_liter_concentration_t conc(2.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "2 mol/L");
}

TEST_F(SiConcentrationFormattingTest, mole_per_liter_wide_formatting)
{
    pkr::units::mole_per_liter_concentration_t conc(2.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"2 mol·L⁻¹");
}

TEST_F(SiConcentrationFormattingTest, molar_ascii_formatting)
{
    pkr::units::molar_concentration_t conc(0.5);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "0.5 M");
}

TEST_F(SiConcentrationFormattingTest, molar_wide_formatting)
{
    pkr::units::molar_concentration_t conc(0.5);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"0.5 M");
}

TEST_F(SiConcentrationFormattingTest, millimolar_ascii_formatting)
{
    pkr::units::millimolar_concentration_t conc(100.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "100 mM");
}

TEST_F(SiConcentrationFormattingTest, millimolar_wide_formatting)
{
    pkr::units::millimolar_concentration_t conc(100.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"100 mM");
}

TEST_F(SiConcentrationFormattingTest, micromolar_ascii_formatting)
{
    pkr::units::micromolar_concentration_t conc(50.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "50 uM");
}

TEST_F(SiConcentrationFormattingTest, micromolar_wide_formatting)
{
    pkr::units::micromolar_concentration_t conc(50.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"50 µM");
}

TEST_F(SiConcentrationFormattingTest, nanomolar_ascii_formatting)
{
    pkr::units::nanomolar_concentration_t conc(25.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "25 nM");
}

TEST_F(SiConcentrationFormattingTest, nanomolar_wide_formatting)
{
    pkr::units::nanomolar_concentration_t conc(25.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"25 nM");
}

TEST_F(SiConcentrationFormattingTest, picomolar_ascii_formatting)
{
    pkr::units::picomolar_concentration_t conc(10.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "10 pM");
}

TEST_F(SiConcentrationFormattingTest, picomolar_wide_formatting)
{
    pkr::units::picomolar_concentration_t conc(10.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"10 pM");
}

TEST_F(SiConcentrationFormattingTest, osmole_per_liter_ascii_formatting)
{
    pkr::units::osmole_per_liter_concentration_t conc(0.3);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "0.3 Osm/L");
}

TEST_F(SiConcentrationFormattingTest, osmole_per_liter_wide_formatting)
{
    pkr::units::osmole_per_liter_concentration_t conc(0.3);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"0.3 Osm·L⁻¹");
}

TEST_F(SiConcentrationFormattingTest, milliosmole_per_liter_ascii_formatting)
{
    pkr::units::milliosmole_per_liter_concentration_t conc(300.0);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "300 mOsm/L");
}

TEST_F(SiConcentrationFormattingTest, milliosmole_per_liter_wide_formatting)
{
    pkr::units::milliosmole_per_liter_concentration_t conc(300.0);
    std::wstring formatted = std::format(L"{}", conc);
    EXPECT_EQ(formatted, L"300 mOsm·L⁻¹");
}

TEST_F(SiConcentrationFormattingTest, format_large_values)
{
    pkr::units::mole_per_cubic_meter_concentration_t conc(1e6);
    std::string formatted = std::format("{}", conc);
    EXPECT_EQ(formatted, "1e+06 mol/m^3");
}
