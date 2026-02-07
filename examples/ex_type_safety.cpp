// ============================================================================
// Example 5: Type Safety - Compiler-Enforced Dimensional Correctness
// ============================================================================
// This example demonstrates how the type system prevents common errors
// by ensuring only dimensionally compatible operations are allowed.
// Invalid operations fail at compile time, not runtime.

#include <pkr_units/si_units.h>
#include <pkr_units/format/si.h>
#include <iostream>
#include <format>
#include <string>

namespace ex {

// Type-safe function: only accepts meter_t
std::wstring format_distance(const pkr::units::meter_t<double>& distance)
{
    return std::format(L"Distance: {}", distance);
}

// Type-safe function: only accepts kilogram_t
std::wstring format_mass(const pkr::units::kilogram_t<double>& mass)
{
    return std::format(L"Mass: {}", mass);
}

void example_type_safety()
{
    std::wcout << L"\n=== Example 5: Type Safety and Dimensional Correctness ===\n";
    
    // Valid operations (same dimension)
    auto distance1 = pkr::units::meter_t<double>(100.0);
    auto distance2 = pkr::units::meter_t<double>(50.0);
    auto total_distance = distance1 + distance2;
    
    std::wcout << L"Distance 1: " << distance1 << L"\n";
    std::wcout << L"Distance 2: " << distance2 << L"\n";
    std::wcout << L"Total distance: " << total_distance << L"\n";
    
    // Division creates new dimension
    auto duration = pkr::units::second_t<double>(10.0);
    auto velocity = total_distance / duration;
    
    std::wcout << L"\nDuration: " << duration << L"\n";
    std::wcout << L"Velocity (distance/time): " << velocity << L"\n";
    
    // Function type safety
    std::wcout << L"\nType-safe function calls:\n";
    
    auto my_distance = pkr::units::meter_t<double>(500.0);
    std::wcout << L"  " << format_distance(my_distance) << L"\n";
    
    // This would fail to compile (wrong dimension):
    // format_distance(duration);        // ERROR: second_t cannot convert to meter_t
    // format_distance(my_mass);         // ERROR: kilogram_t cannot convert to meter_t
    
    // Instead, use the correct type
    auto my_mass = pkr::units::kilogram_t<double>(75.0);
    std::wcout << L"  " << format_mass(my_mass) << L"\n";
    
    std::wcout << L"\nType safety prevents mixing incompatible units at compile time!\n";
}

} // namespace ex
