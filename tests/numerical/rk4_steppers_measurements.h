#pragma once

#include "three_body_helpers.h"
#include <pkr_units/math/measurements/measurement_math_4d.h>

namespace pkr {
namespace test {
namespace numerical {

// ============================================================================
// RK4 Integration for Measurements with RSS Uncertainty Propagation
// ============================================================================

three_body_state_measurement_t rk4_step_meas(const three_body_state_measurement_t& state, const pkr::measurement_t<pkr::units::second_t>& dt) {
    three_body_state_measurement_t k1, k2, k3, k4;

    derivative_meas(state, k1);

    // state2 = state + 0.5 * dt * k1
    auto half_dt = pkr::math::divide_rss(dt, 2.0);
    three_body_state_measurement_t state2{
        state.pos1 + half_dt * k1.pos1,
        state.pos2 + half_dt * k1.pos2,
        state.pos3 + half_dt * k1.pos3,
        state.vel1 + half_dt * k1.vel1,
        state.vel2 + half_dt * k1.vel2,
        state.vel3 + half_dt * k1.vel3
    };

    derivative_meas(state2, k2);

    // state3 = state + 0.5 * dt * k2
    three_body_state_measurement_t state3{
        state.pos1 + half_dt * k2.pos1,
        state.pos2 + half_dt * k2.pos2,
        state.pos3 + half_dt * k2.pos3,
        state.vel1 + half_dt * k2.vel1,
        state.vel2 + half_dt * k2.vel2,
        state.vel3 + half_dt * k2.vel3
    };

    derivative_meas(state3, k3);


    // state4 = state + dt * k3
    three_body_state_measurement_t state4{
        state.pos1 + dt * k3.pos1,
        state.pos2 + dt * k3.pos2,
        state.pos3 + dt * k3.pos3,
        state.vel1 + dt * k3.vel1,
        state.vel2 + dt * k3.vel2,
        state.vel3 + dt * k3.vel3
    };

    derivative_meas(state4, k4);

    // result = state + (dt/6) * (k1 + 2*k2 + 2*k3 + k4)
    auto sixth_dt = pkr::math::divide_rss(dt, 6.0);
    three_body_state_measurement_t result{
        state.pos1 + sixth_dt * (k1.pos1 + 2.0 * k2.pos1 + 2.0 * k3.pos1 + k4.pos1),
        state.pos2 + sixth_dt * (k1.pos2 + 2.0 * k2.pos2 + 2.0 * k3.pos2 + k4.pos2),
        state.pos3 + sixth_dt * (k1.pos3 + 2.0 * k2.pos3 + 2.0 * k3.pos3 + k4.pos3),
        state.vel1 + sixth_dt * (k1.vel1 + 2.0 * k2.vel1 + 2.0 * k3.vel1 + k4.vel1),
        state.vel2 + sixth_dt * (k1.vel2 + 2.0 * k2.vel2 + 2.0 * k3.vel2 + k4.vel2),
        state.vel3 + sixth_dt * (k1.vel3 + 2.0 * k2.vel3 + 2.0 * k3.vel3 + k4.vel3)
    };

    return result;
}

// ============================================================================
// Energy Calculation for Stability Checking
// ============================================================================

pkr::measurement_t<pkr::units::joule_t> compute_total_energy_meas(const three_body_state_measurement_t& state) {
    // Kinetic energy
    auto ke1 = 0.5 * m1_meas * dot(state.vel1, state.vel1);
    auto ke2 = 0.5 * m2_meas * dot(state.vel2, state.vel2);
    auto ke3 = 0.5 * m3_meas * dot(state.vel3, state.vel3);
    auto kinetic = ke1 + ke2 + ke3;

    // Potential energy
    auto r12_vec = state.pos1 - state.pos2;
    auto r12_squared = dot(r12_vec, r12_vec);
    auto r12 = pkr::math::sqrt_rss(r12_squared);

    auto r13_vec = state.pos1 - state.pos3;
    auto r13_squared = dot(r13_vec, r13_vec);
    auto r13 = pkr::math::sqrt_rss(r13_squared);

    auto r23_vec = state.pos2 - state.pos3;
    auto r23_squared = dot(r23_vec, r23_vec);
    auto r23 = pkr::math::sqrt_rss(r23_squared);

    auto potential = -G_meas * (m1_meas*m2_meas/r12 + m1_meas*m3_meas/r13 + m2_meas*m3_meas/r23);

    return kinetic + potential;
}

} // namespace numerical
} // namespace test
} // namespace pkr