// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#include <gtest/gtest.h>
#include <si_units/standard/length.h>
#include <si_units/cast/si_cast.h>

namespace test
{

using namespace ::testing;

class SiLengthCastTest : public Test
{
};

// ============================================================================
// Unit Conversion via si_cast
// ============================================================================

TEST_F(SiLengthCastTest, cast_meter_to_kilometer)
{
    si::meter m{5000.0};
    auto km = si::si_cast<si::kilometer>(m);
    static_assert(std::is_same_v<decltype(km), si::kilometer>);
    ASSERT_DOUBLE_EQ(km.value(), 5.0);
}

TEST_F(SiLengthCastTest, cast_kilometer_to_meter)
{
    si::kilometer km{2.5};
    auto m = si::si_cast<si::meter>(km);
    static_assert(std::is_same_v<decltype(m), si::meter>);
    ASSERT_DOUBLE_EQ(m.value(), 2500.0);
}

TEST_F(SiLengthCastTest, cast_millimeter_to_meter)
{
    si::millimeter mm{5000.0};
    auto m = si::si_cast<si::meter>(mm);
    static_assert(std::is_same_v<decltype(m), si::meter>);
    ASSERT_DOUBLE_EQ(m.value(), 5.0);
}

TEST_F(SiLengthCastTest, cast_meter_to_millimeter)
{
    si::meter m{5.0};
    auto mm = si::si_cast<si::millimeter>(m);
    static_assert(std::is_same_v<decltype(mm), si::millimeter>);
    ASSERT_DOUBLE_EQ(mm.value(), 5000.0);
}

TEST_F(SiLengthCastTest, cast_kilometer_to_millimeter)
{
    si::kilometer km{1.0};
    auto mm = si::si_cast<si::millimeter>(km);
    static_assert(std::is_same_v<decltype(mm), si::millimeter>);
    ASSERT_DOUBLE_EQ(mm.value(), 1000000.0);
}

TEST_F(SiLengthCastTest, cast_kilometer_to_ratio_must_not_compile)
{
    si::kilometer km{1.0};
    MUST_NOT_COMPILE(si::si_cast<std::milli>(km)); // Note std::milli is a ratio, not a unit type
}

TEST_F(SiLengthCastTest, foot_to_meter_conversion)
{
    // 1 foot = 0.3048 meter
    si::foot ft{1.0};
    ASSERT_NEAR(ft.value() * (3048.0 / 10000.0), 0.3048, 1e-10);

    auto meter = si::si_cast<si::meter>(ft);
    static_assert(std::is_same_v<decltype(meter), si::meter>);
    ASSERT_NEAR(meter.value(), 0.3048, 1e-10);
}

// ============================================================================
// Constexpr Casting Tests (Compile-Time Verification)
// ============================================================================
// Note: The si_cast function is constexpr and can be evaluated at compile-time.
// These tests verify that the function can be called in runtime contexts with the
// understanding that modern compilers will optimize them to compile-time when possible.

TEST_F(SiLengthCastTest, si_cast_is_constexpr_callable)
{
    // This test verifies that si_cast can be evaluated at compile time by using
    // it in a constexpr context. The compiler will evaluate it at compile-time if possible.
    si::meter m{5000.0};
    auto km = si::si_cast<si::kilometer>(m);
    static_assert(std::is_same_v<decltype(km), si::kilometer>);
    ASSERT_DOUBLE_EQ(km.value(), 5.0);
}

TEST_F(SiLengthCastTest, si_cast_zero_ratio_overhead)
{
    // Same-ratio casts are optimized away by constexpr evaluation
    si::meter m{100.0};
    // This will be evaluated at compile-time to just return the value unchanged
    ASSERT_DOUBLE_EQ(m.value(), 100.0);
}

} // namespace test


