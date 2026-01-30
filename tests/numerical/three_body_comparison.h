#pragma once

#include <array>
#include <vector>
#include <pkr_units/si_units.h>
#include <pkr_units/measurements/measurement.h>
#include "three_body_helpers.h"
#include "rk4_steppers_double.h"
#include "rk4_steppers_units.h"
#include "rk4_steppers_measurements.h"

namespace pkr {
namespace test {
namespace numerical {

// ============================================================================
// Comprehensive Simulation Results
// ============================================================================

struct three_body_simulation_result_t {
    // Energy conservation
    double max_energy_drift;
    double initial_energy;
    double final_energy;

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
three_body_simulation_result_t run_three_body_simulation_double(int steps = 1000, double dt = 0.01) {
    three_body_simulation_result_t result;
    result.steps_run = steps;
    result.time_step = dt;
    result.total_time = steps * dt;

    auto state = initial_state_double;
    result.initial_energy = compute_total_energy_double(state);
    result.max_energy_drift = 0.0;

    for (int i = 0; i < steps; ++i) {
        state = rk4_step_double(state, dt);
        double current_energy = compute_total_energy_double(state);
        double energy_drift = std::abs((current_energy - result.initial_energy) / result.initial_energy);
        result.max_energy_drift = std::max(result.max_energy_drift, energy_drift);
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
three_body_simulation_result_t run_three_body_simulation_si(int steps = 1000, double dt_years = 0.01) {
    three_body_simulation_result_t result;
    result.steps_run = steps;
    result.time_step = dt_years;
    result.total_time = steps * dt_years;

    auto state = initial_state_si;
    auto initial_energy = compute_total_energy_si(state);
    result.initial_energy = initial_energy.value();
    result.max_energy_drift = 0.0;

    auto dt = dt_years * pkr::units::year_t(1.0);

    for (int i = 0; i < steps; ++i) {
        state = rk4_step_si(state, dt);
        auto current_energy = compute_total_energy_si(state);
        double energy_drift = std::abs((current_energy.value() - result.initial_energy) / result.initial_energy);
        result.max_energy_drift = std::max(result.max_energy_drift, energy_drift);
    }

    auto final_energy = compute_total_energy_si(state);
    result.final_energy = final_energy.value();

    // Convert final positions to AU for comparison
    auto au_conversion = pkr::units::au_t(1.0);
    result.pos1_final = {
        (state.pos1.x / au_conversion).value(),
        (state.pos1.y / au_conversion).value(),
        (state.pos1.z / au_conversion).value()
    };
    result.pos2_final = {
        (state.pos2.x / au_conversion).value(),
        (state.pos2.y / au_conversion).value(),
        (state.pos2.z / au_conversion).value()
    };
    result.pos3_final = {
        (state.pos3.x / au_conversion).value(),
        (state.pos3.y / au_conversion).value(),
        (state.pos3.z / au_conversion).value()
    };

    // Convert final velocities to AU/year for comparison
    auto vel_conversion = pkr::units::au_t(1.0) / pkr::units::year_t(1.0);
    result.vel1_final = {
        (state.vel1.x / vel_conversion).value(),
        (state.vel1.y / vel_conversion).value(),
        (state.vel1.z / vel_conversion).value()
    };
    result.vel2_final = {
        (state.vel2.x / vel_conversion).value(),
        (state.vel2.y / vel_conversion).value(),
        (state.vel2.z / vel_conversion).value()
    };
    result.vel3_final = {
        (state.vel3.x / vel_conversion).value(),
        (state.vel3.y / vel_conversion).value(),
        (state.vel3.z / vel_conversion).value()
    };

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
three_body_simulation_result_t run_three_body_simulation_measurements(int steps = 100, double dt_years = 0.01) {
    three_body_simulation_result_t result;
    result.steps_run = steps;
    result.time_step = dt_years;
    result.total_time = steps * dt_years;

    auto state = initial_state_meas;
    auto initial_energy = compute_total_energy_meas(state);
    result.initial_energy = initial_energy.value().value();
    result.max_energy_drift = 0.0;

    auto dt = pkr::measurement_t<pkr::units::year_t>{dt_years * pkr::units::year_t(1.0), 1e-6 * pkr::units::year_t(1.0)};

    for (int i = 0; i < steps; ++i) {
        state = rk4_step_meas(state, dt);
        auto current_energy = compute_total_energy_meas(state);
        double energy_drift = std::abs((current_energy.value().value() - result.initial_energy) / result.initial_energy);
        result.max_energy_drift = std::max(result.max_energy_drift, energy_drift);
    }

    auto final_energy = compute_total_energy_meas(state);
    result.final_energy = final_energy.value().value();

    // Convert final positions to AU for comparison
    auto au_conversion = pkr::units::au_t(1.0);
    result.pos1_final = {
        (state.pos1.x.value() / au_conversion).value(),
        (state.pos1.y.value() / au_conversion).value(),
        (state.pos1.z.value() / au_conversion).value()
    };
    result.pos2_final = {
        (state.pos2.x.value() / au_conversion).value(),
        (state.pos2.y.value() / au_conversion).value(),
        (state.pos2.z.value() / au_conversion).value()
    };
    result.pos3_final = {
        (state.pos3.x.value() / au_conversion).value(),
        (state.pos3.y.value() / au_conversion).value(),
        (state.pos3.z.value() / au_conversion).value()
    };

    // Convert final velocities to AU/year for comparison
    auto vel_conversion = pkr::units::au_t(1.0) / pkr::units::year_t(1.0);
    result.vel1_final = {
        (state.vel1.x.value() / vel_conversion).value(),
        (state.vel1.y.value() / vel_conversion).value(),
        (state.vel1.z.value() / vel_conversion).value()
    };
    result.vel2_final = {
        (state.vel2.x.value() / vel_conversion).value(),
        (state.vel2.y.value() / vel_conversion).value(),
        (state.vel2.z.value() / vel_conversion).value()
    };
    result.vel3_final = {
        (state.vel3.x.value() / vel_conversion).value(),
        (state.vel3.y.value() / vel_conversion).value(),
        (state.vel3.z.value() / vel_conversion).value()
    };

    // Store uncertainties (converted to AU and AU/year)
    result.pos1_uncertainty = {
        (state.pos1.x.uncertainty() / au_conversion).value(),
        (state.pos1.y.uncertainty() / au_conversion).value(),
        (state.pos1.z.uncertainty() / au_conversion).value()
    };
    result.pos2_uncertainty = {
        (state.pos2.x.uncertainty() / au_conversion).value(),
        (state.pos2.y.uncertainty() / au_conversion).value(),
        (state.pos2.z.uncertainty() / au_conversion).value()
    };
    result.pos3_uncertainty = {
        (state.pos3.x.uncertainty() / au_conversion).value(),
        (state.pos3.y.uncertainty() / au_conversion).value(),
        (state.pos3.z.uncertainty() / au_conversion).value()
    };
    result.vel1_uncertainty = {
        (state.vel1.x.uncertainty() / vel_conversion).value(),
        (state.vel1.y.uncertainty() / vel_conversion).value(),
        (state.vel1.z.uncertainty() / vel_conversion).value()
    };
    result.vel2_uncertainty = {
        (state.vel2.x.uncertainty() / vel_conversion).value(),
        (state.vel2.y.uncertainty() / vel_conversion).value(),
        (state.vel2.z.uncertainty() / vel_conversion).value()
    };
    result.vel3_uncertainty = {
        (state.vel3.x.uncertainty() / vel_conversion).value(),
        (state.vel3.y.uncertainty() / vel_conversion).value(),
        (state.vel3.z.uncertainty() / vel_conversion).value()
    };

    return result;
}

// ============================================================================
// Comparison and Validation Functions
// ============================================================================

// Structure to hold comparison results between methods
struct three_body_comparison_t {
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
three_body_comparison_t run_three_body_comparison(int steps_double = 1000, int steps_si = 1000, int steps_meas = 100) {
    three_body_comparison_t comparison;

    // Run all simulations
    comparison.plain_double = run_three_body_simulation_double(steps_double);
    comparison.si_units = run_three_body_simulation_si(steps_si);
    comparison.measurements = run_three_body_simulation_measurements(steps_meas);

    // Calculate position differences (SI - Plain)
    for (int i = 0; i < 3; ++i) {
        comparison.pos1_diff_si[i] = comparison.si_units.pos1_final[i] - comparison.plain_double.pos1_final[i];
        comparison.pos2_diff_si[i] = comparison.si_units.pos2_final[i] - comparison.plain_double.pos2_final[i];
        comparison.pos3_diff_si[i] = comparison.si_units.pos3_final[i] - comparison.plain_double.pos3_final[i];
        comparison.vel1_diff_si[i] = comparison.si_units.vel1_final[i] - comparison.plain_double.vel1_final[i];
        comparison.vel2_diff_si[i] = comparison.si_units.vel2_final[i] - comparison.plain_double.vel2_final[i];
        comparison.vel3_diff_si[i] = comparison.si_units.vel3_final[i] - comparison.plain_double.vel3_final[i];
    }

    // Calculate position differences (Measurements - Plain)
    for (int i = 0; i < 3; ++i) {
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

    for (int i = 0; i < 3; ++i) {
        comparison.max_pos_diff_si = std::max({comparison.max_pos_diff_si,
                                             std::abs(comparison.pos1_diff_si[i]),
                                             std::abs(comparison.pos2_diff_si[i]),
                                             std::abs(comparison.pos3_diff_si[i])});
        comparison.max_vel_diff_si = std::max({comparison.max_vel_diff_si,
                                             std::abs(comparison.vel1_diff_si[i]),
                                             std::abs(comparison.vel2_diff_si[i]),
                                             std::abs(comparison.vel3_diff_si[i])});
        comparison.max_pos_diff_meas = std::max({comparison.max_pos_diff_meas,
                                               std::abs(comparison.pos1_diff_meas[i]),
                                               std::abs(comparison.pos2_diff_meas[i]),
                                               std::abs(comparison.pos3_diff_meas[i])});
        comparison.max_vel_diff_meas = std::max({comparison.max_vel_diff_meas,
                                               std::abs(comparison.vel1_diff_meas[i]),
                                               std::abs(comparison.vel2_diff_meas[i]),
                                               std::abs(comparison.vel3_diff_meas[i])});
    }

    return comparison;
}

} // namespace numerical
} // namespace test
} // namespace pkr