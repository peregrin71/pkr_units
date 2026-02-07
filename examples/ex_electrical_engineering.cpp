// ============================================================================
// Example 10: Electrical Engineering - Complex Power and Circuit Analysis
// ============================================================================
// Demonstrates type-safe electrical engineering calculations including:
// - Ohm's law and basic circuit analysis
// - DC power calculations
// - AC circuit analysis with RMS values
// - Three-phase power systems
// - Energy calculations with time
// - Power factor and reactive power

#include <pkr_units/si_units.h>
#include <pkr_units/units/derived/electrical.h>
#include <pkr_units/format/si.h>
#include <pkr_units/literals/length.h>
#include <pkr_units/literals/time.h>
#include <iostream>
#include <format>
#include <cmath>
#include <complex>
#include <string>

namespace ex {

void example_electrical_engineering()
{
    std::wcout << L"\n=== Example 10: Electrical Engineering - Power and Circuits ===\n";
    
    using namespace pkr::units::literals;
    constexpr double PI = 3.141592653589793;  // Mathematical constant for angle conversions
    
    // ========================================================================
    // Part 1: DC Circuit - Ohm's Law and Basic Power Calculations
    // ========================================================================
    
    std::wcout << L"\n--- DC Circuit Analysis (Ohm's Law: I = V ÷ R) ---\n";
    
    // Basic DC circuit parameters
    pkr::units::volt_t<double> supply_voltage(12.0);           // 12V power supply
    pkr::units::ohm_t<double> load_resistance(4.0);            // 4 Ω resistive load
    
    // Calculate current using Ohm's law: I = V / R
    auto load_current = supply_voltage / load_resistance;
    std::wcout << L"Supply voltage: " << supply_voltage << L"\n";
    std::wcout << L"Load resistance: " << load_resistance << L"\n";
    std::wcout << L"Current (I = V ÷ R): " << load_current << L"\n";
    
    // Calculate power dissipation: P = V × I
    auto power_vi = supply_voltage * load_current;
    std::wcout << std::format(L"Power (P = V × I): {}\n", power_vi);
    
    // Verify with alternative formula: P = I²R
    auto power_i2r = load_current * load_current * load_resistance;
    std::wcout << std::format(L"Power (P = I² × R): {}\n", power_i2r);
    
    // Verify with third formula: P = V²/R
    auto power_v2r = (supply_voltage * supply_voltage) / load_resistance;
    std::wcout << std::format(L"Power (P = V² ÷ R): {}\n", power_v2r);
    
    // ========================================================================
    // Part 2: Energy Consumption Over Time
    // ========================================================================
    
    std::wcout << L"\n--- Energy Consumption ---\n";
    
    // Operating time
    auto operating_time = 2.0_h;  // 2 hours
    
    // Calculate energy: E = P × t
    auto energy_consumed = power_vi * operating_time;
    std::wcout << L"Operating time: " << operating_time << L"\n";
    std::wcout << L"Energy consumed: " << energy_consumed << L"\n";
    
    // Power consumed by a small residential circuit
    std::wcout << L"\nResidential loads:\n";
    
    pkr::units::volt_t<double> mains_voltage(230.0);           // European mains (230V)
    pkr::units::ampere_t<double> fridge_current(2.5);          // Typical refrigerator
    pkr::units::ampere_t<double> light_current(0.43);          // 100W incandescent bulb
    pkr::units::ampere_t<double> heater_current(13.0);         // Electric heater
    
    auto fridge_power = mains_voltage * fridge_current;
    auto light_power = mains_voltage * light_current;
    auto heater_power = mains_voltage * heater_current;
    
    std::wcout << L"  Refrigerator (" << fridge_current << L"): " << fridge_power << L"\n";
    std::wcout << L"  Light bulb (" << light_current << L"): " << light_power << L"\n";
    std::wcout << L"  Electric heater (" << heater_current << L"): " << heater_power << L"\n";
    
    auto total_load_current = fridge_current + light_current + heater_current;
    auto total_power = mains_voltage * total_load_current;
    std::wcout << L"  Total current: " << total_load_current << L"\n";
    std::wcout << L"  Total power: " << total_power << L"\n";
    
    // ========================================================================
    // Part 3: AC Circuit with Impedance and Reactance
    // ========================================================================
    
    std::wcout << L"\n--- AC Circuit Analysis (Impedance: Z = √(R² + X²)) ---\n";
    
    // AC circuit parameters
    pkr::units::volt_t<double> ac_voltage_rms(230.0);          // RMS voltage
    double frequency = 50.0;                                    // 50 Hz (Europe)
    
    // Inductive load (motor): has both resistance and reactance
    pkr::units::ohm_t<double> motor_resistance(2.0);           // R (Ω)
    pkr::units::ohm_t<double> motor_reactance(4.0);            // X_L (inductive reactance, Ω)
    
    // Calculate impedance magnitude: Z = sqrt(R² + X²)
    double R_val = motor_resistance.value();
    double X_val = motor_reactance.value();
    double Z_magnitude = std::sqrt(R_val * R_val + X_val * X_val);
    
    std::wcout << L"AC voltage (RMS): " << ac_voltage_rms << L"\n";
    std::wcout << std::format(L"Frequency: {:.0f} Hz\n", frequency);
    std::wcout << L"Motor resistance (R): " << motor_resistance << L"\n";
    std::wcout << L"Motor reactance (X_L): " << motor_reactance << L"\n";
    std::wcout << std::format(L"Impedance magnitude (Z = √(R² + X²)): {:.3f} Ω\n", Z_magnitude);
    
    // Calculate phase angle: φ = arctan(X/R)
    double phase_angle_rad = std::atan(X_val / R_val);
    double phase_angle_deg = phase_angle_rad * 180.0 / PI;
    std::wcout << std::format(L"Phase angle (φ): {:.2f}° (lagging)\n", phase_angle_deg);
    
    // AC current
    pkr::units::ampere_t<double> ac_current(ac_voltage_rms.value() / Z_magnitude);
    std::wcout << L"AC current (I = V ÷ Z): " << ac_current << L"\n";
    
    // ========================================================================
    // Part 4: AC Power (Real, Reactive, Apparent)
    // ========================================================================
    
    std::wcout << L"\n--- AC Power Analysis ---\n";
    
    // Apparent power: S = V × I (in VA, volt-amperes)
    auto apparent_power = ac_voltage_rms * ac_current;
    std::wcout << L"Apparent power (S = V × I): " << apparent_power << L"\n";
    
    // Power factor: PF = cos(φ)
    double power_factor = std::cos(phase_angle_rad);
    std::wcout << std::format(L"Power factor (cos φ): {:.3f}\n", power_factor);
    
    // Real power: P = S × cos(φ) (in watts)
    double real_power_value = apparent_power.value() * power_factor;
    std::wcout << std::format(L"Real power (P = S × cos φ): {:.2f} W\n", real_power_value);
    
    // Reactive power: Q = S × sin(φ) (in VAR, volt-amperes reactive)
    double reactive_power_value = apparent_power.value() * std::sin(phase_angle_rad);
    std::wcout << std::format(L"Reactive power (Q = S × sin φ): {:.2f} VAR\n", reactive_power_value);
    
    // ========================================================================
    // Part 5: Three-Phase Power System
    // ========================================================================
    
    std::wcout << L"\n--- Three-Phase Power System (P = √3 × V × I × cos φ) ---\n";
    
    // Industrial three-phase system (400V line-to-line in Europe)
    pkr::units::volt_t<double> three_phase_voltage(400.0);     // Three-phase voltage
    pkr::units::ampere_t<double> three_phase_current(32.0);    // Per-phase current
    double three_phase_pf = 0.85;                               // Typical power factor
    
    std::wcout << L"Three-phase voltage (line-to-line): " << three_phase_voltage << L"\n";
    std::wcout << L"Current per phase: " << three_phase_current << L"\n";
    std::wcout << std::format(L"Power factor (cos φ): {:.2f}\n", three_phase_pf);
    
    // Three-phase power: P = √3 × V × I × cos(φ)
    double sqrt_3 = std::sqrt(3.0);
    double three_phase_power = sqrt_3 * three_phase_voltage.value() * 
                               three_phase_current.value() * three_phase_pf;
    
    std::wcout << std::format(L"Three-phase power (P = √3 × V × I × cos φ): {:.2f} W\n", 
                             three_phase_power);
    
    // Convert to kilowatts for readability
    std::wcout << std::format(L"  ≈ {:.2f} kW\n", three_phase_power / 1000.0);
    
    // ========================================================================
    // Part 6: Circuit with Series and Parallel Elements
    // ========================================================================
    
    std::wcout << L"\n--- Series Circuit Analysis (R_total = R₁ + R₂ + R₃) ---\n";
    
    // Series circuit: R1 - R2 - R3 with voltage source
    pkr::units::volt_t<double> series_voltage(24.0);
    pkr::units::ohm_t<double> r1(5.0);
    pkr::units::ohm_t<double> r2(7.0);
    pkr::units::ohm_t<double> r3(8.0);
    
    // Total resistance in series: R_total = R1 + R2 + R3
    auto total_resistance = r1 + r2 + r3;
    
    // Current through series circuit: I = V ÷ R_total
    auto series_current = series_voltage / total_resistance;
    
    // Voltage drops across each resistor: V = I × R
    auto v1 = series_current * r1;
    auto v2 = series_current * r2;
    auto v3 = series_current * r3;
    
    std::wcout << L"Source voltage: " << series_voltage << L"\n";
    std::wcout << L"Resistances: " << r1 << L" + " << r2 << L" + " << r3 << L" (all Ω)\n";
    std::wcout << L"Total resistance: " << total_resistance << L"\n";
    std::wcout << L"Circuit current: " << series_current << L"\n";
    
    std::wcout << L"\nVoltage drops:\n";
    std::wcout << L"  V(R1): " << v1 << L"\n";
    std::wcout << L"  V(R2): " << v2 << L"\n";
    std::wcout << L"  V(R3): " << v3 << L"\n";
    
    auto total_drop = v1 + v2 + v3;
    std::wcout << L"  Total: " << total_drop << L" (\u2248 source voltage)\n";
    
    // Power dissipated in each resistor
    std::wcout << L"\nPower dissipation (P = I² × R):\n";
    auto p1 = series_current * series_current * r1;
    auto p2 = series_current * series_current * r2;
    auto p3 = series_current * series_current * r3;
    
    std::wcout << L"  R(1): " << p1 << L"\n";
    std::wcout << L"  R(2): " << p2 << L"\n";
    std::wcout << L"  R(3): " << p3 << L"\n";
    
    auto total_power_series = p1 + p2 + p3;
    std::wcout << L"  Total: " << total_power_series << L"\n";
    
    // ========================================================================
    // Part 7: Complex Impedance and Power (using std::complex<double>)
    // ========================================================================
    
    std::wcout << L"\n--- Complex Impedance and AC Power Analysis ---\n";
    
    // Complex impedance: Z = R + jX (impedance has real and imaginary parts)
    // Create a unit type that wraps complex<double> for type safety
    std::complex<double> impedance_raw(motor_resistance.value(), 
                                       motor_reactance.value());  // 2 + 4j Ω
    
    std::wcout << std::format(L"Complex impedance (Z = R + jX): ({:.1f} + {:.1f}j) Ω\n", 
                             impedance_raw.real(), impedance_raw.imag());
    
    // Create a complex-valued unit (ohm_t wrapping complex<double>)
    pkr::units::ohm_t<std::complex<double>> impedance_unit(impedance_raw);
    
    // Use the new magnitude() member function (returns ohm_t<double>)
    auto Z_mag_unit = impedance_unit.magnitude();
    std::wcout << std::format(L"Impedance magnitude |Z|: {:.3f} Ω\n", Z_mag_unit.value());
    
    // Use the new phase() member function (returns radian_t<double>)
    auto Z_phase_unit = impedance_unit.phase();
    double Z_phase_rad = Z_phase_unit.value();
    std::wcout << std::format(L"Impedance phase angle: {:.2f}° = {:.4f} rad\n", 
                             Z_phase_rad * 180.0 / PI, Z_phase_rad);
    
    // AC voltage and current as complex phasors
    // Voltage as reference: V = V_magnitude ∠ 0°
    std::complex<double> v_complex(ac_voltage_rms.value(), 0.0);  // 230 V at 0°
    
    // Current through impedance: I = V / Z (complex division)
    std::complex<double> i_complex = v_complex / impedance_raw;
    
    std::wcout << L"\nComplex voltage and current:\n";
    std::wcout << std::format(L"  Voltage: ({:.1f} + {:.1f}j) V (magnitude: {:.1f} V)\n",
                             v_complex.real(), v_complex.imag(), std::abs(v_complex));
    std::wcout << std::format(L"  Current: ({:.1f} + {:.1f}j) A (magnitude: {:.2f} A)\n",
                             i_complex.real(), i_complex.imag(), std::abs(i_complex));
    
    // Current phase angle (showing lag relative to voltage using the impedance phase)
    std::wcout << std::format(L"  Phase angle difference: {:.2f}° (current lags voltage)\n",
                             Z_phase_rad * 180.0 / PI);
    
    // Complex power: S = V × I* (conjugate of current)
    // This gives us S = P + jQ (real power + reactive power)
    std::complex<double> i_conjugate = std::conj(i_complex);
    std::complex<double> power_complex = v_complex * i_conjugate;
    
    std::wcout << L"\nComplex power (S = P + jQ):\n";
    std::wcout << std::format(L"  Real power (P): {:.2f} W\n", power_complex.real());
    std::wcout << std::format(L"  Reactive power (Q): {:.2f} VAR\n", power_complex.imag());
    
    double apparent_power_calc = std::abs(power_complex);
    std::wcout << std::format(L"  Apparent power (|S|): {:.2f} VA\n", apparent_power_calc);
    
    double power_factor_calc = power_complex.real() / std::abs(power_complex);
    std::wcout << std::format(L"  Power factor: {:.3f}\n", power_factor_calc);
    
    // Example with series RLC circuit resonance
    std::wcout << L"\n--- RLC Series Circuit at Different Frequencies ---\n";
    
    // Circuit parameters
    double R = 10.0;                          // 10 Ω resistance
    double L = 0.01;                          // 10 mH inductance
    double C = 100e-6;                        // 100 µF capacitance
    double V_source = 100.0;                  // 100 V source
    
    // Calculate resonant frequency: f_0 = 1 / (2π√LC)
    double resonant_freq = 1.0 / (2.0 * PI * std::sqrt(L * C));
    std::wcout << std::format(L"Resonant frequency: {:.2f} Hz\n", resonant_freq);
    
    // Analyze at three frequencies: below, at, and above resonance
    double test_frequencies[] = {resonant_freq * 0.5, resonant_freq, resonant_freq * 1.5};
    
    for (double freq : test_frequencies) {
        double omega = 2.0 * PI * freq;
        
        // Inductive reactance: X_L = ωL
        double X_L = omega * L;
        
        // Capacitive reactance: X_C = 1/(ωC)
        double X_C = 1.0 / (omega * C);
        
        // Total impedance: Z = R + j(X_L - X_C)
        std::complex<double> Z_rlc_raw(R, X_L - X_C);
        
        // Create impedance unit and use member functions for type-safe extraction
        pkr::units::ohm_t<std::complex<double>> Z_rlc_unit(Z_rlc_raw);
        auto Z_mag_unit_rlc = Z_rlc_unit.magnitude();  // Returns ohm_t<double>
        auto Z_phase_unit_rlc = pkr::units::unit_cast<pkr::units::degree_t<double>>(Z_rlc_unit.phase());    // Converts radian_t<double> to degree_t<double>

        
        // Current amplitude
        double I_mag = V_source / Z_mag_unit_rlc.value();
        
        std::wcout << std::format(L"\nAt f = {:.2f} Hz:\n", freq);
        std::wcout << std::format(L"  X_L = {:.2f} Ω, X_C = {:.2f} Ω\n", X_L, X_C);
        std::wcout << std::format(L"  |Z| = {:.2f} Ω, ∠φ = {:.2f}\n", 
                                 Z_mag_unit_rlc.value(), Z_phase_unit_rlc);
        std::wcout << std::format(L"  |I| = {:.2f} A\n", I_mag);
    }
}

} // namespace ex
