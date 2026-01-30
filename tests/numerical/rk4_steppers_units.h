#pragma once

#include "three_body_helpers.h"
#include <pkr_units/math/unit/unit_math_4d.h>

namespace pkr {
namespace test {
namespace numerical {

// ============================================================================
// RK4 Integration for SI Units with Stable Math
// ============================================================================

three_body_state_si_t rk4_step_si(const three_body_state_si_t& state, const pkr::units::second_t& dt) {
    three_body_state_si_t k1, k2, k3, k4;

    derivative_si(state, k1);

    // state2 = state + 0.5 * dt * k1
    auto half_dt = pkr::numerical::stable_multiply(0.5, dt);
    three_body_state_si_t state2{
        state.pos1 + half_dt * k1.pos1,
        state.pos2 + half_dt * k1.pos2,
        state.pos3 + half_dt * k1.pos3,
        state.vel1 + half_dt * k1.vel1,
        state.vel2 + half_dt * k1.vel2,
        state.vel3 + half_dt * k1.vel3
    };

    derivative_si(state2, k2);

    // state3 = state + 0.5 * dt * k2
    three_body_state_si_t state3{
        state.pos1 + half_dt * k2.pos1,
        state.pos2 + half_dt * k2.pos2,
        state.pos3 + half_dt * k2.pos3,
        state.vel1 + half_dt * k2.vel1,
        state.vel2 + half_dt * k2.vel2,
        state.vel3 + half_dt * k2.vel3
    };

    derivative_si(state3, k3);

    // state4 = state + dt * k3
    three_body_state_si_t state4{
        state.pos1 + dt * k3.pos1,
        state.pos2 + dt * k3.pos2,
        state.pos3 + dt * k3.pos3,
        state.vel1 + dt * k3.vel1,
        state.vel2 + dt * k3.vel2,
        state.vel3 + dt * k3.vel3
    };

    derivative_si(state4, k4);

    // result = state + (dt/6) * (k1 + 2*k2 + 2*k3 + k4)
    auto sixth_dt = pkr::numerical::stable_divide(dt, 6.0);
    three_body_state_si_t result{
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

pkr::units::joule_t compute_total_energy_si(const three_body_state_si_t& state) {
    // Kinetic energy
    auto ke1 = 0.5 * m1_si * (state.vel1.x*state.vel1.x + state.vel1.y*state.vel1.y + state.vel1.z*state.vel1.z);
    auto ke2 = 0.5 * m2_si * (state.vel2.x*state.vel2.x + state.vel2.y*state.vel2.y + state.vel2.z*state.vel2.z);
    auto ke3 = 0.5 * m3_si * (state.vel3.x*state.vel3.x + state.vel3.y*state.vel3.y + state.vel3.z*state.vel3.z);
    auto kinetic = ke1 + ke2 + ke3;

    // Potential energy
    auto diff12 = state.pos1 - state.pos2;
    auto r12_squared = diff12.x*diff12.x + diff12.y*diff12.y + diff12.z*diff12.z;
    auto r12 = pkr::numerical::stable_sqrt(r12_squared);

    auto diff13 = state.pos1 - state.pos3;
    auto r13_squared = diff13.x*diff13.x + diff13.y*diff13.y + diff13.z*diff13.z;
    auto r13 = pkr::numerical::stable_sqrt(r13_squared);

    auto diff23 = state.pos2 - state.pos3;
    auto r23_squared = diff23.x*diff23.x + diff23.y*diff23.y + diff23.z*diff23.z;
    auto r23 = pkr::numerical::stable_sqrt(r23_squared);

    auto potential = -G_si * (m1_si*m2_si/r12 + m1_si*m3_si/r13 + m2_si*m3_si/r23);

    return kinetic + potential;
}

} // namespace numerical
} // namespace test
} // namespace pkr