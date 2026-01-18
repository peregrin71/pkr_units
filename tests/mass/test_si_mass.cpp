#include <gtest/gtest.h>
#include <pkr_units/standard/mass.h>

using namespace ::testing;

class SiMassTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(SiMassTest, kilogram_construction)
{
    pkr::units::kilogram_t kg{5.0};
    ASSERT_DOUBLE_EQ(kg.value(), 5.0);
}

TEST_F(SiMassTest, kilogram_dereference_operator)
{
    pkr::units::kilogram_t kg{5.0};
    ASSERT_DOUBLE_EQ(*kg, 5.0);
}

TEST_F(SiMassTest, kilogram_zero_value)
{
    pkr::units::kilogram_t kg{0.0};
    ASSERT_DOUBLE_EQ(kg.value(), 0.0);
}

TEST_F(SiMassTest, kilogram_negative_value)
{
    pkr::units::kilogram_t kg{-3.5};
    ASSERT_DOUBLE_EQ(kg.value(), -3.5);
}

TEST_F(SiMassTest, gram_construction)
{
    pkr::units::gram_t g{250.0};
    ASSERT_DOUBLE_EQ(g.value(), 250.0);
}

TEST_F(SiMassTest, milligram_construction)
{
    pkr::units::milligram_t mg{500.0};
    ASSERT_DOUBLE_EQ(mg.value(), 500.0);
}

TEST_F(SiMassTest, microgram_construction)
{
    pkr::units::microgram_t ug{1000.0};
    ASSERT_DOUBLE_EQ(ug.value(), 1000.0);
}

TEST_F(SiMassTest, nanogram_construction)
{
    pkr::units::nanogram_t ng{100.0};
    ASSERT_DOUBLE_EQ(ng.value(), 100.0);
}

TEST_F(SiMassTest, megagram_construction)
{
    pkr::units::megagram_t mg{2.5};
    ASSERT_DOUBLE_EQ(mg.value(), 2.5);
}

// ============================================================================
// Copy and Move Tests
// ============================================================================

TEST_F(SiMassTest, copy_constructor)
{
    pkr::units::kilogram_t kg1{5.0};
    pkr::units::kilogram_t kg2 = kg1;
    ASSERT_DOUBLE_EQ(kg2.value(), 5.0);
}

TEST_F(SiMassTest, move_constructor)
{
    pkr::units::kilogram_t kg1{5.0};
    pkr::units::kilogram_t kg2 = std::move(kg1);
    ASSERT_DOUBLE_EQ(kg2.value(), 5.0);
}

TEST_F(SiMassTest, copy_assignment)
{
    pkr::units::kilogram_t kg1{5.0};
    pkr::units::kilogram_t kg2{0.0};
    kg2 = kg1;
    ASSERT_DOUBLE_EQ(kg2.value(), 5.0);
}

TEST_F(SiMassTest, move_assignment)
{
    pkr::units::kilogram_t kg1{5.0};
    pkr::units::kilogram_t kg2{0.0};
    kg2 = std::move(kg1);
    ASSERT_DOUBLE_EQ(kg2.value(), 5.0);
}

// ============================================================================
// Arithmetic Tests - Same Unit
// ============================================================================

TEST_F(SiMassTest, add_kilograms)
{
    pkr::units::kilogram_t kg1{3.0};
    pkr::units::kilogram_t kg2{2.0};
    auto result = kg1 + kg2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiMassTest, subtract_kilograms)
{
    pkr::units::kilogram_t kg1{5.0};
    pkr::units::kilogram_t kg2{2.0};
    auto result = kg1 - kg2;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiMassTest, add_grams)
{
    pkr::units::gram_t g1{500.0};
    pkr::units::gram_t g2{250.0};
    auto result = g1 + g2;
    ASSERT_DOUBLE_EQ(result.value(), 750.0);
}

TEST_F(SiMassTest, subtract_grams)
{
    pkr::units::gram_t g1{750.0};
    pkr::units::gram_t g2{250.0};
    auto result = g1 - g2;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

// ============================================================================
// Arithmetic Tests - Different Units (Same Dimension)
// ============================================================================

TEST_F(SiMassTest, add_kilogram_to_gram)
{
    pkr::units::kilogram_t kg{1.0};
    pkr::units::gram_t g{500.0};
    auto result = kg + g;
    // Result is in LHS type (kilogram)
    // 1kg + 0.5kg = 1.5kg
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiMassTest, add_gram_to_kilogram)
{
    pkr::units::gram_t g{500.0};
    pkr::units::kilogram_t kg{1.0};
    auto result = g + kg;
    // Result is in LHS type (gram)
    // 500g + 1000g = 1500g
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiMassTest, subtract_kilogram_from_gram)
{
    pkr::units::gram_t g{1500.0};
    pkr::units::kilogram_t kg{1.0};
    auto result = g - kg;
    // Result is in LHS type (gram)
    // 1500g - 1000g = 500g
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiMassTest, subtract_gram_from_kilogram)
{
    pkr::units::kilogram_t kg{2.0};
    pkr::units::gram_t g{500.0};
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
    pkr::units::kilogram_t kg{2.0};
    auto result = kg * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

TEST_F(SiMassTest, divide_kilogram_by_scalar)
{
    pkr::units::kilogram_t kg{6.0};
    auto result = kg / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiMassTest, divide_by_zero_scalar_throws)
{
    pkr::units::kilogram_t kg{5.0};
    ASSERT_THROW(kg / 0.0, std::invalid_argument);
}

TEST_F(SiMassTest, multiply_gram_by_scalar)
{
    pkr::units::gram_t g{100.0};
    auto result = g * 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiMassTest, divide_gram_by_scalar)
{
    pkr::units::gram_t g{500.0};
    auto result = g / 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 100.0);
}

// ============================================================================
// Mass Multiplication (Creates Derived Units)
// ============================================================================

TEST_F(SiMassTest, multiply_kilogram_by_kilogram)
{
    pkr::units::kilogram_t kg1{2.0};
    pkr::units::kilogram_t kg2{3.0};
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
    pkr::units::kilogram_t kg1{10.0};
    pkr::units::kilogram_t kg2{2.0};
    auto result = kg1 / kg2;
    // Result is dimensionless (scalar)
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::dimension::value.mass, 0);
}

TEST_F(SiMassTest, divide_gram_by_gram)
{
    pkr::units::gram_t g1{500.0};
    pkr::units::gram_t g2{100.0};
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
    constexpr pkr::units::kilogram_t kg1{3.0};
    constexpr pkr::units::kilogram_t kg2{2.0};
    constexpr auto result = kg1 + kg2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiMassTest, constexpr_kilogram_multiplication)
{
    constexpr pkr::units::kilogram_t kg{2.0};
    constexpr auto result = kg * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST_F(SiMassTest, very_small_mass_values)
{
    pkr::units::nanogram_t ng{0.001};
    ASSERT_DOUBLE_EQ(ng.value(), 0.001);
}

TEST_F(SiMassTest, very_large_mass_values)
{
    pkr::units::megagram_t mg{1000000.0};
    ASSERT_DOUBLE_EQ(mg.value(), 1000000.0);
}

TEST_F(SiMassTest, add_very_different_scales)
{
    pkr::units::kilogram_t kg1{1.0};       // 1 kilogram
    pkr::units::kilogram_t kg2{0.001};     // 1 gram = 0.001 kg
    auto result = kg1 + kg2;
    // Result in kilogram
    // 1 kg + 0.001 kg = 1.001 kg
    ASSERT_DOUBLE_EQ(result.value(), 1.001);
}

TEST_F(SiMassTest, subtract_resulting_in_negative)
{
    pkr::units::kilogram_t kg1{1.0};
    pkr::units::kilogram_t kg2{3.0};
    auto result = kg1 - kg2;
    ASSERT_DOUBLE_EQ(result.value(), -2.0);
}









