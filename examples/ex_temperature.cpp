// ============================================================================
// Example 8: Temperature - Affine vs Linear Quantities
// ============================================================================
// Temperature is special: absolute temperatures (K, C, F) are affine quantities,
// while temperature differences (ΔK, ΔC, ΔF) are linear. This example shows
// the difference and proper handling of both.

#include <pkr_units/si_units.h>
#include <pkr_units/format/si.h>
#include <iostream>
#include <format>

namespace ex {

void example_temperature()
{
    std::wcout << L"\n=== Example 8: Temperature Handling (Affine vs Linear) ===\n";
    
    // Absolute temperatures (affine quantities)
    std::wcout << L"Absolute Temperatures:\n";
    auto water_freezing_K = pkr::units::kelvin_t<double>(273.15);
    auto water_boiling_K = pkr::units::kelvin_t<double>(373.15);
    
    std::wcout << L"  Water freezes at: " << water_freezing_K << L"\n";
    std::wcout << L"  Water boils at: " << water_boiling_K << L"\n";
    
    // Temperature difference (linear quantity from subtraction of affine quantities)
    std::wcout << L"\nTemperature Differences:\n";
    auto delta_T = water_boiling_K - water_freezing_K;
    std::wcout << L"  Temperature range in water: " << delta_T << L"\n";
    
    // Absolute temperatures (Kelvin scale)
    std::wcout << L"\nAbsolute Temperature (Kelvin):\n";
    pkr::units::kelvin_t<double> room_temp_K(293.15);  // 20°C
    pkr::units::kelvin_t<double> outdoor_temp_K(278.15);  // 5°C
    std::wcout << L"  Room temperature: " << room_temp_K << L"\n";
    std::wcout << L"  Outdoor temperature: " << outdoor_temp_K << L"\n";
    
    auto temp_difference = room_temp_K - outdoor_temp_K;
    std::wcout << L"  Temperature difference: " << temp_difference << L"\n";
    
    // Temperature conversion example
    std::wcout << L"\nTemperature Conversion:\n";
    auto absolute_temp = pkr::units::kelvin_t<double>(300.0);
    // Temperature conversion between scales requires special conversion functions
    // For now, we keep values in Kelvin
    pkr::units::kelvin_t<double> absolute_in_kelvin = absolute_temp;
    std::wcout << std::format(L"  {} (approx {:.1f}°C)\n", absolute_in_kelvin, absolute_in_kelvin.value() - 273.15);
    
    // Heat capacity example: Q = m × c × ΔT
    std::wcout << L"\nHeat Capacity (Q = m × c × ΔT):\n";
    auto material_mass = pkr::units::kilogram_t<double>(1.0);
    /* Note: specific heat constant operations require proper unit definition
       For now, just demonstrate the structure:
    */
    auto temp_increase = pkr::units::kelvin_t<double>(10.0);
    std::wcout << L"  Mass: " << material_mass << L"\n";
    std::wcout << L"  Temperature increase: " << temp_increase << L"\n";
    std::wcout << L"  (Specific heat would be in J/(kg·K))\n";
}

} // namespace ex
