#pragma once

#include "three_body_helpers.h"
#include <pkr_units/math/unit/unit_math_4d.h>

namespace pkr
{
namespace test
{
namespace numerical
{

// ============================================================================
// RK4 Integration for SI Units with Stable Math
// ============================================================================

three_body_state_si_t rk4_step_si(const three_body_state_si_t& state, const pkr::units::second_t& dt)
{
    three_body_derivative_si_t k1, k2, k3, k4;

    k1 = derivative_si(state);

    // state2 = state + 0.5 * dt * k1
    auto half_dt = 0.5 * dt;
    three_body_state_si_t state2{
        state.pos1 + (half_dt * k1.dpos1),
        state.pos2 + (half_dt * k1.dpos2),
        state.pos3 + (half_dt * k1.dpos3),
        state.vel1 + (half_dt * k1.dvel1),
        state.vel2 + (half_dt * k1.dvel2),
        state.vel3 + (half_dt * k1.dvel3)};

    k2 = derivative_si(state2);

    // state3 = state + 0.5 * dt * k2
    three_body_state_si_t state3{
        state.pos1 + (half_dt * k2.dpos1),
        state.pos2 + (half_dt * k2.dpos2),
        state.pos3 + (half_dt * k2.dpos3),
        state.vel1 + (half_dt * k2.dvel1),
        state.vel2 + (half_dt * k2.dvel2),
        state.vel3 + (half_dt * k2.dvel3)};

    k3 = derivative_si(state3);

    // state4 = state + dt * k3
    three_body_state_si_t state4{
        state.pos1 + (dt * k3.dpos1),
        state.pos2 + (dt * k3.dpos2),
        state.pos3 + (dt * k3.dpos3),
        state.vel1 + (dt * k3.dvel1),
        state.vel2 + (dt * k3.dvel2),
        state.vel3 + (dt * k3.dvel3)};

    k4 = derivative_si(state4);

    // result = state + (dt/6) * (k1 + 2*k2 + 2*k3 + k4)
    auto sixth_dt = dt / 6.0;
    three_body_state_si_t result{
        state.pos1 + (sixth_dt * (k1.dpos1 + 2.0 * k2.dpos1 + 2.0 * k3.dpos1 + k4.dpos1)),
        state.pos2 + (sixth_dt * (k1.dpos2 + 2.0 * k2.dpos2 + 2.0 * k3.dpos2 + k4.dpos2)),
        state.pos3 + (sixth_dt * (k1.dpos3 + 2.0 * k2.dpos3 + 2.0 * k3.dpos3 + k4.dpos3)),
        state.vel1 + (sixth_dt * (k1.dvel1 + 2.0 * k2.dvel1 + 2.0 * k3.dvel1 + k4.dvel1)),
        state.vel2 + (sixth_dt * (k1.dvel2 + 2.0 * k2.dvel2 + 2.0 * k3.dvel2 + k4.dvel2)),
        state.vel3 + (sixth_dt * (k1.dvel3 + 2.0 * k2.dvel3 + 2.0 * k3.dvel3 + k4.dvel3))};

    return result;
}

// ============================================================================
// Energy Calculation for Stability Checking
// ============================================================================

pkr::units::joule_t compute_total_energy_si(const three_body_state_si_t& state)
{
    // Kinetic energy: 0.5 * m * v^2 for each body
    auto v1_squared = pkr::units::dot(state.vel1, state.vel1);
    auto v2_squared = pkr::units::dot(state.vel2, state.vel2);
    auto v3_squared = pkr::units::dot(state.vel3, state.vel3);

    auto ke1 = pkr::units::joule_t{(0.5 * m1_si * v1_squared).in_base_si_units().value()};
    auto ke2 = pkr::units::joule_t{(0.5 * m2_si * v2_squared).in_base_si_units().value()};
    auto ke3 = pkr::units::joule_t{(0.5 * m3_si * v3_squared).in_base_si_units().value()};
    auto kinetic = (ke1 + ke2) + ke3;

    // Potential energy: -G * m1*m2/r12 - G*m1*m3/r13 - G*m2*m3/r23
    auto diff12 = state.pos1 - state.pos2;
    auto r12_squared = pkr::units::dot(diff12, diff12);
    auto r12 = pkr::units::sqrt(r12_squared);

    auto diff13 = state.pos1 - state.pos3;
    auto r13_squared = pkr::units::dot(diff13, diff13);
    auto r13 = pkr::units::sqrt(r13_squared);

    auto diff23 = state.pos2 - state.pos3;
    auto r23_squared = pkr::units::dot(diff23, diff23);
    auto r23 = pkr::units::sqrt(r23_squared);

    auto pair12 = m1_si * m2_si / r12;
    auto pair13 = m1_si * m3_si / r13;
    auto pair23 = m2_si * m3_si / r23;
    auto sum_pairs = pair12 + pair13 + pair23;
    auto gm_sum = G_si * sum_pairs;
    auto potential = pkr::units::joule_t{(gm_sum * (-1.0)).in_base_si_units().value()};

    return kinetic + potential;
}

} // namespace numerical
} // namespace test
} // namespace pkr
