//
// Comprehensive test for all physical constants
// Tests all constants from constants.h and related headers

#include <gtest/gtest.h>

#include <pkr_units/constants.h>
#include <pkr_units/constants/atomic_constants.h>
#include <pkr_units/constants/particle_constants.h>
#include <pkr_units/constants/electromagnetic_constants.h>
#include <pkr_units/constants/nuclear_constants.h>
#include <pkr_units/constants/conversion_constants.h>

namespace test
{

using namespace ::testing;

class ConstantsComprehensiveTest : public Test
{
};

// Test all fundamental constants from constants.h
TEST_F(ConstantsComprehensiveTest, FundamentalConstants)
{
    // Test atomic mass unit
    EXPECT_NEAR(pkr::units::details::atomic_mass_unit<double>(), 1.66053906892e-27, 1e-37);

    // Test Avogadro's number
    EXPECT_NEAR(pkr::units::details::avogadro<double>(), 6.02214076e23, 1e13);

    // Test Bohr magneton
    EXPECT_NEAR(pkr::units::details::bohr_magneton<double>(), 9.2740100657e-24, 1e-33);

    // Test Boltzmann constant
    EXPECT_NEAR(pkr::units::details::boltzmann_constant<double>(), 1.380649e-23, 1e-32);

    // Test electron mass
    EXPECT_NEAR(pkr::units::details::electron_mass<double>(), 9.1093837139e-31, 1e-40);

    // Test elementary charge
    EXPECT_NEAR(pkr::units::details::elementary_charge<double>(), 1.602176634e-19, 1e-28);

    // Test Faraday constant
    EXPECT_NEAR(pkr::units::details::faraday_constant<double>(), 96485.33212, 1e-8);

    // Test fine structure constant
    EXPECT_NEAR(pkr::units::details::fine_structure_constant<double>(), 7.2973525643e-3, 1e-12);

    // Test gravitational constant
    EXPECT_NEAR(pkr::units::details::gravitational_constant<double>(), 6.67430e-11, 1e-16);

    // Test molar gas constant
    EXPECT_NEAR(pkr::units::details::molar_gas_constant<double>(), 8.314462618, 1e-12);

    // Test neutron mass
    EXPECT_NEAR(pkr::units::details::neutron_mass<double>(), 1.67492750056e-27, 1e-36);

    // Test nuclear magneton
    EXPECT_NEAR(pkr::units::details::nuclear_magneton<double>(), 5.0507837393e-27, 1e-36);

    // Test Planck constant
    EXPECT_NEAR(pkr::units::details::planck_constant<double>(), 6.62607015e-34, 1e-43);

    // Test proton mass
    EXPECT_NEAR(pkr::units::details::proton_mass<double>(), 1.67262192595e-27, 1e-36);

    // Test reduced Planck constant
    EXPECT_NEAR(pkr::units::details::reduced_planck_constant<double>(), 1.054571817e-34, 1e-43);

    // Test speed of light
    EXPECT_NEAR(pkr::units::details::speed_of_light<double>(), 299792458.0, 1e-1);

    // Test standard gravity
    EXPECT_NEAR(pkr::units::details::standard_gravity<double>(), 9.80665, 1e-5);

    // Test Stefan-Boltzmann constant
    EXPECT_NEAR(pkr::units::details::stefan_boltzmann<double>(), 5.670374419e-8, 1e-17);

    // Test vacuum permeability
    EXPECT_NEAR(pkr::units::details::vacuum_permeability<double>(), 1.25663706127e-6, 1e-15);

    // Test vacuum permittivity
    EXPECT_NEAR(pkr::units::details::vacuum_permittivity<double>(), 8.8541878188e-12, 1e-21);
}

// Test atomic constants
TEST_F(ConstantsComprehensiveTest, AtomicConstants)
{
    // Test Rydberg constant
    EXPECT_NEAR(pkr::units::details::rydberg_constant<double>(), 10973731.568157, 1e-3);

    // Test Bohr radius
    EXPECT_NEAR(pkr::units::details::bohr_radius<double>(), 5.29177210544e-11, 1e-20);
}

// Test particle constants
TEST_F(ConstantsComprehensiveTest, ParticleConstants)
{
    // Test muon mass
    EXPECT_NEAR(pkr::units::details::muon_mass<double>(), 1.883531627e-28, 1e-36);

    // Test tau mass
    EXPECT_NEAR(pkr::units::details::tau_mass<double>(), 3.16754e-27, 1e-32);

    // Test deuteron mass
    EXPECT_NEAR(pkr::units::details::deuteron_mass<double>(), 3.3435837768e-27, 1e-36);

    // Test triton mass
    EXPECT_NEAR(pkr::units::details::triton_mass<double>(), 5.0073567512e-27, 1e-36);

    // Test helion mass
    EXPECT_NEAR(pkr::units::details::helion_mass<double>(), 5.0064127862e-27, 1e-36);

    // Test alpha particle mass
    EXPECT_NEAR(pkr::units::details::alpha_particle_mass<double>(), 6.6446573450e-27, 1e-36);
}

// Test electromagnetic constants
TEST_F(ConstantsComprehensiveTest, ElectromagneticConstants)
{
    // Test vacuum impedance
    EXPECT_NEAR(pkr::units::details::vacuum_impedance<double>(), 376.730313412, 1e-12);

    // Test Josephson constant
    EXPECT_NEAR(pkr::units::details::josephson_constant<double>(), 483597.8484e9, 1e2);

    // Test von Klitzing constant
    EXPECT_NEAR(pkr::units::details::von_klitzing_constant<double>(), 25812.80745, 1e-8);

    // Test magnetic flux quantum
    EXPECT_NEAR(pkr::units::details::magnetic_flux_quantum<double>(), 2.067833848e-15, 1e-23);

    // Test conductance quantum
    EXPECT_NEAR(pkr::units::details::conductance_quantum<double>(), 7.748091729e-5, 1e-13);

    // Test inverse conductance quantum
    EXPECT_NEAR(pkr::units::details::inverse_conductance_quantum<double>(), 12906.40372, 1e-8);
}

// Test nuclear constants
TEST_F(ConstantsComprehensiveTest, NuclearConstants)
{
    // Test Fermi coupling constant
    EXPECT_NEAR(pkr::units::details::fermi_coupling_constant<double>(), 1.1663787e-5, 1e-13);

    // Test weak mixing angle
    EXPECT_NEAR(pkr::units::details::weak_mixing_angle<double>(), 0.22305, 1e-5);

    // Test classical electron radius
    EXPECT_NEAR(pkr::units::details::classical_electron_radius<double>(), 2.8179403205e-15, 1e-23);

    // Test Thomson cross section
    EXPECT_NEAR(pkr::units::details::thomson_cross_section<double>(), 6.6524587051e-29, 1e-37);

    // Test neutron Compton wavelength
    EXPECT_NEAR(pkr::units::details::neutron_compton_wavelength<double>(), 1.31959090382e-15, 1e-23);

    // Test proton Compton wavelength
    EXPECT_NEAR(pkr::units::details::proton_compton_wavelength<double>(), 1.32140985360e-15, 1e-23);
}

// Test conversion constants
TEST_F(ConstantsComprehensiveTest, ConversionConstants)
{
    // Test electron volt (exact value)
    EXPECT_NEAR(pkr::units::details::electron_volt<double>(), 1.602176634e-19, 1e-27);

    // Test hartree in electron volts
    EXPECT_NEAR(pkr::units::details::hartree_in_ev<double>(), 27.211386245981, 1e-8);

    // Test atomic mass unit in electron volts
    EXPECT_NEAR(pkr::units::details::atomic_mass_unit_in_ev<double>(), 931494103.72, 1e-2);

    // Test atomic mass unit in hertz
    EXPECT_NEAR(pkr::units::details::atomic_mass_unit_in_hz<double>(), 2.25234272185e23, 1e15);

    // Test electron volt in hertz
    EXPECT_NEAR(pkr::units::details::ev_in_hz<double>(), 2.417989242e14, 1e6);

    // Test electron volt in inverse meters
    EXPECT_NEAR(pkr::units::details::ev_in_inverse_meter<double>(), 8.065543937e5, 1e-1);

    // Test hertz in inverse meters
    EXPECT_NEAR(pkr::units::details::hz_in_inverse_meter<double>(), 3.335640951e-9, 1e-17);
}

// Test that constants work with different precisions
TEST_F(ConstantsComprehensiveTest, DifferentPrecisions)
{
    // Test float precision
    EXPECT_FLOAT_EQ(pkr::units::details::speed_of_light<float>(), 299792458.0f);

    // Test long double precision
    EXPECT_DOUBLE_EQ(static_cast<double>(pkr::units::details::speed_of_light<long double>()), 299792458.0);
}

// Test typed constants
TEST_F(ConstantsComprehensiveTest, TypedConstants)
{
    // Test that typed constants have correct units
    pkr::units::meter_t<double> c{pkr::units::details::speed_of_light<double>()};
    EXPECT_DOUBLE_EQ(c.value(), 299792458.0);

    pkr::units::joule_t<double> h{pkr::units::details::planck_constant<double>()};
    EXPECT_DOUBLE_EQ(h.value(), 6.62607015e-34);
}

} // namespace test
