#pragma once

#include "three_body_helpers.h"
#include "vector_math_double.h"
#include <pkr_units/math/unit/unit_math_4d.h>

namespace pkr {
namespace test {
namespace numerical {

// ============================================================================
// RK4 Step Functions
// ============================================================================

// RK4 step for plain doubles
three_body_state_double_t rk4_step_double(const three_body_state_double_t& state, double dt) {
    three_body_state_double_t k1, k2, k3, k4;

    derivative_double(state, k1);

    // state2 = state + 0.5 * dt * k1
    double half_dt = 0.5 * dt;
    three_body_state_double_t state2 = {
        state.pos1 + half_dt * k1.pos1,
        state.pos2 + half_dt * k1.pos2,
        state.pos3 + half_dt * k1.pos3,
        state.vel1 + half_dt * k1.vel1,
        state.vel2 + half_dt * k1.vel2,
        state.vel3 + half_dt * k1.vel3
    };
    derivative_double(state2, k2);

    // state3 = state + 0.5 * dt * k2
    three_body_state_double_t state3 = {
        state.pos1 + half_dt * k2.pos1,
        state.pos2 + half_dt * k2.pos2,
        state.pos3 + half_dt * k2.pos3,
        state.vel1 + half_dt * k2.vel1,
        state.vel2 + half_dt * k2.vel2,
        state.vel3 + half_dt * k2.vel3
    };
    derivative_double(state3, k3);

    // state4 = state + dt * k3
    three_body_state_double_t state4 = {
        state.pos1 + dt * k3.pos1,
        state.pos2 + dt * k3.pos2,
        state.pos3 + dt * k3.pos3,
        state.vel1 + dt * k3.vel1,
        state.vel2 + dt * k3.vel2,
        state.vel3 + dt * k3.vel3
    };
    derivative_double(state4, k4);

    // result = state + dt/6 * (k1 + 2*k2 + 2*k3 + k4)
    double sixth_dt = dt / 6.0;
    three_body_state_double_t result = {
        state.pos1 + sixth_dt * (k1.pos1 + 2.0 * k2.pos1 + 2.0 * k3.pos1 + k4.pos1),
        state.pos2 + sixth_dt * (k1.pos2 + 2.0 * k2.pos2 + 2.0 * k3.pos2 + k4.pos2),
        state.pos3 + sixth_dt * (k1.pos3 + 2.0 * k2.pos3 + 2.0 * k3.pos3 + k4.pos3),
        state.vel1 + sixth_dt * (k1.vel1 + 2.0 * k2.vel1 + 2.0 * k3.vel1 + k4.vel1),
        state.vel2 + sixth_dt * (k1.vel2 + 2.0 * k2.vel2 + 2.0 * k3.vel2 + k4.vel2),
        state.vel3 + sixth_dt * (k1.vel3 + 2.0 * k2.vel3 + 2.0 * k3.vel3 + k4.vel3)
    };

    return result;
}

// RK4 step for SI units using stable math
three_body_state_si_t rk4_step_si(const three_body_state_si_t& state, const pkr::units::second_t& dt) {
    three_body_state_si_t k1, k2, k3, k4;

    derivative_si(state, k1);

    // state2 = state + 0.5 * dt * k1
    auto half_dt = pkr::numerical::stable_multiply(0.5, dt);
    three_body_state_si_t state2 = {
        state.pos1 + half_dt * k1.pos1,
        state.pos2 + half_dt * k1.pos2,
        state.pos3 + half_dt * k1.pos3,
        state.vel1 + half_dt * k1.vel1,
        state.vel2 + half_dt * k1.vel2,
        state.vel3 + half_dt * k1.vel3
    };
    derivative_si(state2, k2);

    // state3 = state + 0.5 * dt * k2
    three_body_state_si_t state3 = {
        state.pos1 + half_dt * k2.pos1,
        state.pos2 + half_dt * k2.pos2,
        state.pos3 + half_dt * k2.pos3,
        state.vel1 + half_dt * k2.vel1,
        state.vel2 + half_dt * k2.vel2,
        state.vel3 + half_dt * k2.vel3
    };
    derivative_si(state3, k3);

    // state4 = state + dt * k3
    three_body_state_si_t state4 = {
        state.pos1 + dt * k3.pos1,
        state.pos2 + dt * k3.pos2,
        state.pos3 + dt * k3.pos3,
        state.vel1 + dt * k3.vel1,
        state.vel2 + dt * k3.vel2,
        state.vel3 + dt * k3.vel3
    };
    derivative_si(state4, k4);

    // result = state + dt/6 * (k1 + 2*k2 + 2*k3 + k4)
    auto sixth_dt = pkr::numerical::stable_multiply(1.0/6.0, dt);
    three_body_state_si_t result = {
        state.pos1 + sixth_dt * (k1.pos1 + 2.0 * k2.pos1 + 2.0 * k3.pos1 + k4.pos1),
        state.pos2 + sixth_dt * (k1.pos2 + 2.0 * k2.pos2 + 2.0 * k3.pos2 + k4.pos2),
        state.pos3 + sixth_dt * (k1.pos3 + 2.0 * k2.pos3 + 2.0 * k3.pos3 + k4.pos3),
        state.vel1 + sixth_dt * (k1.vel1 + 2.0 * k2.vel1 + 2.0 * k3.vel1 + k4.vel1),
        state.vel2 + sixth_dt * (k1.vel2 + 2.0 * k2.vel2 + 2.0 * k3.vel2 + k4.vel2),
        state.vel3 + sixth_dt * (k1.vel3 + 2.0 * k2.vel3 + 2.0 * k3.vel3 + k4.vel3)
    };

    return result;
}

// RK4 step for measurements using RSS math
three_body_state_measurement_t rk4_step_meas(const three_body_state_measurement_t& state, const pkr::measurement_t<pkr::units::second_t>& dt) {
    three_body_state_measurement_t k1, k2, k3, k4;

    derivative_meas(state, k1);

    // Convert state components to vectors for vector-based math
    pkr::units::vec_4d_length_measurement_t pos1{state.x1, state.y1, state.z1, pkr::measurement_t<pkr::units::meter_t>(1.0)};
    pkr::units::vec_4d_length_measurement_t pos2{state.x2, state.y2, state.z2, pkr::measurement_t<pkr::units::meter_t>(1.0)};
    pkr::units::vec_4d_length_measurement_t pos3{state.x3, state.y3, state.z3, pkr::measurement_t<pkr::units::meter_t>(1.0)};
    pkr::units::vec_4d_velocity_measurement_t vel1{state.vx1, state.vy1, state.vz1, pkr::measurement_t<pkr::units::meter_per_second_t>(1.0)};
    pkr::units::vec_4d_velocity_measurement_t vel2{state.vx2, state.vy2, state.vz2, pkr::measurement_t<pkr::units::meter_per_second_t>(1.0)};
    pkr::units::vec_4d_velocity_measurement_t vel3{state.vx3, state.vy3, state.vz3, pkr::measurement_t<pkr::units::meter_per_second_t>(1.0)};

    // Convert k1 components to vectors
    pkr::units::vec_4d_length_measurement_t k1_pos1{k1.x1, k1.y1, k1.z1, pkr::measurement_t<pkr::units::meter_t>(1.0)};
    pkr::units::vec_4d_length_measurement_t k1_pos2{k1.x2, k1.y2, k1.z2, pkr::measurement_t<pkr::units::meter_t>(1.0)};
    pkr::units::vec_4d_length_measurement_t k1_pos3{k1.x3, k1.y3, k1.z3, pkr::measurement_t<pkr::units::meter_t>(1.0)};
    pkr::units::vec_4d_velocity_measurement_t k1_vel1{k1.vx1, k1.vy1, k1.vz1, pkr::measurement_t<pkr::units::meter_per_second_t>(1.0)};
    pkr::units::vec_4d_velocity_measurement_t k1_vel2{k1.vx2, k1.vy2, k1.vz2, pkr::measurement_t<pkr::units::meter_per_second_t>(1.0)};
    pkr::units::vec_4d_velocity_measurement_t k1_vel3{k1.vx3, k1.vy3, k1.vz3, pkr::measurement_t<pkr::units::meter_per_second_t>(1.0)};

    // state2 = state + 0.5 * dt * k1
    auto half_dt = pkr::math::multiply_rss(0.5, dt);
    pkr::units::vec_4d_length_measurement_t pos1_2 = pos1 + half_dt * k1_pos1;
    pkr::units::vec_4d_length_measurement_t pos2_2 = pos2 + half_dt * k1_pos2;
    pkr::units::vec_4d_length_measurement_t pos3_2 = pos3 + half_dt * k1_pos3;
    pkr::units::vec_4d_velocity_measurement_t vel1_2 = vel1 + half_dt * k1_vel1;
    pkr::units::vec_4d_velocity_measurement_t vel2_2 = vel2 + half_dt * k1_vel2;
    pkr::units::vec_4d_velocity_measurement_t vel3_2 = vel3 + half_dt * k1_vel3;

    // Create state2 from vectors
    three_body_state_measurement_t state2 = {
        pos1_2.x, pos1_2.y, pos1_2.z,
        pos2_2.x, pos2_2.y, pos2_2.z,
        pos3_2.x, pos3_2.y, pos3_2.z,
        vel1_2.x, vel1_2.y, vel1_2.z,
        vel2_2.x, vel2_2.y, vel2_2.z,
        vel3_2.x, vel3_2.y, vel3_2.z
    };
    derivative_meas(state2, k2);

    // Convert k2 components to vectors
    pkr::units::vec_4d_length_measurement_t k2_pos1{k2.x1, k2.y1, k2.z1, pkr::measurement_t<pkr::units::meter_t>(1.0)};
    pkr::units::vec_4d_length_measurement_t k2_pos2{k2.x2, k2.y2, k2.z2, pkr::measurement_t<pkr::units::meter_t>(1.0)};
    pkr::units::vec_4d_length_measurement_t k2_pos3{k2.x3, k2.y3, k2.z3, pkr::measurement_t<pkr::units::meter_t>(1.0)};
    pkr::units::vec_4d_velocity_measurement_t k2_vel1{k2.vx1, k2.vy1, k2.vz1, pkr::measurement_t<pkr::units::meter_per_second_t>(1.0)};
    pkr::units::vec_4d_velocity_measurement_t k2_vel2{k2.vx2, k2.vy2, k2.vz2, pkr::measurement_t<pkr::units::meter_per_second_t>(1.0)};
    pkr::units::vec_4d_velocity_measurement_t k2_vel3{k2.vx3, k2.vy3, k2.vz3, pkr::measurement_t<pkr::units::meter_per_second_t>(1.0)};

    // state3 = state + 0.5 * dt * k2
    pkr::units::vec_4d_length_measurement_t pos1_3 = pos1 + half_dt * k2_pos1;
    pkr::units::vec_4d_length_measurement_t pos2_3 = pos2 + half_dt * k2_pos2;
    pkr::units::vec_4d_length_measurement_t pos3_3 = pos3 + half_dt * k2_pos3;
    pkr::units::vec_4d_velocity_measurement_t vel1_3 = vel1 + half_dt * k2_vel1;
    pkr::units::vec_4d_velocity_measurement_t vel2_3 = vel2 + half_dt * k2_vel2;
    pkr::units::vec_4d_velocity_measurement_t vel3_3 = vel3 + half_dt * k2_vel3;

    // Create state3 from vectors
    three_body_state_measurement_t state3 = {
        pos1_3.x, pos1_3.y, pos1_3.z,
        pos2_3.x, pos2_3.y, pos2_3.z,
        pos3_3.x, pos3_3.y, pos3_3.z,
        vel1_3.x, vel1_3.y, vel1_3.z,
        vel2_3.x, vel2_3.y, vel2_3.z,
        vel3_3.x, vel3_3.y, vel3_3.z
    };
    derivative_meas(state3, k3);

    // Convert k3 components to vectors
    pkr::units::vec_4d_length_measurement_t k3_pos1{k3.x1, k3.y1, k3.z1, pkr::measurement_t<pkr::units::meter_t>(1.0)};
    pkr::units::vec_4d_length_measurement_t k3_pos2{k3.x2, k3.y2, k3.z2, pkr::measurement_t<pkr::units::meter_t>(1.0)};
    pkr::units::vec_4d_length_measurement_t k3_pos3{k3.x3, k3.y3, k3.z3, pkr::measurement_t<pkr::units::meter_t>(1.0)};
    pkr::units::vec_4d_velocity_measurement_t k3_vel1{k3.vx1, k3.vy1, k3.vz1, pkr::measurement_t<pkr::units::meter_per_second_t>(1.0)};
    pkr::units::vec_4d_velocity_measurement_t k3_vel2{k3.vx2, k3.vy2, k3.vz2, pkr::measurement_t<pkr::units::meter_per_second_t>(1.0)};
    pkr::units::vec_4d_velocity_measurement_t k3_vel3{k3.vx3, k3.vy3, k3.vz3, pkr::measurement_t<pkr::units::meter_per_second_t>(1.0)};

    // state4 = state + dt * k3
    pkr::units::vec_4d_length_measurement_t pos1_4 = pos1 + dt * k3_pos1;
    pkr::units::vec_4d_length_measurement_t pos2_4 = pos2 + dt * k3_pos2;
    pkr::units::vec_4d_length_measurement_t pos3_4 = pos3 + dt * k3_pos3;
    pkr::units::vec_4d_velocity_measurement_t vel1_4 = vel1 + dt * k3_vel1;
    pkr::units::vec_4d_velocity_measurement_t vel2_4 = vel2 + dt * k3_vel2;
    pkr::units::vec_4d_velocity_measurement_t vel3_4 = vel3 + dt * k3_vel3;

    // Create state4 from vectors
    three_body_state_measurement_t state4 = {
        pos1_4.x, pos1_4.y, pos1_4.z,
        pos2_4.x, pos2_4.y, pos2_4.z,
        pos3_4.x, pos3_4.y, pos3_4.z,
        vel1_4.x, vel1_4.y, vel1_4.z,
        vel2_4.x, vel2_4.y, vel2_4.z,
        vel3_4.x, vel3_4.y, vel3_4.z
    };
    derivative_meas(state4, k4);

    // Convert k4 components to vectors
    pkr::units::vec_4d_length_measurement_t k4_pos1{k4.x1, k4.y1, k4.z1, pkr::measurement_t<pkr::units::meter_t>(1.0)};
    pkr::units::vec_4d_length_measurement_t k4_pos2{k4.x2, k4.y2, k4.z2, pkr::measurement_t<pkr::units::meter_t>(1.0)};
    pkr::units::vec_4d_length_measurement_t k4_pos3{k4.x3, k4.y3, k4.z3, pkr::measurement_t<pkr::units::meter_t>(1.0)};
    pkr::units::vec_4d_velocity_measurement_t k4_vel1{k4.vx1, k4.vy1, k4.vz1, pkr::measurement_t<pkr::units::meter_per_second_t>(1.0)};
    pkr::units::vec_4d_velocity_measurement_t k4_vel2{k4.vx2, k4.vy2, k4.vz2, pkr::measurement_t<pkr::units::meter_per_second_t>(1.0)};
    pkr::units::vec_4d_velocity_measurement_t k4_vel3{k4.vx3, k4.vy3, k4.vz3, pkr::measurement_t<pkr::units::meter_per_second_t>(1.0)};

    // result = state + dt/6 * (k1 + 2*k2 + 2*k3 + k4)
    auto sixth_dt = pkr::math::divide_rss(dt, 6.0);
    pkr::units::vec_4d_length_measurement_t pos1_result = pos1 + sixth_dt * (k1_pos1 + 2.0 * k2_pos1 + 2.0 * k3_pos1 + k4_pos1);
    pkr::units::vec_4d_length_measurement_t pos2_result = pos2 + sixth_dt * (k1_pos2 + 2.0 * k2_pos2 + 2.0 * k3_pos2 + k4_pos2);
    pkr::units::vec_4d_length_measurement_t pos3_result = pos3 + sixth_dt * (k1_pos3 + 2.0 * k2_pos3 + 2.0 * k3_pos3 + k4_pos3);
    pkr::units::vec_4d_velocity_measurement_t vel1_result = vel1 + sixth_dt * (k1_vel1 + 2.0 * k2_vel1 + 2.0 * k3_vel1 + k4_vel1);
    pkr::units::vec_4d_velocity_measurement_t vel2_result = vel2 + sixth_dt * (k1_vel2 + 2.0 * k2_vel2 + 2.0 * k3_vel2 + k4_vel2);
    pkr::units::vec_4d_velocity_measurement_t vel3_result = vel3 + sixth_dt * (k1_vel3 + 2.0 * k2_vel3 + 2.0 * k3_vel3 + k4_vel3);

    three_body_state_measurement_t result = {
        pos1_result.x, pos1_result.y, pos1_result.z,
        pos2_result.x, pos2_result.y, pos2_result.z,
        pos3_result.x, pos3_result.y, pos3_result.z,
        vel1_result.x, vel1_result.y, vel1_result.z,
        vel2_result.x, vel2_result.y, vel2_result.z,
        vel3_result.x, vel3_result.y, vel3_result.z
    };

    return result;
}

// ============================================================================
// Energy Calculation for Stability Checking
// ============================================================================

// Compute total energy for plain doubles
double compute_total_energy_double(const three_body_state_double_t& state) {
    // Kinetic energy using vector dot products
    double ke1 = 0.5 * m1 * dot(state.vel1, state.vel1);
    double ke2 = 0.5 * m2 * dot(state.vel2, state.vel2);
    double ke3 = 0.5 * m3 * dot(state.vel3, state.vel3);
    double kinetic = ke1 + ke2 + ke3;

    // Potential energy using vector distances
    vec_4d_t<double> r12_vec = state.pos2 - state.pos1;
    vec_4d_t<double> r13_vec = state.pos3 - state.pos1;
    vec_4d_t<double> r23_vec = state.pos3 - state.pos2;

    double r12 = std::sqrt(dot(r12_vec, r12_vec));
    double r13 = std::sqrt(dot(r13_vec, r13_vec));
    double r23 = std::sqrt(dot(r23_vec, r23_vec));

    double potential = -G * (m1*m2/r12 + m1*m3/r13 + m2*m3/r23);

    return kinetic + potential;
}

} // namespace numerical
} // namespace test
} // namespace pkr