#pragma once

#include <array>
#include <pkr_units/si_units.h>
#include <pkr_units/astronomical_units.h>
#include <pkr_units/measurements/measurement.h>
#include <pkr_units/math/measurements/measurement_math_rss.h>
#include <pkr_units/math/unit/unit_math_4d.h>
#include <pkr_units/math/measurements/measurement_math_4d.h>

namespace pkr {
namespace test {
namespace numerical {

// ============================================================================
// 3-Body Problem State Representations
// ============================================================================

// State for plain doubles: 3 positions + 3 velocities = 6 vectors
struct three_body_state_double_t {
    pkr::units::math::vec_4d_t<double> pos1, pos2, pos3; // Positions (w=0)
    pkr::units::math::vec_4d_t<double> vel1, vel2, vel3; // Velocities (w=0)
};

// State for SI units
struct three_body_state_si_t {
    pkr::units::math::vec_4d_t<pkr::units::meter_t> pos1, pos2, pos3;
    pkr::units::math::vec_4d_t<pkr::units::meter_per_second_t> vel1, vel2, vel3;
};

// State for measurements
struct three_body_state_measurement_t {
    pkr::units::math::vec_4d_t<pkr::units::measurement_t<pkr::units::meter_t>> pos1, pos2, pos3;
    pkr::units::math::vec_4d_t<pkr::units::measurement_t<pkr::units::meter_per_second_t>> vel1, vel2, vel3;
};

// ============================================================================
// Constants
// ============================================================================

const double G = 6.67430e-11; // Gravitational constant in m^3 kg^-1 s^-2
const double SOLAR_MASS = 1.989e30; // Solar mass in kg

const double m1 = 1.0; // Masses in solar masses
const double m2 = 1.0;
const double m3 = 1.0;

const pkr::units::kilogram_t m1_si = SOLAR_MASS * pkr::units::kilogram_t(1.0);
const pkr::units::kilogram_t m2_si = SOLAR_MASS * pkr::units::kilogram_t(1.0);
const pkr::units::kilogram_t m3_si = SOLAR_MASS * pkr::units::kilogram_t(1.0);

const pkr::units::measurement_t<pkr::units::kilogram_t> m1_meas = {SOLAR_MASS * pkr::units::kilogram_t(1.0), 0.01 * SOLAR_MASS * pkr::units::kilogram_t(1.0)};
const pkr::units::measurement_t<pkr::units::kilogram_t> m2_meas = {SOLAR_MASS * pkr::units::kilogram_t(1.0), 0.01 * SOLAR_MASS * pkr::units::kilogram_t(1.0)};
const pkr::units::measurement_t<pkr::units::kilogram_t> m3_meas = {SOLAR_MASS * pkr::units::kilogram_t(1.0), 0.01 * SOLAR_MASS * pkr::units::kilogram_t(1.0)};

const auto G_si = pkr::units::meter_t(1.0) * pkr::units::meter_t(1.0) * pkr::units::meter_t(1.0) /
                  (pkr::units::kilogram_t(1.0) * pkr::units::second_t(1.0) * pkr::units::second_t(1.0)) * G;

const pkr::units::measurement_t<decltype(G_si)> G_meas = {G_si, G_si * 1e-5};

// ============================================================================
// Initial Conditions
// ============================================================================

// Initial state for plain doubles (equilateral triangle)
const three_body_state_double_t initial_state_double = {
    {1.0, 0.0, 0.0, 0.0},      // Body 1 at (1, 0, 0) AU
    {-0.5, std::sqrt(3)/2, 0.0, 0.0},  // Body 2 at (-0.5, √3/2, 0) AU
    {-0.5, -std::sqrt(3)/2, 0.0, 0.0}, // Body 3 at (-0.5, -√3/2, 0) AU
    {0.0, 0.5, 0.0, 0.0},      // Body 1 velocity
    {-0.5, -0.25, 0.0, 0.0},   // Body 2 velocity
    {0.5, -0.25, 0.0, 0.0}     // Body 3 velocity
};

// Initial state in SI units
const three_body_state_si_t initial_state_si = {
    {1.0 * pkr::units::au_t(1.0), 0.0 * pkr::units::au_t(1.0), 0.0 * pkr::units::au_t(1.0), 0.0 * pkr::units::meter_t(1.0)},
    {-0.5 * pkr::units::au_t(1.0), std::sqrt(3)/2 * pkr::units::au_t(1.0), 0.0 * pkr::units::au_t(1.0), 0.0 * pkr::units::meter_t(1.0)},
    {-0.5 * pkr::units::au_t(1.0), -std::sqrt(3)/2 * pkr::units::au_t(1.0), 0.0 * pkr::units::au_t(1.0), 0.0 * pkr::units::meter_t(1.0)},
    {0.0 * pkr::units::meter_per_second_t(1.0), 0.5 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0), 0.0 * pkr::units::meter_per_second_t(1.0), 0.0 * pkr::units::meter_per_second_t(1.0)},
    {-0.5 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0), -0.25 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0), 0.0 * pkr::units::meter_per_second_t(1.0), 0.0 * pkr::units::meter_per_second_t(1.0)},
    {0.5 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0), -0.25 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0), 0.0 * pkr::units::meter_per_second_t(1.0), 0.0 * pkr::units::meter_per_second_t(1.0)}
};

// Initial state with uncertainties
const three_body_state_measurement_t initial_state_meas = {
    {
        {1.0 * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
        {0.0 * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
        {0.0 * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
        {0.0 * pkr::units::meter_t(1.0), 1e3 * pkr::units::meter_t(1.0)}
    },
    {
        {-0.5 * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
        {std::sqrt(3)/2 * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
        {0.0 * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
        {0.0 * pkr::units::meter_t(1.0), 1e3 * pkr::units::meter_t(1.0)}
    },
    {
        {-0.5 * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
        {-std::sqrt(3)/2 * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
        {0.0 * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
        {0.0 * pkr::units::meter_t(1.0), 1e3 * pkr::units::meter_t(1.0)}
    },
    {
        {0.0 * pkr::units::meter_per_second_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
        {0.5 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
        {0.0 * pkr::units::meter_per_second_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
        {0.0 * pkr::units::meter_per_second_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)}
    },
    {
        {-0.5 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
        {-0.25 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
        {0.0 * pkr::units::meter_per_second_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
        {0.0 * pkr::units::meter_per_second_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)}
    },
    {
        {0.5 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
        {-0.25 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
        {0.0 * pkr::units::meter_per_second_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
        {0.0 * pkr::units::meter_per_second_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)}
    }
};

// ============================================================================
// Gravitational Acceleration Functions
// ============================================================================

// Compute gravitational acceleration for plain doubles
void compute_gravitational_acceleration_double(
    const pkr::units::math::vec_4d_t<double>& pos_i,
    const pkr::units::math::vec_4d_t<double>& pos_j,
    double mj,
    pkr::units::math::vec_4d_t<double>& acc_i) {

    pkr::units::math::vec_4d_t<double> diff = pos_j - pos_i;
    double r_squared = diff.x*diff.x + diff.y*diff.y + diff.z*diff.z;
    double r = std::sqrt(r_squared);
    double r_cubed = r * r_squared;

    if (r_cubed > 1e-20) { // Avoid division by zero
        double factor = G * mj / r_cubed;
        acc_i.x += factor * diff.x;
        acc_i.y += factor * diff.y;
        acc_i.z += factor * diff.z;
    }
}

// Compute gravitational acceleration using stable SI units math
void compute_gravitational_acceleration_si(
    const pkr::units::math::vec_4d_t<pkr::units::meter_t>& pos_i,
    const pkr::units::math::vec_4d_t<pkr::units::meter_t>& pos_j,
    const pkr::units::kilogram_t& mj,
    pkr::units::math::vec_4d_t<pkr::units::meter_per_second_squared_t>& acc_i) {

    pkr::units::math::vec_4d_t<pkr::units::meter_t> diff = pos_j - pos_i;
    auto r_squared = diff.x*diff.x + diff.y*diff.y + diff.z*diff.z;
    auto r = pkr::numerical::sqrt(r_squared);
    auto r_cubed = r * r_squared;

    if (r_cubed.value() > 1e-20) {
        auto factor = G_si * mj / r_cubed;
        acc_i.x = acc_i.x + factor * diff.x;
        acc_i.y = acc_i.y + factor * diff.y;
        acc_i.z = acc_i.z + factor * diff.z;
    }
}

// Compute gravitational acceleration using RSS math for measurements
void compute_gravitational_acceleration_meas(
    const pkr::units::math::vec_4d_t<pkr::units::measurement_t<pkr::units::meter_t>>& pos_i,
    const pkr::units::math::vec_4d_t<pkr::units::measurement_t<pkr::units::meter_t>>& pos_j,
    const pkr::units::measurement_t<pkr::units::kilogram_t>& mj,
    pkr::units::math::vec_4d_t<pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>>& acc_i) {

    pkr::units::math::vec_4d_t<pkr::units::measurement_t<pkr::units::meter_t>> diff = pos_j - pos_i;

    auto dx_squared = pkr::units::math::multiply_rss(diff.x, diff.x);
    auto dy_squared = pkr::units::math::multiply_rss(diff.y, diff.y);
    auto dz_squared = pkr::units::math::multiply_rss(diff.z, diff.z);

    auto r_squared = pkr::units::math::add_rss(pkr::units::math::add_rss(dx_squared, dy_squared), dz_squared);

    auto r = pkr::units::math::sqrt_rss(r_squared);

    auto r_cubed = pkr::units::math::multiply_rss(r, r_squared);

    if (r_cubed.unit_value().value() > 1e-20) {
        auto factor = pkr::units::math::divide_rss(pkr::units::math::multiply_rss(G_meas, mj), r_cubed);
        acc_i.x = pkr::units::math::add_rss(acc_i.x, pkr::units::math::multiply_rss(factor, diff.x));
        acc_i.y = pkr::units::math::add_rss(acc_i.y, pkr::units::math::multiply_rss(factor, diff.y));
        acc_i.z = pkr::units::math::add_rss(acc_i.z, pkr::units::math::multiply_rss(factor, diff.z));
    }
}

// ============================================================================
// Derivative Functions
// ============================================================================

// Derivative function for plain doubles
void derivative_double(const three_body_state_double_t& state, three_body_state_double_t& dstate_dt) {
    // Positions are velocities
    dstate_dt.pos1 = state.vel1;
    dstate_dt.pos2 = state.vel2;
    dstate_dt.pos3 = state.vel3;

    // Accelerations from gravity
    dstate_dt.vel1 = {0, 0, 0, 0};
    dstate_dt.vel2 = {0, 0, 0, 0};
    dstate_dt.vel3 = {0, 0, 0, 0};

    // Body 1 acceleration from body 2 and 3
    compute_gravitational_acceleration_double(state.pos1, state.pos2, m2, dstate_dt.vel1);
    compute_gravitational_acceleration_double(state.pos1, state.pos3, m3, dstate_dt.vel1);

    // Body 2 acceleration from body 1 and 3
    compute_gravitational_acceleration_double(state.pos2, state.pos1, m1, dstate_dt.vel2);
    compute_gravitational_acceleration_double(state.pos2, state.pos3, m3, dstate_dt.vel2);

    // Body 3 acceleration from body 1 and 2
    compute_gravitational_acceleration_double(state.pos3, state.pos1, m1, dstate_dt.vel3);
    compute_gravitational_acceleration_double(state.pos3, state.pos2, m2, dstate_dt.vel3);
}

// Derivative function for SI units
void derivative_si(const three_body_state_si_t& state, three_body_state_si_t& dstate_dt) {
    // Positions are velocities
    dstate_dt.pos1 = state.vel1;
    dstate_dt.pos2 = state.vel2;
    dstate_dt.pos3 = state.vel3;

    // Initialize accelerations to zero
    pkr::units::math::vec_4d_t<pkr::units::meter_per_second_squared_t> acc1{0.0 * pkr::units::meter_per_second_squared_t(1.0),
                                                          0.0 * pkr::units::meter_per_second_squared_t(1.0),
                                                          0.0 * pkr::units::meter_per_second_squared_t(1.0)};
    pkr::units::math::vec_4d_t<pkr::units::meter_per_second_squared_t> acc2{0.0 * pkr::units::meter_per_second_squared_t(1.0),
                                                          0.0 * pkr::units::meter_per_second_squared_t(1.0),
                                                          0.0 * pkr::units::meter_per_second_squared_t(1.0)};
    pkr::units::math::vec_4d_t<pkr::units::meter_per_second_squared_t> acc3{0.0 * pkr::units::meter_per_second_squared_t(1.0),
                                                          0.0 * pkr::units::meter_per_second_squared_t(1.0),
                                                          0.0 * pkr::units::meter_per_second_squared_t(1.0)};

    // Body 1 acceleration from body 2 and 3
    compute_gravitational_acceleration_si(state.pos1, state.pos2, m2_si, acc1);
    compute_gravitational_acceleration_si(state.pos1, state.pos3, m3_si, acc1);

    // Body 2 acceleration from body 1 and 3
    compute_gravitational_acceleration_si(state.pos2, state.pos1, m1_si, acc2);
    compute_gravitational_acceleration_si(state.pos2, state.pos3, m3_si, acc2);

    // Body 3 acceleration from body 1 and 2
    compute_gravitational_acceleration_si(state.pos3, state.pos1, m1_si, acc3);
    compute_gravitational_acceleration_si(state.pos3, state.pos2, m2_si, acc3);

    // Set velocities to accelerations
    dstate_dt.vel1 = acc1;
    dstate_dt.vel2 = acc2;
    dstate_dt.vel3 = acc3;
}

// Derivative function for measurements
void derivative_meas(const three_body_state_measurement_t& state, three_body_state_measurement_t& dstate_dt) {
    // Positions are velocities
    dstate_dt.pos1 = state.vel1;
    dstate_dt.pos2 = state.vel2;
    dstate_dt.pos3 = state.vel3;

    // Initialize accelerations to zero
    pkr::units::math::vec_4d_t<pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>> acc1{
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)}
    };
    pkr::units::math::vec_4d_t<pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>> acc2{
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)}
    };
    pkr::units::math::vec_4d_t<pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>> acc3{
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)}
    };

    // Body 1 acceleration from body 2 and 3
    compute_gravitational_acceleration_meas(state.pos1, state.pos2, m2_meas, acc1);
    compute_gravitational_acceleration_meas(state.pos1, state.pos3, m3_meas, acc1);

    // Body 2 acceleration from body 1 and 3
    compute_gravitational_acceleration_meas(state.pos2, state.pos1, m1_meas, acc2);
    compute_gravitational_acceleration_meas(state.pos2, state.pos3, m3_meas, acc2);

    // Body 3 acceleration from body 1 and 2
    compute_gravitational_acceleration_meas(state.pos3, state.pos1, m1_meas, acc3);
    compute_gravitational_acceleration_meas(state.pos3, state.pos2, m2_meas, acc3);

    // Set velocities to accelerations
    dstate_dt.vel1 = acc1;
    dstate_dt.vel2 = acc2;
    dstate_dt.vel3 = acc3;
}

} // namespace numerical
} // namespace test
} // namespace pkr