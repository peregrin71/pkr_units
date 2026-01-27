#include <gtest/gtest.h>
#include <pkr_units/si_units.h>

namespace test
{

using namespace ::testing;

class DimensionalAnalysisTest : public Test
{
};

// ============================================================================
// Basic Dimensional Analysis: Velocity * Time = Distance
// ============================================================================

TEST_F(DimensionalAnalysisTest, velocity_times_time_equals_distance)
{
    // km/h * h = km
    pkr::units::kilometer_per_hour_t speed{100.0}; // 100 km/h
    pkr::units::hour_t time{2.0};                  // 2 hours

    auto distance = speed * time; // Should be kilometers
    ASSERT_DOUBLE_EQ(distance.value(), 200.0);

    // Verify the result has length dimension [L] and no time dimension [T]
    using result_dimension = decltype(distance)::dimension;
    static_assert(result_dimension::value.length == 1, "Distance should have length dimension");
    static_assert(result_dimension::value.time == 0, "Distance should have no time dimension");
}

TEST_F(DimensionalAnalysisTest, meter_per_second_times_second_equals_meter)
{
    // m/s * s = m
    pkr::units::meter_per_second_t speed{10.0}; // 10 m/s
    pkr::units::second_t time{5.0};             // 5 seconds

    auto distance = speed * time; // Should be meters
    ASSERT_DOUBLE_EQ(distance.value(), 50.0);

    // Verify dimensions
    using result_dimension = decltype(distance)::dimension;
    static_assert(result_dimension::value.length == 1, "Distance should have length dimension");
    static_assert(result_dimension::value.time == 0, "Distance should have no time dimension");
}

// ============================================================================
// Acceleration Dimensional Analysis: Acceleration * Time = Velocity
// ============================================================================

TEST_F(DimensionalAnalysisTest, acceleration_times_time_equals_velocity)
{
    // m/s² * s = m/s
    pkr::units::meter_per_second_squared_t accel{9.8}; // 9.8 m/s²
    pkr::units::second_t time{2.0};                    // 2 seconds

    auto velocity = accel * time; // Should be m/s
    ASSERT_DOUBLE_EQ(velocity.value(), 19.6);

    // Verify dimensions: [L]/[T] (velocity)
    using result_dimension = decltype(velocity)::dimension;
    static_assert(result_dimension::value.length == 1, "Velocity should have length dimension");
    static_assert(result_dimension::value.time == -1, "Velocity should have negative time dimension");
}

TEST_F(DimensionalAnalysisTest, acceleration_times_time_squared_equals_distance)
{
    // m/s² * s² = m
    pkr::units::meter_per_second_squared_t accel{9.8};                         // 9.8 m/s²
    auto time_squared = pkr::units::second_t{2.0} * pkr::units::second_t{2.0}; // 4 s²

    auto distance = accel * time_squared; // Should be meters
    ASSERT_DOUBLE_EQ(distance.value(), 39.2);

    // Verify dimensions: [L] (distance)
    using result_dimension = decltype(distance)::dimension;
    static_assert(result_dimension::value.length == 1, "Distance should have length dimension");
    static_assert(result_dimension::value.time == 0, "Distance should have no time dimension");
}

// ============================================================================
// Force Dimensional Analysis: Force = Mass * Acceleration
// ============================================================================

TEST_F(DimensionalAnalysisTest, mass_times_acceleration_equals_force)
{
    // kg * m/s² = N (Newton)
    pkr::units::kilogram_t mass{5.0};                  // 5 kg
    pkr::units::meter_per_second_squared_t accel{9.8}; // 9.8 m/s²

    auto force = mass * accel; // Should be Newtons
    ASSERT_DOUBLE_EQ(force.value(), 49.0);

    // Verify dimensions: [M][L]/[T]² (force)
    using result_dimension = decltype(force)::dimension;
    static_assert(result_dimension::value.mass == 1, "Force should have mass dimension");
    static_assert(result_dimension::value.length == 1, "Force should have length dimension");
    static_assert(result_dimension::value.time == -2, "Force should have negative squared time dimension");
}

TEST_F(DimensionalAnalysisTest, force_times_distance_equals_energy)
{
    // N * m = J (Joule)
    pkr::units::newton_t force{10.0};  // 10 N
    pkr::units::meter_t distance{5.0}; // 5 m

    auto energy = force * distance; // Should be Joules
    ASSERT_DOUBLE_EQ(energy.value(), 50.0);

    // Verify dimensions: [M][L]²/[T]² (energy)
    using result_dimension = decltype(energy)::dimension;
    static_assert(result_dimension::value.mass == 1, "Energy should have mass dimension");
    static_assert(result_dimension::value.length == 2, "Energy should have squared length dimension");
    static_assert(result_dimension::value.time == -2, "Energy should have negative squared time dimension");
}

// ============================================================================
// Power Dimensional Analysis: Power = Energy / Time
// ============================================================================

TEST_F(DimensionalAnalysisTest, energy_divided_by_time_equals_power)
{
    // J / s = W (Watt)
    pkr::units::joule_t energy{100.0}; // 100 J
    pkr::units::second_t time{10.0};   // 10 s

    auto power = energy / time; // Should be Watts
    ASSERT_DOUBLE_EQ(power.value(), 10.0);

    // Verify dimensions: [M][L]²/[T]³ (power)
    using result_dimension = decltype(power)::dimension;
    static_assert(result_dimension::value.mass == 1, "Power should have mass dimension");
    static_assert(result_dimension::value.length == 2, "Power should have squared length dimension");
    static_assert(result_dimension::value.time == -3, "Power should have negative cubed time dimension");
}

TEST_F(DimensionalAnalysisTest, power_times_time_equals_energy)
{
    // W * s = J (Joule)
    pkr::units::watt_t power{50.0};  // 50 W
    pkr::units::second_t time{20.0}; // 20 s

    auto energy = power * time; // Should be Joules
    ASSERT_DOUBLE_EQ(energy.value(), 1000.0);

    // Verify dimensions: [M][L]²/[T]² (energy)
    using result_dimension = decltype(energy)::dimension;
    static_assert(result_dimension::value.mass == 1, "Energy should have mass dimension");
    static_assert(result_dimension::value.length == 2, "Energy should have squared length dimension");
    static_assert(result_dimension::value.time == -2, "Energy should have negative squared time dimension");
}

// ============================================================================
// Pressure Dimensional Analysis: Pressure * Area = Force
// ============================================================================

TEST_F(DimensionalAnalysisTest, pressure_times_area_equals_force)
{
    // Pa * m² = N (Newton)
    pkr::units::pascal_t pressure{1000.0};                           // 1000 Pa
    auto area = pkr::units::meter_t{2.0} * pkr::units::meter_t{2.0}; // 4 m²

    auto force = pressure * area; // Should be Newtons
    ASSERT_DOUBLE_EQ(force.value(), 4000.0);

    // Verify dimensions: [M]/[L][T]² (pressure) * [L]² = [M][L]/[T]² (force)
    using result_dimension = decltype(force)::dimension;
    static_assert(result_dimension::value.mass == 1, "Force should have mass dimension");
    static_assert(result_dimension::value.length == 1, "Force should have length dimension");
    static_assert(result_dimension::value.time == -2, "Force should have negative squared time dimension");
}

// ============================================================================
// Complex Dimensional Analysis: Pressure * Time² = Energy Density
// ============================================================================

TEST_F(DimensionalAnalysisTest, pressure_times_time_squared)
{
    // Pa * s² = (N/m²) * s² = (kg·m/s²/m²) * s² = kg/(m·s²) * s² = kg/m
    // This represents energy density (energy per unit volume)
    pkr::units::pascal_t pressure{1000.0};                                     // 1000 Pa = 1000 N/m²
    auto time_squared = pkr::units::second_t{2.0} * pkr::units::second_t{2.0}; // 4 s²

    auto energy_density = pressure * time_squared; // Should be kg/m (energy density)
    ASSERT_DOUBLE_EQ(energy_density.value(), 4000.0);

    static_assert(
        std::is_same_v<
            decltype(energy_density.normalized()),
            pkr::units::details::unit_t<
                double,
                std::ratio<1, 1>,
                pkr::units::dimension_t{.length = -1, .mass = 1, .time = 0, .current = 0, .temperature = 0, .amount = 0, .intensity = 0, .angle = 0}>>,
        "Resulting type should be kg/m");

    // Verify dimensions: [M]/[L][T]² * [T]² = [M]/[L] (mass per length = energy density)
    using result_dimension = decltype(energy_density)::dimension;
    static_assert(result_dimension::value.mass == 1, "Energy density should have mass dimension");
    static_assert(result_dimension::value.length == -1, "Energy density should have negative length dimension");
    static_assert(result_dimension::value.time == 0, "Energy density should have no time dimension");
}

// ============================================================================
// Chain Dimensional Analysis: Distance from Acceleration
// ============================================================================

TEST_F(DimensionalAnalysisTest, distance_from_acceleration_kinematic_equation)
{
    // Distance = (1/2) * acceleration * time²
    pkr::units::meter_per_second_squared_t accel{2.0};                         // 2 m/s²
    auto time_squared = pkr::units::second_t{3.0} * pkr::units::second_t{3.0}; // 9 s²

    auto distance = 0.5 * accel * time_squared; // Should be meters
    ASSERT_DOUBLE_EQ(distance.value(), 9.0);    // (0.5) * 2 * 9 = 9 meters

    // Verify dimensions: [L] (distance)
    using result_dimension = decltype(distance)::dimension;
    static_assert(result_dimension::value.length == 1, "Distance should have length dimension");
    static_assert(result_dimension::value.time == 0, "Distance should have no time dimension");
}

// ============================================================================
// Work-Energy Theorem: Work = Force * Distance = Energy
// ============================================================================

TEST_F(DimensionalAnalysisTest, work_energy_theorem)
{
    // Simple test: Work = Force * Distance
    pkr::units::newton_t force{10.0};  // 10 N
    pkr::units::meter_t distance{5.0}; // 5 m

    auto work = force * distance; // Should be joules
    ASSERT_DOUBLE_EQ(work.value(), 50.0);

    // Should have energy dimensions: [M][L]²/[T]²
    using result_dimension = decltype(work)::dimension;
    static_assert(result_dimension::value.mass == 1, "Energy should have mass dimension");
    static_assert(result_dimension::value.length == 2, "Energy should have squared length dimension");
    static_assert(result_dimension::value.time == -2, "Energy should have negative squared time dimension");
}

} // namespace test