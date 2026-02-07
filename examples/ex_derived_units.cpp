// ============================================================================
// Example 7: Derived Units - Common Physics Patterns
// ============================================================================
// Demonstrates how derived units emerge naturally from dimensional analysis.
// Types are automatically deduced from basic operations on SI base units.

#include <pkr_units/si_units.h>
#include <pkr_units/format/si.h>
#include <iostream>
#include <format>
#include <string>

namespace ex {

void example_derived_units()
{
    std::wcout << L"\n=== Example 7: Derived Units from Basic Operations ===\n";
    
    // Velocity from distance / time
    std::wcout << L"Velocity (distance ÷ time):\n";
    auto distance = pkr::units::meter_t<double>(100.0);
    auto time = pkr::units::second_t<double>(5.0);
    auto velocity = distance / time;  // Automatically meter_per_second_t
    std::wcout << L"  " << distance << L" ÷ " << time << L" = " << velocity << L"\n";
    
    // Acceleration from velocity / time
    std::wcout << L"\nAcceleration (velocity ÷ time):\n";
    auto initial_velocity = pkr::units::meter_per_second_t<double>(0.0);
    auto final_velocity = pkr::units::meter_per_second_t<double>(20.0);
    auto delta_v = final_velocity - initial_velocity;
    auto duration = pkr::units::second_t<double>(4.0);
    auto acceleration = delta_v / duration;  // Automatically meter_per_second_squared_t
    std::wcout << L"  Δv = " << delta_v << L" ÷ " << duration << L" = " << acceleration << L"\n";
    
    // Force from mass * acceleration
    std::wcout << L"\nForce (mass × acceleration):\n";
    auto mass = pkr::units::kilogram_t<double>(50.0);
    auto f = mass * acceleration;  // Automatically newton_t
    std::wcout << L"  " << mass << L" × " << acceleration << L" = " << f << L"\n";
    
    // Work/Energy from force * distance
    std::wcout << L"\nWork/Energy (force × distance):\n";
    auto displacement = pkr::units::meter_t<double>(10.0);
    auto work = f * displacement;  // Automatically joule_t
    std::wcout << L"  " << f << L" × " << displacement << L" = " << work << L"\n";
    
    // Pressure from force / area
    std::wcout << L"\nPressure (force ÷ area):\n";
    auto width = pkr::units::meter_t<double>(2.0);
    auto height = pkr::units::meter_t<double>(5.0);
    auto area = width * height;
    auto pressure_val = f / area;  // Automatically pascal_t
    std::wcout << L"  " << f << L" ÷ (" << width << L" × " << height << L") = " << pressure_val << L"\n";
    
    // Power from energy / time
    std::wcout << L"\nPower (energy ÷ time):\n";
    auto power = work / time;  // Automatically watt_t
    std::wcout << L"  " << work << L" ÷ " << time << L" = " << power << L"\n";
}

} // namespace ex
