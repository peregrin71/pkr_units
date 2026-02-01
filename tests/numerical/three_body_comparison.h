#pragma once

#include <array>
#include <vector>
#include <pkr_units/si_units.h>
#include <pkr_units/measurements/measurement.h>
#include "three_body_helpers.h"
#include "rk4_steppers_double.h"
#include "rk4_steppers_units.h"
#include "rk4_steppers_measurements.h"

namespace pkr
{
namespace test
{
namespace numerical
{

// ============================================================================
// Comprehensive Simulation Results
// ============================================================================

struct three_body_simulation_result_t
{
    // Energy conservation
    double max_energy_drift;
    double initial_energy;
    double final_energy;

    // Per-step energy history (for diagnostics)
    std::vector<double> energy_history;
    // Step index where max energy drift was observed (-1 if not set)
    int max_energy_drift_step = -1;

    // Snapshot at max-drift step (for diagnostics)
    std::array<double, 3> max_drift_pos1{0.0, 0.0, 0.0};
    std::array<double, 3> max_drift_pos2{0.0, 0.0, 0.0};
    std::array<double, 3> max_drift_pos3{0.0, 0.0, 0.0};
    std::array<double, 3> max_drift_vel1{0.0, 0.0, 0.0};
    std::array<double, 3> max_drift_vel2{0.0, 0.0, 0.0};
    std::array<double, 3> max_drift_vel3{0.0, 0.0, 0.0};

    double max_drift_ke1 = 0.0;
    double max_drift_ke2 = 0.0;
    double max_drift_ke3 = 0.0;
    double max_drift_pair12 = 0.0;
    double max_drift_pair13 = 0.0;
    double max_drift_pair23 = 0.0;
    double max_drift_gm_sum = 0.0;

    // Final positions (in AU for comparison)
    std::array<double, 3> pos1_final;
    std::array<double, 3> pos2_final;
    std::array<double, 3> pos3_final;

    // Final velocities (in AU/year for comparison)
    std::array<double, 3> vel1_final;
    std::array<double, 3> vel2_final;
    std::array<double, 3> vel3_final;

    // For measurements: uncertainties
    std::array<double, 3> pos1_uncertainty;
    std::array<double, 3> pos2_uncertainty;
    std::array<double, 3> pos3_uncertainty;
    std::array<double, 3> vel1_uncertainty;
    std::array<double, 3> vel2_uncertainty;
    std::array<double, 3> vel3_uncertainty;

    // Simulation parameters
    int steps_run;
    double time_step;
    double total_time;
};

// ============================================================================
// Comprehensive Simulation Functions
// ============================================================================

// Run plain double simulation and return comprehensive results
three_body_simulation_result_t run_three_body_simulation_double(int steps = 1000, double dt = 0.01)
{
    three_body_simulation_result_t result;
    result.steps_run = steps;
    result.time_step = dt;
    result.total_time = steps * dt;

    auto state = initial_state_double;
    result.initial_energy = compute_total_energy_double(state);
    result.energy_history.clear();
    result.energy_history.push_back(result.initial_energy);
    result.max_energy_drift = 0.0;
    result.max_energy_drift_step = -1;

    for (int i = 0; i < steps; ++i)
    {
        state = rk4_step_double(state, dt);
        double current_energy = compute_total_energy_double(state);
        result.energy_history.push_back(current_energy);
        double energy_drift = std::abs((current_energy - result.initial_energy) / result.initial_energy);
        if (energy_drift > result.max_energy_drift)
        {
            result.max_energy_drift = energy_drift;
            result.max_energy_drift_step = i + 1; // index in energy_history corresponding to current step
        }
    }

    result.final_energy = compute_total_energy_double(state);

    // Store final positions (already in AU)
    result.pos1_final = {state.pos1.x, state.pos1.y, state.pos1.z};
    result.pos2_final = {state.pos2.x, state.pos2.y, state.pos2.z};
    result.pos3_final = {state.pos3.x, state.pos3.y, state.pos3.z};

    // Store final velocities (already in AU/year)
    result.vel1_final = {state.vel1.x, state.vel1.y, state.vel1.z};
    result.vel2_final = {state.vel2.x, state.vel2.y, state.vel2.z};
    result.vel3_final = {state.vel3.x, state.vel3.y, state.vel3.z};

    // No uncertainties for plain doubles
    result.pos1_uncertainty = {0.0, 0.0, 0.0};
    result.pos2_uncertainty = {0.0, 0.0, 0.0};
    result.pos3_uncertainty = {0.0, 0.0, 0.0};
    result.vel1_uncertainty = {0.0, 0.0, 0.0};
    result.vel2_uncertainty = {0.0, 0.0, 0.0};
    result.vel3_uncertainty = {0.0, 0.0, 0.0};

    return result;
}

// Run SI units simulation and return comprehensive results
three_body_simulation_result_t run_three_body_simulation_si(int steps = 1000, double dt_years = 0.01, int diag_step = -1)
{
    three_body_simulation_result_t result;
    result.steps_run = steps;
    result.time_step = dt_years;
    result.total_time = steps * dt_years;

    auto state = initial_state_si;
    auto initial_energy = compute_total_energy_si(state);
    result.initial_energy = initial_energy.value();
    result.energy_history.clear();
    result.energy_history.push_back(result.initial_energy);
    result.max_energy_drift = 0.0;
    result.max_energy_drift_step = -1;

    auto dt = dt_years * pkr::units::year_t(1.0);

    for (int i = 0; i < steps; ++i)
    {
        // Optional RK4-stage diagnostics for SI and plain-doubles around diag_step
        if (diag_step >= 0 && i >= std::max(0, diag_step - 3) && i <= diag_step + 3)
        {
            std::cout << "\n=== RK4 Stage Diagnostics at step " << i << " ===\n";
            // SI stages
            auto k1 = derivative_si(state);
            // NB: dt is in years here; convert to seconds before using with SI (m/s, m/s^2) derivatives
            auto dt_seconds = pkr::units::unit_cast<pkr::units::second_t>(dt);
            auto half_dt = 0.5 * dt_seconds;
            three_body_state_si_t state2{
                state.pos1 + (half_dt * k1.dpos1),
                state.pos2 + (half_dt * k1.dpos2),
                state.pos3 + (half_dt * k1.dpos3),
                state.vel1 + (half_dt * k1.dvel1),
                state.vel2 + (half_dt * k1.dvel2),
                state.vel3 + (half_dt * k1.dvel3)};
            auto k2 = derivative_si(state2);
            three_body_state_si_t state3{
                state.pos1 + (half_dt * k2.dpos1),
                state.pos2 + (half_dt * k2.dpos2),
                state.pos3 + (half_dt * k2.dpos3),
                state.vel1 + (half_dt * k2.dvel1),
                state.vel2 + (half_dt * k2.dvel2),
                state.vel3 + (half_dt * k2.dvel3)};
            auto k3 = derivative_si(state3);
            three_body_state_si_t state4{
                state.pos1 + (dt_seconds * k3.dpos1),
                state.pos2 + (dt_seconds * k3.dpos2),
                state.pos3 + (dt_seconds * k3.dpos3),
                state.vel1 + (dt_seconds * k3.dvel1),
                state.vel2 + (dt_seconds * k3.dvel2),
                state.vel3 + (dt_seconds * k3.dvel3)};
            auto k4 = derivative_si(state4);

            auto accel_conv = pkr::units::au_t(1.0) / pkr::units::year_t(1.0) / pkr::units::year_t(1.0);
            auto print_si_stage = [&](const char* name, const three_body_derivative_si_t& K)
            {
                auto mag1 =
                    std::sqrt((K.dvel1.x.value() * K.dvel1.x.value()) + (K.dvel1.y.value() * K.dvel1.y.value()) + (K.dvel1.z.value() * K.dvel1.z.value()));
                std::cout << name << " SI dvel1 (m/s^2) = (" << K.dvel1.x.value() << ", " << K.dvel1.y.value() << ", " << K.dvel1.z.value() << ")";
                std::cout << "  (AU/yr^2) = (" << (K.dvel1.x / accel_conv).value() << ", " << (K.dvel1.y / accel_conv).value() << ", "
                          << (K.dvel1.z / accel_conv).value() << ")";
                std::cout << "  |dvel1|=" << mag1 << "\n";
            };

            print_si_stage("k1", k1);
            print_si_stage("k2", k2);
            print_si_stage("k3", k3);
            print_si_stage("k4", k4);

            // Plain-doubles stages for comparison
            three_body_state_double_t pd_state = {
                {state.pos1.x.value(), state.pos1.y.value(), state.pos1.z.value(), state.pos1.w.value()},
                {state.pos2.x.value(), state.pos2.y.value(), state.pos2.z.value(), state.pos2.w.value()},
                {state.pos3.x.value(), state.pos3.y.value(), state.pos3.z.value(), state.pos3.w.value()},
                {state.vel1.x.value(), state.vel1.y.value(), state.vel1.z.value(), state.vel1.w.value()},
                {state.vel2.x.value(), state.vel2.y.value(), state.vel2.z.value(), state.vel2.w.value()},
                {state.vel3.x.value(), state.vel3.y.value(), state.vel3.z.value(), state.vel3.w.value()}};

            three_body_state_double_t k1_pd_state;
            derivative_double(pd_state, k1_pd_state);
            double half_dt_pd = 0.5 * dt_years;
            three_body_state_double_t pd_state2{
                {pd_state.pos1.x + half_dt_pd * k1_pd_state.pos1.x,
                 pd_state.pos1.y + half_dt_pd * k1_pd_state.pos1.y,
                 pd_state.pos1.z + half_dt_pd * k1_pd_state.pos1.z,
                 0.0},
                {pd_state.pos2.x + half_dt_pd * k1_pd_state.pos2.x,
                 pd_state.pos2.y + half_dt_pd * k1_pd_state.pos2.y,
                 pd_state.pos2.z + half_dt_pd * k1_pd_state.pos2.z,
                 0.0},
                {pd_state.pos3.x + half_dt_pd * k1_pd_state.pos3.x,
                 pd_state.pos3.y + half_dt_pd * k1_pd_state.pos3.y,
                 pd_state.pos3.z + half_dt_pd * k1_pd_state.pos3.z,
                 0.0},
                {pd_state.vel1.x + half_dt_pd * k1_pd_state.vel1.x,
                 pd_state.vel1.y + half_dt_pd * k1_pd_state.vel1.y,
                 pd_state.vel1.z + half_dt_pd * k1_pd_state.vel1.z,
                 0.0},
                {pd_state.vel2.x + half_dt_pd * k1_pd_state.vel2.x,
                 pd_state.vel2.y + half_dt_pd * k1_pd_state.vel2.y,
                 pd_state.vel2.z + half_dt_pd * k1_pd_state.vel2.z,
                 0.0},
                {pd_state.vel3.x + half_dt_pd * k1_pd_state.vel3.x,
                 pd_state.vel3.y + half_dt_pd * k1_pd_state.vel3.y,
                 pd_state.vel3.z + half_dt_pd * k1_pd_state.vel3.z,
                 0.0}};
            three_body_state_double_t k2_pd_state;
            derivative_double(pd_state2, k2_pd_state);

            std::cout << "k1 PD dvel1 = (" << k1_pd_state.vel1.x << ", " << k1_pd_state.vel1.y << ", " << k1_pd_state.vel1.z << ")\n";
            std::cout << "k2 PD dvel1 = (" << k2_pd_state.vel1.x << ", " << k2_pd_state.vel1.y << ", " << k2_pd_state.vel1.z << ")\n";
        }

        state = rk4_step_si(state, dt);
        auto current_energy = compute_total_energy_si(state);
        double current_energy_value = current_energy.value();
        result.energy_history.push_back(current_energy_value);
        double energy_drift = std::abs((current_energy_value - result.initial_energy) / result.initial_energy);
        if (energy_drift > result.max_energy_drift)
        {
            result.max_energy_drift = energy_drift;
            result.max_energy_drift_step = i + 1; // step index in energy_history

            // Record snapshot for diagnostics
            auto au_conversion = pkr::units::au_t(1.0);
            auto vel_conversion = pkr::units::au_t(1.0) / pkr::units::year_t(1.0);
            result.max_drift_pos1 = {(state.pos1.x / au_conversion).value(), (state.pos1.y / au_conversion).value(), (state.pos1.z / au_conversion).value()};
            result.max_drift_pos2 = {(state.pos2.x / au_conversion).value(), (state.pos2.y / au_conversion).value(), (state.pos2.z / au_conversion).value()};
            result.max_drift_pos3 = {(state.pos3.x / au_conversion).value(), (state.pos3.y / au_conversion).value(), (state.pos3.z / au_conversion).value()};

            result.max_drift_vel1 = {(state.vel1.x / vel_conversion).value(), (state.vel1.y / vel_conversion).value(), (state.vel1.z / vel_conversion).value()};
            result.max_drift_vel2 = {(state.vel2.x / vel_conversion).value(), (state.vel2.y / vel_conversion).value(), (state.vel2.z / vel_conversion).value()};
            result.max_drift_vel3 = {(state.vel3.x / vel_conversion).value(), (state.vel3.y / vel_conversion).value(), (state.vel3.z / vel_conversion).value()};

            // Compute kinetic components (in joules)
            auto v1_sq = pkr::units::dot(state.vel1, state.vel1);
            auto v2_sq = pkr::units::dot(state.vel2, state.vel2);
            auto v3_sq = pkr::units::dot(state.vel3, state.vel3);
            auto ke1 = 0.5 * m1_si * v1_sq;
            auto ke2 = 0.5 * m2_si * v2_sq;
            auto ke3 = 0.5 * m3_si * v3_sq;
            result.max_drift_ke1 = ke1.in_base_si_units().value();
            result.max_drift_ke2 = ke2.in_base_si_units().value();
            result.max_drift_ke3 = ke3.in_base_si_units().value();

            // Compute pairwise potential pieces and their G*pair contributions
            auto d12 = state.pos1 - state.pos2;
            auto r12 = pkr::units::sqrt(pkr::units::dot(d12, d12));
            auto d13 = state.pos1 - state.pos3;
            auto r13 = pkr::units::sqrt(pkr::units::dot(d13, d13));
            auto d23 = state.pos2 - state.pos3;
            auto r23 = pkr::units::sqrt(pkr::units::dot(d23, d23));

            auto pair12 = m1_si * m2_si / r12;
            auto pair13 = m1_si * m3_si / r13;
            auto pair23 = m2_si * m3_si / r23;
            result.max_drift_pair12 = (pair12).in_base_si_units().value();
            result.max_drift_pair13 = (pair13).in_base_si_units().value();
            result.max_drift_pair23 = (pair23).in_base_si_units().value();

            auto gm_sum = G_si * (pair12 + pair13 + pair23);
            result.max_drift_gm_sum = (gm_sum * (-1.0)).in_base_si_units().value();
        }
    }

    auto final_energy = compute_total_energy_si(state);
    result.final_energy = final_energy.value();

    // Convert final positions to AU for comparison
    auto au_conversion = pkr::units::au_t(1.0);
    result.pos1_final = {(state.pos1.x / au_conversion).value(), (state.pos1.y / au_conversion).value(), (state.pos1.z / au_conversion).value()};
    result.pos2_final = {(state.pos2.x / au_conversion).value(), (state.pos2.y / au_conversion).value(), (state.pos2.z / au_conversion).value()};
    result.pos3_final = {(state.pos3.x / au_conversion).value(), (state.pos3.y / au_conversion).value(), (state.pos3.z / au_conversion).value()};

    // Convert final velocities to AU/year for comparison
    auto vel_conversion = pkr::units::au_t(1.0) / pkr::units::year_t(1.0);
    result.vel1_final = {(state.vel1.x / vel_conversion).value(), (state.vel1.y / vel_conversion).value(), (state.vel1.z / vel_conversion).value()};
    result.vel2_final = {(state.vel2.x / vel_conversion).value(), (state.vel2.y / vel_conversion).value(), (state.vel2.z / vel_conversion).value()};
    result.vel3_final = {(state.vel3.x / vel_conversion).value(), (state.vel3.y / vel_conversion).value(), (state.vel3.z / vel_conversion).value()};

    // No uncertainties for SI units
    result.pos1_uncertainty = {0.0, 0.0, 0.0};
    result.pos2_uncertainty = {0.0, 0.0, 0.0};
    result.pos3_uncertainty = {0.0, 0.0, 0.0};
    result.vel1_uncertainty = {0.0, 0.0, 0.0};
    result.vel2_uncertainty = {0.0, 0.0, 0.0};
    result.vel3_uncertainty = {0.0, 0.0, 0.0};

    return result;
}

// Run SI units simulation from a given initial state (useful for perturbed initial condition tests)
three_body_simulation_result_t
    run_three_body_simulation_si_from_state(const three_body_state_si_t& init_state, int steps = 1000, double dt_years = 0.01, int diag_step = -1)
{
    three_body_simulation_result_t result;
    result.steps_run = steps;
    result.time_step = dt_years;
    result.total_time = steps * dt_years;

    auto state = init_state;
    auto initial_energy = compute_total_energy_si(state);
    result.initial_energy = initial_energy.value();
    result.energy_history.clear();
    result.energy_history.push_back(result.initial_energy);
    result.max_energy_drift = 0.0;
    result.max_energy_drift_step = -1;

    auto dt = dt_years * pkr::units::year_t(1.0);

    for (int i = 0; i < steps; ++i)
    {
        // Optional diagnostics around diag_step
        if (diag_step >= 0 && i >= std::max(0, diag_step - 3) && i <= diag_step + 3)
        {
            std::cout << "(perturbed) RK4 diagnostics at step " << i << "\n";

            // SI stages
            auto k1 = derivative_si(state);
            // Convert dt (years) to seconds for SI-stage diagnostics
            auto dt_seconds = pkr::units::unit_cast<pkr::units::second_t>(dt);
            auto half_dt = 0.5 * dt_seconds;
            three_body_state_si_t state2{
                state.pos1 + (half_dt * k1.dpos1),
                state.pos2 + (half_dt * k1.dpos2),
                state.pos3 + (half_dt * k1.dpos3),
                state.vel1 + (half_dt * k1.dvel1),
                state.vel2 + (half_dt * k1.dvel2),
                state.vel3 + (half_dt * k1.dvel3)};
            auto k2 = derivative_si(state2);
            three_body_state_si_t state3{
                state.pos1 + (half_dt * k2.dpos1),
                state.pos2 + (half_dt * k2.dpos2),
                state.pos3 + (half_dt * k2.dpos3),
                state.vel1 + (half_dt * k2.dvel1),
                state.vel2 + (half_dt * k2.dvel2),
                state.vel3 + (half_dt * k2.dvel3)};
            auto k3 = derivative_si(state3);
            three_body_state_si_t state4{
                state.pos1 + (dt * k3.dpos1),
                state.pos2 + (dt * k3.dpos2),
                state.pos3 + (dt * k3.dpos3),
                state.vel1 + (dt * k3.dvel1),
                state.vel2 + (dt * k3.dvel2),
                state.vel3 + (dt * k3.dvel3)};
            auto k4 = derivative_si(state4);

            auto accel_conv = pkr::units::au_t(1.0) / pkr::units::year_t(1.0) / pkr::units::year_t(1.0);
            auto print_si_stage = [&](const char* name, const three_body_derivative_si_t& K)
            {
                auto mag1 =
                    std::sqrt((K.dvel1.x.value() * K.dvel1.x.value()) + (K.dvel1.y.value() * K.dvel1.y.value()) + (K.dvel1.z.value() * K.dvel1.z.value()));
                std::cout << name << " SI dvel1 (m/s^2) = (" << K.dvel1.x.value() << ", " << K.dvel1.y.value() << ", " << K.dvel1.z.value() << ")";
                std::cout << "  (AU/yr^2) = (" << (K.dvel1.x / accel_conv).value() << ", " << (K.dvel1.y / accel_conv).value() << ", "
                          << (K.dvel1.z / accel_conv).value() << ")";
                std::cout << "  |dvel1|=" << mag1 << "\n";
            };

            print_si_stage("k1", k1);
            print_si_stage("k2", k2);
            print_si_stage("k3", k3);
            print_si_stage("k4", k4);

            // Plain-doubles stages for comparison
            three_body_state_double_t pd_state = {
                {state.pos1.x.value(), state.pos1.y.value(), state.pos1.z.value(), state.pos1.w.value()},
                {state.pos2.x.value(), state.pos2.y.value(), state.pos2.z.value(), state.pos2.w.value()},
                {state.pos3.x.value(), state.pos3.y.value(), state.pos3.z.value(), state.pos3.w.value()},
                {state.vel1.x.value(), state.vel1.y.value(), state.vel1.z.value(), state.vel1.w.value()},
                {state.vel2.x.value(), state.vel2.y.value(), state.vel2.z.value(), state.vel2.w.value()},
                {state.vel3.x.value(), state.vel3.y.value(), state.vel3.z.value(), state.vel3.w.value()}};

            three_body_state_double_t k1_pd_state;
            derivative_double(pd_state, k1_pd_state);
            double half_dt_pd = 0.5 * dt_years;
            three_body_state_double_t pd_state2{
                {pd_state.pos1.x + half_dt_pd * k1_pd_state.pos1.x,
                 pd_state.pos1.y + half_dt_pd * k1_pd_state.pos1.y,
                 pd_state.pos1.z + half_dt_pd * k1_pd_state.pos1.z,
                 0.0},
                {pd_state.pos2.x + half_dt_pd * k1_pd_state.pos2.x,
                 pd_state.pos2.y + half_dt_pd * k1_pd_state.pos2.y,
                 pd_state.pos2.z + half_dt_pd * k1_pd_state.pos2.z,
                 0.0},
                {pd_state.pos3.x + half_dt_pd * k1_pd_state.pos3.x,
                 pd_state.pos3.y + half_dt_pd * k1_pd_state.pos3.y,
                 pd_state.pos3.z + half_dt_pd * k1_pd_state.pos3.z,
                 0.0},
                {pd_state.vel1.x + half_dt_pd * k1_pd_state.vel1.x,
                 pd_state.vel1.y + half_dt_pd * k1_pd_state.vel1.y,
                 pd_state.vel1.z + half_dt_pd * k1_pd_state.vel1.z,
                 0.0},
                {pd_state.vel2.x + half_dt_pd * k1_pd_state.vel2.x,
                 pd_state.vel2.y + half_dt_pd * k1_pd_state.vel2.y,
                 pd_state.vel2.z + half_dt_pd * k1_pd_state.vel2.z,
                 0.0},
                {pd_state.vel3.x + half_dt_pd * k1_pd_state.vel3.x,
                 pd_state.vel3.y + half_dt_pd * k1_pd_state.vel3.y,
                 pd_state.vel3.z + half_dt_pd * k1_pd_state.vel3.z,
                 0.0}};
            three_body_state_double_t k2_pd_state;
            derivative_double(pd_state2, k2_pd_state);

            std::cout << "k1 PD dvel1 = (" << k1_pd_state.vel1.x << ", " << k1_pd_state.vel1.y << ", " << k1_pd_state.vel1.z << ")\n";
            std::cout << "k2 PD dvel1 = (" << k2_pd_state.vel1.x << ", " << k2_pd_state.vel1.y << ", " << k2_pd_state.vel1.z << ")\n";
        }

        state = rk4_step_si(state, dt);
        auto current_energy = compute_total_energy_si(state);
        double current_energy_value = current_energy.value();
        result.energy_history.push_back(current_energy_value);
        double energy_drift = std::abs((current_energy_value - result.initial_energy) / result.initial_energy);
        if (energy_drift > result.max_energy_drift)
        {
            result.max_energy_drift = energy_drift;
            result.max_energy_drift_step = i + 1;

            auto au_conversion = pkr::units::au_t(1.0);
            auto vel_conversion = pkr::units::au_t(1.0) / pkr::units::year_t(1.0);
            result.max_drift_pos1 = {(state.pos1.x / au_conversion).value(), (state.pos1.y / au_conversion).value(), (state.pos1.z / au_conversion).value()};
            result.max_drift_pos2 = {(state.pos2.x / au_conversion).value(), (state.pos2.y / au_conversion).value(), (state.pos2.z / au_conversion).value()};
            result.max_drift_pos3 = {(state.pos3.x / au_conversion).value(), (state.pos3.y / au_conversion).value(), (state.pos3.z / au_conversion).value()};

            result.max_drift_vel1 = {(state.vel1.x / vel_conversion).value(), (state.vel1.y / vel_conversion).value(), (state.vel1.z / vel_conversion).value()};
            result.max_drift_vel2 = {(state.vel2.x / vel_conversion).value(), (state.vel2.y / vel_conversion).value(), (state.vel2.z / vel_conversion).value()};
            result.max_drift_vel3 = {(state.vel3.x / vel_conversion).value(), (state.vel3.y / vel_conversion).value(), (state.vel3.z / vel_conversion).value()};
        }
    }

    auto final_energy = compute_total_energy_si(state);
    result.final_energy = final_energy.value();

    // Convert final positions to AU for comparison
    auto au_conversion = pkr::units::au_t(1.0);
    result.pos1_final = {(state.pos1.x / au_conversion).value(), (state.pos1.y / au_conversion).value(), (state.pos1.z / au_conversion).value()};
    result.pos2_final = {(state.pos2.x / au_conversion).value(), (state.pos2.y / au_conversion).value(), (state.pos2.z / au_conversion).value()};
    result.pos3_final = {(state.pos3.x / au_conversion).value(), (state.pos3.y / au_conversion).value(), (state.pos3.z / au_conversion).value()};

    // Convert final velocities to AU/year for comparison
    auto vel_conversion = pkr::units::au_t(1.0) / pkr::units::year_t(1.0);
    result.vel1_final = {(state.vel1.x / vel_conversion).value(), (state.vel1.y / vel_conversion).value(), (state.vel1.z / vel_conversion).value()};
    result.vel2_final = {(state.vel2.x / vel_conversion).value(), (state.vel2.y / vel_conversion).value(), (state.vel2.z / vel_conversion).value()};
    result.vel3_final = {(state.vel3.x / vel_conversion).value(), (state.vel3.y / vel_conversion).value(), (state.vel3.z / vel_conversion).value()};

    // No uncertainties for SI units
    result.pos1_uncertainty = {0.0, 0.0, 0.0};
    result.pos2_uncertainty = {0.0, 0.0, 0.0};
    result.pos3_uncertainty = {0.0, 0.0, 0.0};
    result.vel1_uncertainty = {0.0, 0.0, 0.0};
    result.vel2_uncertainty = {0.0, 0.0, 0.0};
    result.vel3_uncertainty = {0.0, 0.0, 0.0};

    return result;
}

// Run measurements simulation and return comprehensive results
three_body_simulation_result_t run_three_body_simulation_measurements(int steps = 100, double dt_years = 0.01)
{
    three_body_simulation_result_t result;
    result.steps_run = steps;
    result.time_step = dt_years;
    result.total_time = steps * dt_years;

    auto state = initial_state_meas;
    auto initial_energy = compute_total_energy_meas(state);
    result.initial_energy = initial_energy.value();
    result.energy_history.clear();
    result.energy_history.push_back(result.initial_energy);
    result.max_energy_drift = 0.0;
    result.max_energy_drift_step = -1;

    auto dt_years_meas = pkr::units::measurement_t<pkr::units::year_t>{pkr::units::year_t(dt_years), pkr::units::year_t(1e-6 * dt_years)};
    auto dt_seconds_value = pkr::units::unit_cast<pkr::units::second_t>(dt_years_meas.unit_value());
    auto dt_seconds_uncertainty = pkr::units::unit_cast<pkr::units::second_t>(dt_years_meas.unit_uncertainty());
    auto dt = pkr::units::measurement_t<pkr::units::second_t>{dt_seconds_value, dt_seconds_uncertainty};

    for (int i = 0; i < steps; ++i)
    {
        state = rk4_step_meas(state, dt);
        auto current_energy = compute_total_energy_meas(state);
        double current_energy_value = current_energy.value();
        result.energy_history.push_back(current_energy_value);
        double energy_drift = std::abs((current_energy_value - result.initial_energy) / result.initial_energy);
        if (energy_drift > result.max_energy_drift)
        {
            result.max_energy_drift = energy_drift;
            result.max_energy_drift_step = i + 1;
        }
    }

    auto final_energy = compute_total_energy_meas(state);
    result.final_energy = final_energy.value();

    // Convert final positions to AU for comparison
    auto au_conversion = pkr::units::au_t(1.0);
    result.pos1_final = {
        (state.pos1.x.value() / au_conversion).value(), (state.pos1.y.value() / au_conversion).value(), (state.pos1.z.value() / au_conversion).value()};
    result.pos2_final = {
        (state.pos2.x.value() / au_conversion).value(), (state.pos2.y.value() / au_conversion).value(), (state.pos2.z.value() / au_conversion).value()};
    result.pos3_final = {
        (state.pos3.x.value() / au_conversion).value(), (state.pos3.y.value() / au_conversion).value(), (state.pos3.z.value() / au_conversion).value()};

    // Convert final velocities to AU/year for comparison
    auto vel_conversion = pkr::units::au_t(1.0) / pkr::units::year_t(1.0);
    result.vel1_final = {
        (state.vel1.x.value() / vel_conversion).value(), (state.vel1.y.value() / vel_conversion).value(), (state.vel1.z.value() / vel_conversion).value()};
    result.vel2_final = {
        (state.vel2.x.value() / vel_conversion).value(), (state.vel2.y.value() / vel_conversion).value(), (state.vel2.z.value() / vel_conversion).value()};
    result.vel3_final = {
        (state.vel3.x.value() / vel_conversion).value(), (state.vel3.y.value() / vel_conversion).value(), (state.vel3.z.value() / vel_conversion).value()};

    // Store uncertainties (converted to AU and AU/year)
    result.pos1_uncertainty = {
        (state.pos1.x.uncertainty() / au_conversion).value(),
        (state.pos1.y.uncertainty() / au_conversion).value(),
        (state.pos1.z.uncertainty() / au_conversion).value()};
    result.pos2_uncertainty = {
        (state.pos2.x.uncertainty() / au_conversion).value(),
        (state.pos2.y.uncertainty() / au_conversion).value(),
        (state.pos2.z.uncertainty() / au_conversion).value()};
    result.pos3_uncertainty = {
        (state.pos3.x.uncertainty() / au_conversion).value(),
        (state.pos3.y.uncertainty() / au_conversion).value(),
        (state.pos3.z.uncertainty() / au_conversion).value()};
    result.vel1_uncertainty = {
        (state.vel1.x.uncertainty() / vel_conversion).value(),
        (state.vel1.y.uncertainty() / vel_conversion).value(),
        (state.vel1.z.uncertainty() / vel_conversion).value()};
    result.vel2_uncertainty = {
        (state.vel2.x.uncertainty() / vel_conversion).value(),
        (state.vel2.y.uncertainty() / vel_conversion).value(),
        (state.vel2.z.uncertainty() / vel_conversion).value()};
    result.vel3_uncertainty = {
        (state.vel3.x.uncertainty() / vel_conversion).value(),
        (state.vel3.y.uncertainty() / vel_conversion).value(),
        (state.vel3.z.uncertainty() / vel_conversion).value()};

    return result;
}

// ============================================================================
// Comparison and Validation Functions
// ============================================================================

// Structure to hold comparison results between methods
struct three_body_comparison_t
{
    three_body_simulation_result_t plain_double;
    three_body_simulation_result_t si_units;
    three_body_simulation_result_t measurements;

    // Position differences (SI - Plain, Measurements - Plain)
    std::array<double, 3> pos1_diff_si;
    std::array<double, 3> pos2_diff_si;
    std::array<double, 3> pos3_diff_si;
    std::array<double, 3> pos1_diff_meas;
    std::array<double, 3> pos2_diff_meas;
    std::array<double, 3> pos3_diff_meas;

    // Velocity differences
    std::array<double, 3> vel1_diff_si;
    std::array<double, 3> vel2_diff_si;
    std::array<double, 3> vel3_diff_si;
    std::array<double, 3> vel1_diff_meas;
    std::array<double, 3> vel2_diff_meas;
    std::array<double, 3> vel3_diff_meas;

    // Maximum position/velocity differences
    double max_pos_diff_si;
    double max_vel_diff_si;
    double max_pos_diff_meas;
    double max_vel_diff_meas;
};

// Run all three simulations and compare results
three_body_comparison_t run_three_body_comparison(int steps_double = 1000, int steps_si = 1000, int steps_meas = 100)
{
    three_body_comparison_t comparison;

    // Run all simulations
    comparison.plain_double = run_three_body_simulation_double(steps_double);
    comparison.si_units = run_three_body_simulation_si(steps_si);
    comparison.measurements = run_three_body_simulation_measurements(steps_meas);

    // Calculate position differences (SI - Plain)
    for (int i = 0; i < 3; ++i)
    {
        comparison.pos1_diff_si[i] = comparison.si_units.pos1_final[i] - comparison.plain_double.pos1_final[i];
        comparison.pos2_diff_si[i] = comparison.si_units.pos2_final[i] - comparison.plain_double.pos2_final[i];
        comparison.pos3_diff_si[i] = comparison.si_units.pos3_final[i] - comparison.plain_double.pos3_final[i];
        comparison.vel1_diff_si[i] = comparison.si_units.vel1_final[i] - comparison.plain_double.vel1_final[i];
        comparison.vel2_diff_si[i] = comparison.si_units.vel2_final[i] - comparison.plain_double.vel2_final[i];
        comparison.vel3_diff_si[i] = comparison.si_units.vel3_final[i] - comparison.plain_double.vel3_final[i];
    }

    // Calculate position differences (Measurements - Plain)
    for (int i = 0; i < 3; ++i)
    {
        comparison.pos1_diff_meas[i] = comparison.measurements.pos1_final[i] - comparison.plain_double.pos1_final[i];
        comparison.pos2_diff_meas[i] = comparison.measurements.pos2_final[i] - comparison.plain_double.pos2_final[i];
        comparison.pos3_diff_meas[i] = comparison.measurements.pos3_final[i] - comparison.plain_double.pos3_final[i];
        comparison.vel1_diff_meas[i] = comparison.measurements.vel1_final[i] - comparison.plain_double.vel1_final[i];
        comparison.vel2_diff_meas[i] = comparison.measurements.vel1_final[i] - comparison.plain_double.vel1_final[i];
        comparison.vel3_diff_meas[i] = comparison.measurements.vel3_final[i] - comparison.plain_double.vel3_final[i];
    }

    // Find maximum differences
    comparison.max_pos_diff_si = 0.0;
    comparison.max_vel_diff_si = 0.0;
    comparison.max_pos_diff_meas = 0.0;
    comparison.max_vel_diff_meas = 0.0;

    for (int i = 0; i < 3; ++i)
    {
        comparison.max_pos_diff_si = std::max(
            {comparison.max_pos_diff_si, std::abs(comparison.pos1_diff_si[i]), std::abs(comparison.pos2_diff_si[i]), std::abs(comparison.pos3_diff_si[i])});
        comparison.max_vel_diff_si = std::max(
            {comparison.max_vel_diff_si, std::abs(comparison.vel1_diff_si[i]), std::abs(comparison.vel2_diff_si[i]), std::abs(comparison.vel3_diff_si[i])});
        comparison.max_pos_diff_meas = std::max(
            {comparison.max_pos_diff_meas,
             std::abs(comparison.pos1_diff_meas[i]),
             std::abs(comparison.pos2_diff_meas[i]),
             std::abs(comparison.pos3_diff_meas[i])});
        comparison.max_vel_diff_meas = std::max(
            {comparison.max_vel_diff_meas,
             std::abs(comparison.vel1_diff_meas[i]),
             std::abs(comparison.vel2_diff_meas[i]),
             std::abs(comparison.vel3_diff_meas[i])});
    }

    return comparison;
}

} // namespace numerical
} // namespace test
} // namespace pkr
