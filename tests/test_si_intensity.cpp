// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#include <gtest/gtest.h>
#include <units/impl/intensity.h>

using namespace ::testing;

class SiIntensityTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(SiIntensityTest, candela_construction)
{
    si::candela cd{5.0};
    ASSERT_DOUBLE_EQ(cd.value(), 5.0);
}

TEST_F(SiIntensityTest, candela_dereference_operator)
{
    si::candela cd{5.0};
    ASSERT_DOUBLE_EQ(*cd, 5.0);
}

TEST_F(SiIntensityTest, candela_zero_value)
{
    si::candela cd{0.0};
    ASSERT_DOUBLE_EQ(cd.value(), 0.0);
}

TEST_F(SiIntensityTest, candela_negative_value)
{
    si::candela cd{-3.5};
    ASSERT_DOUBLE_EQ(cd.value(), -3.5);
}

TEST_F(SiIntensityTest, millicandela_construction)
{
    si::millicandela mcd{250.0};
    ASSERT_DOUBLE_EQ(mcd.value(), 250.0);
}

TEST_F(SiIntensityTest, microcandela_construction)
{
    si::microcandela ucd{1000.0};
    ASSERT_DOUBLE_EQ(ucd.value(), 1000.0);
}

TEST_F(SiIntensityTest, nanocandela_construction)
{
    si::nanocandela ncd{100.0};
    ASSERT_DOUBLE_EQ(ncd.value(), 100.0);
}

TEST_F(SiIntensityTest, kilocandela_construction)
{
    si::kilocandela kcd{2.5};
    ASSERT_DOUBLE_EQ(kcd.value(), 2.5);
}

// ============================================================================
// Copy and Move Tests
// ============================================================================

TEST_F(SiIntensityTest, copy_constructor)
{
    si::candela cd1{5.0};
    si::candela cd2 = cd1;
    ASSERT_DOUBLE_EQ(cd2.value(), 5.0);
}

TEST_F(SiIntensityTest, move_constructor)
{
    si::candela cd1{5.0};
    si::candela cd2 = std::move(cd1);
    ASSERT_DOUBLE_EQ(cd2.value(), 5.0);
}

TEST_F(SiIntensityTest, copy_assignment)
{
    si::candela cd1{5.0};
    si::candela cd2{0.0};
    cd2 = cd1;
    ASSERT_DOUBLE_EQ(cd2.value(), 5.0);
}

TEST_F(SiIntensityTest, move_assignment)
{
    si::candela cd1{5.0};
    si::candela cd2{0.0};
    cd2 = std::move(cd1);
    ASSERT_DOUBLE_EQ(cd2.value(), 5.0);
}

// ============================================================================
// Arithmetic Tests - Same Unit
// ============================================================================

TEST_F(SiIntensityTest, add_candelas)
{
    si::candela cd1{3.0};
    si::candela cd2{2.0};
    auto result = cd1 + cd2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiIntensityTest, subtract_candelas)
{
    si::candela cd1{5.0};
    si::candela cd2{2.0};
    auto result = cd1 - cd2;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiIntensityTest, add_millicandelas)
{
    si::millicandela mcd1{500.0};
    si::millicandela mcd2{250.0};
    auto result = mcd1 + mcd2;
    ASSERT_DOUBLE_EQ(result.value(), 750.0);
}

TEST_F(SiIntensityTest, subtract_millicandelas)
{
    si::millicandela mcd1{750.0};
    si::millicandela mcd2{250.0};
    auto result = mcd1 - mcd2;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

// ============================================================================
// Arithmetic Tests - Different Units (Same Dimension)
// ============================================================================

TEST_F(SiIntensityTest, add_candela_to_millicandela)
{
    si::candela cd{1.0};
    si::millicandela mcd{500.0};
    auto result = cd + mcd;
    // Result is in LHS type (candela)
    // 1cd + 0.5cd = 1.5cd
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiIntensityTest, add_millicandela_to_candela)
{
    si::millicandela mcd{500.0};
    si::candela cd{1.0};
    auto result = mcd + cd;
    // Result is in LHS type (millicandela)
    // 500mcd + 1000mcd = 1500mcd
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiIntensityTest, subtract_candela_from_millicandela)
{
    si::millicandela mcd{1500.0};
    si::candela cd{1.0};
    auto result = mcd - cd;
    // Result is in LHS type (millicandela)
    // 1500mcd - 1000mcd = 500mcd
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiIntensityTest, subtract_millicandela_from_candela)
{
    si::candela cd{2.0};
    si::millicandela mcd{500.0};
    auto result = cd - mcd;
    // Result is in LHS type (candela)
    // 2cd - 0.5cd = 1.5cd
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

// ============================================================================
// Scalar Multiplication and Division
// ============================================================================

TEST_F(SiIntensityTest, multiply_candela_by_scalar)
{
    si::candela cd{2.0};
    auto result = cd * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

TEST_F(SiIntensityTest, divide_candela_by_scalar)
{
    si::candela cd{6.0};
    auto result = cd / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiIntensityTest, divide_by_zero_scalar_throws)
{
    si::candela cd{5.0};
    ASSERT_THROW(cd / 0.0, std::invalid_argument);
}

TEST_F(SiIntensityTest, multiply_millicandela_by_scalar)
{
    si::millicandela mcd{100.0};
    auto result = mcd * 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiIntensityTest, divide_millicandela_by_scalar)
{
    si::millicandela mcd{500.0};
    auto result = mcd / 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 100.0);
}

// ============================================================================
// Intensity Multiplication (Creates Derived Units)
// ============================================================================

TEST_F(SiIntensityTest, multiply_candela_by_candela)
{
    si::candela cd1{2.0};
    si::candela cd2{3.0};
    auto result = cd1 * cd2;
    // Result has intensity dimension = 2 (cd²)
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
    ASSERT_EQ(decltype(result)::dimension::value.intensity, 2);
}

// ============================================================================
// Intensity Division (Creates Dimensionless)
// ============================================================================

TEST_F(SiIntensityTest, divide_candela_by_candela)
{
    si::candela cd1{10.0};
    si::candela cd2{2.0};
    auto result = cd1 / cd2;
    // Result is dimensionless (scalar)
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::dimension::value.intensity, 0);
}

TEST_F(SiIntensityTest, divide_millicandela_by_millicandela)
{
    si::millicandela mcd1{500.0};
    si::millicandela mcd2{100.0};
    auto result = mcd1 / mcd2;
    // Result is dimensionless
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::dimension::value.intensity, 0);
}

// ============================================================================
// Constexpr Tests
// ============================================================================

TEST_F(SiIntensityTest, constexpr_candela_addition)
{
    constexpr si::candela cd1{3.0};
    constexpr si::candela cd2{2.0};
    constexpr auto result = cd1 + cd2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiIntensityTest, constexpr_candela_multiplication)
{
    constexpr si::candela cd{2.0};
    constexpr auto result = cd * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST_F(SiIntensityTest, very_small_intensity_values)
{
    si::nanocandela ncd{0.001};
    ASSERT_DOUBLE_EQ(ncd.value(), 0.001);
}

TEST_F(SiIntensityTest, very_large_intensity_values)
{
    si::kilocandela kcd{1000000.0};
    ASSERT_DOUBLE_EQ(kcd.value(), 1000000.0);
}

TEST_F(SiIntensityTest, add_very_different_scales)
{
    si::millicandela mcd{1.0};  // 1 millicandela
    si::candela cd{1.0};        // 1 candela = 1000 mcd
    auto result = mcd + cd;
    // Result is in LHS type (millicandela)
    // 1 mcd + 1000 mcd = 1001 mcd
    ASSERT_DOUBLE_EQ(result.value(), 1001.0);
}

TEST_F(SiIntensityTest, subtract_resulting_in_negative)
{
    si::candela cd1{1.0};
    si::candela cd2{3.0};
    auto result = cd1 - cd2;
    ASSERT_DOUBLE_EQ(result.value(), -2.0);
}
