#include <gtest/gtest.h>
#include <format>
#include <ratio>
#include <string>
#include <pkr_units/si_units.h>
#include <pkr_units/si_formatting.h>
#include <pkr_units/impl/decls/unit_t_decl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/unit_formatting_traits.h>

// Test basic length unit formatting
TEST(FormattingTest, BasicLengthUnit)
{
    pkr::units::meter_t length{5.0};
    auto formatted = std::format("{}", length);
    EXPECT_EQ(formatted, "5 m");
}

// Test derived unit (velocity) formatting
TEST(FormattingTest, VelocityDerivedUnit)
{
    pkr::units::meter_t distance{10.0};
    pkr::units::second_t time{2.0};
    auto velocity = distance / time;
    auto formatted = std::format("{}", velocity);
    EXPECT_EQ(formatted, "5 m/s");
}

// Test precision control with format
TEST(FormattingTest, PrecisionControl)
{
    pkr::units::meter_t length{5.123456};
    auto formatted = std::format("{:.2}", length);
    EXPECT_EQ(formatted, "5.1 m");
}

// Test dimensionless quantity formatting
TEST(FormattingTest, DimensionlessQuantity)
{
    pkr::units::kilogram_t mass1{10.0};
    pkr::units::kilogram_t mass2{2.0};
    auto dimensionless = mass1 / mass2;
    auto formatted = std::format("{}", dimensionless);
    EXPECT_EQ(formatted, "5 ");
}

// Test complex derived unit (Force: kg·m·s⁻²)
TEST(FormattingTest, ComplexDerivedUnit)
{
    pkr::units::kilogram_t mass{5.0};
    pkr::units::meter_t distance{2.0};
    pkr::units::second_t time{1.0};

    auto force = mass * distance / (time * time);
    auto formatted = std::format("{}", force);
    EXPECT_EQ(formatted, "10 N");

    auto normalized_force = force.in_base_si_units();
    auto formatted_normalized = std::format("{}", normalized_force);
    EXPECT_EQ(formatted_normalized, "10 kg·m·s⁻²");
}

// Test different scales of same unit
TEST(FormattingTest, DifferentUnitScales)
{
    pkr::units::kilometer_t distance{100.0};
    auto formatted = std::format("{}", distance);
    EXPECT_EQ(formatted, "100 km");
}

// Test mass unit formatting
TEST(FormattingTest, MassUnit)
{
    pkr::units::kilogram_t mass{10.0};
    auto formatted = std::format("{}", mass);
    EXPECT_EQ(formatted, "10 kg");
}

// Test time unit formatting
TEST(FormattingTest, TimeUnit)
{
    pkr::units::second_t duration{30.0};
    auto formatted = std::format("{}", duration);
    EXPECT_EQ(formatted, "30 s");
}

// Test current unit formatting
TEST(FormattingTest, CurrentUnit)
{
    pkr::units::ampere_t current{2.5};
    auto formatted = std::format("{}", current);
    EXPECT_EQ(formatted, "2.5 A");
}

// Test temperature unit formatting
TEST(FormattingTest, TemperatureUnit)
{
    pkr::units::kelvin_t temperature{273.15};
    auto formatted = std::format("{}", temperature);
    EXPECT_EQ(formatted, "273.15 K");
}

// Test format with default precision
TEST(FormattingTest, DefaultPrecision)
{
    pkr::units::meter_t length{3.141592653589793};
    auto formatted = std::format("{}", length);
    EXPECT_EQ(formatted, "3.141592653589793 m");
}

// Test that formatting doesn't lose precision in the value
TEST(FormattingTest, ValuePreservation)
{
    pkr::units::meter_t length{123.456};
    auto formatted = std::format("{}", length);
    EXPECT_EQ(formatted, "123.456 m");
}

TEST(FormattingTest, WideLengthUnit)
{
    pkr::units::meter_t length{5.0};
    auto formatted = std::format(L"{}", length);
    EXPECT_EQ(formatted, L"5 m");
}

TEST(FormattingTest, BaseUnitFormatting)
{
    using base_length_t = pkr::units::details::unit_t<double, std::ratio<1, 1>, pkr::units::length_dimension>;
    base_length_t length{7.0};
    auto formatted = std::format("{}", length);
    EXPECT_EQ(formatted, "7 m");
}

TEST(FormattingTest, BaseUnitFormattingWide)
{
    using base_length_t = pkr::units::details::unit_t<double, std::ratio<1, 1>, pkr::units::length_dimension>;
    base_length_t length{7.0};
    auto formatted = std::format(L"{}", length);
    EXPECT_EQ(formatted, L"7 m");
}

TEST(FormattingTraitsTest, SuperscriptExponentPositive)
{
    auto exp = pkr::units::superscript_exponent<char>(2);
    ASSERT_FALSE(exp.empty());
    EXPECT_EQ(exp.front(), '^');
}

TEST(FormattingTraitsTest, SuperscriptExponentZero)
{
    auto exp = pkr::units::superscript_exponent<char>(0);
    EXPECT_TRUE(exp.empty());
}

TEST(FormattingTraitsTest, SuperscriptExponentNegative)
{
    auto exp = pkr::units::superscript_exponent<char>(-2);
    ASSERT_FALSE(exp.empty());
    EXPECT_NE(exp.front(), '^');
}

TEST(FormattingTraitsTest, SuperscriptDigitLookupDefault)
{
    auto valid = pkr::units::impl::superscript_digit_lookup<char>(2);
    EXPECT_FALSE(valid.empty());

    auto invalid = pkr::units::impl::superscript_digit_lookup<char>(10);
    EXPECT_TRUE(invalid.empty());
}

TEST(FormattingTraitsTest, CharTraitsDispatchChar)
{
    auto plus_minus = pkr::units::impl::char_traits_dispatch<char>::plus_minus();
    EXPECT_NE(plus_minus.find('+'), std::string_view::npos);
    EXPECT_NE(plus_minus.find('-'), std::string_view::npos);
    EXPECT_NE(plus_minus.find('/'), std::string_view::npos);
    EXPECT_FALSE(pkr::units::impl::char_traits_dispatch<char>::superscript_caret().empty());
}

TEST(FormattingTraitsTest, CharTraitsDispatchWchar)
{
    auto plus_minus = pkr::units::impl::char_traits_dispatch<wchar_t>::plus_minus();
    ASSERT_FALSE(plus_minus.empty());
    EXPECT_EQ(plus_minus.front(), L' ');
    EXPECT_EQ(plus_minus.back(), L' ');
}

TEST(FormattingTraitsTest, CharTraitsDispatchChar8)
{
    auto plus_minus = pkr::units::impl::char_traits_dispatch<char8_t>::plus_minus();
    ASSERT_FALSE(plus_minus.empty());
    EXPECT_EQ(plus_minus.front(), u8' ');
    EXPECT_EQ(plus_minus.back(), u8' ');
}

TEST(FormattingTraitsTest, BuildDimensionSymbolCharAndChar8)
{
    pkr::units::dimension_t dim{1, 1, -2, 0, 0, 0, 0, 0};
    auto symbol = pkr::units::build_dimension_symbol<char>(dim);
    EXPECT_NE(symbol.find("kg"), std::string::npos);
    EXPECT_NE(symbol.find("m"), std::string::npos);
    EXPECT_NE(symbol.find("s"), std::string::npos);

    auto symbol_u8 = pkr::units::build_dimension_symbol<char8_t>(dim);
    EXPECT_GT(symbol_u8.size(), 0U);
    EXPECT_NE(symbol_u8.find(u8"kg"), std::u8string::npos);
}

TEST(FormattingTraitsTest, BuildDimensionSymbolScalarIsEmpty)
{
    auto symbol = pkr::units::build_dimension_symbol<char>(pkr::units::scalar_dimension);
    EXPECT_TRUE(symbol.empty());

    auto w_symbol = pkr::units::build_dimension_symbol<wchar_t>(pkr::units::scalar_dimension);
    EXPECT_TRUE(w_symbol.empty());
}
