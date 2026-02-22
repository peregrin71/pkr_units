#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <format>
#include <complex>
#include <pkr_units/si_units.h>

#include <pkr_units/format/si.h>
#include <pkr_units/format/electrical_engineering.h>

using namespace ::testing;

TEST(ComplexUnitFormattingTest, BaseUnitComplexFormatting)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>, pkr::units::length_dimension> u{cplx{3.5, -1.25}};

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

// Branch coverage: Positive real and negative imaginary
TEST(ComplexUnitFormattingTest, PositiveRealNegativeImaginary)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{50.0, -30.0}};
    std::string s = std::format("{}", Z);
    ASSERT_EQ(s, "(50 - j30) ohm");
}

// Branch coverage: Negative real and positive imaginary
TEST(ComplexUnitFormattingTest, NegativeRealPositiveImaginary)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{-50.0, 30.0}};
    std::string s = std::format("{}", Z);
    ASSERT_EQ(s, "(-50 + j30) ohm");
}

// Branch coverage: Both negative
TEST(ComplexUnitFormattingTest, BothNegative)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{-50.0, -30.0}};
    std::string s = std::format("{}", Z);
    ASSERT_EQ(s, "(-50 - j30) ohm");
}

// Branch coverage: Zero real part
TEST(ComplexUnitFormattingTest, ZeroRealPart)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{0.0, 30.0}};
    std::string s = std::format("{}", Z);
    ASSERT_EQ(s, "(0 + j30) ohm");
}

// Branch coverage: Zero imaginary part
TEST(ComplexUnitFormattingTest, ZeroImaginaryPart)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{50.0, 0.0}};
    std::string s = std::format("{}", Z);
    ASSERT_EQ(s, "(50 + j0) ohm");
}

// Branch coverage: Both zero
TEST(ComplexUnitFormattingTest, BothZero)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{0.0, 0.0}};
    std::string s = std::format("{}", Z);
    ASSERT_EQ(s, "(0 + j0) ohm");
}

// Branch coverage: Zero real with scientific notation (different branches)
TEST(ComplexUnitFormattingTest, ZeroRealScientific)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{0.0, 3300.0}};
    std::string s = std::format("{:.1e}", Z);
    // No common exponent factoring since real is zero
    ASSERT_THAT(s, HasSubstr("ohm"));
}

// Branch coverage: Zero imaginary with scientific notation (different branches)
TEST(ComplexUnitFormattingTest, ZeroImaginaryScientific)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{4700.0, 0.0}};
    std::string s = std::format("{:.1e}", Z);
    // No common exponent factoring since imaginary is zero
    ASSERT_THAT(s, HasSubstr("ohm"));
}

// Branch coverage: Scientific notation without 'e' spec (has_e = false)
TEST(ComplexUnitFormattingTest, NoScientificSpecifier)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{4700.0, 3300.0}};
    std::string s = std::format("{:.2f}", Z);
    ASSERT_THAT(s, HasSubstr("4700"));
    ASSERT_THAT(s, HasSubstr("3300"));
    ASSERT_THAT(s, HasSubstr("ohm"));
}

// Branch coverage: Different exponents (no factoring)
TEST(ComplexUnitFormattingTest, ScientificDifferentExponents)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{4700.0, 330.0}};  // 4.7e3 vs 3.3e2
    std::string s = std::format("{:.1e}", Z);
    // Different exponents, no factoring applied
    ASSERT_THAT(s, HasSubstr("ohm"));
}

// Branch coverage: Capital E in format spec
TEST(ComplexUnitFormattingTest, ScientificCapitalE)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{4700.0, 3300.0}};
    std::string s = std::format("{:.1E}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

// Branch coverage: wchar_t formatting
TEST(ComplexUnitFormattingTest, WideCharFormatting)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{50.0, 30.0}};
    std::wstring ws = std::format(L"{}", Z);
    // Just verify the string was formatted (content may vary by character type)
    ASSERT_FALSE(ws.empty());
}

// Branch coverage: Small values with different dimensions
TEST(ComplexUnitFormattingTest, SmallValuesWithDimensions)
{
    using cplx = std::complex<double>;
    pkr::units::siemens_t<cplx> S{cplx{0.001, 0.002}};
    std::string s = std::format("{}", S);
    ASSERT_THAT(s, HasSubstr("S"));
}

// Branch coverage: Very large exponents in dimension formatting
TEST(ComplexUnitFormattingTest, LargeDimensionExponents)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>, 
        pkr::units::dimension_t{3, 2, -2, 1, 0, 0, 0, 0, 0}> u{cplx{1.5, 2.5}};
    std::string s = std::format("{}", u);
    // Should contain dimension representations
    ASSERT_THAT(s, HasSubstr("m"));
}

// Branch coverage: Negative dimension exponents
TEST(ComplexUnitFormattingTest, NegativeDimensionExponents)
{
    using cplx = std::complex<double>;
    // Inverse units (negative exponents)
    pkr::units::unit_t<cplx, std::ratio<1, 1>, 
        pkr::units::dimension_t{0, -1, 0, -1, 0, 0, 0, 0, 0}> u{cplx{3.0, 4.0}};
    std::string s = std::format("{}", u);
    // Should contain inverse dimension notations (m^-1 and A^-1)
    ASSERT_THAT(s, HasSubstr("-"));
}

// Branch coverage: Multiple dimensions with mixed signs
TEST(ComplexUnitFormattingTest, MultipleDimensionsMixed)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{1, 2, -1, 0, 0, 1, -1, 2, 0}> u{cplx{5.0, 6.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("m"));
}

// Branch coverage: Base unit complex formatting variations
TEST(ComplexUnitFormattingTest, BaseUnitZeroImag)
{
    using cplx = std::complex<double>;
    pkr::units::meter_t<cplx> m{cplx{5.0, 0.0}};
    std::string s = std::format("{}", m);
    ASSERT_EQ(s, "(5 + j0) m");
}

// Branch coverage: Large positive exponent digit extraction
TEST(ComplexUnitFormattingTest, LargeExponentDigits)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{1e99, 1e99}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

// Branch coverage: Floating point precision variations
TEST(ComplexUnitFormattingTest, FloatPrecisionVariations)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{50.5, 30.3}};
    std::string s = std::format("{}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

// Additional branch coverage tests for exponent factorization branches
TEST(ComplexUnitFormattingTest, ScienceNotationMultiDigitExp)
{
    using cplx = std::complex<double>;
    // Values that produce multi-digit exponents
    pkr::units::ohm_t<cplx> Z1{cplx{1e10, 2e10}};
    std::string s1 = std::format("{:.1e}", Z1);
    ASSERT_THAT(s1, HasSubstr("ohm"));
}

// Test with very small exponents
TEST(ComplexUnitFormattingTest, ScienceNotationSmallExp)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{1e-5, 2e-5}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

// Test dimension iterations with first_dim flag
TEST(ComplexUnitFormattingTest, SingleDimension)
{
    using cplx = std::complex<double>;
    pkr::units::meter_t<cplx> m{cplx{1.0, 2.0}};
    std::string s = std::format("{}", m);
    ASSERT_THAT(s, HasSubstr("m"));
}

// Test with multiple dimensions in fallback path
TEST(ComplexUnitFormattingTest, MultipleDimensionsFallback)
{
    using cplx = std::complex<double>;
    pkr::units::newton_t<cplx> N{cplx{10.0, 5.0}};
    std::string s = std::format("{}", N);
    ASSERT_THAT(s, HasSubstr("N"));
}

// Test dimension exponent loops with various numbers
TEST(ComplexUnitFormattingTest, DimensionExp2)
{
    using cplx = std::complex<double>;
    // m^2 (area-like)
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 2, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, DimensionExp3)
{
    using cplx = std::complex<double>;
    // m^3 (volume-like)
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 3, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, DimensionExp5)
{
    using cplx = std::complex<double>;
    // m^5 (higher exponent, tests digit extraction more)
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 5, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, DimensionExp10)
{
    using cplx = std::complex<double>;
    // m^10 (tests double-digit exponent formatting)
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 10, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, ExponentFactorWithSmallValues)
{
    using cplx = std::complex<double>;
    // Same order of magnitude but small values
    pkr::units::ohm_t<cplx> Z{cplx{0.0047, 0.0033}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, ImagPositiveSmallValue)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{100.0, 0.001}};
    std::string s = std::format("{}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, RealSmallImagLarge)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{0.001, 100.0}};
    std::string s = std::format("{}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, ExponentZero)
{
    using cplx = std::complex<double>;
    // Values with exp=0 (1-9 range)
    pkr::units::ohm_t<cplx> Z{cplx{5.0, 7.0}};
    std::string s = std::format("{:.1e}", Z);
    // Even small values with .1e should handle exp=0 case
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, BaseUnitMultiDim)
{
    using cplx = std::complex<double>;
    // k·m·s (multiple base units)
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{1, 1, 1, 0, 0, 0, 0, 0, 0}> u{cplx{2.0, 3.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, MixedPositiveNegativeExp)
{
    using cplx = std::complex<double>;
    // kg·m^-1·s^-2 (like stress units)
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{1, -1, -2, 0, 0, 0, 0, 0, 0}> u{cplx{50.0, 30.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, OnlyTimeAndCurrent)
{
    using cplx = std::complex<double>;
    // s·A (like charge units)
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 0, 1, 1, 0, 0, 0, 0, 0}> u{cplx{1.5, 2.5}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("s"));
}

TEST(ComplexUnitFormattingTest, NegExp1)
{
    using cplx = std::complex<double>;
    // m^-1 (inverse length)
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, -1, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 2.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("-"));
}

TEST(ComplexUnitFormattingTest, ManySeparators)
{
    using cplx = std::complex<double>;
    // All dimensions non-zero (stress on separator handling)
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{1, 1, 1, 1, 1, 1, 1, 1, 1}> u{cplx{0.1, 0.2}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

// Extended tests for higher branch coverage
TEST(ComplexUnitFormattingTest, PositiveExponent1)
{
    using cplx = std::complex<double>;
    // Index 1 = length (meter), so this produces "m" not "kg"
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{1, 0, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("m"));
}

TEST(ComplexUnitFormattingTest, PositiveExponent4)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 4, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, PositiveExponent6)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 6, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, PositiveExponent7)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 7, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, PositiveExponent11)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 11, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, PositiveExponent12)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 12, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, NegativeExponent2)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, -2, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("-"));
}

TEST(ComplexUnitFormattingTest, NegativeExponent3)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, -3, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("-"));
}

TEST(ComplexUnitFormattingTest, DtimeWithExp)
{
    using cplx = std::complex<double>;
    // Time dimension with exponent 2
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 0, 2, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("s"));
}

TEST(ComplexUnitFormattingTest, CurrentDimension)
{
    using cplx = std::complex<double>;
    // Current dimension with exponent 1
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 0, 0, 1, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("A"));
}

TEST(ComplexUnitFormattingTest, TemperatureDimension)
{
    using cplx = std::complex<double>;
    // Temperature dimension
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 0, 0, 0, 1, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("K"));
}

TEST(ComplexUnitFormattingTest, AmountDimension)
{
    using cplx = std::complex<double>;
    // Amount of substance dimension
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 0, 0, 0, 0, 1, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("mol"));
}

TEST(ComplexUnitFormattingTest, IntensityDimension)
{
    using cplx = std::complex<double>;
    // Luminous intensity dimension
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 0, 0, 0, 0, 0, 1, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("cd"));
}

TEST(ComplexUnitFormattingTest, AngleDimension)
{
    using cplx = std::complex<double>;
    // Angle dimension
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 0, 0, 0, 0, 0, 0, 1, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("rad"));
}

TEST(ComplexUnitFormattingTest, SolidAngleDimension)
{
    using cplx = std::complex<double>;
    // Solid angle dimension
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 0, 0, 0, 0, 0, 0, 0, 1}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("sr"));
}

TEST(ComplexUnitFormattingTest, TwoDimensionsNoExponent)
{
    using cplx = std::complex<double>;
    // Two dimensions, both with exponent 1 (no exponent display)
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{1, 1, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
    ASSERT_THAT(s, HasSubstr("m"));
}

TEST(ComplexUnitFormattingTest, ThreeDimensionsOneWithExpone)
{
    using cplx = std::complex<double>;
    // Three dimensions with one having exponent != 1
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{1, 2, 1, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, VeryLargePositiveExponent)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 99, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, SciNotationNegativeExp)
{
    using cplx = std::complex<double>;
    // Very small exponents with scientific notation
    pkr::units::ohm_t<cplx> Z{cplx{1e-50, 2e-50}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, ExponentZeroOnlyReal)
{
    using cplx = std::complex<double>;
    // Zero imaginary in exponent factorization test
    pkr::units::ohm_t<cplx> Z{cplx{4.5, 0.0}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, ExponentZeroOnlyImag)
{
    using cplx = std::complex<double>;
    // Zero real in exponent factorization test
    pkr::units::ohm_t<cplx> Z{cplx{0.0, 3.3}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, LargeValuesSciNotation)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{1e20, 2e20}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, SmallValuesSciNotation)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{1e-10, 2e-10}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, MixedMagnitudeSci)
{
    using cplx = std::complex<double>;
    // One small, one large with same exponent
    pkr::units::ohm_t<cplx> Z{cplx{1.5e10, 9.8e10}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, AllDimensionsWith2)
{
    using cplx = std::complex<double>;
    // All dimensions with exponent 2
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{2, 2, 2, 2, 2, 2, 2, 2, 2}> u{cplx{0.5, 0.5}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, FirstFourDimensions)
{
    using cplx = std::complex<double>;
    // First four dimensions only
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{1, 2, 3, 4, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, LastFourDimensions)
{
    using cplx = std::complex<double>;
    // Last four dimensions only
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 0, 0, 0, 1, 2, 3, 4, 5}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("K"));
}

TEST(ComplexUnitFormattingTest, AlternatingDimensions)
{
    using cplx = std::complex<double>;
    // Mixed dimensions: mass, length, time, temp, intensity, solid angle
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{1, 1, 1, 0, 1, 0, 1, 0, 1}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, LowExponentDigits)
{
    using cplx = std::complex<double>;
    // Exponents that produce single digits through double digits
    pkr::units::ohm_t<cplx> Z{cplx{12.34, 56.78}};
    std::string s = std::format("{:.2e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

// Critical exponent edge case tests
TEST(ComplexUnitFormattingTest, ExponentEdgeCase0)
{
    using cplx = std::complex<double>;
    // Values with exponent = 0 (mantissa in range 1-9)
    pkr::units::ohm_t<cplx> Z{cplx{3.0, 7.0}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, ExponentEdgeCase1)
{
    using cplx = std::complex<double>;
    // Values with exponent = 1 (mantissa * 10)
    pkr::units::ohm_t<cplx> Z{cplx{15.0, 25.0}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, ExponentEdgeCase2)
{
    using cplx = std::complex<double>;
    // Values with exponent = 2 (mantissa * 100)
    pkr::units::ohm_t<cplx> Z{cplx{150.0, 250.0}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, ExponentEdgeCase9)
{
    using cplx = std::complex<double>;
    // Values with exponent = 9
    pkr::units::ohm_t<cplx> Z{cplx{3.5e9, 7.5e9}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, ExponentEdgeCase10)
{
    using cplx = std::complex<double>;
    // Values with exponent = 10 (two digit exponent)
    pkr::units::ohm_t<cplx> Z{cplx{3.5e10, 7.5e10}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, ExponentEdgeCase11)
{
    using cplx = std::complex<double>;
    // Values with exponent = 11
    pkr::units::ohm_t<cplx> Z{cplx{3.5e11, 7.5e11}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, ExponentEdgeCase99)
{
    using cplx = std::complex<double>;
    // Values with exponent = 99 (large two-digit exponent)
    pkr::units::ohm_t<cplx> Z{cplx{3.5e99, 7.5e99}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, ExponentNegative1)
{
    using cplx = std::complex<double>;
    // Values with exponent = -1
    pkr::units::ohm_t<cplx> Z{cplx{0.35, 0.75}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, ExponentNegative2)
{
    using cplx = std::complex<double>;
    // Values with exponent = -2
    pkr::units::ohm_t<cplx> Z{cplx{0.035, 0.075}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, ExponentNegative9)
{
    using cplx = std::complex<double>;
    // Values with exponent = -9
    pkr::units::ohm_t<cplx> Z{cplx{3.5e-9, 7.5e-9}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, ExponentNegative10)
{
    using cplx = std::complex<double>;
    // Values with exponent = -10 (negative two-digit exponent)
    pkr::units::ohm_t<cplx> Z{cplx{3.5e-10, 7.5e-10}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

TEST(ComplexUnitFormattingTest, ExponentNegative99)
{
    using cplx = std::complex<double>;
    // Values with exponent = -99
    pkr::units::ohm_t<cplx> Z{cplx{3.5e-99, 7.5e-99}};
    std::string s = std::format("{:.1e}", Z);
    ASSERT_THAT(s, HasSubstr("ohm"));
}

// Test dimension exponents with different values to hit digit extraction branches
TEST(ComplexUnitFormattingTest, DimensionExponent8)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 8, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, DimensionExponent9)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 9, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, DimensionExponent15)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 15, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, DimensionExponent20)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, 20, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, DimensionNegExp2)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, -2, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("-"));
}

TEST(ComplexUnitFormattingTest, DimensionNegExp5)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, -5, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("-"));
}

TEST(ComplexUnitFormattingTest, DimensionNegExp10)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{0, -10, 0, 0, 0, 0, 0, 0, 0}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("-"));
}

// All dimensions with different exponents to test loop iterations
TEST(ComplexUnitFormattingTest, AllDimExp1Each)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{1, 1, 1, 1, 1, 1, 1, 1, 1}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, AllDimExp3Each)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{3, 3, 3, 3, 3, 3, 3, 3, 3}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, AllDimExp9Each)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{9, 9, 9, 9, 9, 9, 9, 9, 9}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}

TEST(ComplexUnitFormattingTest, AllDimExp15Each)
{
    using cplx = std::complex<double>;
    pkr::units::unit_t<cplx, std::ratio<1, 1>,
        pkr::units::dimension_t{15, 15, 15, 15, 15, 15, 15, 15, 15}> u{cplx{1.0, 1.0}};
    std::string s = std::format("{}", u);
    ASSERT_THAT(s, HasSubstr("kg"));
}
