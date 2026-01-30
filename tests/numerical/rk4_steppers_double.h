#pragma once

#include "three_body_helpers.h"
#include "vector_math_double.h"

namespace pkr {
namespace test {
namespace numerical {

// ============================================================================
// RK4 Integration for Plain Doubles
// ============================================================================

three_body_state_double_t rk4_step_double(const three_body_state_double_t& state, double dt) {
    three_body_state_double_t k1, k2, k3, k4;

    derivative_double(state, k1);

    // state2 = state + 0.5 * dt * k1
    double half_dt = 0.5 * dt;
    three_body_state_double_t state2{
        state.pos1 + half_dt * k1.pos1,
        state.pos2 + half_dt * k1.pos2,
        state.pos3 + half_dt * k1.pos3,
        state.vel1 + half_dt * k1.vel1,
        state.vel2 + half_dt * k1.vel2,
        state.vel3 + half_dt * k1.vel3
    };

    derivative_double(state2, k2);

    // state3 = state + 0.5 * dt * k2
    three_body_state_double_t state3{
        state.pos1 + half_dt * k2.pos1,
        state.pos2 + half_dt * k2.pos2,
        state.pos3 + half_dt * k2.pos3,
        state.vel1 + half_dt * k2.vel1,
        state.vel2 + half_dt * k2.vel2,
        state.vel3 + half_dt * k2.vel3
    };

    derivative_double(state3, k3);

    // state4 = state + dt * k3
    three_body_state_double_t state4{
        state.pos1 + dt * k3.pos1,
        state.pos2 + dt * k3.pos2,
        state.pos3 + dt * k3.pos3,
        state.vel1 + dt * k3.vel1,
        state.vel2 + dt * k3.vel2,
        state.vel3 + dt * k3.vel3
    };

    derivative_double(state4, k4);

    // result = state + (dt/6) * (k1 + 2*k2 + 2*k3 + k4)
    double sixth_dt = dt / 6.0;
    three_body_state_double_t result{
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

double compute_total_energy_double(const three_body_state_double_t& state) {
    // Kinetic energy
    double ke1 = 0.5 * m1 * dot(state.vel1, state.vel1);
    double ke2 = 0.5 * m2 * dot(state.vel2, state.vel2);
    double ke3 = 0.5 * m3 * dot(state.vel3, state.vel3);
    double kinetic = ke1 + ke2 + ke3;

    // Potential energy
    auto r12_vec = state.pos1 - state.pos2;
    double r12_squared = dot(r12_vec, r12_vec);
    double r12 = std::sqrt(r12_squared);

    auto r13_vec = state.pos1 - state.pos3;
    double r13_squared = dot(r13_vec, r13_vec);
    double r13 = std::sqrt(r13_squared);

    auto r23_vec = state.pos2 - state.pos3;
    double r23_squared = dot(r23_vec, r23_vec);
    double r23 = std::sqrt(r23_squared);

    double potential = -G * (m1*m2/r12 + m1*m3/r13 + m2*m3/r23);

    return kinetic + potential;
}

} // namespace numerical
} // namespace test
} // namespace pkr