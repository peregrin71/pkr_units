#pragma once

#include <array>
#include <pkr_units/si_units.h>
#include <pkr_units/astronomical_units.h>
#include <pkr_units/constants/astronomical_constants.h>
#include <pkr_units/measurements/measurement.h>
#include <pkr_units/math/measurements/measurement_math_rss.h>
#include <pkr_units/math/unit/unit_math_4d.h>
#include <pkr_units/math/measurements/measurement_math_4d.h>
#include <pkr_units/math/4d/vector_4d_units.h>
#include <pkr_units/math/4d/vector_4d_measurements_rss.h>

namespace pkr
{
namespace test
{
namespace numerical
{

// ============================================================================
// 3-Body Problem State Representations
// ============================================================================

// State for plain doubles: 3 positions + 3 velocities = 6 vectors
struct three_body_state_double_t
{
    pkr::units::vec_4d_t<double> pos1, pos2, pos3; // Positions (w=0)
    pkr::units::vec_4d_t<double> vel1, vel2, vel3; // Velocities (w=0)
};

// State for SI units
struct three_body_state_si_t
{
    pkr::units::vec_4d_units_t<pkr::units::meter_t> pos1, pos2, pos3;
    pkr::units::vec_4d_units_t<pkr::units::meter_per_second_t> vel1, vel2, vel3;
};

// Derivative state for SI units (contains time derivatives)
struct three_body_derivative_si_t
{
    pkr::units::vec_4d_units_t<pkr::units::meter_per_second_t> dpos1, dpos2, dpos3;         // d(position)/dt = velocity
    pkr::units::vec_4d_units_t<pkr::units::meter_per_second_squared_t> dvel1, dvel2, dvel3; // d(velocity)/dt = acceleration
};

// State for measurements
struct three_body_state_measurement_t
{
    pkr::units::vec_4d_measurements_rss_t<pkr::units::measurement_t<pkr::units::meter_t>> pos1, pos2, pos3;
    pkr::units::vec_4d_measurements_rss_t<pkr::units::measurement_t<pkr::units::meter_per_second_t>> vel1, vel2, vel3;
};

// Derivative state for measurements
struct three_body_derivative_measurement_t
{
    pkr::units::vec_4d_measurements_rss_t<pkr::units::measurement_t<pkr::units::meter_per_second_t>> dpos1, dpos2, dpos3;
    pkr::units::vec_4d_measurements_rss_t<pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>> dvel1, dvel2, dvel3;
};

// ============================================================================
// Constants
// ============================================================================

// Use SDK-provided astronomical constants

const double m1 = 1.0; // Masses in solar masses
const double m2 = 1.0;
const double m3 = 1.0;

const pkr::units::kilogram_t m1_si = pkr::units::constants::solar_mass;
const pkr::units::kilogram_t m2_si = pkr::units::constants::solar_mass;
const pkr::units::kilogram_t m3_si = pkr::units::constants::solar_mass;

const pkr::units::measurement_t<pkr::units::kilogram_t> m1_meas =
    pkr::units::measurement_t<pkr::units::kilogram_t>{pkr::units::constants::solar_mass, pkr::units::kilogram_t{pkr::units::constants::solar_mass_kg * 0.01}};
const pkr::units::measurement_t<pkr::units::kilogram_t> m2_meas =
    pkr::units::measurement_t<pkr::units::kilogram_t>{pkr::units::constants::solar_mass, pkr::units::kilogram_t{pkr::units::constants::solar_mass_kg * 0.01}};
const pkr::units::measurement_t<pkr::units::kilogram_t> m3_meas =
    pkr::units::measurement_t<pkr::units::kilogram_t>{pkr::units::constants::solar_mass, pkr::units::kilogram_t{pkr::units::constants::solar_mass_kg * 0.01}};

// Use SDK-provided unit-typed gravitational constant and measurement
constexpr auto G_si = pkr::units::constants::gravitational_constant;
constexpr auto G_meas = pkr::units::measurement_t<decltype(pkr::units::constants::gravitational_constant)>{
    pkr::units::constants::gravitational_constant,
    decltype(pkr::units::constants::gravitational_constant){pkr::units::constants::gravitational_constant_value * 1e-5}};

// Plain double gravitational constant for double-based tests
constexpr double G = pkr::units::constants::gravitational_constant_value;

// ============================================================================
// Initial Conditions
// ============================================================================

// Initial state for plain doubles (slightly perturbed equilateral triangle to break symmetry)
const three_body_state_double_t initial_state_double = {
    {1.0, 0.0, 0.0, 0.0},                         // Body 1 at (1, 0, 0) AU
    {-0.505, std::sqrt(3) / 2 + 1e-4, 0.0, 0.0},  // Body 2 slightly perturbed
    {-0.495, -std::sqrt(3) / 2 - 1e-4, 0.0, 0.0}, // Body 3 slightly perturbed
    {0.0, 0.5005, 0.0, 0.0},                      // Body 1 velocity (small perturbation)
    {-0.4995, -0.2495, 0.0, 0.0},                 // Body 2 velocity
    {0.4995, -0.2505, 0.0, 0.0}                   // Body 3 velocity
};

// Initial state in SI units (slightly perturbed to break symmetry)
const three_body_state_si_t initial_state_si = {
    {1.0 * pkr::units::au_t(1.0), 0.0 * pkr::units::au_t(1.0), 0.0 * pkr::units::au_t(1.0), 0.0 * pkr::units::meter_t(1.0)},
    {-0.505 * pkr::units::au_t(1.0), (std::sqrt(3) / 2 + 1e-4) * pkr::units::au_t(1.0), 0.0 * pkr::units::au_t(1.0), 0.0 * pkr::units::meter_t(1.0)},
    {-0.495 * pkr::units::au_t(1.0), (-std::sqrt(3) / 2 - 1e-4) * pkr::units::au_t(1.0), 0.0 * pkr::units::au_t(1.0), 0.0 * pkr::units::meter_t(1.0)},
    {0.0 * pkr::units::meter_per_second_t(1.0),
     0.5005 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0),
     0.0 * pkr::units::meter_per_second_t(1.0),
     0.0 * pkr::units::meter_per_second_t(1.0)},
    {-0.4995 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0),
     -0.2495 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0),
     0.0 * pkr::units::meter_per_second_t(1.0),
     0.0 * pkr::units::meter_per_second_t(1.0)},
    {0.4995 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0),
     -0.2505 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0),
     0.0 * pkr::units::meter_per_second_t(1.0),
     0.0 * pkr::units::meter_per_second_t(1.0)}};

// Initial state with uncertainties (means perturbed to break symmetry)
const three_body_state_measurement_t initial_state_meas = {
    {{1.0 * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
     {0.0 * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
     {0.0 * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
     {0.0 * pkr::units::meter_t(1.0), 1e3 * pkr::units::meter_t(1.0)}},
    {{-0.505 * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
     {(std::sqrt(3) / 2 + 1e-4) * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
     {0.0 * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
     {0.0 * pkr::units::meter_t(1.0), 1e3 * pkr::units::meter_t(1.0)}},
    {{-0.495 * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
     {(-std::sqrt(3) / 2 - 1e-4) * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
     {0.0 * pkr::units::au_t(1.0), 1e3 * pkr::units::meter_t(1.0)},
     {0.0 * pkr::units::meter_t(1.0), 1e3 * pkr::units::meter_t(1.0)}},
    {{0.0 * pkr::units::meter_per_second_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
     {0.5005 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
     {0.0 * pkr::units::meter_per_second_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
     {0.0 * pkr::units::meter_per_second_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)}},
    {{-0.4995 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
     {-0.2495 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
     {0.0 * pkr::units::meter_per_second_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
     {0.0 * pkr::units::meter_per_second_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)}},
    {{0.4995 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
     {-0.2505 * pkr::units::au_t(1.0) / pkr::units::year_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
     {0.0 * pkr::units::meter_per_second_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)},
     {0.0 * pkr::units::meter_per_second_t(1.0), 1e-3 * pkr::units::meter_per_second_t(1.0)}}};

// ============================================================================
// Gravitational Acceleration Functions
// ============================================================================

// Compute gravitational acceleration for plain doubles
void compute_gravitational_acceleration_double(
    const pkr::units::vec_4d_t<double>& pos_i,
    const pkr::units::vec_4d_t<double>& pos_j,
    double mj,
    pkr::units::vec_4d_t<double>& acc_i)
{
    pkr::units::vec_4d_t<double> diff = pos_j - pos_i;
    double r_squared = pkr::units::dot(diff, diff);
    double r = std::sqrt(r_squared);
    double r_cubed = r * r_squared;

    double factor = G * mj * (1.0 / r_cubed);
    auto delta = pkr::units::vec_4d_t<double>{factor * diff.x, factor * diff.y, factor * diff.z, factor * diff.w};
    acc_i = acc_i + delta;
}

// Compute gravitational acceleration using stable SI units math
void compute_gravitational_acceleration_si(
    const pkr::units::vec_4d_units_t<pkr::units::meter_t>& pos_i,
    const pkr::units::vec_4d_units_t<pkr::units::meter_t>& pos_j,
    const pkr::units::kilogram_t& mj,
    pkr::units::vec_4d_units_t<pkr::units::meter_per_second_squared_t>& acc_i)
{
    pkr::units::vec_4d_units_t<pkr::units::meter_t> diff = pos_j - pos_i;
    auto r_squared = pkr::units::dot(diff, diff);
    auto r = pkr::units::sqrt(r_squared);
    auto r_cubed = pkr::units::cube(r);

    auto inv_r_cubed = pkr::units::scalar_t{1.0} / r_cubed;
    auto gm = G_si * mj;
    auto factor = gm * inv_r_cubed;
    acc_i = acc_i + factor * diff;
}

// Compute gravitational acceleration using RSS math for measurements
void compute_gravitational_acceleration_meas(
    const pkr::units::vec_4d_measurements_rss_t<pkr::units::measurement_t<pkr::units::meter_t>>& pos_i,
    const pkr::units::vec_4d_measurements_rss_t<pkr::units::measurement_t<pkr::units::meter_t>>& pos_j,
    const pkr::units::measurement_t<pkr::units::kilogram_t>& mj,
    pkr::units::vec_4d_measurements_rss_t<pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>>& acc_i)
{
    pkr::units::vec_4d_measurements_rss_t<pkr::units::measurement_t<pkr::units::meter_t>> diff = pos_j - pos_i;

    // RSS-safe computation of distance
    auto r_squared = pkr::units::sum_of_squares_rss(diff.x, diff.y, diff.z);

    auto r = pkr::units::sqrt_rss(r_squared);

    // Use cube_rss for correlated exponentiation (r^3)
    auto r_cubed = pkr::units::cube_rss(r);

    auto inv_r_cubed = pkr::units::divide_rss(1.0, r_cubed);
    auto gm = pkr::units::multiply_rss(G_meas, mj);
    auto factor = pkr::units::multiply_rss(gm, inv_r_cubed);
    acc_i = pkr::units::add_rss(acc_i, pkr::units::multiply_rss(factor, diff));
}

// ============================================================================
// Derivative Functions
// ============================================================================

// Derivative function for plain doubles
void derivative_double(const three_body_state_double_t& state, three_body_state_double_t& dstate_dt)
{
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
three_body_derivative_si_t derivative_si(const three_body_state_si_t& state)
{
    three_body_derivative_si_t dstate_dt;

    // Positions derivatives are velocities
    dstate_dt.dpos1 = state.vel1;
    dstate_dt.dpos2 = state.vel2;
    dstate_dt.dpos3 = state.vel3;

    // Initialize accelerations to zero
    pkr::units::vec_4d_units_t<pkr::units::meter_per_second_squared_t> acc1{
        0.0 * pkr::units::meter_per_second_squared_t(1.0),
        0.0 * pkr::units::meter_per_second_squared_t(1.0),
        0.0 * pkr::units::meter_per_second_squared_t(1.0),
        0.0 * pkr::units::meter_per_second_squared_t(1.0)};
    pkr::units::vec_4d_units_t<pkr::units::meter_per_second_squared_t> acc2{
        0.0 * pkr::units::meter_per_second_squared_t(1.0),
        0.0 * pkr::units::meter_per_second_squared_t(1.0),
        0.0 * pkr::units::meter_per_second_squared_t(1.0),
        0.0 * pkr::units::meter_per_second_squared_t(1.0)};
    pkr::units::vec_4d_units_t<pkr::units::meter_per_second_squared_t> acc3{
        0.0 * pkr::units::meter_per_second_squared_t(1.0),
        0.0 * pkr::units::meter_per_second_squared_t(1.0),
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

    // Set velocity derivatives to accelerations
    dstate_dt.dvel1 = acc1;
    dstate_dt.dvel2 = acc2;
    dstate_dt.dvel3 = acc3;

    return dstate_dt;
}

// Derivative function for measurements
three_body_derivative_measurement_t derivative_meas(const three_body_state_measurement_t& state)
{
    three_body_derivative_measurement_t dstate_dt;

    // Positions are velocities
    dstate_dt.dpos1 = state.vel1;
    dstate_dt.dpos2 = state.vel2;
    dstate_dt.dpos3 = state.vel3;

    // Initialize accelerations to zero
    pkr::units::vec_4d_measurements_rss_t<pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>> acc1{
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{
            0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{
            0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{
            0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{
            0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)}};
    pkr::units::vec_4d_measurements_rss_t<pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>> acc2{
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{
            0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{
            0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{
            0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{
            0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)}};
    pkr::units::vec_4d_measurements_rss_t<pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>> acc3{
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{
            0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{
            0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{
            0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{
            0.0 * pkr::units::meter_per_second_squared_t(1.0), 0.0 * pkr::units::meter_per_second_squared_t(1.0)}};

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
    dstate_dt.dvel1 = acc1;
    dstate_dt.dvel2 = acc2;
    dstate_dt.dvel3 = acc3;

    return dstate_dt;
}

} // namespace numerical
} // namespace test
} // namespace pkr
