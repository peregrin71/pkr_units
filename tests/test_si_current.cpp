// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#include <gtest/gtest.h>
#include <units/impl/current.h>

using namespace ::testing;

class SiCurrentTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(SiCurrentTest, ampere_construction)
{
    si::ampere a{5.0};
    ASSERT_DOUBLE_EQ(a.value(), 5.0);
}

TEST_F(SiCurrentTest, ampere_dereference_operator)
{
    si::ampere a{5.0};
    ASSERT_DOUBLE_EQ(*a, 5.0);
}

TEST_F(SiCurrentTest, ampere_zero_value)
{
    si::ampere a{0.0};
    ASSERT_DOUBLE_EQ(a.value(), 0.0);
}

TEST_F(SiCurrentTest, ampere_negative_value)
{
    si::ampere a{-3.5};
    ASSERT_DOUBLE_EQ(a.value(), -3.5);
}

TEST_F(SiCurrentTest, milliampere_construction)
{
    si::milliampere ma{250.0};
    ASSERT_DOUBLE_EQ(ma.value(), 250.0);
}

TEST_F(SiCurrentTest, microampere_construction)
{
    si::microampere ua{1000.0};
    ASSERT_DOUBLE_EQ(ua.value(), 1000.0);
}

TEST_F(SiCurrentTest, nanoampere_construction)
{
    si::nanoampere na{100.0};
    ASSERT_DOUBLE_EQ(na.value(), 100.0);
}

TEST_F(SiCurrentTest, kiloampere_construction)
{
    si::kiloampere ka{2.5};
    ASSERT_DOUBLE_EQ(ka.value(), 2.5);
}

// ============================================================================
// Copy and Move Tests
// ============================================================================

TEST_F(SiCurrentTest, copy_constructor)
{
    si::ampere a1{5.0};
    si::ampere a2 = a1;
    ASSERT_DOUBLE_EQ(a2.value(), 5.0);
}

TEST_F(SiCurrentTest, move_constructor)
{
    si::ampere a1{5.0};
    si::ampere a2 = std::move(a1);
    ASSERT_DOUBLE_EQ(a2.value(), 5.0);
}

TEST_F(SiCurrentTest, copy_assignment)
{
    si::ampere a1{5.0};
    si::ampere a2{0.0};
    a2 = a1;
    ASSERT_DOUBLE_EQ(a2.value(), 5.0);
}

TEST_F(SiCurrentTest, move_assignment)
{
    si::ampere a1{5.0};
    si::ampere a2{0.0};
    a2 = std::move(a1);
    ASSERT_DOUBLE_EQ(a2.value(), 5.0);
}

// ============================================================================
// Arithmetic Tests - Same Unit
// ============================================================================

TEST_F(SiCurrentTest, add_amperes)
{
    si::ampere a1{3.0};
    si::ampere a2{2.0};
    auto result = a1 + a2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiCurrentTest, subtract_amperes)
{
    si::ampere a1{5.0};
    si::ampere a2{2.0};
    auto result = a1 - a2;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiCurrentTest, add_milliamperes)
{
    si::milliampere ma1{500.0};
    si::milliampere ma2{250.0};
    auto result = ma1 + ma2;
    ASSERT_DOUBLE_EQ(result.value(), 750.0);
}

TEST_F(SiCurrentTest, subtract_milliamperes)
{
    si::milliampere ma1{750.0};
    si::milliampere ma2{250.0};
    auto result = ma1 - ma2;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

// ============================================================================
// Arithmetic Tests - Different Units (Same Dimension)
// ============================================================================

TEST_F(SiCurrentTest, add_ampere_to_milliampere)
{
    si::ampere a{1.0};
    si::milliampere ma{500.0};
    auto result = a + ma;
    // Result is in LHS type (ampere)
    // 1A + 0.5A = 1.5A
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiCurrentTest, add_milliampere_to_ampere)
{
    si::milliampere ma{500.0};
    si::ampere a{1.0};
    auto result = ma + a;
    // Result is in LHS type (milliampere)
    // 500mA + 1000mA = 1500mA
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiCurrentTest, subtract_ampere_from_milliampere)
{
    si::milliampere ma{1500.0};
    si::ampere a{1.0};
    auto result = ma - a;
    // Result is in LHS type (milliampere)
    // 1500mA - 1000mA = 500mA
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiCurrentTest, subtract_milliampere_from_ampere)
{
    si::ampere a{2.0};
    si::milliampere ma{500.0};
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
    si::ampere a{2.0};
    auto result = a * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

TEST_F(SiCurrentTest, divide_ampere_by_scalar)
{
    si::ampere a{6.0};
    auto result = a / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiCurrentTest, divide_by_zero_scalar_throws)
{
    si::ampere a{5.0};
    ASSERT_THROW(a / 0.0, std::invalid_argument);
}

TEST_F(SiCurrentTest, multiply_milliampere_by_scalar)
{
    si::milliampere ma{100.0};
    auto result = ma * 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiCurrentTest, divide_milliampere_by_scalar)
{
    si::milliampere ma{500.0};
    auto result = ma / 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 100.0);
}

// ============================================================================
// Current Multiplication (Creates Derived Units)
// ============================================================================

TEST_F(SiCurrentTest, multiply_ampere_by_ampere)
{
    si::ampere a1{2.0};
    si::ampere a2{3.0};
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
    si::ampere a1{10.0};
    si::ampere a2{2.0};
    auto result = a1 / a2;
    // Result is dimensionless (scalar)
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::dimension::value.current, 0);
}

TEST_F(SiCurrentTest, divide_milliampere_by_milliampere)
{
    si::milliampere ma1{500.0};
    si::milliampere ma2{100.0};
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
    constexpr si::ampere a1{3.0};
    constexpr si::ampere a2{2.0};
    constexpr auto result = a1 + a2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiCurrentTest, constexpr_ampere_multiplication)
{
    constexpr si::ampere a{2.0};
    constexpr auto result = a * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST_F(SiCurrentTest, very_small_current_values)
{
    si::nanoampere na{0.001};
    ASSERT_DOUBLE_EQ(na.value(), 0.001);
}

TEST_F(SiCurrentTest, very_large_current_values)
{
    si::kiloampere ka{1000000.0};
    ASSERT_DOUBLE_EQ(ka.value(), 1000000.0);
}

TEST_F(SiCurrentTest, add_very_different_scales)
{
    si::milliampere ma{1.0};   // 1 milliampere
    si::ampere a{1.0};         // 1 ampere = 1000 mA
    auto result = ma + a;
    // Result is in LHS type (milliampere)
    // 1 mA + 1000 mA = 1001 mA
    ASSERT_DOUBLE_EQ(result.value(), 1001.0);
}

TEST_F(SiCurrentTest, subtract_resulting_in_negative)
{
    si::ampere a1{1.0};
    si::ampere a2{3.0};
    auto result = a1 - a2;
    ASSERT_DOUBLE_EQ(result.value(), -2.0);
}
