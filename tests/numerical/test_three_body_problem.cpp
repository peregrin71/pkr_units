#include <gtest/gtest.h>
#include <pkr_units/si_units.h>
#include <pkr_units/astronomical_units.h>
#include <pkr_units/measurements/measurement.h>
#include <pkr_units/math/measurements/measurement_math_rss.h>
#include <vector>
#include <cmath>
#include <iostream>

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

// ============================================================================
// 3-Body Problem Tests
// ============================================================================

TEST_F(NumericalStabilityTest, ThreeBodyProblem_PlainDoubles) {
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

TEST_F(NumericalStabilityTest, ThreeBodyProblem_SIUnits) {
    auto result = pkr::test::numerical::run_three_body_simulation_si();

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
    EXPECT_LT(result.max_energy_drift, 1e-6) << "Energy conservation violated - numerical instability detected";

    // Check that positions are finite
    EXPECT_TRUE(std::isfinite(result.pos1_final[0]) && std::isfinite(result.pos1_final[1]) && std::isfinite(result.pos1_final[2]));
    EXPECT_TRUE(std::isfinite(result.pos2_final[0]) && std::isfinite(result.pos2_final[1]) && std::isfinite(result.pos2_final[2]));
    EXPECT_TRUE(std::isfinite(result.pos3_final[0]) && std::isfinite(result.pos3_final[1]) && std::isfinite(result.pos3_final[2]));
}

TEST_F(NumericalStabilityTest, ThreeBodyProblem_Measurements) {
    auto result = pkr::test::numerical::run_three_body_simulation_measurements();

    // Report comprehensive results
    std::cout << "\n=== Measurements Results ===\n";
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
    std::cout << "Position uncertainties (AU): (" << result.pos1_uncertainty[0] << ", " << result.pos1_uncertainty[1] << ", " << result.pos1_uncertainty[2] << ") "
              << "(" << result.pos2_uncertainty[0] << ", " << result.pos2_uncertainty[1] << ", " << result.pos2_uncertainty[2] << ") "
              << "(" << result.pos3_uncertainty[0] << ", " << result.pos3_uncertainty[1] << ", " << result.pos3_uncertainty[2] << ")\n";
    std::cout << "Velocity uncertainties (AU/year): (" << result.vel1_uncertainty[0] << ", " << result.vel1_uncertainty[1] << ", " << result.vel1_uncertainty[2] << ") "
              << "(" << result.vel2_uncertainty[0] << ", " << result.vel2_uncertainty[1] << ", " << result.vel2_uncertainty[2] << ") "
              << "(" << result.vel3_uncertainty[0] << ", " << result.vel3_uncertainty[1] << ", " << result.vel3_uncertainty[2] << ")\n";

    // Check that energy drift is reasonable (measurements have uncertainty propagation)
    EXPECT_LT(result.max_energy_drift, 1e-4) << "Energy conservation violated - numerical instability detected";

    // Check that positions are finite and uncertainties are reasonable
    EXPECT_TRUE(std::isfinite(result.pos1_final[0]) && std::isfinite(result.pos1_final[1]) && std::isfinite(result.pos1_final[2]));
    EXPECT_TRUE(std::isfinite(result.pos2_final[0]) && std::isfinite(result.pos2_final[1]) && std::isfinite(result.pos2_final[2]));
    EXPECT_TRUE(std::isfinite(result.pos3_final[0]) && std::isfinite(result.pos3_final[1]) && std::isfinite(result.pos3_final[2]));

    // Check that uncertainties haven't exploded
    EXPECT_LT(result.pos1_uncertainty[0], 1e10);
    EXPECT_LT(result.pos1_uncertainty[1], 1e10);
    EXPECT_LT(result.pos1_uncertainty[2], 1e10);
}

TEST_F(ThreeBodyAccuracyTest, ThreeBodyProblem_MethodComparison) {
    auto comparison = pkr::test::numerical::run_three_body_comparison();

    // Report comprehensive comparison results
    std::cout << "\n=== Method Comparison Results ===\n";
    std::cout << "Plain Doubles - Max energy drift: " << comparison.plain_double.max_energy_drift << "\n";
    std::cout << "SI Units - Max energy drift: " << comparison.si_units.max_energy_drift << "\n";
    std::cout << "Measurements - Max energy drift: " << comparison.measurements.max_energy_drift << "\n";

    std::cout << "\nFinal Positions (AU) - Plain Doubles:\n";
    std::cout << "Body 1: (" << comparison.plain_double.pos1_final[0] << ", " << comparison.plain_double.pos1_final[1] << ", " << comparison.plain_double.pos1_final[2] << ")\n";
    std::cout << "Body 2: (" << comparison.plain_double.pos2_final[0] << ", " << comparison.plain_double.pos2_final[1] << ", " << comparison.plain_double.pos2_final[2] << ")\n";
    std::cout << "Body 3: (" << comparison.plain_double.pos3_final[0] << ", " << comparison.plain_double.pos3_final[1] << ", " << comparison.plain_double.pos3_final[2] << ")\n";

    std::cout << "\nFinal Positions (AU) - SI Units:\n";
    std::cout << "Body 1: (" << comparison.si_units.pos1_final[0] << ", " << comparison.si_units.pos1_final[1] << ", " << comparison.si_units.pos1_final[2] << ")\n";
    std::cout << "Body 2: (" << comparison.si_units.pos2_final[0] << ", " << comparison.si_units.pos2_final[1] << ", " << comparison.si_units.pos2_final[2] << ")\n";
    std::cout << "Body 3: (" << comparison.si_units.pos3_final[0] << ", " << comparison.si_units.pos3_final[1] << ", " << comparison.si_units.pos3_final[2] << ")\n";

    std::cout << "\nFinal Positions (AU) - Measurements:\n";
    std::cout << "Body 1: (" << comparison.measurements.pos1_final[0] << ", " << comparison.measurements.pos1_final[1] << ", " << comparison.measurements.pos1_final[2] << ")\n";
    std::cout << "Body 2: (" << comparison.measurements.pos2_final[0] << ", " << comparison.measurements.pos2_final[1] << ", " << comparison.measurements.pos2_final[2] << ")\n";
    std::cout << "Body 3: (" << comparison.measurements.pos3_final[0] << ", " << comparison.measurements.pos3_final[1] << ", " << comparison.measurements.pos3_final[2] << ")\n";

    std::cout << "\nPosition Differences (SI - Plain Doubles):\n";
    std::cout << "Body 1: (" << comparison.pos1_diff_si[0] << ", " << comparison.pos1_diff_si[1] << ", " << comparison.pos1_diff_si[2] << ")\n";
    std::cout << "Body 2: (" << comparison.pos2_diff_si[0] << ", " << comparison.pos2_diff_si[1] << ", " << comparison.pos2_diff_si[2] << ")\n";
    std::cout << "Body 3: (" << comparison.pos3_diff_si[0] << ", " << comparison.pos3_diff_si[1] << ", " << comparison.pos3_diff_si[2] << ")\n";
    std::cout << "Max position difference: " << comparison.max_pos_diff_si << " AU\n";

    std::cout << "\nPosition Differences (Measurements - Plain Doubles):\n";
    std::cout << "Body 1: (" << comparison.pos1_diff_meas[0] << ", " << comparison.pos1_diff_meas[1] << ", " << comparison.pos1_diff_meas[2] << ")\n";
    std::cout << "Body 2: (" << comparison.pos2_diff_meas[0] << ", " << comparison.pos2_diff_meas[1] << ", " << comparison.pos2_diff_meas[2] << ")\n";
    std::cout << "Body 3: (" << comparison.pos3_diff_meas[0] << ", " << comparison.pos3_diff_meas[1] << ", " << comparison.pos3_diff_meas[2] << ")\n";
    std::cout << "Max position difference: " << comparison.max_pos_diff_meas << " AU\n";

    // Validate that all methods produce very similar results
    EXPECT_LT(comparison.max_pos_diff_si, 1e-10) << "SI units results differ too much from plain doubles";
    EXPECT_LT(comparison.max_vel_diff_si, 1e-10) << "SI units velocity results differ too much from plain doubles";

    // Measurements should be close but may have some differences due to uncertainty propagation and fewer steps
    EXPECT_LT(comparison.max_pos_diff_meas, 1e-6) << "Measurement results differ too much from plain doubles";
    EXPECT_LT(comparison.max_vel_diff_meas, 1e-6) << "Measurement velocity results differ too much from plain doubles";

    // Energy conservation should be similar across methods
    EXPECT_LT(std::abs(comparison.plain_double.max_energy_drift - comparison.si_units.max_energy_drift), 1e-12)
        << "Energy conservation differs between plain doubles and SI units";
}

} // namespace test