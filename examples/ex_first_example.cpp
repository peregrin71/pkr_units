// ============================================================================
// Example 1: First Example - Basic Units and Velocity Calculation
// ============================================================================
// This example demonstrates the fundamental concept of dimensional analysis:
// creating quantities with units and performing calculations that automatically
// deduce result types.

#include <pkr_units/si_units.h>
#include <pkr_units/format/si.h>
#include <iostream>
#include <format>
#include <string>

namespace ex {

void example_first_example()
{
    std::wcout << L"\n=== Example 1: Basic Units and Velocity ===\n";
    
    // Create quantities with units
    pkr::units::meter_t<double> distance(100.0);           // 100 meters
    pkr::units::second_t<double> time(5.0);                // 5 seconds
    
    // Divide to get velocity (automatic type deduction)
    auto velocity = distance / time;    // Result is meter_per_second_t
    
    // Print using library's formatting specializations
    std::wcout << L"Distance: " << distance << L"\n";
    std::wcout << L"Time: " << time << L"\n";
    std::string velocity_str = std::format("{}", velocity);
    std::wstring wvelocity_str = std::format(L"{}", velocity);
    std::wcout << L"Velocity: " << velocity << L"\n";
    
    // Additional calculation: distance = velocity * time
    auto reconstructed_distance = velocity * time;
    std::string output = std::format("{}",reconstructed_distance);
    std::wcout << L"Reconstructed distance: " << reconstructed_distance << L"\n";
    std::wcout << L"Hello world\n";
}

} // namespace ex
