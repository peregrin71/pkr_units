#include <gtest/gtest.h>
#include <format>
#include <complex>
#include <pkr_units/si_units.h>

#include <pkr_units/format/si.h>
#include <pkr_units/format/electrical_engineering.h>

using namespace ::testing;

TEST(ComplexUnitFormattingTest, BaseUnitComplexFormatting)
{
    using cplx = std::complex<double>;
    pkr::units::details::unit_t<cplx, std::ratio<1, 1>, pkr::units::length_dimension> u{cplx{3.5, -1.25}};

    std::string s = std::format("{}", u);
    ASSERT_EQ(s, "(3.5 - j1.25) m");

    std::wstring ws = std::format(L"{}", u);
    ASSERT_EQ(ws, L"(3.5 - j1.25) m");
}

TEST(ComplexUnitFormattingTest, DerivedUnitComplexFormatting)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{50.0, 30.0}};
    std::string s = std::format("{}", Z);
    ASSERT_EQ(s, "(50 + j30) ohm");

    std::wstring ws = std::format(L"{}", Z);
    ASSERT_EQ(ws, L"(50 + j30) \u03a9");
}

TEST(ComplexUnitFormattingTest, ScientificFactorCommonExponent)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{4700.0, 3300.0}};

    std::string s = std::format("{:.1e}", Z);
    // Expect: (4.7 + j3.3) x10^3 ohm (ASCII format for char type)
    ASSERT_EQ(s, "(4.7 + j3.3) x10^3 ohm");
}
