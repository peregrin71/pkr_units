#include <gtest/gtest.h>
#include <pkr_units/measurements/measurement.h>
#include <pkr_units/measurements/measurement_math_linear.h>
#include <pkr_units/si_units.h>

// Define test types
namespace pkr
{
namespace units
{

// Area unit (m²) for testing
using square_meter_t = details::unit_t<double, std::ratio<1>, dimension_t{2, 0, 0, 0, 0, 0, 0, 0}>;

// Dimensionless unit for testing
using scalar_t = details::unit_t<double, std::ratio<1>, scalar_dimension>;

} // namespace units
} // namespace pkr

namespace test
{

using namespace ::testing;

class MeasurementTest : public Test
{
};

// ============================================================================
// Basic Construction and Access
// ============================================================================

TEST_F(MeasurementTest, construction_and_access)
{
    // Create a measurement with value and uncertainty
    pkr::units::measurement_t<pkr::units::meter_t> length{5.0, 0.1};

    ASSERT_DOUBLE_EQ(length.value(), 5.0);
    ASSERT_DOUBLE_EQ(length.uncertainty(), 0.1);
    ASSERT_TRUE(length.is_valid());
}

TEST_F(MeasurementTest, negative_uncertainty_becomes_zero)
{
    // Negative uncertainty should be clamped to zero
    pkr::units::measurement_t<pkr::units::meter_t> length{5.0, -0.1};

    ASSERT_DOUBLE_EQ(length.uncertainty(), 0.0);
}

// ============================================================================
// Arithmetic Operations
// ============================================================================

TEST_F(MeasurementTest, addition_same_units)
{
    pkr::units::measurement_t<pkr::units::meter_t> len1{5.0, 0.1};
    pkr::units::measurement_t<pkr::units::meter_t> len2{3.0, 0.2};

    auto result = len1 + len2;

    // Values should add: 5.0 + 3.0 = 8.0
    ASSERT_DOUBLE_EQ(result.value(), 8.0);

    // Uncertainties should combine in quadrature: √(0.1² + 0.2²) = √(0.05) ≈ 0.2236
    ASSERT_NEAR(result.uncertainty(), 0.22360679774997897, 1e-10);
}

TEST_F(MeasurementTest, addition_different_units)
{
    pkr::units::measurement_t<pkr::units::meter_t> len1{5.0, 0.1};
    pkr::units::measurement_t<pkr::units::centimeter_t> len2{300.0, 5.0}; // 3.0 m ± 0.05 m

    auto result = len1 + len2;

    // Values should add with conversion: 5.0 m + 3.0 m = 8.0 m
    ASSERT_DOUBLE_EQ(result.value(), 8.0);

    // Uncertainties should combine in quadrature after conversion
    // 0.1 m and 0.05 m → √(0.1² + 0.05²) ≈ 0.1118
    ASSERT_NEAR(result.uncertainty(), 0.11180339887498948, 1e-10);
}

TEST_F(MeasurementTest, subtraction)
{
    pkr::units::measurement_t<pkr::units::second_t> time1{10.0, 0.1};
    pkr::units::measurement_t<pkr::units::second_t> time2{3.0, 0.2};

    auto result = time1 - time2;

    // Values should subtract: 10.0 - 3.0 = 7.0
    ASSERT_DOUBLE_EQ(result.value(), 7.0);

    // Uncertainties should combine in quadrature: √(0.1² + 0.2²) ≈ 0.2236
    ASSERT_NEAR(result.uncertainty(), 0.22360679774997897, 1e-10);
}

TEST_F(MeasurementTest, multiplication)
{
    pkr::units::measurement_t<pkr::units::meter_t> length{5.0, 0.1}; // 2% relative uncertainty
    pkr::units::measurement_t<pkr::units::meter_t> width{3.0, 0.15}; // 5% relative uncertainty

    auto result = length * width;

    // Values should multiply: 5.0 * 3.0 = 15.0 m²
    ASSERT_DOUBLE_EQ(result.value(), 15.0);

    // Relative uncertainties should add: 2% + 5% = 7%
    // Absolute uncertainty: 15.0 * 0.07 = 1.05
    ASSERT_NEAR(result.uncertainty(), 1.05, 1e-10);
}

TEST_F(MeasurementTest, division)
{
    pkr::units::measurement_t<pkr::units::meter_t> distance{10.0, 0.2}; // 2% relative uncertainty
    pkr::units::measurement_t<pkr::units::second_t> time{2.0, 0.1};     // 5% relative uncertainty

    auto result = distance / time;

    // Values should divide: 10.0 / 2.0 = 5.0 m/s
    ASSERT_DOUBLE_EQ(result.value(), 5.0);

    // Relative uncertainties should add: 2% + 5% = 7%
    // Absolute uncertainty: 5.0 * 0.07 = 0.35
    ASSERT_NEAR(result.uncertainty(), 0.35, 1e-10);
}

// ============================================================================
// Velocity Calculation Example
// ============================================================================

TEST_F(MeasurementTest, velocity_calculation)
{
    // Distance measurement
    pkr::units::measurement_t<pkr::units::millimeter_t> distance{5000.0, 50.0};

    // Time measurement
    pkr::units::measurement_t<pkr::units::second_t> time{2.5, 0.1};

    // Calculate velocity
    auto velocity = distance / time;

    // Values: 5000 mm / 2.5 s = 2000 mm/s = 2.0 m/s
    ASSERT_DOUBLE_EQ(velocity.value(), 2.0);

    // Relative uncertainties: distance (50/5000 = 1%) + time (0.1/2.5 = 4%) = 5%
    // Absolute uncertainty: 2.0 * 0.05 = 0.1 m/s
    ASSERT_NEAR(velocity.uncertainty(), 0.1, 1e-10);
}

// ============================================================================
// Relative Uncertainty
// ============================================================================

TEST_F(MeasurementTest, relative_uncertainty)
{
    pkr::units::measurement_t<pkr::units::meter_t> length{10.0, 0.5};

    auto rel_uncertainty = length.relative_uncertainty();

    // Relative uncertainty should be 0.5 / 10.0 = 0.05 (5%)
    ASSERT_DOUBLE_EQ(rel_uncertainty.value(), 0.05);
}

// ============================================================================
// Comparison and Output
// ============================================================================

TEST_F(MeasurementTest, equality)
{
    pkr::units::measurement_t<pkr::units::meter_t> len1{5.0, 0.1};
    pkr::units::measurement_t<pkr::units::meter_t> len2{5.0, 0.1};
    pkr::units::measurement_t<pkr::units::meter_t> len3{5.0, 0.2};

    ASSERT_EQ(len1, len2);
    ASSERT_NE(len1, len3);
}

TEST_F(MeasurementTest, output_stream)
{
    pkr::units::measurement_t<pkr::units::meter_t> length{5.0, 0.1};

    std::stringstream ss;
    ss << length;

    ASSERT_EQ(ss.str(), "5 +/- 0.1 m");
}

TEST_F(MeasurementTest, format_with_units)
{
    pkr::units::measurement_t<pkr::units::meter_t> length{5.0, 0.1};

    // Test ASCII formatting with +/-
    std::string ascii_result = std::format("{}", length);
    ASSERT_EQ(ascii_result, "5 +/- 0.1 m");

    // Test wide char formatting with ±
    std::wstring wide_result = std::format(L"{}", length);
    ASSERT_EQ(wide_result, L"5 \u00B1 0.1 m");
}

TEST_F(MeasurementTest, format_with_precision_specifier)
{
    pkr::units::measurement_t<pkr::units::meter_t> length{5.123456, 0.123456};

    // Test with 2 decimal places
    std::string result = std::format("{:.2f}", length);
    ASSERT_EQ(result, "5.12 +/- 0.12 m");
}

TEST_F(MeasurementTest, format_with_scientific_notation)
{
    pkr::units::measurement_t<pkr::units::meter_t> length{1.234567e6, 1.234567e4};

    // Test with scientific notation
    std::string result = std::format("{:e}", length);
    ASSERT_EQ(result, "1.234567e+06 +/- 1.234567e+04 m");
}

TEST_F(MeasurementTest, format_with_width_and_precision)
{
    pkr::units::measurement_t<pkr::units::meter_t> length{5.123, 0.456};

    // Test with width and precision
    std::string result = std::format("{:8.2f}", length);
    ASSERT_EQ(result, "    5.12 +/-     0.46 m");
}

// ============================================================================
// Math Functions with Uncertainty Propagation
// ============================================================================

TEST_F(MeasurementTest, math_sqrt)
{
    pkr::units::measurement_t<pkr::units::square_meter_t> area{16.0, 1.0}; // 16 ± 1 m²

    auto length = pkr::units::math::sqrt(area);

    // Value: √16 = 4 m
    ASSERT_DOUBLE_EQ(length.value(), 4.0);

    // Relative uncertainty: (1/2) * (1/16) = 1/32 ≈ 0.03125
    // Absolute uncertainty: 4 * 0.03125 = 0.125 m
    ASSERT_NEAR(length.uncertainty(), 0.125, 1e-10);
}

TEST_F(MeasurementTest, math_exp)
{
    // Dimensionless measurement
    pkr::units::measurement_t<pkr::units::scalar_t> exponent{1.0, 0.1}; // 1.0 ± 0.1

    auto result = pkr::units::math::exp(exponent);

    // Value: e^1 ≈ 2.71828
    ASSERT_NEAR(result.value(), 2.718281828459045, 1e-10);

    // Uncertainty: e^1 * 0.1 ≈ 0.2718
    ASSERT_NEAR(result.uncertainty(), 0.2718281828459045, 1e-10);
}

TEST_F(MeasurementTest, math_log)
{
    // Dimensionless measurement
    pkr::units::measurement_t<pkr::units::scalar_t> value{10.0, 1.0}; // 10.0 ± 1.0

    auto result = pkr::units::math::log(value);

    // Value: ln(10) ≈ 2.302585
    ASSERT_NEAR(result.value(), 2.302585092994046, 1e-10);

    // Uncertainty: relative uncertainty of input = 1.0/10.0 = 0.1
    ASSERT_NEAR(result.uncertainty(), 0.1, 1e-10);
}

TEST_F(MeasurementTest, math_pow_scalar_exponent)
{
    pkr::units::measurement_t<pkr::units::meter_t> length{2.0, 0.1}; // 2.0 ± 0.1 m

    auto result = pkr::units::math::pow(length, 3.0);

    // Value: 2^3 = 8 m³
    ASSERT_DOUBLE_EQ(result.value(), 8.0);

    // Relative uncertainty: |3| * (0.1/2.0) = 3 * 0.05 = 0.15
    // Absolute uncertainty: 8 * 0.15 = 1.2
    ASSERT_NEAR(result.uncertainty(), 1.2, 1e-10);
}

TEST_F(MeasurementTest, math_sin)
{
    // Angle measurement in radians
    pkr::units::measurement_t<pkr::units::radian_t> angle{0.0, 0.1}; // 0 ± 0.1 radians

    auto result = pkr::units::math::sin(angle);

    // Value: sin(0) = 0
    ASSERT_DOUBLE_EQ(result.value(), 0.0);

    // Uncertainty: |cos(0)| * 0.1 = 1 * 0.1 = 0.1
    ASSERT_NEAR(result.uncertainty(), 0.1, 1e-10);
}

TEST_F(MeasurementTest, math_cos)
{
    // Angle measurement in radians
    pkr::units::measurement_t<pkr::units::radian_t> angle{0.0, 0.1}; // 0 ± 0.1 radians

    auto result = pkr::units::math::cos(angle);

    // Value: cos(0) = 1
    ASSERT_DOUBLE_EQ(result.value(), 1.0);

    // Uncertainty: |sin(0)| * 0.1 = 0 * 0.1 = 0.0
    ASSERT_DOUBLE_EQ(result.uncertainty(), 0.0);
}

TEST_F(MeasurementTest, combined_uncertainty_method)
{
    pkr::units::measurement_t<pkr::units::meter_t> length{5.0, 0.1};

    // combined_uncertainty() should return the same as uncertainty()
    ASSERT_DOUBLE_EQ(length.combined_uncertainty().value(), 0.1);
    ASSERT_EQ(length.combined_uncertainty(), length.unit_uncertainty());
}

TEST_F(MeasurementTest, relative_uncertainty_percent)
{
    pkr::units::measurement_t<pkr::units::meter_t> length{10.0, 0.5};

    // 0.5 / 10.0 = 0.05 = 5%
    ASSERT_DOUBLE_EQ(pkr::units::math::relative_uncertainty_percent(length), 5.0);
}

TEST_F(MeasurementTest, drag_force_calculation)
{
    // Drag force calculation: F_d = (1/2) * ρ * v² * C_d * A
    // Using realistic values for a car moving through air

    // Air density: 1.225 ± 0.005 kg/m³
    pkr::units::measurement_t<pkr::units::kilogram_per_cubic_meter_t> density{1.225, 0.005};

    // Velocity: 30.0 ± 0.5 m/s
    pkr::units::measurement_t<pkr::units::meter_per_second_t> velocity{30.0, 0.5};

    // Drag coefficient: 0.30 ± 0.02 (dimensionless)
    pkr::units::measurement_t<pkr::units::scalar_t> drag_coefficient{0.30, 0.02};

    // Cross-sectional area: 2.5 ± 0.1 m²
    pkr::units::measurement_t<pkr::units::square_meter_t> area{2.5, 0.1};

    // Calculate drag force: F_d = 0.5 * ρ * v² * C_d * A
    auto velocity_squared = pkr::units::math::multiply(velocity, velocity);
    // v² = 30² = 900 m²/s², uncertainty: 2 * (0.5/30) * 900 ≈ 30 m²/s²
    ASSERT_NEAR(velocity_squared.value(), 900.0, 1e-10);
    ASSERT_NEAR(velocity_squared.uncertainty(), 30.0, 1e-1);

    auto temp1 = pkr::units::math::multiply(density, velocity_squared);
    // ρ * v² = 1.225 * 900 = 1102.5 kg/(m·s²), uncertainty ≈ 41.2 kg/(m·s²)
    ASSERT_NEAR(temp1.value(), 1102.5, 1e-1);
    ASSERT_NEAR(temp1.uncertainty(), 41.2, 1e-1);

    auto temp2 = pkr::units::math::multiply(temp1, drag_coefficient);
    // temp1 * C_d = 1102.5 * 0.30 = 330.75 kg/(m·s²), uncertainty ≈ 34.4 kg/(m·s²)
    ASSERT_NEAR(temp2.value(), 330.75, 1e-2);
    ASSERT_NEAR(temp2.uncertainty(), 34.4, 1e-1);

    auto temp3 = pkr::units::math::multiply(temp2, area);

    // temp2 * A = 330.75 * 2.5 = 826.875 kg/(m·s²), uncertainty ≈ 119.1 kg/(m·s²)
    ASSERT_NEAR(temp3.value(), 826.875, 1e-3);
    ASSERT_NEAR(temp3.uncertainty(), 119.1, 1e-1);

    auto drag_force = pkr::units::math::multiply(pkr::units::measurement_t<pkr::units::scalar_t>{0.5, 0.0}, temp3);

    // Expected calculation:
    // v² = 30² = 900 m²/s²
    // 0.5 * 1.225 * 900 * 0.30 * 2.5 = 0.5 * 1.225 * 900 * 0.30 * 2.5
    // = 0.5 * 1.225 = 0.6125
    // = 0.6125 * 900 = 551.25
    // = 551.25 * 0.30 = 165.375
    // = 165.375 * 2.5 = 413.4375 N

    ASSERT_NEAR(drag_force.value(), 413.4, 1e-1);

    // Dimensional uncertainty analysis (linear sum, library behavior):
    // Relative uncertainties: rho: 0.408%, v: 1.67% (x2 for v^2 = 3.33%), Cd: 6.67%, A: 4.00%
    // For step-by-step multiplication: relative uncertainties add
    // Total relative uncertainty: 0.408% + 3.33% + 6.67% + 4.00% = 14.41%
    // Absolute uncertainty: 413.44 N x 0.1441 ~= 59.6 N
    ASSERT_NEAR(drag_force.uncertainty(), 59.6, 0.1);

    // Verify the result has the correct unit type (force)
    // Note: The actual type checking would depend on how the unit system handles
    // complex multiplications. For now, we just verify the calculation works.
    // using expected_force_type = pkr::units::newton_t;
    // static_assert(std::is_same_v<decltype(drag_force.value()), expected_force_type>,
    //               "Drag force should have newton units");
}

TEST_F(MeasurementTest, relative_uncertainty_zero_value_is_zero)
{
    pkr::units::measurement_t<pkr::units::meter_t> length{0.0, 0.5};

    auto rel_uncertainty = length.relative_uncertainty();

    // Special case: zero value => relative uncertainty treated as 0 (not NaN/inf).
    ASSERT_DOUBLE_EQ(rel_uncertainty.value(), 0.0);
}

TEST_F(MeasurementTest, multiplication_with_zero_value_has_zero_uncertainty)
{
    pkr::units::measurement_t<pkr::units::meter_t> length{0.0, 0.5};
    pkr::units::measurement_t<pkr::units::meter_t> width{3.0, 0.15};

    auto result = length * width;

    ASSERT_DOUBLE_EQ(result.value(), 0.0);
    // Special case: zero value => relative uncertainty treated as 0, so absolute uncertainty is 0.
    ASSERT_DOUBLE_EQ(result.uncertainty(), 0.0);
}

} // namespace test
