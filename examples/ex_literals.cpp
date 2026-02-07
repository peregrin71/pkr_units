// ============================================================================
// Example 4: User-Defined Literals (UDL) for Convenience
// ============================================================================
// Demonstrates ergonomic creation of units using user-defined literals.
// Literals provide a concise way to express physical quantities with proper types.

#include <pkr_units/si_units.h>
#include <pkr_units/format/si.h>
#include <pkr_units/literals/length.h>
#include <pkr_units/literals/mass.h>
#include <pkr_units/literals/time.h>
#include <iostream>
#include <format>
#include <string>

namespace ex {

void example_literals()
{
    std::wcout << L"\n=== Example 4: User-Defined Literals (UDL) ===\n";
    
    using namespace pkr::units::literals;
    
    // Create units with user-defined literals for ergonomic syntax
    auto distance = 42.195_km;      // Marathon distance
    auto hours = 2.0_h;             // 2 hours
    auto minutes = 2.0_min;         // 2 minutes
    auto seconds = 57.0_s;          // 57 seconds
    
    // Calculate pace (result type is auto-deduced)
    auto total_time = hours + minutes + seconds;
    auto pace = distance / total_time;
    
    // Display results using library formatting
    std::wcout << L"Marathon:\n";
    std::wcout << L"  Distance: " << distance << L"\n";
    std::wcout << L"  Time: " << hours << L" + " << minutes << L" + " << seconds << L"\n";
    std::wcout << L"  Total Time: " << total_time << L"\n";
    std::wcout << L"  Pace: " << pace << L"\n";
    
    // More examples using literals
    std::wcout << L"\nLength scales:\n";
    
    auto height = 1.75_m;           // Height in meters
    auto thickness = 2.5_mm;        // Thickness in millimeters
    auto distance_cm = 100.0_cm;    // Distance in centimeters
    
    std::wcout << L"  Height: " << height << L"\n";
    std::wcout << L"  Thickness: " << thickness << L"\n";
    std::wcout << L"  Distance: " << distance_cm << L"\n";
    
    // Mass measurements
    std::wcout << L"\nMass measurements:\n";
    
    auto body_mass = 75.0_kg;       // Body mass in kilograms
    auto pill_mass = 500.0_mg;      // Pill mass in milligrams
    auto dust_mass = 2.5_ug;        // Dust mass in micrograms
    
    std::wcout << L"  Body mass: " << body_mass << L"\n";
    std::wcout << L"  Pill mass: " << pill_mass << L"\n";
    std::wcout << L"  Dust mass: " << dust_mass << L"\n";
    
    // Time measurements
    std::wcout << L"\nTime measurements:\n";
    
    auto reaction_time = 250.0_ms;  // Reaction time in milliseconds
    auto hour_value = 1.0_h;        // One hour
    auto minute_value = 60.0_s;     // One minute in seconds
    
    std::wcout << L"  Reaction time: " << reaction_time << L"\n";
    std::wcout << L"  Hour: " << hour_value << L"\n";
    std::wcout << L"  Minute in seconds: " << minute_value << L"\n";
}

} // namespace ex
