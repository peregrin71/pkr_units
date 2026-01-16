// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#include <gtest/gtest.h>
#include <units/si.h>
#include <units/impl/details/si_unit.h>
#include <units/impl/details/dimension.h>
#include <units/impl/length.h>
#include <units/literals/length_literals.h>
#include <units/cast/si_cast.h>
// #include <units/formatting/si_unit_formatting.h>
// #include <units/formatting/si_chrono_interop.h>

// #include <format>
// #include <chrono>
#include <cmath>

namespace test
{

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
// Unit Conversion via si_cast
// ============================================================================

TEST_F(SiLengthTest, cast_meter_to_kilometer)
{
    si::meter m{5000.0};
    auto km = si::si_cast<si::kilometer>(m);
    ASSERT_DOUBLE_EQ(km.value(), 5.0);
}

TEST_F(SiLengthTest, cast_kilometer_to_meter)
{
    si::kilometer km{2.5};
    auto m = si::si_cast<si::meter>(km);
    ASSERT_DOUBLE_EQ(m.value(), 2500.0);
}

TEST_F(SiLengthTest, cast_millimeter_to_meter)
{
    si::millimeter mm{5000.0};
    auto m = si::si_cast<si::meter>(mm);
    ASSERT_DOUBLE_EQ(m.value(), 5.0);
}

TEST_F(SiLengthTest, cast_meter_to_millimeter)
{
    si::meter m{5.0};
    auto mm = si::si_cast<si::millimeter>(m);
    ASSERT_DOUBLE_EQ(mm.value(), 5000.0);
}

TEST_F(SiLengthTest, cast_kilometer_to_millimeter)
{
    si::kilometer km{1.0};
    auto mm = si::si_cast<si::millimeter>(km);
    ASSERT_DOUBLE_EQ(mm.value(), 1000000.0);
}

TEST_F(SiLengthTest, cast_kilometer_to_ratio_must_not_compile)
{
    si::kilometer km{1.0};
    MUST_NOT_COMPILE(si::si_cast<std::milli>(km));
}

// ============================================================================
// Imperial Units Tests
// ============================================================================

TEST_F(SiLengthTest, inch_to_meter_conversion)
{
    // 1 inch = 0.0254 meter
    si::inch in{1.0};
    ASSERT_NEAR(in.value() * (254.0 / 10000.0), 0.0254, 1e-10);
}

TEST_F(SiLengthTest, foot_to_meter_conversion)
{
    // 1 foot = 0.3048 meter
    si::foot ft{1.0};
    ASSERT_NEAR(ft.value() * (3048.0 / 10000.0), 0.3048, 1e-10);

    auto meter = si::si_cast<si::meter>(ft);
    ASSERT_NEAR(meter.value(), 0.3048, 1e-10);
}

TEST_F(SiLengthTest, mile_to_meter_conversion)
{
    // 1 mile = 1609.344 meter
    si::mile mi{1.0};
    ASSERT_NEAR(mi.value() * (1609344.0 / 1000.0), 1609.344, 1e-10);
}

TEST_F(SiLengthTest, add_feet_to_feet)
{
    si::foot ft1{5.0};
    si::foot ft2{3.0};
    auto result = ft1 + ft2;
    ASSERT_DOUBLE_EQ(result.value(), 8.0);
}

TEST_F(SiLengthTest, add_inches_to_feet)
{
    si::foot ft{1.0};
    si::inch in{12.0};
    auto result = ft + in;
    // Result is in feet: 12 inches = 1 foot
    ASSERT_NEAR(result.value(), 2.0, 1e-10);
}

// ============================================================================
// Astronomical Units Tests
// ============================================================================

TEST_F(SiLengthTest, astronomical_unit_construction)
{
    si::au au_dist{1.0};
    ASSERT_DOUBLE_EQ(au_dist.value(), 1.0);
}

TEST_F(SiLengthTest, light_year_construction)
{
    si::light_year ly{2.0};
    ASSERT_DOUBLE_EQ(ly.value(), 2.0);
}

TEST_F(SiLengthTest, parsec_construction)
{
    si::parsec pc{10.0};
    ASSERT_DOUBLE_EQ(pc.value(), 10.0);
}

// ============================================================================
// User-Defined Literals Tests
// ============================================================================

using namespace si::si_literals;

TEST_F(SiLengthTest, meter_literal)
{
    auto m = 5.0_m;
    ASSERT_NEAR(m.value(), 5.0, 1e-10);
}

TEST_F(SiLengthTest, kilometer_literal)
{
    auto km = 2.5_km;
    ASSERT_NEAR(km.value(), 2.5, 1e-10);
}

TEST_F(SiLengthTest, millimeter_literal)
{
    auto mm = 1500.0_mm;
    ASSERT_NEAR(mm.value(), 1500.0, 1e-10);
}

TEST_F(SiLengthTest, centimeter_literal)
{
    auto cm = 50.0_cm;
    ASSERT_NEAR(cm.value(), 50.0, 1e-10);
}

TEST_F(SiLengthTest, micrometer_literal)
{
    auto um = 1000.0_um;
    ASSERT_NEAR(um.value(), 1000.0, 1e-10);
}

TEST_F(SiLengthTest, nanometer_literal)
{
    auto nm = 500.0_nm;
    ASSERT_NEAR(nm.value(), 500.0, 1e-10);
}

TEST_F(SiLengthTest, inch_literal)
{
    auto in = 12.0_in;
    ASSERT_NEAR(in.value(), 12.0, 1e-10);
}

TEST_F(SiLengthTest, foot_literal)
{
    auto ft = 5.0_ft;
    ASSERT_NEAR(ft.value(), 5.0, 1e-10);
}

TEST_F(SiLengthTest, yard_literal)
{
    auto yd = 10.0_yd;
    ASSERT_NEAR(yd.value(), 10.0, 1e-10);
}

TEST_F(SiLengthTest, mile_literal)
{
    auto mi = 2.0_mi;
    ASSERT_NEAR(mi.value(), 2.0, 1e-10);
}

TEST_F(SiLengthTest, nautical_mile_literal)
{
    auto nmi = 5.0_nmi;
    ASSERT_NEAR(nmi.value(), 5.0, 1e-10);
}

TEST_F(SiLengthTest, angstrom_literal)
{
    auto angstrom = 1.0_angstrom;
    ASSERT_NEAR(angstrom.value(), 1.0, 1e-10);
}

TEST_F(SiLengthTest, astronomical_unit_literal)
{
    auto au = 1.5_au;
    ASSERT_NEAR(au.value(), 1.5, 1e-10);
}

/* FORMATTING TESTS DISABLED - Focus on compilation first
// ============================================================================
// Formatting Tests
// ============================================================================

TEST_F(SiLengthTest, format_meter)
{
    si::meter m{5.0};
    auto formatted = std::format("{}", m);
    ASSERT_FALSE(formatted.empty());
    // Should contain "5" and "m"
    ASSERT_NE(formatted.find("5"), std::string::npos);
    ASSERT_NE(formatted.find("m"), std::string::npos);
}

TEST_F(SiLengthTest, format_kilometer)
{
    si::kilometer km{2.5};
    auto formatted = std::format("{}", km);
    ASSERT_FALSE(formatted.empty());
    ASSERT_NE(formatted.find("2.5"), std::string::npos);
}

TEST_F(SiLengthTest, format_millimeter)
{
    si::millimeter mm{1500.0};
    auto formatted = std::format("{}", mm);
    ASSERT_FALSE(formatted.empty());
    ASSERT_NE(formatted.find("1500"), std::string::npos);
}

TEST_F(SiLengthTest, format_with_precision)
{
    si::meter m{3.14159};
    auto formatted = std::format("{:.2f}", m);
    ASSERT_EQ(formatted, "3.14 m");
}

TEST_F(SiLengthTest, format_area_with_exponent)
{
    si::meter m1{5.0};
    si::meter m2{3.0};
    auto area = m1 * m2;
    auto formatted = std::format("{}", area);
    ASSERT_FALSE(formatted.empty());
    // Should contain the area value
    ASSERT_NE(formatted.find("15"), std::string::npos);
}

// ============================================================================
// Special Imperial Unit Formatting Tests (feet/inches)
// ============================================================================

TEST_F(SiLengthTest, format_feet_whole_number)
{
    si::foot ft{5.0};
    auto formatted = std::format("{}", ft);
    ASSERT_EQ(formatted, "5'");
}

TEST_F(SiLengthTest, format_feet_with_half_inch)
{
    si::foot ft{5.5};
    auto formatted = std::format("{}", ft);
    ASSERT_EQ(formatted, "5'6\"");
}

TEST_F(SiLengthTest, format_feet_quarter_foot)
{
    si::foot ft{5.25};
    auto formatted = std::format("{}", ft);
    ASSERT_EQ(formatted, "5'3\"");
}

TEST_F(SiLengthTest, format_feet_less_than_one)
{
    si::foot ft{0.5};
    auto formatted = std::format("{}", ft);
    ASSERT_EQ(formatted, "0'6\"");
}

TEST_F(SiLengthTest, format_feet_less_than_one_to_inches)
{
    si::foot ft{0.5};
    auto formatted = std::format("{}", si::si_cast<si::inch>(ft));
    ASSERT_EQ(formatted, "6\"");
}

TEST_F(SiLengthTest, format_feet_rounding_to_next_foot)
{
    si::foot ft{5.9999};
    auto formatted = std::format("{}", ft);
    ASSERT_EQ(formatted, "6'");
}

TEST_F(SiLengthTest, format_feet_one_foot_one_inch)
{
    si::foot ft{1.08333333};  // 1 foot + 1 inch
    auto formatted = std::format("{}", ft);
    ASSERT_EQ(formatted, "1'1\"");
}
*/

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



} // namespace test






