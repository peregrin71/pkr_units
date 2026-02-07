// ============================================================================
// Example 2: Physics Calculation - Kinetic Energy
// ============================================================================
// Demonstrates how physics formulas (E = 0.5 * m * v²) become fully type-safe
// with automatic dimensional analysis. The result type is deduced correctly
// without any explicit type specification.

#include <pkr_units/si_units.h>
#include <pkr_units/format/si.h>
#include <pkr_units/literals/mass.h>
#include <pkr_units/literals/velocity.h>
#include <iostream>
#include <format>
#include <cmath>
#include <string>

namespace ex {

void example_kinetic_energy()
{
    std::wcout << L"\n=== Example 2: Kinetic Energy (E = 0.5 * m * v²) ===\n";
    
    using namespace pkr::units::literals;
    
    // Define physical quantities using user-defined literals for ergonomic syntax
    // Note: Literals work with floating-point values (use decimal point)
    auto mass = 10.0_kg;               // kilogram_t<double> with literal
    auto velocity = 4.0_mps;           // meter_per_second_t<double> with literal (_mps for m/s)
    
    // Calculate kinetic energy: E = 0.5 * m * v²
    // The compiler automatically deduces the result type as joule_t
    auto energy = 0.5 * mass * (velocity * velocity);
    
    // Display inputs and result
    std::wcout << L"Mass: " << mass << L"\n";
    std::wcout << L"Velocity: " << velocity << L"\n";
    std::wcout << L"Kinetic Energy: " << energy << L"\n";
    
    // Demonstrate with different values using literals
    auto heavy_mass = 1000.0_kg;       // 1 metric ton
    auto high_velocity = 50.0_mps;     // 50 m/s (180 km/h)
    auto heavy_energy = 0.5 * heavy_mass * (high_velocity * high_velocity);
    
    std::wcout << L"\nHeavy object at high speed:\n";
    std::wcout << L"  Mass: " << heavy_mass << L"\n";
    std::wcout << L"  Velocity: " << high_velocity << L"\n";
    std::wcout << L"  Kinetic Energy: " << heavy_energy << L"\n";
}

} // namespace ex
