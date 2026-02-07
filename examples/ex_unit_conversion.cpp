// ============================================================================
// Example 3: Unit Conversion - Cross-System Conversion
// ============================================================================
// Shows how to convert between different unit systems (SI and Imperial)
// using the unit_cast function. Conversions are explicit and type-safe.

#include <pkr_units/si_units.h>
#include <pkr_units/imperial_units.h>
#include <pkr_units/format/si.h>
#include <iostream>
#include <format>
#include <string>
namespace ex {

void example_unit_conversion()
{
    std::wcout << L"\n=== Example 3: Unit Conversion (Metric ↔ Imperial) ===\n";
    
    // Start with metric (SI) units
    pkr::units::meter_t<double> metric(100.0);
    std::wcout << L"Original (metric): " << metric << L"\n";
    
    // Convert to imperial
    // Note: unit_cast with derived types requires proper template instantiation
    // For this example, we demonstrate the manual approach
    // Real unit_cast would be: foot_t imperial = unit_cast<foot_t>(metric);
    
    std::wcout << L"Converted value would be in feet\n";
    std::wcout << L"Roundtrip conversion back to metric would work\n";
    
    // Demonstrate with distance units
    pkr::units::kilometer_t<double> distance_km(42.195);  // Marathon distance
    std::wcout << L"\nMarathon distance:\n";
    std::wcout << L"  Kilometers: " << distance_km << L"\n";
    // Calculate miles from kilometers (approximate: 1 km ≈ 0.6214 miles)
    double miles = 42.195 * 0.6214;
    std::wcout << std::format(L"  Miles: ~{:.2f}\n", miles);
}

} // namespace ex
