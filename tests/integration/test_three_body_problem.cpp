#include "three_body_simulation/double_body.h"
#include "three_body_simulation/units_body.h"
#include "three_body_simulation/measurements_body.h"
#include <gtest/gtest.h>
#include <cmath>

class ThreeBodySimulationTest : public ::testing::Test
{
protected:
    // Initial conditions: three bodies in a stable configuration
    // Sun-like body at origin, two equal bodies in orbit

    void SetUp() override
    {
        double_bodies.clear();
        units_bodies.clear();
        measurements_bodies.clear();

        // Create initial conditions for all three implementations
        setup_double_system();
        setup_units_system();
        setup_measurements_system();
    }

    void setup_double_system()
    {
        using namespace three_body_double;

        // Realistic astronomical system: Sun-Jupiter-Ganymede
        // Sun mass: 1.989e30 kg
        // Jupiter mass: 1.898e27 kg
        // Ganymede (largest moon of Jupiter) mass: 1.4819e23 kg
        // Jupiter-Sun distance: 778.5e6 km (5.2 AU)
        // Ganymede-Jupiter distance: 1,070,400 km
        // Jupiter orbital velocity: ~13.07 km/s
        // Ganymede orbital velocity around Jupiter: ~10.88 km/s

        // Body 1: Sun (at origin, stationary)
        double_bodies.push_back(Body(
            make_position(0.0, 0.0, 0.0),
            make_direction(0.0, 0.0, 0.0),
            1.989e30 // Sun mass in kg
            ));

        // Body 2: Jupiter (5.2 AU away, orbital velocity ~13.07 km/s)
        double_bodies.push_back(Body(
            make_position(778.5e6, 0.0, 0.0), // 5.2 AU in km
            make_direction(0.0, 13.07, 0.0),  // ~13.07 km/s tangential velocity
            1.898e27                          // Jupiter mass in kg
            ));

        // Body 3: Ganymede (orbiting Jupiter, which orbits Sun)
        // Ganymede positioned perpendicular to Sun-Jupiter line
        double_bodies.push_back(Body(
            make_position(778.5e6, 1.070400e6, 0.0), // Jupiter position + Ganymede's orbital distance
            make_direction(0.0, 13.07 + 10.88, 0.0), // Jupiter velocity + Ganymede's orbital velocity
            1.4819e23                                // Ganymede mass in kg
            ));

        double_system = std::make_unique<three_body_double::ThreeBodySystem>(double_bodies);
        double_initial_energy = double_system->total_energy();
    }

    void setup_units_system()
    {
        using namespace three_body_units;

        // Realistic astronomical system: Sun-Jupiter-Ganymede
        // Body 1: Sun (at origin, stationary)
        units_bodies.push_back(Body(
            make_position(0.0, 0.0, 0.0),
            make_direction(0.0, 0.0, 0.0),
            1.989e30 // Sun mass in kg
            ));

        // Body 2: Jupiter (5.2 AU away, orbital velocity ~13.07 km/s)
        units_bodies.push_back(Body(
            make_position(778.5e6, 0.0, 0.0), // 5.2 AU in km
            make_direction(0.0, 13.07, 0.0),  // ~13.07 km/s tangential velocity
            1.898e27                          // Jupiter mass in kg
            ));

        // Body 3: Ganymede (orbiting Jupiter, which orbits Sun)
        units_bodies.push_back(Body(
            make_position(778.5e6, 1.070400e6, 0.0), // Jupiter + Ganymede's orbital distance
            make_direction(0.0, 13.07 + 10.88, 0.0), // Jupiter velocity + Ganymede's orbital velocity
            1.4819e23                                // Ganymede mass in kg
            ));

        units_system = std::make_unique<three_body_units::ThreeBodySystem>(units_bodies);
        units_initial_energy = units_system->total_energy();
    }

    void setup_measurements_system()
    {
        using namespace three_body_measurements;

        // Realistic astronomical system: Sun-Jupiter-Ganymede
        // Body 1: Sun (at origin, stationary)
        measurements_bodies.push_back(Body(
            make_position(0.0, 0.0, 0.0),
            make_direction(0.0, 0.0, 0.0),
            1.989e30 // Sun mass in kg
            ));

        // Body 2: Jupiter (5.2 AU away, orbital velocity ~13.07 km/s)
        measurements_bodies.push_back(Body(
            make_position(778.5e6, 0.0, 0.0), // 5.2 AU in km
            make_direction(0.0, 13.07, 0.0),  // ~13.07 km/s tangential velocity
            1.898e27                          // Jupiter mass in kg
            ));

        // Body 3: Ganymede (orbiting Jupiter, which orbits Sun)
        measurements_bodies.push_back(Body(
            make_position(778.5e6, 1.070400e6, 0.0), // Jupiter + Ganymede's orbital distance
            make_direction(0.0, 13.07 + 10.88, 0.0), // Jupiter velocity + Ganymede's orbital velocity
            1.4819e23                                // Ganymede mass in kg
            ));

        measurements_system = std::make_unique<three_body_measurements::ThreeBodySystem>(measurements_bodies);
        measurements_initial_energy = measurements_system->total_energy();
    }

    std::vector<three_body_double::Body> double_bodies;
    std::unique_ptr<three_body_double::ThreeBodySystem> double_system;
    double double_initial_energy;

    std::vector<three_body_units::Body> units_bodies;
    std::unique_ptr<three_body_units::ThreeBodySystem> units_system;
    double units_initial_energy;

    std::vector<three_body_measurements::Body> measurements_bodies;
    std::unique_ptr<three_body_measurements::ThreeBodySystem> measurements_system;
    double measurements_initial_energy;
};

TEST_F(ThreeBodySimulationTest, three_body_simulation_convergence)
{
    using namespace three_body_double;
    using namespace three_body_units;
    using namespace three_body_measurements;

    const int num_steps = 10000;
    const double dt = 0.001;

    // Lambda to extract positions from double system
    auto get_double_positions = [](const auto& system)
    {
        const auto& bodies = system.get_bodies();
        std::vector<std::array<double, 3>> positions;
        for (const auto& body : bodies)
        {
            positions.push_back(std::array<double, 3>{{body.position.x, body.position.y, body.position.z}});
        }
        return positions;
    };

    // Lambda to extract positions from units system
    auto get_units_positions = [](const auto& system)
    {
        const auto& bodies = system.get_bodies();
        std::vector<std::array<double, 3>> positions;
        for (const auto& body : bodies)
        {
            positions.push_back(std::array<double, 3>{{body.position.x.value(), body.position.y.value(), body.position.z.value()}});
        }
        return positions;
    };

    // Lambda to extract positions from measurements system
    auto get_measurements_positions = [](const auto& system)
    {
        const auto& bodies = system.get_bodies();
        std::vector<std::array<double, 3>> positions;
        for (const auto& body : bodies)
        {
            positions.push_back(std::array<double, 3>{{body.position.x.value(), body.position.y.value(), body.position.z.value()}});
        }
        return positions;
    };

    // Run simulation for all three implementations
    for (int step = 0; step < num_steps; ++step)
    {
        double_system->rk4_step(dt);
        units_system->rk4_step(dt);
        measurements_system->rk4_step(dt);

        // Periodically check energy conservation and position divergence
        if (step % 100 == 0)
        {
            double double_energy = double_system->total_energy();
            double units_energy = units_system->total_energy();
            double measurements_energy = measurements_system->total_energy();

            // Energy should change by less than 1% over the simulation
            double double_energy_deviation = std::abs(double_energy - double_initial_energy) / std::abs(double_initial_energy);
            double units_energy_deviation = std::abs(units_energy - units_initial_energy) / std::abs(units_initial_energy);
            double measurements_energy_deviation = std::abs(measurements_energy - measurements_initial_energy) / std::abs(measurements_initial_energy);

            EXPECT_LT(double_energy_deviation, 0.01) << "Double precision energy drift at step " << step;
            EXPECT_LT(units_energy_deviation, 0.01) << "Units energy drift at step " << step;
            EXPECT_LT(measurements_energy_deviation, 0.02) << "Measurements energy drift at step " << step;

            // Check position convergence between implementations
            auto double_pos = get_double_positions(*double_system);
            auto units_pos = get_units_positions(*units_system);
            auto measurements_pos = get_measurements_positions(*measurements_system);

            for (size_t i = 0; i < double_pos.size(); ++i)
            {
                // Maximum allowed position divergence: 1% of initial separation or 1e5 km
                double max_divergence = 1e5;

                double dist_double_units = std::sqrt(
                    (double_pos[i][0] - units_pos[i][0]) * (double_pos[i][0] - units_pos[i][0]) +
                    (double_pos[i][1] - units_pos[i][1]) * (double_pos[i][1] - units_pos[i][1]) +
                    (double_pos[i][2] - units_pos[i][2]) * (double_pos[i][2] - units_pos[i][2]));

                double dist_double_measurements = std::sqrt(
                    (double_pos[i][0] - measurements_pos[i][0]) * (double_pos[i][0] - measurements_pos[i][0]) +
                    (double_pos[i][1] - measurements_pos[i][1]) * (double_pos[i][1] - measurements_pos[i][1]) +
                    (double_pos[i][2] - measurements_pos[i][2]) * (double_pos[i][2] - measurements_pos[i][2]));

                EXPECT_LT(dist_double_units, max_divergence)
                    << "Body " << i << " position divergence (double vs units) at step " << step << ": " << dist_double_units << " km";
                EXPECT_LT(dist_double_measurements, max_divergence)
                    << "Body " << i << " position divergence (double vs measurements) at step " << step << ": " << dist_double_measurements << " km";
            }
        }
    }

    // Final energy conservation check
    double double_final = double_system->total_energy();
    double units_final = units_system->total_energy();
    double measurements_final = measurements_system->total_energy();

    double double_deviation = std::abs(double_final - double_initial_energy) / std::abs(double_initial_energy);
    double units_deviation = std::abs(units_final - units_initial_energy) / std::abs(units_initial_energy);
    double measurements_deviation = std::abs(measurements_final - measurements_initial_energy) / std::abs(measurements_initial_energy);

    EXPECT_LT(double_deviation, 0.01) << "Final double precision energy deviation";
    EXPECT_LT(units_deviation, 0.01) << "Final units energy deviation";
    EXPECT_LT(measurements_deviation, 0.02) << "Final measurements energy deviation";

    // Final position convergence check
    auto final_double_pos = get_double_positions(*double_system);
    auto final_units_pos = get_units_positions(*units_system);
    auto final_measurements_pos = get_measurements_positions(*measurements_system);

    for (size_t i = 0; i < final_double_pos.size(); ++i)
    {
        double max_final_divergence = 1e5; // 100,000 km tolerance

        double final_dist_double_units = std::sqrt(
            (final_double_pos[i][0] - final_units_pos[i][0]) * (final_double_pos[i][0] - final_units_pos[i][0]) +
            (final_double_pos[i][1] - final_units_pos[i][1]) * (final_double_pos[i][1] - final_units_pos[i][1]) +
            (final_double_pos[i][2] - final_units_pos[i][2]) * (final_double_pos[i][2] - final_units_pos[i][2]));

        double final_dist_double_measurements = std::sqrt(
            (final_double_pos[i][0] - final_measurements_pos[i][0]) * (final_double_pos[i][0] - final_measurements_pos[i][0]) +
            (final_double_pos[i][1] - final_measurements_pos[i][1]) * (final_double_pos[i][1] - final_measurements_pos[i][1]) +
            (final_double_pos[i][2] - final_measurements_pos[i][2]) * (final_double_pos[i][2] - final_measurements_pos[i][2]));

        EXPECT_LT(final_dist_double_units, max_final_divergence)
            << "Final body " << i << " position divergence (double vs units): " << final_dist_double_units << " km";
        EXPECT_LT(final_dist_double_measurements, max_final_divergence)
            << "Final body " << i << " position divergence (double vs measurements): " << final_dist_double_measurements << " km";
    }
}

TEST_F(ThreeBodySimulationTest, three_body_numerical_stability_comparison)
{
    using namespace three_body_double;
    using namespace three_body_units;
    using namespace three_body_measurements;

    const int num_steps = 100;
    const double dt = 0.001;

    // Store initial positions for all three systems
    auto get_double_positions = [](const auto& system)
    {
        const auto& bodies = system.get_bodies();
        std::vector<std::tuple<double, double, double>> positions;
        for (const auto& body : bodies)
        {
            positions.push_back(std::make_tuple(body.position.x, body.position.y, body.position.z));
        }
        return positions;
    };

    auto get_units_positions = [](const auto& system)
    {
        const auto& bodies = system.get_bodies();
        std::vector<std::tuple<double, double, double>> positions;
        for (const auto& body : bodies)
        {
            positions.push_back(std::make_tuple(body.position.x.value(), body.position.y.value(), body.position.z.value()));
        }
        return positions;
    };

    auto get_measurements_positions = [](const auto& system)
    {
        const auto& bodies = system.get_bodies();
        std::vector<std::tuple<double, double, double>> positions;
        for (const auto& body : bodies)
        {
            positions.push_back(std::make_tuple(body.position.x.value(), body.position.y.value(), body.position.z.value()));
        }
        return positions;
    };

    auto initial_double = get_double_positions(*double_system);
    auto initial_units = get_units_positions(*units_system);
    auto initial_measurements = get_measurements_positions(*measurements_system);

    // Run all three simulations in parallel
    for (int step = 0; step < num_steps; ++step)
    {
        double_system->rk4_step(dt);
        units_system->rk4_step(dt);
        measurements_system->rk4_step(dt);
    }

    auto final_double = get_double_positions(*double_system);
    auto final_units = get_units_positions(*units_system);
    auto final_measurements = get_measurements_positions(*measurements_system);

    // Compare displacements between all three implementations
    for (size_t i = 0; i < initial_double.size(); ++i)
    {
        // Double-based displacements
        double dx_double = std::get<0>(final_double[i]) - std::get<0>(initial_double[i]);
        double dy_double = std::get<1>(final_double[i]) - std::get<1>(initial_double[i]);
        double dz_double = std::get<2>(final_double[i]) - std::get<2>(initial_double[i]);

        // Units-based displacements
        double dx_units = std::get<0>(final_units[i]) - std::get<0>(initial_units[i]);
        double dy_units = std::get<1>(final_units[i]) - std::get<1>(initial_units[i]);
        double dz_units = std::get<2>(final_units[i]) - std::get<2>(initial_units[i]);

        // Measurements-based displacements
        double dx_measurements = std::get<0>(final_measurements[i]) - std::get<0>(initial_measurements[i]);
        double dy_measurements = std::get<1>(final_measurements[i]) - std::get<1>(initial_measurements[i]);
        double dz_measurements = std::get<2>(final_measurements[i]) - std::get<2>(initial_measurements[i]);

        // All three systems should produce nearly identical trajectories
        // Allow small numerical differences due to different precision types
        double tol_double_vs_units = 1e-6;
        double tol_double_vs_measurements = 1e-6;

        EXPECT_NEAR(dx_double, dx_units, tol_double_vs_units) << "Body " << i << " X displacement mismatch (double vs units)";
        EXPECT_NEAR(dy_double, dy_units, tol_double_vs_units) << "Body " << i << " Y displacement mismatch (double vs units)";
        EXPECT_NEAR(dz_double, dz_units, tol_double_vs_units) << "Body " << i << " Z displacement mismatch (double vs units)";

        EXPECT_NEAR(dx_double, dx_measurements, tol_double_vs_measurements) << "Body " << i << " X displacement mismatch (double vs measurements)";
        EXPECT_NEAR(dy_double, dy_measurements, tol_double_vs_measurements) << "Body " << i << " Y displacement mismatch (double vs measurements)";
        EXPECT_NEAR(dz_double, dz_measurements, tol_double_vs_measurements) << "Body " << i << " Z displacement mismatch (double vs measurements)";
    }
}
