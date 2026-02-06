#include <gtest/gtest.h>
#include <pkr_units/format/si.h>
#include <format>
#include <pkr_units/units/derived/electrical.h>

using namespace ::testing;

class SiElectricalFormattingTest : public Test
{
};

// ============================================================================
// Electric Potential Formatting (ASCII)
// ============================================================================

TEST_F(SiElectricalFormattingTest, volt_ascii_formatting)
{
    pkr::units::volt_t<double> v{12.5};
    std::string result = std::format("{}", v);
    ASSERT_EQ(result, "12.5 V");
}

TEST_F(SiElectricalFormattingTest, kilovolt_ascii_formatting)
{
    pkr::units::kilovolt_t<double> kv{3.0};
    std::string result = std::format("{}", kv);
    ASSERT_EQ(result, "3 kV");
}

TEST_F(SiElectricalFormattingTest, microvolt_ascii_formatting)
{
    pkr::units::microvolt_t<double> uv{2.0};
    std::string result = std::format("{}", uv);
    ASSERT_EQ(result, "2 uV");
}

// ============================================================================
// Wide Character Formatting Tests - wchar_t
// ============================================================================

TEST_F(SiElectricalFormattingTest, volt_wide_formatting)
{
    pkr::units::volt_t<double> v{12.5};
    std::wstring result = std::format(L"{}", v);
    std::wstring expected = std::wstring(L"12.5 ") + std::wstring(pkr::units::volt_t<double>::w_symbol);
    ASSERT_EQ(result, expected);
}

TEST_F(SiElectricalFormattingTest, microvolt_wide_formatting)
{
    pkr::units::microvolt_t<double> uv{2.5};
    std::wstring result = std::format(L"{}", uv);
    std::wstring expected = std::wstring(L"2.5 ") + std::wstring(pkr::units::microvolt_t<double>::w_symbol);
    ASSERT_EQ(result, expected);
}

// ============================================================================
// Electric Charge Formatting (ASCII)
// ============================================================================

TEST_F(SiElectricalFormattingTest, coulomb_ascii_formatting)
{
    pkr::units::coulomb_t<double> c{5.0};
    std::string result = std::format("{}", c);
    ASSERT_EQ(result, "5 C");
}

TEST_F(SiElectricalFormattingTest, millicoulomb_ascii_formatting)
{
    pkr::units::millicoulomb_t<double> mc{1.5};
    std::string result = std::format("{}", mc);
    ASSERT_EQ(result, "1.5 mC");
}

TEST_F(SiElectricalFormattingTest, microcoulomb_ascii_formatting)
{
    pkr::units::microcoulomb_t<double> uc{7.0};
    std::string result = std::format("{}", uc);
    ASSERT_EQ(result, "7 uC");
}

// ============================================================================
// Capacitance Formatting (ASCII)
// ============================================================================

TEST_F(SiElectricalFormattingTest, farad_ascii_formatting)
{
    pkr::units::farad_t<double> f{10.0};
    std::string result = std::format("{}", f);
    ASSERT_EQ(result, "10 F");
}

TEST_F(SiElectricalFormattingTest, microfarad_ascii_formatting)
{
    pkr::units::microfarad_t<double> uf{22.0};
    std::string result = std::format("{}", uf);
    ASSERT_EQ(result, "22 uF");
}

TEST_F(SiElectricalFormattingTest, nanofarad_ascii_formatting)
{
    pkr::units::nanofarad_t<double> nf{47.0};
    std::string result = std::format("{}", nf);
    ASSERT_EQ(result, "47 nF");
}

// ============================================================================
// Conductance Formatting (ASCII)
// ============================================================================

TEST_F(SiElectricalFormattingTest, siemens_ascii_formatting)
{
    pkr::units::siemens_t<double> s{0.5};
    std::string result = std::format("{}", s);
    ASSERT_EQ(result, "0.5 S");
}

TEST_F(SiElectricalFormattingTest, microsiemens_ascii_formatting)
{
    pkr::units::microsiemens_t<double> us{12.0};
    std::string result = std::format("{}", us);
    ASSERT_EQ(result, "12 uS");
}

// ============================================================================
// Inductance Formatting (ASCII)
// ============================================================================

TEST_F(SiElectricalFormattingTest, henry_ascii_formatting)
{
    pkr::units::henry_t<double> h{3.0};
    std::string result = std::format("{}", h);
    ASSERT_EQ(result, "3 H");
}

TEST_F(SiElectricalFormattingTest, microhenry_ascii_formatting)
{
    pkr::units::microhenry_t<double> uh{15.0};
    std::string result = std::format("{}", uh);
    ASSERT_EQ(result, "15 uH");
}
