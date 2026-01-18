#include <gtest/gtest.h>
#include <si_units/standard/mass.h>

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
    si::gram g{250.0};
    ASSERT_DOUBLE_EQ(g.value(), 250.0);
}

TEST_F(SiMassTest, milligram_construction)
{
    si::milligram mg{500.0};
    ASSERT_DOUBLE_EQ(mg.value(), 500.0);
}

TEST_F(SiMassTest, microgram_construction)
{
    si::microgram ug{1000.0};
    ASSERT_DOUBLE_EQ(ug.value(), 1000.0);
}

TEST_F(SiMassTest, nanogram_construction)
{
    si::nanogram ng{100.0};
    ASSERT_DOUBLE_EQ(ng.value(), 100.0);
}

TEST_F(SiMassTest, megagram_construction)
{
    si::megagram mg{2.5};
    ASSERT_DOUBLE_EQ(mg.value(), 2.5);
}

// ============================================================================
// Copy and Move Tests
// ============================================================================

TEST_F(SiMassTest, copy_constructor)
{
    si::kilogram kg1{5.0};
    si::kilogram kg2 = kg1;
    ASSERT_DOUBLE_EQ(kg2.value(), 5.0);
}

TEST_F(SiMassTest, move_constructor)
{
    si::kilogram kg1{5.0};
    si::kilogram kg2 = std::move(kg1);
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
// Arithmetic Tests - Same Unit
// ============================================================================

TEST_F(SiMassTest, add_kilograms)
{
    si::kilogram kg1{3.0};
    si::kilogram kg2{2.0};
    auto result = kg1 + kg2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiMassTest, subtract_kilograms)
{
    si::kilogram kg1{5.0};
    si::kilogram kg2{2.0};
    auto result = kg1 - kg2;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiMassTest, add_grams)
{
    si::gram g1{500.0};
    si::gram g2{250.0};
    auto result = g1 + g2;
    ASSERT_DOUBLE_EQ(result.value(), 750.0);
}

TEST_F(SiMassTest, subtract_grams)
{
    si::gram g1{750.0};
    si::gram g2{250.0};
    auto result = g1 - g2;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

// ============================================================================
// Arithmetic Tests - Different Units (Same Dimension)
// ============================================================================

TEST_F(SiMassTest, add_kilogram_to_gram)
{
    si::kilogram kg{1.0};
    si::gram g{500.0};
    auto result = kg + g;
    // Result is in LHS type (kilogram)
    // 1kg + 0.5kg = 1.5kg
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiMassTest, add_gram_to_kilogram)
{
    si::gram g{500.0};
    si::kilogram kg{1.0};
    auto result = g + kg;
    // Result is in LHS type (gram)
    // 500g + 1000g = 1500g
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiMassTest, subtract_kilogram_from_gram)
{
    si::gram g{1500.0};
    si::kilogram kg{1.0};
    auto result = g - kg;
    // Result is in LHS type (gram)
    // 1500g - 1000g = 500g
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiMassTest, subtract_gram_from_kilogram)
{
    si::kilogram kg{2.0};
    si::gram g{500.0};
    auto result = kg - g;
    // Result is in LHS type (kilogram)
    // 2kg - 0.5kg = 1.5kg
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

// ============================================================================
// Scalar Multiplication and Division
// ============================================================================

TEST_F(SiMassTest, multiply_kilogram_by_scalar)
{
    si::kilogram kg{2.0};
    auto result = kg * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

TEST_F(SiMassTest, divide_kilogram_by_scalar)
{
    si::kilogram kg{6.0};
    auto result = kg / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiMassTest, divide_by_zero_scalar_throws)
{
    si::kilogram kg{5.0};
    ASSERT_THROW(kg / 0.0, std::invalid_argument);
}

TEST_F(SiMassTest, multiply_gram_by_scalar)
{
    si::gram g{100.0};
    auto result = g * 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiMassTest, divide_gram_by_scalar)
{
    si::gram g{500.0};
    auto result = g / 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 100.0);
}

// ============================================================================
// Mass Multiplication (Creates Derived Units)
// ============================================================================

TEST_F(SiMassTest, multiply_kilogram_by_kilogram)
{
    si::kilogram kg1{2.0};
    si::kilogram kg2{3.0};
    auto result = kg1 * kg2;
    // Result has mass dimension = 2 (kg²)
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
    ASSERT_EQ(decltype(result)::dimension::value.mass, 2);
}

// ============================================================================
// Mass Division (Creates Dimensionless)
// ============================================================================

TEST_F(SiMassTest, divide_kilogram_by_kilogram)
{
    si::kilogram kg1{10.0};
    si::kilogram kg2{2.0};
    auto result = kg1 / kg2;
    // Result is dimensionless (scalar)
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::dimension::value.mass, 0);
}

TEST_F(SiMassTest, divide_gram_by_gram)
{
    si::gram g1{500.0};
    si::gram g2{100.0};
    auto result = g1 / g2;
    // Result is dimensionless
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::dimension::value.mass, 0);
}

// ============================================================================
// Constexpr Tests
// ============================================================================

TEST_F(SiMassTest, constexpr_kilogram_addition)
{
    constexpr si::kilogram kg1{3.0};
    constexpr si::kilogram kg2{2.0};
    constexpr auto result = kg1 + kg2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiMassTest, constexpr_kilogram_multiplication)
{
    constexpr si::kilogram kg{2.0};
    constexpr auto result = kg * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST_F(SiMassTest, very_small_mass_values)
{
    si::nanogram ng{0.001};
    ASSERT_DOUBLE_EQ(ng.value(), 0.001);
}

TEST_F(SiMassTest, very_large_mass_values)
{
    si::megagram mg{1000000.0};
    ASSERT_DOUBLE_EQ(mg.value(), 1000000.0);
}

TEST_F(SiMassTest, add_very_different_scales)
{
    si::milligram mg{1.0};  // 1 milligram
    si::kilogram kg{1.0};   // 1 kilogram = 1000000 mg
    auto result = mg + kg;
    // Result is in LHS type (milligram)
    // 1 mg + 1000000 mg = 1000001 mg
    ASSERT_DOUBLE_EQ(result.value(), 1000001.0);
}

TEST_F(SiMassTest, subtract_resulting_in_negative)
{
    si::kilogram kg1{1.0};
    si::kilogram kg2{3.0};
    auto result = kg1 - kg2;
    ASSERT_DOUBLE_EQ(result.value(), -2.0);
}








