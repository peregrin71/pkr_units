#pragma once

#include "three_body_helpers.h"
#include "vector_math_double.h"

namespace pkr
{
namespace test
{
namespace numerical
{

// ============================================================================
// RK4 Integration for Plain Doubles
// ============================================================================

three_body_state_double_t rk4_step_double(const three_body_state_double_t& state, double dt)
{
    three_body_state_double_t k1, k2, k3, k4;

    derivative_double(state, k1);

    // state2 = state + 0.5 * dt * k1
    double half_dt = 0.5 * dt;
    three_body_state_double_t state2{
        state.pos1 + (half_dt * k1.pos1),
        state.pos2 + (half_dt * k1.pos2),
        state.pos3 + (half_dt * k1.pos3),
        state.vel1 + (half_dt * k1.vel1),
        state.vel2 + (half_dt * k1.vel2),
        state.vel3 + (half_dt * k1.vel3)};

    derivative_double(state2, k2);

    // state3 = state + 0.5 * dt * k2
    three_body_state_double_t state3{
        state.pos1 + (half_dt * k2.pos1),
        state.pos2 + (half_dt * k2.pos2),
        state.pos3 + (half_dt * k2.pos3),
        state.vel1 + (half_dt * k2.vel1),
        state.vel2 + (half_dt * k2.vel2),
        state.vel3 + (half_dt * k2.vel3)};

    derivative_double(state3, k3);

    // state4 = state + dt * k3
    three_body_state_double_t state4{
        state.pos1 + (dt * k3.pos1),
        state.pos2 + (dt * k3.pos2),
        state.pos3 + (dt * k3.pos3),
        state.vel1 + (dt * k3.vel1),
        state.vel2 + (dt * k3.vel2),
        state.vel3 + (dt * k3.vel3)};

    derivative_double(state4, k4);

    // result = state + (dt/6) * (k1 + 2*k2 + 2*k3 + k4)
    double sixth_dt = dt / 6.0;
    three_body_state_double_t result{
        state.pos1 + (sixth_dt * (k1.pos1 + 2.0 * k2.pos1 + 2.0 * k3.pos1 + k4.pos1)),
        state.pos2 + (sixth_dt * (k1.pos2 + 2.0 * k2.pos2 + 2.0 * k3.pos2 + k4.pos2)),
        state.pos3 + (sixth_dt * (k1.pos3 + 2.0 * k2.pos3 + 2.0 * k3.pos3 + k4.pos3)),
        state.vel1 + (sixth_dt * (k1.vel1 + 2.0 * k2.vel1 + 2.0 * k3.vel1 + k4.vel1)),
        state.vel2 + (sixth_dt * (k1.vel2 + 2.0 * k2.vel2 + 2.0 * k3.vel2 + k4.vel2)),
        state.vel3 + (sixth_dt * (k1.vel3 + 2.0 * k2.vel3 + 2.0 * k3.vel3 + k4.vel3))};

    return result;
}

} // namespace numerical
} // namespace test
} // namespace pkr
