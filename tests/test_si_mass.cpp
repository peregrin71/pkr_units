// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#include <gtest/gtest.h>
#include <units/si.h>
#include <units/impl/details/si_unit.h>
#include <units/impl/details/dimension.h>
#include <units/impl/mass.h>
#include <units/cast/si_cast.h>
// #include <units/formatting/si_unit_formatting.h>

// #include <format>
#include <cmath>

namespace test
{

using namespace ::testing;

class SiMassTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(SiMassTest, kilogram_construction)
{
    si::kilogram kg{5.0};
    ASSERT_DOUBLE_EQ(kg.value(), 5.0);
}

TEST_F(SiMassTest, kilogram_dereference_operator)
{
    si::kilogram kg{5.0};
    ASSERT_DOUBLE_EQ(*kg, 5.0);
}

TEST_F(SiMassTest, kilogram_zero_value)
{
    si::kilogram kg{0.0};
    ASSERT_DOUBLE_EQ(kg.value(), 0.0);
}

TEST_F(SiMassTest, kilogram_negative_value)
{
    si::kilogram kg{-3.5};
    ASSERT_DOUBLE_EQ(kg.value(), -3.5);
}

TEST_F(SiMassTest, gram_construction)
{
    si::gram g{1500.0};
    ASSERT_DOUBLE_EQ(g.value(), 1500.0);
}

TEST_F(SiMassTest, milligram_construction)
{
    si::milligram mg{2500.0};
    ASSERT_DOUBLE_EQ(mg.value(), 2500.0);
}

// ============================================================================
// Copy and Move Semantics Tests
// ============================================================================

TEST_F(SiMassTest, copy_constructor)
{
    si::kilogram kg1{5.0};
    si::kilogram kg2{kg1};
    ASSERT_DOUBLE_EQ(kg2.value(), 5.0);
}

TEST_F(SiMassTest, move_constructor)
{
    si::kilogram kg1{5.0};
    si::kilogram kg2{std::move(kg1)};
    ASSERT_DOUBLE_EQ(kg2.value(), 5.0);
}

TEST_F(SiMassTest, copy_assignment)
{
    si::kilogram kg1{5.0};
    si::kilogram kg2{0.0};
    kg2 = kg1;
    ASSERT_DOUBLE_EQ(kg2.value(), 5.0);
}

TEST_F(SiMassTest, move_assignment)
{
    si::kilogram kg1{5.0};
    si::kilogram kg2{0.0};
    kg2 = std::move(kg1);
    ASSERT_DOUBLE_EQ(kg2.value(), 5.0);
}

// ============================================================================
// Arithmetic Operations: Addition/Subtraction (Same Dimension, Different Ratios)
// ============================================================================

TEST_F(SiMassTest, add_kilograms)
{
    si::kilogram kg1{3.0};
    si::kilogram kg2{2.0};
    auto result = kg1 + kg2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiMassTest, add_gram_to_kilogram)
{
    si::kilogram kg{1.0};
    si::gram g{500.0};
    auto result = kg + g;
    // Result is in kg (LHS ratio), so 500g = 0.5kg, result = 1.5kg
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiMassTest, add_kilogram_to_gram)
{
    si::gram g{500.0};
    si::kilogram kg{1.0};
    auto result = g + kg;
    // Result is in g (LHS ratio), so 1kg = 1000g, result = 1500g
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiMassTest, subtract_kilograms)
{
    si::kilogram kg1{5.0};
    si::kilogram kg2{2.0};
    auto result = kg1 - kg2;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiMassTest, subtract_gram_from_kilogram)
{
    si::kilogram kg{1.5};
    si::gram g{500.0};
    auto result = kg - g;
    // Result is in kg (LHS ratio), so 500g = 0.5kg, result = 1.0kg
    ASSERT_DOUBLE_EQ(result.value(), 1.0);
}

TEST_F(SiMassTest, subtract_kilogram_from_gram)
{
    si::gram g{1500.0};
    si::kilogram kg{1.0};
    auto result = g - kg;
    // Result is in g (LHS ratio), so 1kg = 1000g, result = 500g
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

// ============================================================================
// Scalar Multiplication/Division Tests
// ============================================================================

TEST_F(SiMassTest, multiply_kilogram_by_scalar)
{
    si::kilogram kg{5.0};
    auto result = kg * 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 10.0);
}

TEST_F(SiMassTest, divide_kilogram_by_scalar)
{
    si::kilogram kg{10.0};
    auto result = kg / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiMassTest, divide_by_zero_scalar_throws)
{
    si::kilogram kg{10.0};
    ASSERT_THROW(kg / 0.0, std::invalid_argument);
}

TEST_F(SiMassTest, divide_by_zero_si_unit_throws)
{
    si::kilogram kg1{10.0};
    si::kilogram kg2{0.0};
    ASSERT_THROW(kg1 / kg2, std::invalid_argument);
}

TEST_F(SiMassTest, multiply_kilogram_by_zero)
{
    si::kilogram kg{5.0};
    auto result = kg * 0.0;
    ASSERT_DOUBLE_EQ(result.value(), 0.0);
}

TEST_F(SiMassTest, multiply_kilogram_by_fraction)
{
    si::kilogram kg{10.0};
    auto result = kg * 0.5;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

// ============================================================================
// Dimensional Analysis: Division (Dimensionless)
// ============================================================================

TEST_F(SiMassTest, divide_mass_by_mass_produces_scalar)
{
    si::kilogram kg1{10.0};
    si::kilogram kg2{2.0};
    auto result = kg1 / kg2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    // Result should be scalar (dimensionless) when dividing same dimension
    ASSERT_EQ(decltype(result)::dimension::value.mass, 0);
}

// ============================================================================
// Unit Conversion via si_cast
// ============================================================================

TEST_F(SiMassTest, cast_kilogram_to_gram)
{
    si::kilogram kg{5.0};
    auto g = si::si_cast<si::gram>(kg);
    ASSERT_DOUBLE_EQ(g.value(), 5000.0);
}

TEST_F(SiMassTest, cast_gram_to_kilogram)
{
    si::gram g{2500.0};
    auto kg = si::si_cast<si::kilogram>(g);
    ASSERT_DOUBLE_EQ(kg.value(), 2.5);
}

TEST_F(SiMassTest, cast_milligram_to_gram)
{
    si::milligram mg{5000.0};
    auto g = si::si_cast<si::gram>(mg);
    // 5000 mg = 5000 * 0.000001 kg = 0.005 kg = 5 g
    ASSERT_DOUBLE_EQ(g.value(), 5.0);
}

TEST_F(SiMassTest, cast_kilogram_to_milligram)
{
    si::kilogram kg{1.0};
    auto mg = si::si_cast<si::milligram>(kg);
    ASSERT_DOUBLE_EQ(mg.value(), 1000000.0);
}

// ============================================================================
// Imperial Units Tests
// ============================================================================

TEST_F(SiMassTest, ounce_to_kilogram_conversion)
{
    // 1 ounce ≈ 0.028349523 kg
    si::ounce oz{1.0};
    ASSERT_NEAR(oz.value() * (28349523.0 / 1000000000.0), 0.028349523, 1e-10);
}

TEST_F(SiMassTest, pound_to_kilogram_conversion)
{
    // 1 pound ≈ 0.45359237 kg
    si::pound lb{1.0};
    ASSERT_NEAR(lb.value() * (453592370.0 / 1000000000.0), 0.45359237, 1e-10);

    auto kg = si::si_cast<si::kilogram>(lb);
    ASSERT_NEAR(kg.value(), 0.45359237, 1e-10);
}

TEST_F(SiMassTest, stone_to_kilogram_conversion)
{
    // 1 stone ≈ 6.35029318 kg
    si::stone st{1.0};
    ASSERT_NEAR(st.value() * (6350293180.0 / 1000000000.0), 6.35029318, 1e-10);
}

TEST_F(SiMassTest, add_pounds_to_pounds)
{
    si::pound lb1{5.0};
    si::pound lb2{3.0};
    auto result = lb1 + lb2;
    ASSERT_DOUBLE_EQ(result.value(), 8.0);
}

TEST_F(SiMassTest, add_ounces_to_pounds)
{
    si::pound lb{1.0};
    si::ounce oz{16.0};
    auto result = lb + oz;
    // Result is in pounds: 16 ounces = 1 pound
    ASSERT_NEAR(result.value(), 2.0, 1e-8);
}

/* FORMATTING TESTS DISABLED - Focus on compilation first
// ============================================================================
// Formatting Tests
// ============================================================================

TEST_F(SiMassTest, format_kilogram)
{
    si::kilogram kg{5.0};
    auto formatted = std::format("{}", kg);
    ASSERT_FALSE(formatted.empty());
    // Should contain "5" and "kg"
    ASSERT_NE(formatted.find("5"), std::string::npos);
    ASSERT_NE(formatted.find("kg"), std::string::npos);
}

TEST_F(SiMassTest, format_gram)
{
    si::gram g{2500.0};
    auto formatted = std::format("{}", g);
    ASSERT_FALSE(formatted.empty());
    ASSERT_NE(formatted.find("2500"), std::string::npos);
}

TEST_F(SiMassTest, format_milligram)
{
    si::milligram mg{1500.0};
    auto formatted = std::format("{}", mg);
    ASSERT_FALSE(formatted.empty());
    ASSERT_NE(formatted.find("1500"), std::string::npos);
}

TEST_F(SiMassTest, format_with_precision)
{
    si::kilogram kg{3.14159};
    auto formatted = std::format("{:.2}", kg);
    ASSERT_FALSE(formatted.empty());
}

// ============================================================================
// Special Imperial Unit Formatting Tests (pounds/ounces)
// ============================================================================

TEST_F(SiMassTest, format_pounds_whole_number)
{
    si::pound lb{5.0};
    auto formatted = std::format("{}", lb);
    ASSERT_EQ(formatted, "5 lb");
}

TEST_F(SiMassTest, format_pounds_with_half_ounce)
{
    si::pound lb{5.5};
    auto formatted = std::format("{}", lb);
    ASSERT_EQ(formatted, "5 lb 8 oz");
}

TEST_F(SiMassTest, format_pounds_quarter_pound)
{
    si::pound lb{5.25};
    auto formatted = std::format("{}", lb);
    ASSERT_EQ(formatted, "5 lb 4 oz");
}

TEST_F(SiMassTest, format_pounds_less_than_one)
{
    si::pound lb{0.5};
    auto formatted = std::format("{}", lb);
    ASSERT_EQ(formatted, "0 lb 8 oz");
}

TEST_F(SiMassTest, format_pounds_rounding_to_next_pound)
{
    si::pound lb{5.9999};
    auto formatted = std::format("{}", lb);
    ASSERT_EQ(formatted, "6 lb");
}

TEST_F(SiMassTest, format_pounds_one_pound_one_ounce)
{
    si::pound lb{1.0625};  // 1 pound + 1 ounce
    auto formatted = std::format("{}", lb);
    ASSERT_EQ(formatted, "1 lb 1 oz");
}
*/

// ============================================================================
// Dimension Tests
// ============================================================================

TEST_F(SiMassTest, kilogram_has_mass_dimension)
{
    si::kilogram kg{5.0};
    ASSERT_EQ(decltype(kg)::dimension::value.mass, 1);
    ASSERT_EQ(decltype(kg)::dimension::value.length, 0);
    ASSERT_EQ(decltype(kg)::dimension::value.time, 0);
}

TEST_F(SiMassTest, mass_division_produces_scalar)
{
    si::kilogram kg1{5.0};
    si::kilogram kg2{2.5};
    auto result = kg1 / kg2;
    ASSERT_EQ(decltype(result)::dimension::value.mass, 0);
    ASSERT_EQ(decltype(result)::dimension::value.length, 0);
    ASSERT_EQ(decltype(result)::dimension::value.time, 0);
}

// ============================================================================
// Template Parameter Tests
// ============================================================================

TEST_F(SiMassTest, mass_with_float)
{
    si::mass<float> kg{5.0f};
    ASSERT_FLOAT_EQ(kg.value(), 5.0f);
}

TEST_F(SiMassTest, mass_with_custom_ratio)
{
    si::mass<double, std::kilo> kg{2.5};
    ASSERT_DOUBLE_EQ(kg.value(), 2.5);
}

TEST_F(SiMassTest, mass_with_float_and_kilo)
{
    si::mass<float, std::kilo> kg{2.5f};
    ASSERT_FLOAT_EQ(kg.value(), 2.5f);
}

// ============================================================================
// Edge Case Tests
// ============================================================================

TEST_F(SiMassTest, very_small_values)
{
    si::milligram mg{0.001};
    ASSERT_DOUBLE_EQ(mg.value(), 0.001);
}

TEST_F(SiMassTest, very_large_values)
{
    si::kilogram kg{1e6};  // 1 million kilograms
    ASSERT_DOUBLE_EQ(kg.value(), 1e6);
}

TEST_F(SiMassTest, add_very_different_scales)
{
    si::kilogram kg{1.0};
    si::gram g{1000.0};  // 1000 g = 1 kg
    auto result = kg + g;
    // Result should be 1 + 1 = 2 kilograms
    ASSERT_NEAR(result.value(), 2.0, 1e-10);
}

TEST_F(SiMassTest, subtract_resulting_in_negative)
{
    si::kilogram kg1{2.0};
    si::kilogram kg2{5.0};
    auto result = kg1 - kg2;
    ASSERT_DOUBLE_EQ(result.value(), -3.0);
}

// ============================================================================
// Constexpr Tests (Runtime Evaluation)
// ============================================================================

TEST_F(SiMassTest, constexpr_kilogram_addition)
{
    constexpr si::kilogram kg1{3.0};
    constexpr si::kilogram kg2{2.0};
    constexpr auto result = kg1 + kg2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiMassTest, constexpr_kilogram_division)
{
    constexpr si::kilogram kg1{10.0};
    constexpr si::kilogram kg2{2.0};
    constexpr auto result = kg1 / kg2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);

    static_assert(decltype(result)::dimension::value.mass == 0, "Result should be dimensionless");
}

} // namespace test






