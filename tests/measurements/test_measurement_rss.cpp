#include <cmath>
#include <gtest/gtest.h>
#include <pkr_units/measurements/measurement.h>
#include <pkr_units/math/measurements/measurement_math_rss.h>
#include <pkr_units/si_units.h>
#include <pkr_units/units/dimensionless/scalar.h>
#include <pkr_units/units/derived/area/area_units.h>

using namespace ::testing;

namespace pkr
{
namespace units
{

} // namespace units
} // namespace pkr

class MeasurementRssTest : public Test
{
};

TEST_F(MeasurementRssTest, drag_force_calculation_rss)
{
    // Drag force calculation: F_d = (1/2) * rho * v^2 * C_d * A
    // Using RSS for relative uncertainty propagation in multiply/divide.

    // Air density: 1.225 ± 0.005 kg/m^3
    pkr::units::measurement_t<pkr::units::kilogram_per_cubic_meter_t> density{1.225, 0.005};

    // Velocity: 30.0 ± 0.5 m/s
    pkr::units::measurement_t<pkr::units::meter_per_second_t> velocity{30.0, 0.5};

    // Drag coefficient: 0.30 ± 0.02 (dimensionless)
    pkr::units::measurement_t<pkr::units::scalar_t> drag_coefficient{0.30, 0.02};

    // Cross-sectional area: 2.5 ± 0.1 m^2
    pkr::units::measurement_t<pkr::units::square_meter_t> area{2.5, 0.1};

    // Same measurement used twice -> fully correlated, rel uncertainty = 2 * dv/v
    // For fully correlated values use square_rss NOT multiply_rss with the same values
    auto velocity_squared = pkr::units::square_rss(velocity);
    ASSERT_NEAR(velocity_squared.value(), 900.0, 1e-10);
    ASSERT_NEAR(velocity_squared.uncertainty(), 30.0, 1e-6);

    auto temp1 = pkr::units::multiply_rss(density, velocity_squared);
    ASSERT_NEAR(temp1.value(), 1102.5, 1e-2);
    ASSERT_NEAR(temp1.uncertainty(), 37.0245, 1e-3);
    auto temp2 = pkr::units::multiply_rss(temp1, drag_coefficient);
    ASSERT_NEAR(temp2.value(), 330.75, 1e-2);
    ASSERT_NEAR(temp2.uncertainty(), 24.6896, 1e-3);
    auto temp3 = pkr::units::multiply_rss(temp2, area);
    ASSERT_NEAR(temp3.value(), 826.875, 1e-3);
    ASSERT_NEAR(temp3.uncertainty(), 70.0272, 1e-3);
    auto drag_force = pkr::units::multiply_rss(0.5, temp3);

    ASSERT_NEAR(drag_force.value(), 413.4, 1e-1);
    ASSERT_NEAR(drag_force.uncertainty(), 35.0, 0.2);
}
TEST_F(MeasurementRssTest, pow_integer_exponent_rss)
{
    // Test power function with fully correlated uncertainty
    // Measurement: x = 2.0 ± 0.1 m
    pkr::units::measurement_t<pkr::units::meter_t> measurement{2.0, 0.1};

    // x^0 should equal 1 (dimensionless)
    auto power_zero = pkr::units::pow_rss<0>(measurement);
    ASSERT_DOUBLE_EQ(power_zero.value(), 1.0);
    ASSERT_DOUBLE_EQ(power_zero.uncertainty(), 0.0);

    // x^2 = 4 m^2, relative uncertainty = 2 * 0.1/2.0 = 0.1, absolute = 0.4
    auto power_two = pkr::units::pow_rss<2>(measurement);
    ASSERT_DOUBLE_EQ(power_two.value(), 4.0);
    ASSERT_NEAR(power_two.uncertainty(), 0.4, 1e-10);

    // x^3 = 8 m^3, relative uncertainty = 3 * 0.1/2.0 = 0.15, absolute = 1.2
    auto power_three = pkr::units::pow_rss<3>(measurement);
    ASSERT_DOUBLE_EQ(power_three.value(), 8.0);
    ASSERT_NEAR(power_three.uncertainty(), 1.2, 1e-10);

    // x^-1 = 0.5 m^-1, relative uncertainty = 1 * 0.1/2.0 = 0.05, absolute = 0.025
    auto power_neg_one = pkr::units::pow_rss<-1>(measurement);
    ASSERT_DOUBLE_EQ(power_neg_one.value(), 0.5);
    ASSERT_NEAR(power_neg_one.uncertainty(), 0.025, 1e-10);
}

TEST_F(MeasurementRssTest, sin_rss_measurement)
{
    // Angle measurement in radians: 0 ± 0.1 rad
    pkr::units::measurement_t<pkr::units::radian_t> angle{0.0, 0.1};

    auto result = pkr::units::sin_rss(angle);

    // sin(0) = 0
    ASSERT_NEAR(result.value(), 0.0, 1e-10);
    // Uncertainty: |cos(0)| * 0.1 = 1.0 * 0.1 = 0.1
    ASSERT_NEAR(result.uncertainty(), 0.1, 1e-10);
}

TEST_F(MeasurementRssTest, cos_rss_measurement)
{
    // Angle measurement in radians: 0 ± 0.1 rad
    pkr::units::measurement_t<pkr::units::radian_t> angle{0.0, 0.1};

    auto result = pkr::units::cos_rss(angle);

    // cos(0) = 1
    ASSERT_NEAR(result.value(), 1.0, 1e-10);
    // Uncertainty: |sin(0)| * 0.1 = 0.0 * 0.1 = 0.0
    ASSERT_NEAR(result.uncertainty(), 0.0, 1e-10);
}

TEST_F(MeasurementRssTest, tan_rss_measurement)
{
    // Angle measurement in radians: pi/4 ± 0.05 rad
    pkr::units::measurement_t<pkr::units::radian_t> angle{M_PI / 4.0, 0.05};

    auto result = pkr::units::tan_rss(angle);

    // tan(pi/4) = 1
    ASSERT_NEAR(result.value(), 1.0, 1e-10);
    // Uncertainty: sec²(pi/4) * 0.05 = 2 * 0.05 = 0.1
    ASSERT_NEAR(result.uncertainty(), 0.1, 1e-10);
}