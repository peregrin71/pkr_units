#include <gtest/gtest.h>
#include <pkr_units/units/base/mass.h>

using namespace ::testing;

class SiMassOperatorsTest : public Test
{
};

// ============================================================================
// Arithmetic Operations: Addition/Subtraction (Same Dimension, Different Ratios)
// ============================================================================

TEST_F(SiMassOperatorsTest, add_kilograms)
{
    pkr::units::kilogram_t<double> kg1{3.0};
    pkr::units::kilogram_t<double> kg2{2.0};
    auto result = kg1 + kg2;
    static_assert(std::is_same_v<decltype(result), pkr::units::kilogram_t<double>>);
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiMassOperatorsTest, add_gram_to_kilogram)
{
    pkr::units::gram_t<double> g{500.0};
    pkr::units::kilogram_t<double> kg{1.0};
    auto result = g + kg; // preserves LHS (gram)

    static_assert(std::is_same_v<decltype(result), pkr::units::gram_t<double>>, "operator+ should preserve LHS type (gram)");
    // 500 g + 1000 g = 1500 g
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiMassOperatorsTest, add_kilogram_to_gram)
{
    pkr::units::kilogram_t<double> kg{1.0};
    pkr::units::gram_t<double> g{500.0};
    auto result = kg + g;
    static_assert(std::is_same_v<decltype(result), pkr::units::kilogram_t<double>>);
    // Result is in LHS unit (kilogram), so 500g = 0.5kg, result = 1.5kg
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiMassOperatorsTest, subtract_kilograms)
{
    pkr::units::kilogram_t<double> kg1{5.0};
    pkr::units::kilogram_t<double> kg2{2.0};
    auto result = kg1 - kg2;
    static_assert(std::is_same_v<decltype(result), pkr::units::kilogram_t<double>>);
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiMassOperatorsTest, subtract_gram_from_kilogram)
{
    pkr::units::kilogram_t<double> kg{1.0};
    pkr::units::gram_t<double> g{500.0};
    auto result = kg - g;
    static_assert(std::is_same_v<decltype(result), pkr::units::kilogram_t<double>>);
    // 1kg - 500g = 1000g - 500g = 500g = 0.5kg
    ASSERT_DOUBLE_EQ(result.value(), 0.5);
}

TEST_F(SiMassOperatorsTest, subtract_kilogram_from_gram)
{
    pkr::units::gram_t<double> g{1500.0};
    pkr::units::kilogram_t<double> kg{1.0};
    auto result = g - kg; // preserves LHS (gram)

    static_assert(std::is_same_v<decltype(result), pkr::units::gram_t<double>>, "operator- should preserve LHS type (gram)");
    // 1500 g - 1000 g = 500 g
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

// ============================================================================
// Multiplication/Division by Scalar
// ============================================================================

TEST_F(SiMassOperatorsTest, multiply_kilogram_by_scalar)
{
    pkr::units::kilogram_t<double> kg{5.0};
    auto result = kg * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 15.0);
}

TEST_F(SiMassOperatorsTest, divide_kilogram_by_scalar)
{
    pkr::units::kilogram_t<double> kg{10.0};
    auto result = kg / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiMassOperatorsTest, multiply_kilogram_by_zero)
{
    pkr::units::kilogram_t<double> kg{5.0};
    auto result = kg * 0.0;
    ASSERT_DOUBLE_EQ(result.value(), 0.0);
}

TEST_F(SiMassOperatorsTest, multiply_kilogram_by_fraction)
{
    pkr::units::kilogram_t<double> kg{6.0};
    auto result = kg * 0.5;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

// ============================================================================
// Comparison Operators
// ============================================================================

TEST_F(SiMassOperatorsTest, equal_kilograms)
{
    pkr::units::kilogram_t<double> kg1{5.0};
    pkr::units::kilogram_t<double> kg2{5.0};
    ASSERT_TRUE(kg1 == kg2);
}

TEST_F(SiMassOperatorsTest, not_equal_kilograms)
{
    pkr::units::kilogram_t<double> kg1{5.0};
    pkr::units::kilogram_t<double> kg2{3.0};
    ASSERT_TRUE(kg1 != kg2);
}

TEST_F(SiMassOperatorsTest, less_than_kilograms)
{
    pkr::units::kilogram_t<double> kg1{3.0};
    pkr::units::kilogram_t<double> kg2{5.0};
    ASSERT_TRUE(kg1 < kg2);
}

TEST_F(SiMassOperatorsTest, less_than_or_equal_kilograms)
{
    pkr::units::kilogram_t<double> kg1{5.0};
    pkr::units::kilogram_t<double> kg2{5.0};
    ASSERT_TRUE(kg1 <= kg2);
}

TEST_F(SiMassOperatorsTest, greater_than_kilograms)
{
    pkr::units::kilogram_t<double> kg1{5.0};
    pkr::units::kilogram_t<double> kg2{3.0};
    ASSERT_TRUE(kg1 > kg2);
}

TEST_F(SiMassOperatorsTest, greater_than_or_equal_kilograms)
{
    pkr::units::kilogram_t<double> kg1{5.0};
    pkr::units::kilogram_t<double> kg2{5.0};
    ASSERT_TRUE(kg1 >= kg2);
}

// ============================================================================
// Constexpr Operations
// ============================================================================

TEST_F(SiMassOperatorsTest, constexpr_kilogram_addition)
{
    constexpr pkr::units::kilogram_t<double> kg1{3.0};
    constexpr pkr::units::kilogram_t<double> kg2{2.0};
    constexpr auto result = kg1 + kg2;
    static_assert(result.value() == 5.0);
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiMassOperatorsTest, constexpr_kilogram_multiplication_and_division)
{
    constexpr pkr::units::kilogram_t<double> kg{10.0};
    constexpr auto multiplied = kg * 2.0;
    constexpr auto divided = multiplied / 5.0;
    static_assert(divided.value() == 4.0);
    ASSERT_DOUBLE_EQ(divided.value(), 4.0);
}

// ============================================================================
// Scalar Operations: RHS scalar multiplication/division
// ============================================================================

TEST_F(SiMassOperatorsTest, scalar_rhs_multiply_kilogram)
{
    pkr::units::kilogram_t<double> kg{5.0};
    auto result = kg * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 15.0);
}

TEST_F(SiMassOperatorsTest, scalar_rhs_divide_kilogram)
{
    pkr::units::kilogram_t<double> kg{4.0};
    auto result = kg / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 2.0);
}
