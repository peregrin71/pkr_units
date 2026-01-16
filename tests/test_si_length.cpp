// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#include <gtest/gtest.h>
#include <units/impl/length.h>
#include <units/imperial/length.h>
#include <units/astronomical/length.h>

namespace si
{
// Test support namespace
}

using namespace ::testing;

class SiLengthTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(SiLengthTest, meter_construction)
{
    si::meter m{5.0};
    ASSERT_DOUBLE_EQ(m.value(), 5.0);
}

TEST_F(SiLengthTest, meter_dereference_operator)
{
    si::meter m{5.0};
    ASSERT_DOUBLE_EQ(*m, 5.0);
}

TEST_F(SiLengthTest, meter_zero_value)
{
    si::meter m{0.0};
    ASSERT_DOUBLE_EQ(m.value(), 0.0);
}

TEST_F(SiLengthTest, meter_negative_value)
{
    si::meter m{-3.5};
    ASSERT_DOUBLE_EQ(m.value(), -3.5);
}

TEST_F(SiLengthTest, kilometer_construction)
{
    si::kilometer km{2.5};
    ASSERT_DOUBLE_EQ(km.value(), 2.5);
}

TEST_F(SiLengthTest, millimeter_construction)
{
    si::millimeter mm{1500.0};
    ASSERT_DOUBLE_EQ(mm.value(), 1500.0);
}

// ============================================================================
// Copy and Move Semantics Tests
// ============================================================================

TEST_F(SiLengthTest, copy_constructor)
{
    si::meter m1{5.0};
    si::meter m2{m1};
    ASSERT_DOUBLE_EQ(m2.value(), 5.0);
}

TEST_F(SiLengthTest, move_constructor)
{
    si::meter m1{5.0};
    si::meter m2{std::move(m1)};
    ASSERT_DOUBLE_EQ(m2.value(), 5.0);
}

TEST_F(SiLengthTest, copy_assignment)
{
    si::meter m1{5.0};
    si::meter m2{0.0};
    m2 = m1;
    ASSERT_DOUBLE_EQ(m2.value(), 5.0);
}

TEST_F(SiLengthTest, move_assignment)
{
    si::meter m1{5.0};
    si::meter m2{0.0};
    m2 = std::move(m1);
    ASSERT_DOUBLE_EQ(m2.value(), 5.0);
}

// ============================================================================
// Arithmetic Operations: Addition/Subtraction (Same Dimension, Different Ratios)
// ============================================================================

TEST_F(SiLengthTest, add_meters)
{
    si::meter m1{3.0};
    si::meter m2{2.0};
    auto result = m1 + m2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiLengthTest, add_kilometer_to_meter)
{
    si::kilometer km{1.0};
    si::meter m{500.0};
    auto result = km + m;
    // Result is in km (LHS ratio), so 500m = 0.5km, result = 1.5km
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiLengthTest, add_meter_to_kilometer)
{
    si::meter m{500.0};
    si::kilometer km{1.0};
    auto result = m + km;
    // Result is in m (LHS ratio), so 1km = 1000m, result = 1500m
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiLengthTest, subtract_meters)
{
    si::meter m1{5.0};
    si::meter m2{2.0};
    auto result = m1 - m2;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiLengthTest, subtract_kilometer_from_meter)
{
    si::meter m{1500.0};
    si::kilometer km{1.0};
    auto result = m - km;
    // Result is in m (LHS ratio), so 1km = 1000m, result = 500m
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiLengthTest, subtract_meter_from_kilometer)
{
    si::kilometer km{2.0};
    si::meter m{500.0};
    auto result = km - m;
    // Result is in km (LHS ratio), so 500m = 0.5km, result = 1.5km
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiLengthTest, add_millimeter_to_meter)
{
    si::meter m{1.0};
    si::millimeter mm{500.0};
    auto result = m + mm;
    // Result is in m, 500mm = 0.5m, result = 1.5m
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

// ============================================================================
// Scalar Multiplication/Division Tests
// ============================================================================

TEST_F(SiLengthTest, multiply_meter_by_scalar)
{
    si::meter m{5.0};
    auto result = m * 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 10.0);
}

TEST_F(SiLengthTest, divide_meter_by_scalar)
{
    si::meter m{10.0};
    auto result = m / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiLengthTest, divide_by_zero_scalar_throws)
{
    si::meter m{10.0};
    ASSERT_THROW(m / 0.0, std::invalid_argument);
}

TEST_F(SiLengthTest, divide_by_zero_si_unit_throws)
{
    si::meter m1{10.0};
    si::meter m2{0.0};
    ASSERT_THROW(m1 / m2, std::invalid_argument);
}

TEST_F(SiLengthTest, multiply_meter_by_zero)
{
    si::meter m{5.0};
    auto result = m * 0.0;
    ASSERT_DOUBLE_EQ(result.value(), 0.0);
}

TEST_F(SiLengthTest, multiply_meter_by_fraction)
{
    si::meter m{10.0};
    auto result = m * 0.5;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

// ============================================================================
// Dimensional Analysis: Multiplication (Area)
// ============================================================================

TEST_F(SiLengthTest, multiply_length_by_length_produces_area)
{
    si::meter m1{2.0};
    si::meter m2{3.0};
    auto area = m1 * m2;
    ASSERT_DOUBLE_EQ(area.value(), 6.0);
    // Verify dimension: length exponent should be 2
    ASSERT_EQ(decltype(area)::dimension::value.length, 2);
}

TEST_F(SiLengthTest, multiply_kilometer_by_kilometer)
{
    si::kilometer km1{2.0};
    si::kilometer km2{3.0};
    auto area = km1 * km2;
    ASSERT_DOUBLE_EQ(area.value(), 6.0);
    ASSERT_EQ(decltype(area)::dimension::value.length, 2);
}

TEST_F(SiLengthTest, multiply_meter_by_kilometer_produces_area)
{
    si::meter m{1000.0};
    si::kilometer km{1.0};
    auto area = m * km;
    // Result has combined ratio: meter (1/1) * kilometer (1000/1) = 1000/1
    // Value: 1000 * 1 = 1000 with ratio 1000, so actual area = 1000 square-meters
    ASSERT_DOUBLE_EQ(area.value(), 1000.0);
    ASSERT_EQ(decltype(area)::dimension::value.length, 2);
}

TEST_F(SiLengthTest, multiply_meter_by_millimeter_produces_area)
{
    si::meter m{5.0};
    si::millimeter mm{2000.0};  // 2000mm = 2m
    auto area = m * mm;
    // Ratio product: 1/1 * 1/1000 = 1/1000
    // Stored value: 5 * 2000 = 10000
    // Physical value: 10000 * (1/1000) = 10 square-meters
    ASSERT_DOUBLE_EQ(area.value(), 10000.0);
    ASSERT_EQ(decltype(area)::dimension::value.length, 2);
}

// ============================================================================
// Dimensional Analysis: Division (Velocity)
// ============================================================================

TEST_F(SiLengthTest, divide_length_by_time_produces_velocity)
{
    // This test demonstrates the concept - actual time type would need time dimension
    // Just verify that length division works
    si::meter m1{10.0};
    si::meter m2{2.0};
    auto result = m1 / m2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    // Result should be dimensionless when dividing same dimension
    ASSERT_EQ(decltype(result)::dimension::value.length, 0);
}

// ============================================================================
// Dimension Tests
// ============================================================================

TEST_F(SiLengthTest, meter_has_length_dimension)
{
    si::meter m{5.0};
    ASSERT_EQ(decltype(m)::dimension::value.length, 1);
    ASSERT_EQ(decltype(m)::dimension::value.mass, 0);
    ASSERT_EQ(decltype(m)::dimension::value.time, 0);
}

TEST_F(SiLengthTest, area_has_correct_dimension)
{
    si::meter m1{5.0};
    si::meter m2{3.0};
    auto area = m1 * m2;
    ASSERT_EQ(decltype(area)::dimension::value.length, 2);
    ASSERT_EQ(decltype(area)::dimension::value.mass, 0);
    ASSERT_EQ(decltype(area)::dimension::value.time, 0);
}

TEST_F(SiLengthTest, volume_has_correct_dimension)
{
    si::meter m1{5.0};
    si::meter m2{3.0};
    si::meter m3{2.0};
    auto area = m1 * m2;
    auto volume = area * m3;
    ASSERT_EQ(decltype(volume)::dimension::value.length, 3);
}

// ============================================================================
// Template Parameter Tests
// ============================================================================

TEST_F(SiLengthTest, length_with_float)
{
    si::length<float> m{5.0f};
    ASSERT_FLOAT_EQ(m.value(), 5.0f);
}

TEST_F(SiLengthTest, length_with_custom_ratio)
{
    si::length<double, std::kilo> km{2.5};
    ASSERT_DOUBLE_EQ(km.value(), 2.5);
}

TEST_F(SiLengthTest, length_with_float_and_kilo)
{
    si::length<float, std::kilo> km{2.5f};
    ASSERT_FLOAT_EQ(km.value(), 2.5f);
}

// ============================================================================
// Edge Case Tests
// ============================================================================

TEST_F(SiLengthTest, very_small_values)
{
    si::nanometer nm{0.001};
    ASSERT_DOUBLE_EQ(nm.value(), 0.001);
}

TEST_F(SiLengthTest, very_large_values)
{
    si::kilometer km{1e6};  // 1 million kilometers
    ASSERT_DOUBLE_EQ(km.value(), 1e6);
}

TEST_F(SiLengthTest, add_very_different_scales)
{
    si::meter m{1.0};
    si::nanometer nm{1e9};  // 1e9 nm = 1 m
    auto result = m + nm;
    // Result should be 1 + 1 = 2 meters
    ASSERT_NEAR(result.value(), 2.0, 1e-10);
}

TEST_F(SiLengthTest, subtract_resulting_in_negative)
{
    si::meter m1{2.0};
    si::meter m2{5.0};
    auto result = m1 - m2;
    ASSERT_DOUBLE_EQ(result.value(), -3.0);
}

// ============================================================================
// Constexpr Tests (Runtime Evaluation)
// ============================================================================

TEST_F(SiLengthTest, constexpr_meter_addition)
{
    constexpr si::meter m1{3.0};
    constexpr si::meter m2{2.0};
    constexpr auto result = m1 + m2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiLengthTest, constexpr_meter_multiplication_and_division)
{
    constexpr si::meter m1{2.0};
    constexpr si::meter m2{3.0};
    constexpr si::meter m3{4.0};

    constexpr auto area = m1 * m2;
    constexpr auto volume = area * m3;
    constexpr auto area2 = volume / m2;

    ASSERT_DOUBLE_EQ(area.value(), 6.0);
    ASSERT_DOUBLE_EQ(area2.value(), 8.0);

    // I want to statically assert the dimension for length is two now
    static_assert(decltype(area)::dimension::value.length == 2, "Area should have length dimension of 2");
    static_assert(decltype(area2)::dimension::value.length == 2, "Area should have length dimension of 2");
    static_assert(decltype(volume)::dimension::value.length == 3, "Volume should have length dimension of 3");
}











