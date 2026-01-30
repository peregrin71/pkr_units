#include <cmath>
#include <gtest/gtest.h>
#include <pkr_units/measurements/measurement.h>
#include <pkr_units/math/measurements/measurement_math_rss.h>
#include <pkr_units/si_units.h>

using namespace ::testing;

namespace pkr
{
namespace units
{

// Area unit (m^2) for testing
using square_meter_t = details::unit_t<double, std::ratio<1>, dimension_t{2, 0, 0, 0, 0, 0, 0, 0}>;

// Dimensionless unit for testing
using scalar_t = details::unit_t<double, std::ratio<1>, scalar_dimension>;

} // namespace units
} // namespace pkr

class MeasurementRssTest : public Test
{
};

TEST_F(MeasurementRssTest, multiply_uses_rss_relative_uncertainty)
{
    pkr::units::measurement_t<pkr::units::meter_t> length{10.0, 1.0}; // 10% uncertainty
    pkr::units::measurement_t<pkr::units::meter_t> width{20.0, 2.0};  // 10% uncertainty

    auto result = pkr::units::math::multiply_rss(length, width);

    ASSERT_DOUBLE_EQ(result.value(), 200.0);

    auto expected_rel = std::sqrt(0.1 * 0.1 + 0.1 * 0.1);
    ASSERT_NEAR(result.uncertainty(), 200.0 * expected_rel, 1e-12);
}

TEST_F(MeasurementRssTest, divide_uses_rss_relative_uncertainty)
{
    pkr::units::measurement_t<pkr::units::meter_t> distance{10.0, 1.0}; // 10% uncertainty
    pkr::units::measurement_t<pkr::units::second_t> time{4.0, 0.2};     // 5% uncertainty

    auto result = pkr::units::math::divide_rss(distance, time);

    ASSERT_DOUBLE_EQ(result.value(), 2.5);

    auto expected_rel = std::sqrt(0.1 * 0.1 + 0.05 * 0.05);
    ASSERT_NEAR(result.uncertainty(), 2.5 * expected_rel, 1e-12);
}

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
    auto velocity_squared = pkr::units::math::square_rss(velocity);
    ASSERT_NEAR(velocity_squared.value(), 900.0, 1e-10);
    ASSERT_NEAR(velocity_squared.uncertainty(), 30.0, 1e-6);

    auto temp1 = pkr::units::math::multiply_rss(density, velocity_squared);
    ASSERT_NEAR(temp1.value(), 1102.5, 1e-2);
    ASSERT_NEAR(temp1.uncertainty(), 37.0245, 1e-3);
    auto temp2 = pkr::units::math::multiply_rss(temp1, drag_coefficient);
    ASSERT_NEAR(temp2.value(), 330.75, 1e-2);
    ASSERT_NEAR(temp2.uncertainty(), 24.6896, 1e-3);
    auto temp3 = pkr::units::math::multiply_rss(temp2, area);
    ASSERT_NEAR(temp3.value(), 826.875, 1e-3);
    ASSERT_NEAR(temp3.uncertainty(), 70.0272, 1e-3);
    auto drag_force = pkr::units::math::multiply_rss(0.5, temp3);

    ASSERT_NEAR(drag_force.value(), 413.4, 1e-1);
    ASSERT_NEAR(drag_force.uncertainty(), 35.0, 0.2);
}
