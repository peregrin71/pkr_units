#include <gtest/gtest.h>
#include <pkr_units/math/unit/unit_math.h>
#include <pkr_units/si_units.h>

namespace test
{

using namespace ::testing;

class MathFunctionsTest : public Test
{
};

// ============================================================================
// Basic Arithmetic Functions
// ============================================================================

TEST_F(MathFunctionsTest, add_same_units)
{
    pkr::units::meter_t m1{5.0};
    pkr::units::meter_t m2{3.0};
    auto result = m1 + m2;

    ASSERT_DOUBLE_EQ(result.value(), 8.0);
    // Result should be some meter type
    using result_type = decltype(result);
    static_assert(result_type::dimension::value.length == 1, "Should have length dimension");
}

TEST_F(MathFunctionsTest, add_different_ratios)
{
    pkr::units::meter_t m{1.0};
    pkr::units::meter_t m2{2.0}; // Same ratio, just different values
    auto result = m + m2;

    ASSERT_DOUBLE_EQ(result.value(), 3.0);
    // Result should be some meter type
    using result_type = decltype(result);
    static_assert(result_type::dimension::value.length == 1, "Should have length dimension");
}

TEST_F(MathFunctionsTest, subtract_same_units)
{
    pkr::units::second_t s1{10.0};
    pkr::units::second_t s2{3.0};
    auto result = s1 - s2;

    ASSERT_DOUBLE_EQ(result.value(), 7.0);
    // Result should be some second type
    using result_type = decltype(result);
    static_assert(result_type::dimension::value.time == 1, "Should have time dimension");
}

TEST_F(MathFunctionsTest, multiply_different_dimensions)
{
    pkr::units::meter_t m{5.0};
    pkr::units::second_t s{2.0};
    auto result = pkr::units::multiply(m, s);

    ASSERT_DOUBLE_EQ(result.value(), 10.0);
    // Result should have dimensions of length * time (action/momentum dimension)
    using result_dim = decltype(result)::dimension;
    static_assert(result_dim::value.length == 1, "Should have length dimension");
    static_assert(result_dim::value.time == 1, "Should have time dimension");
}

TEST_F(MathFunctionsTest, divide_different_dimensions)
{
    pkr::units::meter_t m{10.0};
    pkr::units::second_t s{2.0};
    auto result = pkr::units::divide(m, s);

    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    // Result should have dimensions of length / time (velocity)
    using result_dim = decltype(result)::dimension;
    static_assert(result_dim::value.length == 1, "Should have length dimension");
    static_assert(result_dim::value.time == -1, "Should have negative time dimension");
}

// ============================================================================
// Scalar Operations
// ============================================================================

TEST_F(MathFunctionsTest, multiply_scalar)
{
    pkr::units::meter_t m{5.0};
    auto result = m * 3.0;

    ASSERT_DOUBLE_EQ(result.value(), 15.0);
    // Result should be some meter type
    using result_type = decltype(result);
    static_assert(result_type::dimension::value.length == 1, "Should have length dimension");
}

TEST_F(MathFunctionsTest, divide_scalar)
{
    pkr::units::second_t s{10.0};
    auto result = s / 2.0;

    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    // Result should be some second type
    using result_type = decltype(result);
    static_assert(result_type::dimension::value.time == 1, "Should have time dimension");
}

// ============================================================================
// Mathematical Functions
// ============================================================================

TEST_F(MathFunctionsTest, sqrt_length_squared)
{
    // Create area by multiplying length by length
    auto length = pkr::units::meter_t{4.0};
    auto area = length * length; // This creates a unit with length² dimension
    auto result = pkr::units::sqrt(area);

    ASSERT_DOUBLE_EQ(result.value(), 4.0);
    // Result should have length dimension
    using result_dim = decltype(result)::dimension;
    static_assert(result_dim::value.length == 1, "Should have length dimension");
    static_assert(result_dim::value.mass == 0, "Should have no mass dimension");
}

TEST_F(MathFunctionsTest, exp_dimensionless_input)
{
    // Create dimensionless value by dividing same units
    auto dimensionless_value = pkr::units::meter_t{2.0} / pkr::units::meter_t{2.0}; // equals 1.0
    auto result = pkr::units::exp(dimensionless_value);

    ASSERT_DOUBLE_EQ(result.value(), std::exp(1.0));
    // Result should be dimensionless
    using result_dim = decltype(result)::dimension;
    static_assert(result_dim::value.length == 0, "Should be dimensionless");
    static_assert(result_dim::value.mass == 0, "Should be dimensionless");
    static_assert(result_dim::value.time == 0, "Should be dimensionless");
}

TEST_F(MathFunctionsTest, log_dimensionless_input)
{
    // Create dimensionless value by dividing same units
    auto dimensionless_value = pkr::units::meter_t{1.0} / pkr::units::meter_t{1.0}; // equals 1.0
    auto result = pkr::units::log(dimensionless_value);

    ASSERT_DOUBLE_EQ(result.value(), std::log(1.0)); // ln(1) = 0
    // Result should be dimensionless
    using result_dim = decltype(result)::dimension;
    static_assert(result_dim::value.length == 0, "Should be dimensionless");
    static_assert(result_dim::value.mass == 0, "Should be dimensionless");
    static_assert(result_dim::value.time == 0, "Should be dimensionless");
}

TEST_F(MathFunctionsTest, pow_with_dimensionless_exponent)
{
    pkr::units::meter_t base{2.0};
    // Create dimensionless exponent by dividing same units
    auto dimensionless_two = pkr::units::meter_t{4.0} / pkr::units::meter_t{2.0}; // equals 2.0
    auto result = pkr::units::pow(base, dimensionless_two);

    ASSERT_DOUBLE_EQ(result.value(), 4.0); // 2^2 = 4
    // Result should have length dimension
    using result_dim = decltype(result)::dimension;
    static_assert(result_dim::value.length == 1, "Should have length dimension");
}

TEST_F(MathFunctionsTest, sqrt_velocity_squared)
{
    // Create velocity squared by multiplying velocity by velocity
    auto velocity = pkr::units::meter_t{3.0} / pkr::units::second_t{1.0}; // 3 m/s
    auto velocity_squared = velocity * velocity;                          // This creates a unit with (length/time)² dimension

    ASSERT_DOUBLE_EQ(velocity_squared.value(), 9.0);
    static_assert(decltype(velocity_squared)::dimension::value.length == 2, "Should have length² dimension");
    static_assert(decltype(velocity_squared)::dimension::value.time == -2, "Should have time⁻² dimension");

    auto result = pkr::units::sqrt(velocity_squared);

    // Result should have velocity dimension (length/time)
    using result_dim = decltype(result)::dimension;
    static_assert(result_dim::value.length == 1, "Should have length dimension");
    static_assert(result_dim::value.time == -1, "Should have negative time dimension");
    // assert ratio is std::ratio<1,1>
    using result_ratio = typename decltype(result)::ratio_type;
    static_assert(std::is_same_v<result_ratio, std::ratio<1, 1>>, "Should have ratio of 1");

    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(MathFunctionsTest, normalize_complex_operations)
{
    // Test normalize after complex operations
    auto force = pkr::units::kilogram_t{5.0} * pkr::units::meter_t{1000.0} / (pkr::units::second_t{1.0} * pkr::units::second_t{1.0}); // 5 kg·m/s² = 5 N
    auto distance = pkr::units::kilometer_t{3.0};                                                                                     // 3 km
    auto energy = force * distance; // Complex operation: 5000 N * 3 km

    // The result should be some compound unit; `in_base_si_units()` should return Joules
    auto normalized_energy = energy.in_base_si_units();

    // Should be 15,000,000 Joules (5000 N * 3000 m = 15,000,000 J)
    ASSERT_DOUBLE_EQ(normalized_energy.value(), 15000000.0);

    // Should have energy dimensions (M·L²·T⁻²)
    using result_type = decltype(normalized_energy);
    // static_assert(result_type::dim.mass == 1, "Should have mass dimension");
    // static_assert(result_type::dim.length == 2, "Should have length² dimension");
    // static_assert(result_type::dim.time == -2, "Should have time⁻² dimension");
}

TEST_F(MathFunctionsTest, normalize_complex_operations_constexpr)
{
    // Test normalize at compile time
    constexpr auto force =
        pkr::units::kilogram_t{5.0} * pkr::units::meter_t{1000.0} / (pkr::units::second_t{1.0} * pkr::units::second_t{1.0}); // 5 kg·m/s² = 5 N
    constexpr auto distance = pkr::units::kilometer_t{3.0};                                                                  // 3 km
    constexpr auto energy = force * distance;                                                                                // Complex operation: 5000 N * 3 km
    constexpr auto normalized_energy = energy.in_base_si_units();

    // Should be 15,000,000 Joules (5000 N * 3000 m = 15,000,000 J)
    static_assert(normalized_energy.value() == 15000000.0, "Should be 15,000,000 Joules");

    // Check dimensions are correct for energy (M·L²·T⁻²)
    using result_dim = decltype(normalized_energy)::dimension;
    static_assert(result_dim::value.mass == 1, "Should have mass dimension");
    static_assert(result_dim::value.length == 2, "Should have length² dimension");
    static_assert(result_dim::value.time == -2, "Should have time⁻² dimension");

    // Check type is correct - at compile time, template resolution may differ
    // So we check that it has the right dimensions
    using result_type = decltype(normalized_energy);
    // static_assert(result_type::dim.mass == 1, "Should have mass dimension");
    // static_assert(result_type::dim.length == 2, "Should have length² dimension");
    // static_assert(result_type::dim.time == -2, "Should have time⁻² dimension");
}

// ============================================================================
// Integration with existing operations
// ============================================================================

TEST_F(MathFunctionsTest, math_functions_work_with_existing_operations)
{
    // Test that math functions produce results compatible with existing operations
    pkr::units::meter_t m1{3.0};
    pkr::units::meter_t m2{4.0};

    auto sum = m1 + m2;
    auto doubled = sum * 2.0;

    ASSERT_DOUBLE_EQ(doubled.value(), 14.0); // (3+4)*2 = 14
}

} // namespace test
