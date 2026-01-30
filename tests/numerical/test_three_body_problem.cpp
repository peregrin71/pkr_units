#include <gtest/gtest.h>
#include <pkr_units/si_units.h>
#include <pkr_units/astronomical_units.h>
#include <pkr_units/measurements/measurement.h>
#include <pkr_units/math/measurement_math_rss.h>
#include <vector>
#include <cmath>
#include <iostream>

#include "three_body_helpers.h"
#include "vector_math_double.h"
#include <pkr_units/math/unit_math_4d.h>
#include "rk4_steppers_double.h"
#include "rk4_steppers_units.h"
#include "rk4_steppers_measurements.h"

namespace test
{

using namespace ::testing;

class NumericalStabilityTest : public Test
{
};

// ============================================================================
// 3-Body Problem Tests
// ============================================================================

TEST_F(NumericalStabilityTest, ThreeBodyProblem_PlainDoubles) {
    auto state = pkr::test::numerical::initial_state_double;
    double dt = 0.01; // Small time step
    int steps = 1000; // Simulate for 10 years

    double initial_energy = pkr::test::numerical::compute_total_energy_double(state);
    double max_energy_drift = 0.0;

    for (int i = 0; i < steps; ++i) {
        state = pkr::test::numerical::rk4_step_double(state, dt);
        double current_energy = pkr::test::numerical::compute_total_energy_double(state);
        double energy_drift = std::abs((current_energy - initial_energy) / initial_energy);
        max_energy_drift = std::max(max_energy_drift, energy_drift);
    }

    // Check that energy drift is small (numerical stability)
    EXPECT_LT(max_energy_drift, 1e-6) << "Energy conservation violated - numerical instability detected";

    // Check that positions are reasonable (not NaN or infinite)
    EXPECT_TRUE(std::isfinite(state.x1) && std::isfinite(state.y1) && std::isfinite(state.z1));
    EXPECT_TRUE(std::isfinite(state.x2) && std::isfinite(state.y2) && std::isfinite(state.z2));
    EXPECT_TRUE(std::isfinite(state.x3) && std::isfinite(state.y3) && std::isfinite(state.z3));
}

TEST_F(NumericalStabilityTest, ThreeBodyProblem_SIUnits) {
    auto state = pkr::test::numerical::initial_state_si;
    auto dt = 0.01 * pkr::units::year_t(1.0); // Small time step in years
    int steps = 1000;

    auto initial_energy = pkr::test::numerical::compute_total_energy_si(state);
    double max_energy_drift = 0.0;

    for (int i = 0; i < steps; ++i) {
        state = pkr::test::numerical::rk4_step_si(state, dt);
        auto current_energy = pkr::test::numerical::compute_total_energy_si(state);
        double energy_drift = std::abs((current_energy.value() - initial_energy.value()) / initial_energy.value());
        max_energy_drift = std::max(max_energy_drift, energy_drift);
    }

    // Check that energy drift is small (numerical stability)
    EXPECT_LT(max_energy_drift, 1e-6) << "Energy conservation violated - numerical instability detected";

    // Check that positions are finite
    EXPECT_TRUE(std::isfinite(state.x1.value()) && std::isfinite(state.y1.value()) && std::isfinite(state.z1.value()));
    EXPECT_TRUE(std::isfinite(state.x2.value()) && std::isfinite(state.y2.value()) && std::isfinite(state.z2.value()));
    EXPECT_TRUE(std::isfinite(state.x3.value()) && std::isfinite(state.y3.value()) && std::isfinite(state.z3.value()));
}

TEST_F(NumericalStabilityTest, ThreeBodyProblem_Measurements) {
    auto state = pkr::test::numerical::initial_state_meas;
    auto dt = pkr::measurement_t<pkr::units::year_t>{0.01 * pkr::units::year_t(1.0), 1e-6 * pkr::units::year_t(1.0)};
    int steps = 100;

    auto initial_energy = pkr::test::numerical::compute_total_energy_meas(state);
    double max_energy_drift = 0.0;

    // Run fewer steps due to complexity of measurement calculations
    for (int i = 0; i < steps; ++i) {
        state = pkr::test::numerical::rk4_step_meas(state, dt);
        auto current_energy = pkr::test::numerical::compute_total_energy_meas(state);
        double energy_drift = std::abs((current_energy.value().value() - initial_energy.value().value()) / initial_energy.value().value());
        max_energy_drift = std::max(max_energy_drift, energy_drift);
    }

    // Check that energy drift is reasonable (measurements have uncertainty propagation)
    EXPECT_LT(max_energy_drift, 1e-4) << "Energy conservation violated - numerical instability detected";

    // Check that positions are finite and uncertainties are reasonable
    EXPECT_TRUE(std::isfinite(state.x1.value().value()) && std::isfinite(state.y1.value().value()) && std::isfinite(state.z1.value().value()));
    EXPECT_TRUE(std::isfinite(state.x2.value().value()) && std::isfinite(state.y2.value().value()) && std::isfinite(state.z2.value().value()));
    EXPECT_TRUE(std::isfinite(state.x3.value().value()) && std::isfinite(state.y3.value().value()) && std::isfinite(state.z3.value().value()));

    // Check that uncertainties haven't exploded
    EXPECT_LT(state.x1.uncertainty().value(), 1e10);
    EXPECT_LT(state.y1.uncertainty().value(), 1e10);
    EXPECT_LT(state.z1.uncertainty().value(), 1e10);
}

} // namespace test