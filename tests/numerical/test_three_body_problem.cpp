#include <gtest/gtest.h>
#include <pkr_units/si_units.h>
#include <pkr_units/astronomical_units.h>
#include <pkr_units/measurements/measurement.h>
#include <pkr_units/math/measurements/measurement_math_rss.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <type_traits>

#include "three_body_helpers.h"
#include "vector_math_double.h"
#include <pkr_units/math/unit_math_4d.h>
#include "rk4_steppers_double.h"
#include "rk4_steppers_units.h"
#include "rk4_steppers_measurements.h"
#include "three_body_comparison.h"

namespace test
{

using namespace ::testing;

class NumericalStabilityTest : public Test
{
};

class ThreeBodyAccuracyTest : public Test
{
};

// ---------------------------------------------------------------------------
// Small focused tests for building-block debugging (in increasing complexity)
// ---------------------------------------------------------------------------

TEST_F(NumericalStabilityTest, ComputeGravitationalAccelerationDouble_Simple)
{
    using namespace pkr::test::numerical;
    pkr::units::vec_4d_t<double> pos_i{0.0, 0.0, 0.0, 0.0};
    pkr::units::vec_4d_t<double> pos_j{1.0, 0.0, 0.0, 0.0};
    pkr::units::vec_4d_t<double> acc{0.0, 0.0, 0.0, 0.0};

    compute_gravitational_acceleration_double(pos_i, pos_j, 1.0, acc);

    // For r = 1.0 and mj = 1.0, acceleration magnitude should equal gravitational constant
    EXPECT_NEAR(acc.x, G, 1e-15);
    EXPECT_DOUBLE_EQ(acc.y, 0.0);
    EXPECT_DOUBLE_EQ(acc.z, 0.0);
}

TEST_F(NumericalStabilityTest, ComputeGravitationalAccelerationSI_Simple)
{
    using namespace pkr::test::numerical;

    pkr::units::vec_4d_units_t<pkr::units::meter_t> pos_i{
        pkr::units::meter_t(0.0), pkr::units::meter_t(0.0), pkr::units::meter_t(0.0), pkr::units::meter_t(0.0)};
    pkr::units::vec_4d_units_t<pkr::units::meter_t> pos_j{
        pkr::units::meter_t(1.0), pkr::units::meter_t(0.0), pkr::units::meter_t(0.0), pkr::units::meter_t(0.0)};
    pkr::units::vec_4d_units_t<pkr::units::meter_per_second_squared_t> acc{
        pkr::units::meter_per_second_squared_t(0.0),
        pkr::units::meter_per_second_squared_t(0.0),
        pkr::units::meter_per_second_squared_t(0.0),
        pkr::units::meter_per_second_squared_t(0.0)};

    compute_gravitational_acceleration_si(pos_i, pos_j, pkr::units::kilogram_t(1.0), acc);

    // acc.x (m/s^2) should approximately equal the gravitational constant G
    EXPECT_NEAR(acc.x.value(), G, 1e-15);
    EXPECT_DOUBLE_EQ(acc.y.value(), 0.0);
    EXPECT_DOUBLE_EQ(acc.z.value(), 0.0);
}

TEST_F(NumericalStabilityTest, ComputeGravitationalAccelerationMeas_Simple)
{
    using namespace pkr::test::numerical;

    using meter_meas = pkr::units::measurement_t<pkr::units::meter_t>;
    using kg_meas = pkr::units::measurement_t<pkr::units::kilogram_t>;

    pkr::units::vec_4d_measurements_rss_t<meter_meas> pos_i{
        meter_meas{pkr::units::meter_t(0.0), pkr::units::meter_t(0.0)},
        meter_meas{pkr::units::meter_t(0.0), pkr::units::meter_t(0.0)},
        meter_meas{pkr::units::meter_t(0.0), pkr::units::meter_t(0.0)},
        meter_meas{pkr::units::meter_t(0.0), pkr::units::meter_t(0.0)}};
    pkr::units::vec_4d_measurements_rss_t<meter_meas> pos_j{
        meter_meas{pkr::units::meter_t(1.0), pkr::units::meter_t(0.01)},
        meter_meas{pkr::units::meter_t(0.0), pkr::units::meter_t(0.01)},
        meter_meas{pkr::units::meter_t(0.0), pkr::units::meter_t(0.01)},
        meter_meas{pkr::units::meter_t(0.0), pkr::units::meter_t(0.01)}};

    pkr::units::measurement_t<pkr::units::kilogram_t> mj{pkr::units::kilogram_t(1.0), pkr::units::kilogram_t(0.0)};

    pkr::units::vec_4d_measurements_rss_t<pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>> acc{
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{
            pkr::units::meter_per_second_squared_t(0.0), pkr::units::meter_per_second_squared_t(0.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{
            pkr::units::meter_per_second_squared_t(0.0), pkr::units::meter_per_second_squared_t(0.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{
            pkr::units::meter_per_second_squared_t(0.0), pkr::units::meter_per_second_squared_t(0.0)},
        pkr::units::measurement_t<pkr::units::meter_per_second_squared_t>{
            pkr::units::meter_per_second_squared_t(0.0), pkr::units::meter_per_second_squared_t(0.0)}};

    compute_gravitational_acceleration_meas(pos_i, pos_j, mj, acc);

    EXPECT_TRUE(std::isfinite(acc.x.value()));
    EXPECT_GE(acc.x.uncertainty(), 0.0);
}

TEST_F(NumericalStabilityTest, RK4StepDouble_Sanity)
{
    auto state = pkr::test::numerical::initial_state_double;
    auto next = pkr::test::numerical::rk4_step_double(state, 0.01);

    // Basic sanity: values should be finite
    EXPECT_TRUE(std::isfinite(next.pos1.x));
    EXPECT_TRUE(std::isfinite(next.vel1.x));
}

TEST_F(NumericalStabilityTest, ThreeBodyHelpers_TypesCompileAndDefaultConstruct)
{
    using namespace pkr::test::numerical;

    // Compile-time type checks
    static_assert(std::is_same_v<decltype(initial_state_double.pos1), pkr::units::vec_4d_t<double>>);
    static_assert(std::is_same_v<decltype(initial_state_si.pos1), pkr::units::vec_4d_units_t<pkr::units::meter_t>>);
    static_assert(
        std::is_same_v<decltype(initial_state_meas.pos1), pkr::units::vec_4d_measurements_rss_t<pkr::units::measurement_t<pkr::units::meter_t>>>);

    // Default / example values are accessible at runtime
    EXPECT_TRUE(std::isfinite(initial_state_double.pos1.x));
    EXPECT_TRUE(std::isfinite(initial_state_si.pos1.x.value()));
    EXPECT_TRUE(std::isfinite(initial_state_meas.pos1.x.value()));
    EXPECT_GE(initial_state_meas.pos1.x.uncertainty(), 0.0);

    // Derivative types default construct and have expected member types
    three_body_derivative_measurement_t d;
    (void)d; // just ensure instantiation compiles
}

// ============================================================================
// 3-Body Problem Tests
// ============================================================================

TEST_F(NumericalStabilityTest, ThreeBodyProblem_PlainDoubles)
{
    auto result = pkr::test::numerical::run_three_body_simulation_double();

    // Report comprehensive results
    std::cout << "\n=== Plain Doubles Results ===\n";
    std::cout << "Steps: " << result.steps_run << ", Time step: " << result.time_step << " years, Total time: " << result.total_time << " years\n";
    std::cout << "Initial energy: " << result.initial_energy << "\n";
    std::cout << "Final energy: " << result.final_energy << "\n";
    std::cout << "Max energy drift: " << result.max_energy_drift << "\n";
    std::cout << "Final positions (AU): (" << result.pos1_final[0] << ", " << result.pos1_final[1] << ", " << result.pos1_final[2] << ") "
              << "(" << result.pos2_final[0] << ", " << result.pos2_final[1] << ", " << result.pos2_final[2] << ") "
              << "(" << result.pos3_final[0] << ", " << result.pos3_final[1] << ", " << result.pos3_final[2] << ")\n";
    std::cout << "Final velocities (AU/year): (" << result.vel1_final[0] << ", " << result.vel1_final[1] << ", " << result.vel1_final[2] << ") "
              << "(" << result.vel2_final[0] << ", " << result.vel2_final[1] << ", " << result.vel2_final[2] << ") "
              << "(" << result.vel3_final[0] << ", " << result.vel3_final[1] << ", " << result.vel3_final[2] << ")\n";

    // Check that energy drift is small (numerical stability)
    EXPECT_LT(result.max_energy_drift, 1e-6) << "Energy conservation violated - numerical instability detected";

    // Check that positions are reasonable (not NaN or infinite)
    EXPECT_TRUE(std::isfinite(result.pos1_final[0]) && std::isfinite(result.pos1_final[1]) && std::isfinite(result.pos1_final[2]));
    EXPECT_TRUE(std::isfinite(result.pos2_final[0]) && std::isfinite(result.pos2_final[1]) && std::isfinite(result.pos2_final[2]));
    EXPECT_TRUE(std::isfinite(result.pos3_final[0]) && std::isfinite(result.pos3_final[1]) && std::isfinite(result.pos3_final[2]));
}

TEST_F(NumericalStabilityTest, ThreeBodyProblem_SIUnits)
{
    // Use a smaller timestep in SI to ensure integrator stability (units preserved by stable math)
    auto result = pkr::test::numerical::run_three_body_simulation_si(1000, 0.0001);

    // Report comprehensive results
    std::cout << "\n=== SI Units Results ===\n";
    std::cout << "Steps: " << result.steps_run << ", Time step: " << result.time_step << " years, Total time: " << result.total_time << " years\n";
    std::cout << "Initial energy: " << result.initial_energy << "\n";
    std::cout << "Final energy: " << result.final_energy << "\n";
    std::cout << "Max energy drift: " << result.max_energy_drift << "\n";
    std::cout << "Final positions (AU): (" << result.pos1_final[0] << ", " << result.pos1_final[1] << ", " << result.pos1_final[2] << ") "
              << "(" << result.pos2_final[0] << ", " << result.pos2_final[1] << ", " << result.pos2_final[2] << ") "
              << "(" << result.pos3_final[0] << ", " << result.pos3_final[1] << ", " << result.pos3_final[2] << ")\n";
    std::cout << "Final velocities (AU/year): (" << result.vel1_final[0] << ", " << result.vel1_final[1] << ", " << result.vel1_final[2] << ") "
              << "(" << result.vel2_final[0] << ", " << result.vel2_final[1] << ", " << result.vel2_final[2] << ") "
              << "(" << result.vel3_final[0] << ", " << result.vel3_final[1] << ", " << result.vel3_final[2] << ")\n";

    // Check that energy drift is small (numerical stability)
    // Diagnostic output: print energy history size and sample near max-drift step
    std::cout << "Energy history size: " << result.energy_history.size() << "\n";
    std::cout << "Max energy drift: " << result.max_energy_drift << " at step " << result.max_energy_drift_step << "\n";
    if (result.max_energy_drift_step >= 0 && result.max_energy_drift_step < static_cast<int>(result.energy_history.size()))
    {
        int idx = result.max_energy_drift_step;
        int start = std::max(0, idx - 2);
        int end = std::min(static_cast<int>(result.energy_history.size()) - 1, idx + 2);
        std::cout << std::scientific;
        std::cout << "Energy sample around max-drift step: ";
        for (int i = start; i <= end; ++i)
        {
            std::cout << "step[" << i << "]=" << result.energy_history[i] << " ";
        }
        std::cout << std::defaultfloat << "\n";

        std::cout << "Snapshot at max-drift step (positions in AU, velocities in AU/year):\n";
        std::cout << "pos1: (" << result.max_drift_pos1[0] << ", " << result.max_drift_pos1[1] << ", " << result.max_drift_pos1[2] << ")\n";
        std::cout << "pos2: (" << result.max_drift_pos2[0] << ", " << result.max_drift_pos2[1] << ", " << result.max_drift_pos2[2] << ")\n";
        std::cout << "pos3: (" << result.max_drift_pos3[0] << ", " << result.max_drift_pos3[1] << ", " << result.max_drift_pos3[2] << ")\n";
        std::cout << "vel1: (" << result.max_drift_vel1[0] << ", " << result.max_drift_vel1[1] << ", " << result.max_drift_vel1[2] << ")\n";
        std::cout << "vel2: (" << result.max_drift_vel2[0] << ", " << result.max_drift_vel2[1] << ", " << result.max_drift_vel2[2] << ")\n";
        std::cout << "vel3: (" << result.max_drift_vel3[0] << ", " << result.max_drift_vel3[1] << ", " << result.max_drift_vel3[2] << ")\n";
        std::cout << std::scientific;
        std::cout << "KEs (J): ke1=" << result.max_drift_ke1 << " ke2=" << result.max_drift_ke2 << " ke3=" << result.max_drift_ke3 << "\n";
        std::cout << "Pair masses (base SI) pair12=" << result.max_drift_pair12 << " pair13=" << result.max_drift_pair13
                  << " pair23=" << result.max_drift_pair23 << "\n";
        std::cout << "Potential G*sum (J): " << result.max_drift_gm_sum << std::defaultfloat << "\n";

        // Try smaller timesteps to see if instability is timestep related
        auto r1 = pkr::test::numerical::run_three_body_simulation_si(1000, 0.001);
        std::cout << "Small dt (0.001 yr) max_energy_drift=" << r1.max_energy_drift << " final_energy=" << r1.final_energy << "\n";
        auto r2 = pkr::test::numerical::run_three_body_simulation_si(1000, 0.0001);
        std::cout << "Smaller dt (0.0001 yr) max_energy_drift=" << r2.max_energy_drift << " final_energy=" << r2.final_energy << "\n";

        // Compare against plain doubles at the same step to see if dynamics match
        if (result.max_energy_drift_step > 0)
        {
            auto pd = pkr::test::numerical::run_three_body_simulation_double(result.max_energy_drift_step, result.time_step);
            int idx = std::min(static_cast<int>(pd.energy_history.size()) - 1, result.max_energy_drift_step);
            std::cout << "Plain doubles energy at step " << idx << " = " << pd.energy_history[idx] << "\n";
            std::cout << std::fixed;
            std::cout << "Plain doubles snapshot at that step (positions AU):\n";
            std::cout << "pd pos1: (" << pd.pos1_final[0] << ", " << pd.pos1_final[1] << ", " << pd.pos1_final[2] << ")\n";
            std::cout << "pd pos2: (" << pd.pos2_final[0] << ", " << pd.pos2_final[1] << ", " << pd.pos2_final[2] << ")\n";
            std::cout << "pd pos3: (" << pd.pos3_final[0] << ", " << pd.pos3_final[1] << ", " << pd.pos3_final[2] << ")\n";
            std::cout << std::defaultfloat;

            // Print side-by-side energy comparison around the step
            int start = std::max(0, idx - 3);
            int end = std::min(static_cast<int>(result.energy_history.size()) - 1, idx + 3);
            std::cout << std::scientific;
            std::cout << "SI vs Plain energies around step " << idx << ":\n";
            for (int i = start; i <= end; ++i)
            {
                double si_e = result.energy_history[i];
                double pd_e = (i < static_cast<int>(pd.energy_history.size()) ? pd.energy_history[i] : std::numeric_limits<double>::quiet_NaN());
                double diff = si_e - pd_e;
                double rel = (std::isfinite(pd_e) && pd_e != 0.0) ? diff / pd_e : std::numeric_limits<double>::infinity();
                std::cout << "step[" << i << "] SI=" << si_e << " PD=" << pd_e << " diff=" << diff << " rel=" << rel << "\n";
            }
            std::cout << std::defaultfloat;
        }
    }

    EXPECT_LT(result.max_energy_drift, 1e-6) << "Energy conservation violated - numerical instability detected";

    // Check that positions are finite
    EXPECT_TRUE(std::isfinite(result.pos1_final[0]) && std::isfinite(result.pos1_final[1]) && std::isfinite(result.pos1_final[2]));
    EXPECT_TRUE(std::isfinite(result.pos2_final[0]) && std::isfinite(result.pos2_final[1]) && std::isfinite(result.pos2_final[2]));
    EXPECT_TRUE(std::isfinite(result.pos3_final[0]) && std::isfinite(result.pos3_final[1]) && std::isfinite(result.pos3_final[2]));
}

TEST_F(NumericalStabilityTest, ThreeBodyProblem_SIUnits_Perturbed) {
    using namespace pkr::test::numerical;

    // Deterministic small perturbations (in AU for positions, AU/year for velocities)
    std::vector<double> pos_eps = {1e-6, 1e-4, 1e-3};
    double dt = 0.01; // original problematic dt; ensure non-degenerate initial conditions are stable

    for (double eps : pos_eps) {
        // Start from the perturbed initial condition
        three_body_state_si_t s = initial_state_si;

        // Perturb body 2 and 3 positions slightly
        s.pos2.x = s.pos2.x - pkr::units::au_t(eps);
        s.pos2.y = s.pos2.y + pkr::units::au_t(eps * 0.1);
        s.pos3.x = s.pos3.x + pkr::units::au_t(eps * 0.2);
        s.pos3.y = s.pos3.y - pkr::units::au_t(eps * 0.05);

        // Small velocity perturbation
        s.vel1.y = s.vel1.y + (pkr::units::au_t(eps) / pkr::units::year_t(1.0)) * 0.01;

        // For diagnostics: run SI simulation from this perturbed state with RK4-stage diagnostics enabled at suspected close-approach step
        int debug_diag_step = 23; // inspect k1..k4 around the previously observed close approach
        auto result = run_three_body_simulation_si_from_state(s, 1000, dt, debug_diag_step);

        // Numerical stability checks: finite final positions & velocities
        EXPECT_TRUE(std::isfinite(result.pos1_final[0]) && std::isfinite(result.pos1_final[1]) && std::isfinite(result.pos1_final[2]));
        EXPECT_TRUE(std::isfinite(result.vel1_final[0]) && std::isfinite(result.vel1_final[1]) && std::isfinite(result.vel1_final[2]));

        // Energy drift should be bounded (non-explosive) for non-degenerate perturbed cases
        EXPECT_LT(result.max_energy_drift, 1e-2) << "Energy drift too large for eps=" << eps;
    }
}

TEST_F(NumericalStabilityTest, ThreeBodyDiagnostics_GravPerStep)
{
    using namespace pkr::test::numerical;
    using namespace pkr::units;

    // Run a small number of steps with the original problematic timestep to inspect per-step values
    int steps = 30;
    double dt_years = 0.01; // original timestep where instability was observed
    auto dt = dt_years * year_t(1.0);

    auto state_si = initial_state_si;
    auto state_pd = initial_state_double;

    std::cout << "\n=== Per-step Gravitational Diagnostics (first " << steps << " steps) ===\n";
    std::cout << std::scientific << std::setprecision(6);

    for (int i = 0; i < steps; ++i)
    {
        // Print header for step
        std::cout << "Step " << i << "\n";

        // For SI: compute pairwise diagnostics
        auto print_pair_si = [&](const auto& pai, const auto& paj, const kilogram_t& mj, const char* label)
        {
            auto diff = paj - pai;
            auto r2 = pkr::units::dot(diff, diff);
            auto r = pkr::units::sqrt(r2);
            auto r3 = r * r2;
            auto inv_r3 = pkr::units::stable_divide(1.0, r3);
            auto gm = pkr::units::stable_multiply(constants::gravitational_constant, mj);
            auto factor = pkr::units::stable_multiply(gm, inv_r3);
            auto delta = pkr::units::stable_multiply(factor, diff);

            auto accel_conv = (au_t(1.0) / year_t(1.0) / year_t(1.0));
            auto delta_in_au_per_year2 = (delta.x / accel_conv).value();
            std::cout << label << " SI: r(m)=" << r.in_base_si_units().value() << " inv_r3(1/m^3)=" << inv_r3.in_base_si_units().value()
                      << " gm=" << gm.in_base_si_units().value() << " factor=" << factor.in_base_si_units().value() << " delta.x(m/s^2)=" << delta.x.value()
                      << " delta.x(AU/yr^2)=" << delta_in_au_per_year2 << "\n";
        };

        print_pair_si(state_si.pos1, state_si.pos2, m2_si, "pair12");
        print_pair_si(state_si.pos1, state_si.pos3, m3_si, "pair13");
        print_pair_si(state_si.pos2, state_si.pos3, m3_si, "pair23");

        // For plain doubles: compute pairwise diagnostics
        auto print_pair_pd = [&](const auto& pdi, const auto& pdj, double mj, const char* label)
        {
            auto diff = pdj - pdi;
            double r2 = pkr::units::dot(diff, diff);
            double r = std::sqrt(r2);
            double r3 = r * r2;
            double inv_r3 = 1.0 / r3;
            double gm = G * mj;
            double factor = gm * inv_r3;
            auto delta = pkr::units::vec_4d_t<double>{factor * diff.x, factor * diff.y, factor * diff.z, factor * diff.w};
            std::cout << label << " PD: r=" << r << " inv_r3=" << inv_r3 << " gm=" << gm << " factor=" << factor << " delta.x=" << delta.x << "\n";
        };

        print_pair_pd(state_pd.pos1, state_pd.pos2, m2, "pair12");
        print_pair_pd(state_pd.pos1, state_pd.pos3, m3, "pair13");
        print_pair_pd(state_pd.pos2, state_pd.pos3, m3, "pair23");

        // Advance one RK4 step for both systems
        state_si = rk4_step_si(state_si, dt);
        state_pd = rk4_step_double(state_pd, dt_years);

        // Basic sanity: no NaNs or infinities in the short run
        EXPECT_TRUE(std::isfinite(state_pd.pos1.x));
        EXPECT_TRUE(std::isfinite(state_si.pos1.x.value()));
    }

    // TEST_F(NumericalStabilityTest, ThreeBodyProblem_Measurements) {
    //     auto result = pkr::test::numerical::run_three_body_simulation_measurements();

    //     // Report comprehensive results
    //     std::cout << "\n=== Measurements Results ===\n";
    //     std::cout << "Steps: " << result.steps_run << ", Time step: " << result.time_step << " years, Total time: " << result.total_time << " years\n";
    //     std::cout << "Initial energy: " << result.initial_energy << "\n";
    //     std::cout << "Final energy: " << result.final_energy << "\n";
    //     std::cout << "Max energy drift: " << result.max_energy_drift << "\n";
    //     std::cout << "Final positions (AU): (" << result.pos1_final[0] << ", " << result.pos1_final[1] << ", " << result.pos1_final[2] << ") "
    //               << "(" << result.pos2_final[0] << ", " << result.pos2_final[1] << ", " << result.pos2_final[2] << ") "
    //               << "(" << result.pos3_final[0] << ", " << result.pos3_final[1] << ", " << result.pos3_final[2] << ")\n";
    //     std::cout << "Final velocities (AU/year): (" << result.vel1_final[0] << ", " << result.vel1_final[1] << ", " << result.vel1_final[2] << ") "
    //               << "(" << result.vel2_final[0] << ", " << result.vel2_final[1] << ", " << result.vel2_final[2] << ") "
    //               << "(" << result.vel3_final[0] << ", " << result.vel3_final[1] << ", " << result.vel3_final[2] << ")\n";
    //     std::cout << "Position uncertainties (AU): (" << result.pos1_uncertainty[0] << ", " << result.pos1_uncertainty[1] << ", " << result.pos1_uncertainty[2] << ") "
    //               << "(" << result.pos2_uncertainty[0] << ", " << result.pos2_uncertainty[1] << ", " << result.pos2_uncertainty[2] << ") "
    //               << "(" << result.pos3_uncertainty[0] << ", " << result.pos3_uncertainty[1] << ", " << result.pos3_uncertainty[2] << ")\n";
    //     std::cout << "Velocity uncertainties (AU/year): (" << result.vel1_uncertainty[0] << ", " << result.vel1_uncertainty[1] << ", " << result.vel1_uncertainty[2] << ") "
    //               << "(" << result.vel2_uncertainty[0] << ", " << result.vel2_uncertainty[1] << ", " << result.vel2_uncertainty[2] << ") "
    //               << "(" << result.vel3_uncertainty[0] << ", " << result.vel3_uncertainty[1] << ", " << result.vel3_uncertainty[2] << ")\n";

    //     // Check that energy drift is reasonable (measurements have uncertainty propagation)
    //     EXPECT_LT(result.max_energy_drift, 1e-4) << "Energy conservation violated - numerical instability detected";

    //     // Check that positions are finite and uncertainties are reasonable
    //     EXPECT_TRUE(std::isfinite(result.pos1_final[0]) && std::isfinite(result.pos1_final[1]) && std::isfinite(result.pos1_final[2]));
    //     EXPECT_TRUE(std::isfinite(result.pos2_final[0]) && std::isfinite(result.pos2_final[1]) && std::isfinite(result.pos2_final[2]));
    //     EXPECT_TRUE(std::isfinite(result.pos3_final[0]) && std::isfinite(result.pos3_final[1]) && std::isfinite(result.pos3_final[2]));

    //     // Check that uncertainties haven't exploded
    //     EXPECT_LT(result.pos1_uncertainty[0], 1e10);
    //     EXPECT_LT(result.pos1_uncertainty[1], 1e10);
    //     EXPECT_LT(result.pos1_uncertainty[2], 1e10);
    // }

    // TEST_F(ThreeBodyAccuracyTest, ThreeBodyProblem_MethodComparison) {
    //     auto comparison = pkr::test::numerical::run_three_body_comparison();

    //     // Report comprehensive comparison results
    //     std::cout << "\n=== Method Comparison Results ===\n";
    //     std::cout << "Plain Doubles - Max energy drift: " << comparison.plain_double.max_energy_drift << "\n";
    //     std::cout << "SI Units - Max energy drift: " << comparison.si_units.max_energy_drift << "\n";
    //     std::cout << "Measurements - Max energy drift: " << comparison.measurements.max_energy_drift << "\n";

    //     std::cout << "\nFinal Positions (AU) - Plain Doubles:\n";
    //     std::cout << "Body 1: (" << comparison.plain_double.pos1_final[0] << ", " << comparison.plain_double.pos1_final[1] << ", " << comparison.plain_double.pos1_final[2] << ")\n";
    //     std::cout << "Body 2: (" << comparison.plain_double.pos2_final[0] << ", " << comparison.plain_double.pos2_final[1] << ", " << comparison.plain_double.pos2_final[2] << ")\n";
    //     std::cout << "Body 3: (" << comparison.plain_double.pos3_final[0] << ", " << comparison.plain_double.pos3_final[1] << ", " << comparison.plain_double.pos3_final[2] << ")\n";

    //     std::cout << "\nFinal Positions (AU) - SI Units:\n";
    //     std::cout << "Body 1: (" << comparison.si_units.pos1_final[0] << ", " << comparison.si_units.pos1_final[1] << ", " << comparison.si_units.pos1_final[2] << ")\n";
    //     std::cout << "Body 2: (" << comparison.si_units.pos2_final[0] << ", " << comparison.si_units.pos2_final[1] << ", " << comparison.si_units.pos2_final[2] << ")\n";
    //     std::cout << "Body 3: (" << comparison.si_units.pos3_final[0] << ", " << comparison.si_units.pos3_final[1] << ", " << comparison.si_units.pos3_final[2] << ")\n";

    //     std::cout << "\nFinal Positions (AU) - Measurements:\n";
    //     std::cout << "Body 1: (" << comparison.measurements.pos1_final[0] << ", " << comparison.measurements.pos1_final[1] << ", " << comparison.measurements.pos1_final[2] << ")\n";
    //     std::cout << "Body 2: (" << comparison.measurements.pos2_final[0] << ", " << comparison.measurements.pos2_final[1] << ", " << comparison.measurements.pos2_final[2] << ")\n";
    //     std::cout << "Body 3: (" << comparison.measurements.pos3_final[0] << ", " << comparison.measurements.pos3_final[1] << ", " << comparison.measurements.pos3_final[2] << ")\n";

    //     std::cout << "\nPosition Differences (SI - Plain Doubles):\n";
    //     std::cout << "Body 1: (" << comparison.pos1_diff_si[0] << ", " << comparison.pos1_diff_si[1] << ", " << comparison.pos1_diff_si[2] << ")\n";
    //     std::cout << "Body 2: (" << comparison.pos2_diff_si[0] << ", " << comparison.pos2_diff_si[1] << ", " << comparison.pos2_diff_si[2] << ")\n";
    //     std::cout << "Body 3: (" << comparison.pos3_diff_si[0] << ", " << comparison.pos3_diff_si[1] << ", " << comparison.pos3_diff_si[2] << ")\n";
    //     std::cout << "Max position difference: " << comparison.max_pos_diff_si << " AU\n";

    //     std::cout << "\nPosition Differences (Measurements - Plain Doubles):\n";
    //     std::cout << "Body 1: (" << comparison.pos1_diff_meas[0] << ", " << comparison.pos1_diff_meas[1] << ", " << comparison.pos1_diff_meas[2] << ")\n";
    //     std::cout << "Body 2: (" << comparison.pos2_diff_meas[0] << ", " << comparison.pos2_diff_meas[1] << ", " << comparison.pos2_diff_meas[2] << ")\n";
    //     std::cout << "Body 3: (" << comparison.pos3_diff_meas[0] << ", " << comparison.pos3_diff_meas[1] << ", " << comparison.pos3_diff_meas[2] << ")\n";
    //     std::cout << "Max position difference: " << comparison.max_pos_diff_meas << " AU\n";

    //     // Validate that all methods produce very similar results
    //     EXPECT_LT(comparison.max_pos_diff_si, 1e-10) << "SI units results differ too much from plain doubles";
    //     EXPECT_LT(comparison.max_vel_diff_si, 1e-10) << "SI units velocity results differ too much from plain doubles";

    //     // Measurements should be close but may have some differences due to uncertainty propagation and fewer steps
    //     EXPECT_LT(comparison.max_pos_diff_meas, 1e-6) << "Measurement results differ too much from plain doubles";
    //     EXPECT_LT(comparison.max_vel_diff_meas, 1e-6) << "Measurement velocity results differ too much from plain doubles";

    //     // Energy conservation should be similar across methods
    //     EXPECT_LT(std::abs(comparison.plain_double.max_energy_drift - comparison.si_units.max_energy_drift), 1e-12)
    //         << "Energy conservation differs between plain doubles and SI units";
    // }

}
} // namespace test