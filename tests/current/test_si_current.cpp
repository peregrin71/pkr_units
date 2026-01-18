#include <gtest/gtest.h>
#include <si_units/standard/current.h>

using namespace ::testing;

class SiCurrentTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(SiCurrentTest, ampere_construction)
{
    pkr::units::ampere_t a{5.0};
    ASSERT_DOUBLE_EQ(a.value(), 5.0);
}

TEST_F(SiCurrentTest, ampere_dereference_operator)
{
    pkr::units::ampere_t a{5.0};
    ASSERT_DOUBLE_EQ(*a, 5.0);
}

TEST_F(SiCurrentTest, ampere_zero_value)
{
    pkr::units::ampere_t a{0.0};
    ASSERT_DOUBLE_EQ(a.value(), 0.0);
}

TEST_F(SiCurrentTest, ampere_negative_value)
{
    pkr::units::ampere_t a{-3.5};
    ASSERT_DOUBLE_EQ(a.value(), -3.5);
}

TEST_F(SiCurrentTest, milliampere_construction)
{
    pkr::units::milliampere_t ma{250.0};
    ASSERT_DOUBLE_EQ(ma.value(), 250.0);
}

TEST_F(SiCurrentTest, microampere_construction)
{
    pkr::units::microampere_t ua{1000.0};
    ASSERT_DOUBLE_EQ(ua.value(), 1000.0);
}

TEST_F(SiCurrentTest, nanoampere_construction)
{
    pkr::units::nanoampere_t na{100.0};
    ASSERT_DOUBLE_EQ(na.value(), 100.0);
}

TEST_F(SiCurrentTest, kiloampere_construction)
{
    pkr::units::kiloampere_t ka{2.5};
    ASSERT_DOUBLE_EQ(ka.value(), 2.5);
}

// ============================================================================
// Copy and Move Tests
// ============================================================================

TEST_F(SiCurrentTest, copy_constructor)
{
    pkr::units::ampere_t a1{5.0};
    pkr::units::ampere_t a2 = a1;
    ASSERT_DOUBLE_EQ(a2.value(), 5.0);
}

TEST_F(SiCurrentTest, move_constructor)
{
    pkr::units::ampere_t a1{5.0};
    pkr::units::ampere_t a2 = std::move(a1);
    ASSERT_DOUBLE_EQ(a2.value(), 5.0);
}

TEST_F(SiCurrentTest, copy_assignment)
{
    pkr::units::ampere_t a1{5.0};
    pkr::units::ampere_t a2{0.0};
    a2 = a1;
    ASSERT_DOUBLE_EQ(a2.value(), 5.0);
}

TEST_F(SiCurrentTest, move_assignment)
{
    pkr::units::ampere_t a1{5.0};
    pkr::units::ampere_t a2{0.0};
    a2 = std::move(a1);
    ASSERT_DOUBLE_EQ(a2.value(), 5.0);
}

// ============================================================================
// Arithmetic Tests - Same Unit
// ============================================================================

TEST_F(SiCurrentTest, add_amperes)
{
    pkr::units::ampere_t a1{3.0};
    pkr::units::ampere_t a2{2.0};
    auto result = a1 + a2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiCurrentTest, subtract_amperes)
{
    pkr::units::ampere_t a1{5.0};
    pkr::units::ampere_t a2{2.0};
    auto result = a1 - a2;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiCurrentTest, add_milliamperes)
{
    pkr::units::milliampere_t ma1{500.0};
    pkr::units::milliampere_t ma2{250.0};
    auto result = ma1 + ma2;
    ASSERT_DOUBLE_EQ(result.value(), 750.0);
}

TEST_F(SiCurrentTest, subtract_milliamperes)
{
    pkr::units::milliampere_t ma1{750.0};
    pkr::units::milliampere_t ma2{250.0};
    auto result = ma1 - ma2;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

// ============================================================================
// Arithmetic Tests - Different Units (Same Dimension)
// ============================================================================

TEST_F(SiCurrentTest, add_ampere_to_milliampere)
{
    pkr::units::ampere_t a{1.0};
    pkr::units::milliampere_t ma{500.0};
    auto result = a + ma;
    // Result is in LHS type (ampere)
    // 1A + 0.5A = 1.5A
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiCurrentTest, add_milliampere_to_ampere)
{
    pkr::units::milliampere_t ma{500.0};
    pkr::units::ampere_t a{1.0};
    auto result = ma + a;
    // Result is in LHS type (milliampere)
    // 500mA + 1000mA = 1500mA
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiCurrentTest, subtract_ampere_from_milliampere)
{
    pkr::units::milliampere_t ma{1500.0};
    pkr::units::ampere_t a{1.0};
    auto result = ma - a;
    // Result is in LHS type (milliampere)
    // 1500mA - 1000mA = 500mA
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiCurrentTest, subtract_milliampere_from_ampere)
{
    pkr::units::ampere_t a{2.0};
    pkr::units::milliampere_t ma{500.0};
    auto result = a - ma;
    // Result is in LHS type (ampere)
    // 2A - 0.5A = 1.5A
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

// ============================================================================
// Scalar Multiplication and Division
// ============================================================================

TEST_F(SiCurrentTest, multiply_ampere_by_scalar)
{
    pkr::units::ampere_t a{2.0};
    auto result = a * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

TEST_F(SiCurrentTest, divide_ampere_by_scalar)
{
    pkr::units::ampere_t a{6.0};
    auto result = a / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiCurrentTest, divide_by_zero_scalar_throws)
{
    pkr::units::ampere_t a{5.0};
    ASSERT_THROW(a / 0.0, std::invalid_argument);
}

TEST_F(SiCurrentTest, multiply_milliampere_by_scalar)
{
    pkr::units::milliampere_t ma{100.0};
    auto result = ma * 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiCurrentTest, divide_milliampere_by_scalar)
{
    pkr::units::milliampere_t ma{500.0};
    auto result = ma / 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 100.0);
}

// ============================================================================
// Current Multiplication (Creates Derived Units)
// ============================================================================

TEST_F(SiCurrentTest, multiply_ampere_by_ampere)
{
    pkr::units::ampere_t a1{2.0};
    pkr::units::ampere_t a2{3.0};
    auto result = a1 * a2;
    // Result has current dimension = 2 (A²)
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
    ASSERT_EQ(decltype(result)::dimension::value.current, 2);
}

// ============================================================================
// Current Division (Creates Dimensionless)
// ============================================================================

TEST_F(SiCurrentTest, divide_ampere_by_ampere)
{
    pkr::units::ampere_t a1{10.0};
    pkr::units::ampere_t a2{2.0};
    auto result = a1 / a2;
    // Result is dimensionless (scalar)
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::dimension::value.current, 0);
}

TEST_F(SiCurrentTest, divide_milliampere_by_milliampere)
{
    pkr::units::milliampere_t ma1{500.0};
    pkr::units::milliampere_t ma2{100.0};
    auto result = ma1 / ma2;
    // Result is dimensionless
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::dimension::value.current, 0);
}

// ============================================================================
// Constexpr Tests
// ============================================================================

TEST_F(SiCurrentTest, constexpr_ampere_addition)
{
    constexpr pkr::units::ampere_t a1{3.0};
    constexpr pkr::units::ampere_t a2{2.0};
    constexpr auto result = a1 + a2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiCurrentTest, constexpr_ampere_multiplication)
{
    constexpr pkr::units::ampere_t a{2.0};
    constexpr auto result = a * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST_F(SiCurrentTest, very_small_current_values)
{
    pkr::units::nanoampere_t na{0.001};
    ASSERT_DOUBLE_EQ(na.value(), 0.001);
}

TEST_F(SiCurrentTest, very_large_current_values)
{
    pkr::units::kiloampere_t ka{1000000.0};
    ASSERT_DOUBLE_EQ(ka.value(), 1000000.0);
}

TEST_F(SiCurrentTest, add_very_different_scales)
{
    pkr::units::milliampere_t ma{1.0};   // 1 milliampere
    pkr::units::ampere_t a{1.0};         // 1 ampere = 1000 mA
    auto result = ma + a;
    // Result is in LHS type (milliampere)
    // 1 mA + 1000 mA = 1001 mA
    ASSERT_DOUBLE_EQ(result.value(), 1001.0);
}

TEST_F(SiCurrentTest, subtract_resulting_in_negative)
{
    pkr::units::ampere_t a1{1.0};
    pkr::units::ampere_t a2{3.0};
    auto result = a1 - a2;
    ASSERT_DOUBLE_EQ(result.value(), -2.0);
}



