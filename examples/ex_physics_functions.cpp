// ============================================================================
// Example 6: Physics Functions - Type-Safe Dimensional Equations
// ============================================================================
// Shows how physics equations become type-safe functions that enforce
// dimensional correctness automatically. The compiler verifies the physics!

#include <pkr_units/si_units.h>
#include <pkr_units/units/derived/area/area_units.h>
#include <pkr_units/units/derived/volume/volume_units.h>
#include <pkr_units/format/si.h>
#include <iostream>
#include <format>
#include <string>

namespace ex {

// Type-safe physics functions
// The return type is automatically deduced from the calculation

// F = m * a  (Newton's Second Law)
pkr::units::newton_t<double> force(
    const pkr::units::kilogram_t<double>& mass, 
    const pkr::units::meter_per_second_squared_t<double>& acceleration)
{
    return mass * acceleration;
}

// E_k = 0.5 * m * v²  (Kinetic Energy)
pkr::units::joule_t<double> kinetic_energy(
    const pkr::units::kilogram_t<double>& mass,
    const pkr::units::meter_per_second_t<double>& velocity)
{
    return 0.5 * mass * (velocity * velocity);
}

// P = F / A  (Pressure)
auto pressure(
    const pkr::units::newton_t<double>& applied_force,
    const auto& area)
{
    return applied_force / area;
}

// ρ = m / V  (Density)
auto density(
    const pkr::units::kilogram_t<double>& mass,
    const auto& volume)
{
    return mass / volume;
}

void example_physics_functions()
{
    std::wcout << L"\n=== Example 6: Type-Safe Physics Functions ===\n";
    
    // Newton's Second Law: F = m * a
    std::wcout << L"Newton's Second Law (F = m × a):\n";
    pkr::units::kilogram_t<double> mass(10.0);
    pkr::units::meter_per_second_squared_t<double> acceleration(5.0);
    auto f = force(mass, acceleration);
    std::wcout << L"  m = " << mass << L", a = " << acceleration << L" → F = " << f << L"\n";
    
    // Kinetic Energy: E = 0.5 * m * v²
    std::wcout << L"\nKinetic Energy (E = ½ × m × v²):\n";
    pkr::units::meter_per_second_t<double> velocity(20.0);
    auto e_k = kinetic_energy(mass, velocity);
    std::wcout << L"  m = " << mass << L", v = " << velocity << L" → E = " << e_k << L"\n";
    
    // Pressure: P = F / A
    std::wcout << L"\nPressure (P = F ÷ A):\n";
    pkr::units::meter_t<double> side(2.0);
    auto area = side * side;  // square_meter_t - type deduced
    auto p = pressure(f, area);
    std::wcout << L"  F = " << f << L", A = " << area << L" → P = " << p << L"\n";
    
    // Density: ρ = m / V
    std::wcout << L"\nDensity (ρ = m ÷ V):\n";
    pkr::units::meter_t<double> length(1.0);
    auto volume = length * length * length;  // cubic_meter_t - type deduced
    auto rho = density(mass, volume);
    std::wcout << L"  m = " << mass << L", V = " << volume << L" → ρ = " << rho << L"\n";
}

} // namespace ex
