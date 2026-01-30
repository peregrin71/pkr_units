#include <gtest/gtest.h>
#include <pkr_units/units/base/length.h>
#include <pkr_units/units/imperial/length.h>
#include <pkr_units/units/astronomical/length.h>

using namespace ::testing;

class SiLengthOperatorsTest : public Test
{
};

// ============================================================================
// Arithmetic Operations: Addition/Subtraction (Same Dimension, Different Ratios)
// ============================================================================

TEST_F(SiLengthOperatorsTest, add_meters)
{
    pkr::units::meter_t m1{3.0};
    pkr::units::meter_t m2{2.0};
    auto result = m1 + m2;
    static_assert(std::is_same_v<decltype(result), pkr::units::meter_t>);
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiLengthOperatorsTest, add_kilometer_to_meter)
{
    pkr::units::kilometer_t km{1.0};
    pkr::units::meter_t m{500.0};
    auto result = km + m;
    static_assert(std::is_same_v<decltype(result), pkr::units::kilometer_t>);
    // Result is in LHS unit (kilometer), so 500m = 0.5km, result = 1.5km
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiLengthOperatorsTest, add_meter_to_kilometer)
{
    pkr::units::meter_t m{500.0};
    pkr::units::kilometer_t km{1.0};
    auto result = m + km;
    static_assert(std::is_same_v<decltype(result), pkr::units::meter_t>);
    // Result is in canonical unit (meter), so 1km = 1000m, result = 1500m
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiLengthOperatorsTest, subtract_meters)
{
    pkr::units::meter_t m1{5.0};
    pkr::units::meter_t m2{2.0};
    auto result = m1 - m2;

    static_assert(std::is_same_v<decltype(result), pkr::units::meter_t>);

    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiLengthOperatorsTest, subtract_kilometer_from_meter)
{
    pkr::units::meter_t m{1500.0};
    pkr::units::kilometer_t km{1.0};
    auto result = m - km;
    static_assert(std::is_same_v<decltype(result), pkr::units::meter_t>);
    // Result is in m (LHS ratio), so 1km = 1000m, result = 500m
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiLengthOperatorsTest, subtract_meter_from_kilometer)
{
    pkr::units::kilometer_t km{2.0};
    pkr::units::meter_t m{500.0};
    auto result = km - m;
    static_assert(std::is_same_v<decltype(result), pkr::units::kilometer_t>);
    // Result is in LHS unit (kilometer), so 500m = 0.5km, result = 1.5km
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiLengthOperatorsTest, add_millimeter_to_meter)
{
    pkr::units::meter_t m{1.0};
    pkr::units::millimeter_t mm{500.0};
    auto result = m + mm;
    static_assert(std::is_same_v<decltype(result), pkr::units::meter_t>);
    // Result is in canonical unit (meter), so 500mm = 0.5m, result = 1.5m
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

// ============================================================================
// Scalar Multiplication/Division Tests
// ============================================================================

TEST_F(SiLengthOperatorsTest, multiply_meter_by_scalar)
{
    pkr::units::meter_t m{5.0};
    auto result = m * 2.0;
    // Note: scalar operations on derived types return unit_t base, not the derived type
    ASSERT_DOUBLE_EQ(result.value(), 10.0);
}

TEST_F(SiLengthOperatorsTest, divide_meter_by_scalar)
{
    pkr::units::meter_t m{10.0};
    auto result = m / 2.0;
    // Note: scalar operations on derived types return unit_t base, not the derived type
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiLengthOperatorsTest, multiply_meter_by_zero)
{
    pkr::units::meter_t m{5.0};
    auto result = m * 0.0;
    // Note: scalar operations on derived types return unit_t base, not the derived type
    ASSERT_DOUBLE_EQ(result.value(), 0.0);
}

TEST_F(SiLengthOperatorsTest, multiply_meter_by_fraction)
{
    pkr::units::meter_t m{10.0};
    auto result = m * 0.5;
    // Note: scalar operations on derived types return unit_t base, not the derived type
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

// ============================================================================
// Dimensional Analysis: Multiplication (Area)
// ============================================================================

TEST_F(SiLengthOperatorsTest, multiply_length_by_length_produces_area)
{
    pkr::units::meter_t m1{2.0};
    pkr::units::meter_t m2{3.0};
    auto area = m1 * m2;
    ASSERT_DOUBLE_EQ(area.value(), 6.0);
    // Verify dimension: length exponent should be 2
    ASSERT_EQ(decltype(area)::dimension::value.length, 2);
}

TEST_F(SiLengthOperatorsTest, multiply_kilometer_by_kilometer)
{
    pkr::units::kilometer_t km1{2.0};
    pkr::units::kilometer_t km2{3.0};
    auto area = km1 * km2;
    ASSERT_DOUBLE_EQ(area.value(), 6.0);
    ASSERT_EQ(decltype(area)::dimension::value.length, 2);
}

TEST_F(SiLengthOperatorsTest, multiply_meter_by_kilometer_produces_area)
{
    pkr::units::meter_t m{1000.0};
    pkr::units::kilometer_t km{1.0};
    auto area = m * km;
    // Result has combined ratio: meter (1/1) * kilometer (1000/1) = 1000/1
    // Value: 1000 * 1 = 1000 with ratio 1000, so actual area = 1000 square-meters
    ASSERT_DOUBLE_EQ(area.value(), 1000.0);
    ASSERT_EQ(decltype(area)::dimension::value.length, 2);
}

TEST_F(SiLengthOperatorsTest, multiply_meter_by_millimeter_produces_area)
{
    pkr::units::meter_t m{5.0};
    pkr::units::millimeter_t mm{2000.0}; // 2000mm = 2m
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

TEST_F(SiLengthOperatorsTest, divide_length_by_time_produces_velocity)
{
    // This test demonstrates the concept - actual time type would need time dimension
    // Just verify that length division works
    pkr::units::meter_t m1{10.0};
    pkr::units::meter_t m2{2.0};
    auto result = m1 / m2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    // Result should be dimensionless when dividing same dimension
    ASSERT_EQ(decltype(result)::dimension::value.length, 0);
}

// ============================================================================
// Edge Case Tests with Operators
// ============================================================================

TEST_F(SiLengthOperatorsTest, add_very_different_scales)
{
    pkr::units::meter_t m{1.0};
    pkr::units::nanometer_t nm{1e9}; // 1e9 nm = 1 m
    auto result = m + nm;
    // Result should be 1 + 1 = 2 meters
    ASSERT_NEAR(result.value(), 2.0, 1e-10);
}

TEST_F(SiLengthOperatorsTest, subtract_resulting_in_negative)
{
    pkr::units::meter_t m1{2.0};
    pkr::units::meter_t m2{5.0};
    auto result = m1 - m2;
    ASSERT_DOUBLE_EQ(result.value(), -3.0);
}

// ============================================================================
// Constexpr Tests (Runtime Evaluation)
// ============================================================================

TEST_F(SiLengthOperatorsTest, constexpr_meter_addition)
{
    constexpr pkr::units::meter_t m1{3.0};
    constexpr pkr::units::meter_t m2{2.0};
    constexpr auto result = m1 + m2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiLengthOperatorsTest, constexpr_meter_multiplication_and_division)
{
    constexpr pkr::units::meter_t m1{2.0};
    constexpr pkr::units::meter_t m2{3.0};
    constexpr pkr::units::meter_t m3{4.0};

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

TEST_F(SiLengthOperatorsTest, add_to)
{
    pkr::units::decimeter_t m1{3.0}; // 3 decimeters = 0.3 meters
    pkr::units::kilometer_t m2{2.0}; // 2 kilometers = 2000 meters
    auto result = pkr::units::add<pkr::units::millimeter_t>(m1, m2);
    // 0.3 + 2000 = 2000.3 meters = 2000300 millimeters
    ASSERT_DOUBLE_EQ(result.value(), 2000300.0);
}

TEST_F(SiLengthOperatorsTest, constexpr_add_to)
{
    constexpr pkr::units::meter_t m1{1.0};      // 1 meter
    constexpr pkr::units::decimeter_t m2{30.0}; // 30 decimeters = 3 meters
    constexpr auto result = pkr::units::add<pkr::units::millimeter_t>(m1, m2);
    // 1 + 3 = 4 meters = 4000 millimeters (power of 2 in meters domain)
    static_assert(result.value() == 4000.0, "add should result in 4000 millimeters");
}

// ============================================================================
// Scalar Operations: Both LHS and RHS scalar multiplication/division
// ============================================================================

TEST_F(SiLengthOperatorsTest, scalar_rhs_multiply_meter)
{
    pkr::units::meter_t m{5.0};
    auto result = m * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 15.0);
}

TEST_F(SiLengthOperatorsTest, scalar_rhs_divide_meter)
{
    pkr::units::meter_t m{4.0};
    auto result = m / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 2.0);
}
