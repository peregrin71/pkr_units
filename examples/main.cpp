#include <iostream>
#include <complex>

#include <pkr_units/si_units.h>
#include <pkr_units/imperial_units.h>

void set_distance_in_meters(const pkr::units::meter_t<double>& distance)
{
    std::cout << "Distance in meters: " << distance.value() << " m\n";
}

void complex_units()
{
    // === Electrical example: complex impedance ===
    // Impedance Z = R + jX (ohms), current I (amperes) may be complex.
    // Use complex-valued units (std::complex<double>) and take the real part when needed.
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{50.0, 30.0}};   // 50 + j30 ohm
    pkr::units::ampere_t<cplx> I{cplx{2.0, -1.0}}; // 2 - j1 A

    auto V = Z * I; // volt_t<cplx>

    std::cout << "Impedance Z: (" << std::real(Z.value()) << ") + j(" << std::imag(Z.value()) << ") ohm\n";
    std::cout << "Voltage V = Z * I: (" << std::real(V.value()) << ") + j(" << std::imag(V.value()) << ") V\n";

    // If you only want the resistive (real) part, extract it and use a real-valued unit
    pkr::units::ohm_t<double> resistance{std::real(Z.value())};
    std::cout << "Resistance (real part of Z): " << resistance.value() << " ohm\n";
}

int main()
{
    pkr::units::foot_t<double> distance_in_feet{10.0};
    // Automatic conversion from foot to meter when passing to function
    // this works since both units have the same dimensions.
    set_distance_in_meters(distance_in_feet);

    complex_units();

    return 0;
}