#include <cmath>
#include <gtest/gtest.h>
#include <pkr_units/measurements/measurement_rss_4d.h>
#include <pkr_units/measurements/decl/measurement_rss_decl.h>
#include <pkr_units/si_units.h>

namespace test
{

using namespace ::testing;

class RK4CalculationPatternsTest : public ::testing::Test
{
};

// Test 1: Multi-stage derivative combination
TEST_F(RK4CalculationPatternsTest, MultiStageDerivativeCombination)
{
    using meters_per_sec = pkr::units::measurement_rss_t<pkr::units::meter_per_second_t>;
    auto k1 = meters_per_sec{1.0, 0.0};
    auto k2 = meters_per_sec{1.05, 0.0};
    auto k3 = meters_per_sec{1.05, 0.0};
    auto k4 = meters_per_sec{1.1, 0.0};

    // Standard RK4 combination
    auto combined = k1 + 2.0 * k2 + 2.0 * k3 + k4;
    auto result = combined / 6.0;

    EXPECT_DOUBLE_EQ(result.value(), (1.0 + 2.1 + 2.1 + 1.1) / 6.0);
}

// Test 2: Velocity update
TEST_F(RK4CalculationPatternsTest, VelocityUpdate)
{
    auto v_old = pkr::units::measurement_rss_t<pkr::units::meter_per_second_t>{1.0, 0.05};
    auto dv = pkr::units::measurement_rss_t<pkr::units::meter_per_second_t>{0.1, 0.01}; // Change in velocity

    auto v_new = v_old + dv;

    EXPECT_DOUBLE_EQ(v_new.value(), 1.1);
    EXPECT_GT(v_new.uncertainty(), v_old.uncertainty());
}

// Test 3: Position with vector operations
TEST_F(RK4CalculationPatternsTest, VectorPositionOperations)
{
    auto v1 = pkr::units::vec_measurement_rss_4d_t<pkr::units::meter_t>{{1.0, 0.1}, {2.0, 0.1}, {3.0, 0.1}};
    auto v2 = pkr::units::vec_measurement_rss_4d_t<pkr::units::meter_t>{{0.5, 0.05}, {0.5, 0.05}, {0.5, 0.05}};

    auto result = v1 + v2;

    EXPECT_DOUBLE_EQ(result.x.value(), 1.5);
    EXPECT_DOUBLE_EQ(result.y.value(), 2.5);
    EXPECT_DOUBLE_EQ(result.z.value(), 3.5);
}

// Test 4: Distance magnitude calculation
TEST_F(RK4CalculationPatternsTest, DistanceMagnitude)
{
    using vec_meas = pkr::units::vec_measurement_rss_4d_t<pkr::units::meter_t>;
    using meter_meas = pkr::units::measurement_rss_t<pkr::units::meter_t>;

    auto pos1 = vec_meas{meter_meas{0.0, 0.01}, meter_meas{0.0, 0.01}, meter_meas{0.0, 0.01}};
    auto pos2 = vec_meas{meter_meas{3.0, 0.05}, meter_meas{4.0, 0.05}, meter_meas{0.0, 0.01}};

    auto displacement = pos2 - pos1;
    auto distance = displacement.magnitude();

    EXPECT_DOUBLE_EQ(distance.value(), 5.0);
    EXPECT_GT(distance.uncertainty(), 0.0);
}

// Test 5: Scaled vector addition (like combining RK4 stages with weights)
TEST_F(RK4CalculationPatternsTest, WeightedVectorCombination)
{
    auto k1 = pkr::units::vec_measurement_rss_4d_t<pkr::units::meter_t>{{1.0, 0.1}, {2.0, 0.1}, {3.0, 0.1}};
    auto k2 = pkr::units::vec_measurement_rss_4d_t<pkr::units::meter_t>{{1.1, 0.1}, {2.1, 0.1}, {3.1, 0.1}};
    auto k3 = pkr::units::vec_measurement_rss_4d_t<pkr::units::meter_t>{{1.05, 0.1}, {2.05, 0.1}, {3.05, 0.1}};

    // RK4-style weighting: (k1 + 2*k2 + 2*k3) / 6 (without k4)
    auto weighted = (1.0 * k1 + 2.0 * k2 + 2.0 * k3) * (1.0 / 6.0);

    // Expected: ((1.0 + 2*1.1 + 2*1.05) / 6, ...)
    double expected_x = (1.0 + 2.2 + 2.1) / 6.0; // 5.3 / 6 ≈ 0.883...
    EXPECT_DOUBLE_EQ(weighted.x.value(), expected_x);

    // All components should have uncertainty
    EXPECT_GT(weighted.x.uncertainty(), 0.0);
    EXPECT_GT(weighted.y.uncertainty(), 0.0);
    EXPECT_GT(weighted.z.uncertainty(), 0.0);
}

// // Test 7: Error propagation through intermediate calculations
TEST_F(RK4CalculationPatternsTest, ErrorPropagationThroughCalculations)
{
    // Simulate calculation like: force = G * m1 * m2 / r², with uncertainties
    auto r = pkr::units::measurement_rss_t<pkr::units::meter_t>{1000.0, 10.0}; // Distance with 1% uncertainty

    // r² calculation (distance squared)
    auto r_squared = pkr::units::square_rss(r);

    // Basic check: if r = 1000 m, then r² = 1,000,000 m²
    EXPECT_DOUBLE_EQ(r_squared.value(), 1000000.0);

    // Uncertainty should increase through multiplication
    EXPECT_GT(r_squared.uncertainty(), r.uncertainty());
}

// Test 8: Vector magnitude with accumulated errors from multiple sources
TEST_F(RK4CalculationPatternsTest, MagnitudeWithAccumulatedErrors)
{
    // Components with different error sources
    pkr::units::vec_measurement_rss_4d_t<pkr::units::meter_t> v{
        {1.0, 0.10},  // 10% uncertainty
        {1.0, 0.05},  // 5% uncertainty
        {1.0, 0.02}}; // 2% uncertainty

    // Magnitude = sqrt(1² + 1² + 1²) = sqrt(3) ≈ 1.732
    auto mag = v.magnitude();

    EXPECT_DOUBLE_EQ(mag.value(), std::sqrt(3.0));

    // Uncertainty should be present due to component uncertainties
    EXPECT_GT(mag.uncertainty(), 0.0);

    // Uncertainty should be dominated by the largest component uncertainty
    EXPECT_LT(mag.uncertainty(), 0.15); // But less than largest individual uncertainty
}

// Test 9: Cumulative error in time stepping (repeated updates)
TEST_F(RK4CalculationPatternsTest, CumulativeErrorInTimeStepping)
{
    // Simulate multiple time steps, each with uncertainty, accumulating
    auto position = pkr::units::measurement_rss_t<pkr::units::meter_t>{0.0, 0.0};   // Start at origin
    auto step_size = pkr::units::measurement_rss_t<pkr::units::meter_t>{1.0, 0.05}; // Each step: 1 ± 0.05 m

    // Perform 5 time steps
    for (int i = 0; i < 5; ++i)
    {
        position = position + step_size;
    }

    // Position should be 5 m, but uncertainty should accumulate
    EXPECT_DOUBLE_EQ(position.value(), 5.0);

    // After 5 additions, uncertainty should be accumulated through RSS
    EXPECT_GT(position.uncertainty(), 0.1);
}

// Test 10: Calculation pattern for force magnitude (from position difference)
TEST_F(RK4CalculationPatternsTest, ForceMagnitudePattern)
{
    // Two bodies separated in 3D space
    auto body1_pos = pkr::units::vec_measurement_rss_4d_t<pkr::units::meter_t>{{0.0, 0.01}, {0.0, 0.01}, {0.0, 0.01}};
    auto body2_pos = pkr::units::vec_measurement_rss_4d_t<pkr::units::meter_t>{{6.0, 0.1}, {8.0, 0.1}, {0.0, 0.01}};

    // Calculate separation vector
    auto separation = body2_pos - body1_pos;

    // Calculate distance for force magnitude calculation
    auto distance = separation.magnitude();

    // For 6-8-0 triangle: distance = 10 m
    EXPECT_DOUBLE_EQ(distance.value(), 10.0);

    // Simulate force magnitude: F ∝ 1/r²
    auto distance_sq = pkr::units::square_rss(distance);

    // distance_sq should be 100 m²
    EXPECT_DOUBLE_EQ(distance_sq.value(), 100.0);
}
} // namespace test
