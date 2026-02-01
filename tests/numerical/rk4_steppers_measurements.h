#pragma once

#include "three_body_helpers.h"
#include <pkr_units/math/measurements/measurement_math_4d.h>

namespace pkr
{
namespace test
{
namespace numerical
{

using namespace pkr::units::math;

// ============================================================================
// RK4 Integration for Measurements with RSS Uncertainty Propagation
// ============================================================================

three_body_state_measurement_t rk4_step_meas(const three_body_state_measurement_t& state, const pkr::units::measurement_t<pkr::units::second_t>& dt)
{
    three_body_derivative_measurement_t k1, k2, k3, k4;

    k1 = derivative_meas(state);

    // state2 = state + 0.5 * dt * k1
    auto half_dt = dt / 2.0;
    three_body_state_measurement_t state2{
        state.pos1 + (half_dt * k1.dpos1),
        state.pos2 + (half_dt * k1.dpos2),
        state.pos3 + (half_dt * k1.dpos3),
        state.vel1 + (half_dt * k1.dvel1),
        state.vel2 + (half_dt * k1.dvel2),
        state.vel3 + (half_dt * k1.dvel3)};

    k2 = derivative_meas(state2);

    // state3 = state + 0.5 * dt * k2
    three_body_state_measurement_t state3{
        state.pos1 + (half_dt * k2.dpos1),
        state.pos2 + (half_dt * k2.dpos2),
        state.pos3 + (half_dt * k2.dpos3),
        state.vel1 + (half_dt * k2.dvel1),
        state.vel2 + (half_dt * k2.dvel2),
        state.vel3 + (half_dt * k2.dvel3)};

    k3 = derivative_meas(state3);

    // state4 = state + dt * k3
    three_body_state_measurement_t state4{
        state.pos1 + (dt * k3.dpos1),
        state.pos2 + (dt * k3.dpos2),
        state.pos3 + (dt * k3.dpos3),
        state.vel1 + (dt * k3.dvel1),
        state.vel2 + (dt * k3.dvel2),
        state.vel3 + (dt * k3.dvel3)};

    k4 = derivative_meas(state4);

    // result = state + (dt/6) * (k1 + 2*k2 + 2*k3 + k4)
    auto sixth_dt = dt / 6.0;
    auto k_sum_pos1 = (k1.dpos1 + (2.0 * k2.dpos1) + (2.0 * k3.dpos1) + k4.dpos1);
    auto k_sum_pos2 = (k1.dpos2 + (2.0 * k2.dpos2) + (2.0 * k3.dpos2) + k4.dpos2);
    auto k_sum_pos3 = (k1.dpos3 + (2.0 * k2.dpos3) + (2.0 * k3.dpos3) + k4.dpos3);
    auto k_sum_vel1 = (k1.dvel1 + (2.0 * k2.dvel1) + (2.0 * k3.dvel1) + k4.dvel1);
    auto k_sum_vel2 = (k1.dvel2 + (2.0 * k2.dvel2) + (2.0 * k3.dvel2) + k4.dvel2);
    auto k_sum_vel3 = (k1.dvel3 + (2.0 * k2.dvel3) + (2.0 * k3.dvel3) + k4.dvel3);

    three_body_state_measurement_t result{
        state.pos1 + (sixth_dt * k_sum_pos1),
        state.pos2 + (sixth_dt * k_sum_pos2),
        state.pos3 + (sixth_dt * k_sum_pos3),
        state.vel1 + (sixth_dt * k_sum_vel1),
        state.vel2 + (sixth_dt * k_sum_vel2),
        state.vel3 + (sixth_dt * k_sum_vel3)};

    return result;
}

// ============================================================================
// Energy Calculation for Stability Checking
// ============================================================================

pkr::units::measurement_t<pkr::units::joule_t> compute_total_energy_meas(const three_body_state_measurement_t& state)
{
    // Kinetic energy: 0.5 * m * v^2 for each body
    auto v1_squared = pkr::units::math::sum_of_squares_rss(state.vel1.x, state.vel1.y, state.vel1.z);
    auto v2_squared = pkr::units::math::sum_of_squares_rss(state.vel2.x, state.vel2.y, state.vel2.z);
    auto v3_squared = pkr::units::math::sum_of_squares_rss(state.vel3.x, state.vel3.y, state.vel3.z);

    // Use a reusable constexpr scalar measurement for 1/2 so multiply_rss resolves correctly
    constexpr auto half_scalar = pkr::units::measurement_t<pkr::units::scalar_t>{0.5, 0.0};

    // Compute kinetic energy pieces with one math op per line for easier debugging
    auto half_m1 = pkr::units::math::multiply_rss(half_scalar, m1_meas);
    auto ke1 = pkr::units::math::multiply_rss(half_m1, v1_squared);

    auto half_m2 = pkr::units::math::multiply_rss(half_scalar, m2_meas);
    auto ke2 = pkr::units::math::multiply_rss(half_m2, v2_squared);

    auto half_m3 = pkr::units::math::multiply_rss(half_scalar, m3_meas);
    auto ke3 = pkr::units::math::multiply_rss(half_m3, v3_squared);

    auto kin12 = pkr::units::math::add_rss(ke1, ke2);
    auto kinetic = pkr::units::math::add_rss(kin12, ke3);

    // Potential energy: -G * m1*m2/r12 - G*m1*m3/r13 - G*m2*m3/r23
    auto diff12 = state.pos1 - state.pos2;
    auto r12_squared = pkr::units::math::add_rss(
        pkr::units::math::add_rss(pkr::units::math::multiply_rss(diff12.x, diff12.x), pkr::units::math::multiply_rss(diff12.y, diff12.y)),
        pkr::units::math::multiply_rss(diff12.z, diff12.z));
    auto r12 = pkr::units::math::sqrt_rss(r12_squared);

    auto diff13 = state.pos1 - state.pos3;
    auto r13_squared = pkr::units::math::add_rss(
        pkr::units::math::add_rss(pkr::units::math::multiply_rss(diff13.x, diff13.x), pkr::units::math::multiply_rss(diff13.y, diff13.y)),
        pkr::units::math::multiply_rss(diff13.z, diff13.z));
    auto r13 = pkr::units::math::sqrt_rss(r13_squared);

    auto diff23 = state.pos2 - state.pos3;
    auto r23_squared = pkr::units::math::add_rss(
        pkr::units::math::add_rss(pkr::units::math::multiply_rss(diff23.x, diff23.x), pkr::units::math::multiply_rss(diff23.y, diff23.y)),
        pkr::units::math::multiply_rss(diff23.z, diff23.z));
    auto r23 = pkr::units::math::sqrt_rss(r23_squared);

    auto potential = pkr::units::math::multiply_rss(
        -G_meas,
        pkr::units::math::add_rss(
            pkr::units::math::add_rss(
                pkr::units::math::divide_rss(pkr::units::math::multiply_rss(m1_meas, m2_meas), r12),
                pkr::units::math::divide_rss(pkr::units::math::multiply_rss(m1_meas, m3_meas), r13)),
            pkr::units::math::divide_rss(pkr::units::math::multiply_rss(m2_meas, m3_meas), r23)));

    return pkr::units::math::add_rss(kinetic, potential);
}

// ============================================================================
// Tests for RK4 measurements helpers (included by test TU)
// ============================================================================

#include <gtest/gtest.h>
#include <cmath>

using namespace pkr::test::numerical;

TEST(RK4MeasurementsTest, MultiplyRSSUsesScalarMeasurement) {
    auto half = pkr::units::measurement_t<pkr::units::scalar_t>{0.5, 0.0};
    auto res = pkr::units::math::multiply_rss(half, m1_meas);
    EXPECT_TRUE(std::isfinite(res.value()));
    EXPECT_GE(res.uncertainty(), 0.0);
}

TEST(RK4MeasurementsTest, ComputeTotalEnergyMeas_Sanity) {
    auto energy = compute_total_energy_meas(initial_state_meas);
    EXPECT_TRUE(std::isfinite(energy.value()));
    EXPECT_GE(energy.uncertainty(), 0.0);
}

TEST(RK4MeasurementsTest, RK4StepMeas_NoNaNAndUnitsPreserved) {
    auto dt = pkr::units::measurement_t<pkr::units::second_t>{1.0, 0.0};
    auto next = rk4_step_meas(initial_state_meas, dt);

    // Verify values and uncertainties are finite and non-negative respectively
    EXPECT_TRUE(std::isfinite(next.pos1.x.value()));
    EXPECT_TRUE(std::isfinite(next.vel1.x.value()));
    EXPECT_GE(next.pos1.x.uncertainty(), 0.0);
    EXPECT_GE(next.vel1.x.uncertainty(), 0.0);
}

} // namespace numerical
} // namespace test
} // namespace pkr