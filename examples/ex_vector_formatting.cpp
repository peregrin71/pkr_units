// ============================================================================
// Example 9: Vector Formatting with Units
// ============================================================================
// Demonstrates working with 3D vectors of units and their formatting.
// Vectors with units enable type-safe spatial calculations in physics,
// engineering, and computer graphics.

#include <pkr_units/si_units.h>
#include <pkr_units/units/math/vector_unit_3d.h>
#include <pkr_units/impl/formatting/vector_unit_3d.h>
#include <pkr_units/format/si.h>
#include <pkr_units/literals/length.h>
#include <pkr_units/literals/velocity.h>
#include <iostream>
#include <format>
#include <cmath>

namespace ex {

void example_vector_formatting()
{
    std::cout << "\n=== Example 9: Vector Formatting with Units ===\n";
    
    using namespace pkr::units::literals;
    
    // Create 3D position vectors in meters
    std::cout << "Position Vectors (location in 3D space):\n";
    
    pkr::units::vec_3d_units_t<pkr::units::meter_t<double>> pos1{0.0_m, 0.0_m, 0.0_m};
    pkr::units::vec_3d_units_t<pkr::units::meter_t<double>> pos2{10.0_m, 20.0_m, 5.0_m};
    
    std::cout << std::format("  Position 1: {}\n", pos1);
    std::cout << std::format("  Position 2: {}\n", pos2);
    
    // Calculate displacement vector
    auto displacement = pos2 - pos1;
    std::cout << std::format("  Displacement: {}\n", displacement);
    
    // Velocity vectors
    std::cout << "\nVelocity Vectors (motion in 3D space):\n";
    
    pkr::units::vec_3d_units_t<pkr::units::meter_per_second_t<double>> velocity1{
        pkr::units::meter_per_second_t<double>(5.0),
        pkr::units::meter_per_second_t<double>(3.0),
        pkr::units::meter_per_second_t<double>(1.0)
    };
    
    pkr::units::vec_3d_units_t<pkr::units::meter_per_second_t<double>> velocity2{
        10.0_m_per_s,
        -5.0_m_per_s,
        2.0_m_per_s
    };
    
    std::cout << std::format("  Velocity 1: {}\n", velocity1);
    std::cout << std::format("  Velocity 2: {}\n", velocity2);
    
    // Vector magnitude calculation
    std::cout << "\nVector Operations:\n";
    
    // Calculate magnitude of displacement
    auto dx = displacement.x.value();
    auto dy = displacement.y.value();
    auto dz = displacement.z.value();
    double distance = std::sqrt(dx*dx + dy*dy + dz*dz);
    
    std::cout << std::format("  Distance between points: {:.2f} m\n", distance);
    
    // Velocity magnitude
    auto vx = velocity1.x.value();
    auto vy = velocity1.y.value();
    auto vz = velocity1.z.value();
    double speed = std::sqrt(vx*vx + vy*vy + vz*vz);
    
    std::cout << std::format("  Speed (magnitude of velocity1): {:.2f} m/s\n", speed);
    
    // Vector addition
    auto combined_velocity = velocity1 + velocity2;
    std::cout << std::format("  Combined velocity: {}\n", combined_velocity);
    
    // Acceleration vectors
    std::cout << "\nAcceleration Vectors:\n";
    
    auto gravity = pkr::units::vec_3d_units_t<pkr::units::meter_per_second_squared_t<double>>{
        0.0_m_per_s2,
        0.0_m_per_s2,
        -9.81_m_per_s2  // Standard gravity pointing downward
    };
    
    std::cout << std::format("  Gravity acceleration: {}\n", gravity);
    
    // Formatting with precision
    std::cout << "\nFormatting with different precisions:\n";
    
    auto precise_pos = pkr::units::vec_3d_units_t<pkr::units::meter_t<double>>{
        3.14159_m,
        2.71828_m,
        1.41421_m
    };
    
    std::cout << std::format("  Default precision:  {}\n", precise_pos);
    std::cout << std::format("  2 decimal places:   {:.2f}\n", precise_pos);
    std::cout << std::format("  4 decimal places:   {:.4f}\n", precise_pos);
    
    // Force vectors (mechanical)
    std::cout << "\nForce Vectors (from multi-body system):\n";
    
    auto force1 = pkr::units::vec_3d_units_t<pkr::units::newton_t<double>>{
        100.0,  // Will be interpreted as newton_t<double>
        50.0,
        0.0
    };
    
    auto force2 = pkr::units::vec_3d_units_t<pkr::units::newton_t<double>>{
        -30.0,
        40.0,
        25.0
    };
    
    std::cout << std::format("  Force 1: {}\n", force1);
    std::cout << std::format("  Force 2: {}\n", force2);
    
    auto net_force = force1 + force2;
    std::cout << std::format("  Net force: {}\n", net_force);
}

} // namespace ex
