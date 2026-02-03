//
// Test constants functionality
// Verifies that physical constants can be properly accessed and used in calculations

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

// using namespace pkr::units;

class ConstantsTest : public Test
{
};

// Test that fundamental constants are accessible and have correct values
TEST_F(ConstantsTest, FundamentalConstantsAccessible)
{
    // Test speed of light
    EXPECT_DOUBLE_EQ(*pkr::units::speed_of_light, 299792458.0);

    // Test Planck constant
    EXPECT_DOUBLE_EQ(pkr::units::planck_constant, 6.62607015e-34);

    // Test elementary charge
    EXPECT_DOUBLE_EQ(pkr::units::elementary_charge, 1.602176634e-19);

    // Test Avogadro constant
    EXPECT_DOUBLE_EQ(pkr::units::avogadro, 6.02214076e23);

    // Test Boltzmann constant
    EXPECT_DOUBLE_EQ(pkr::units::boltzmann_constant, 1.380649e-23);
}

// Test that typed constants work correctly
TEST_F(ConstantsTest, TypedConstantsWork)
{
    // Test kilogram_t constants
    pkr::units::kilogram_t<double> electron_mass_const{pkr::units::details::electron_mass<double>()};
    pkr::units::kilogram_t<double> proton_mass_const{pkr::units::details::proton_mass<double>()};

    // Test that they can be used in calculations
    pkr::units::kilogram_t<double> total_mass = electron_mass_const + proton_mass_const;
    EXPECT_GT(total_mass.value(), electron_mass_const.value());
    EXPECT_GT(total_mass.value(), proton_mass_const.value());

    // Test speed of light typed constant
    pkr::units::meter_per_second_t<double> c{pkr::units::speed_of_light};
    EXPECT_DOUBLE_EQ(c.value(), 299792458.0);
}

// Test that constants can be used in mathematical operations
TEST_F(ConstantsTest, ConstantsInCalculations)
{
    // Calculate energy using E = mc²
    pkr::units::joule_t<double> rest_energy_electron{(pkr::units::electron_mass * pkr::units::speed_of_light * pkr::units::speed_of_light).value()};
    EXPECT_GT(rest_energy_electron.value(), 0.0);

    // Test with typed constants
    pkr::units::kilogram_t<double> m_e{pkr::units::details::electron_mass<double>()};
    pkr::units::meter_per_second_t<double> c{pkr::units::speed_of_light};
    pkr::units::joule_t<double> energy{(m_e * c * c).value()};

    EXPECT_GT(energy.value(), 0.0);
}

// Test atomic physics constants
TEST_F(ConstantsTest, AtomicConstantsWork)
{
    // Test Hartree energy
    pkr::units::joule_t<double> hartree_energy_const{pkr::units::details::hartree_energy<double>()};
    EXPECT_GT(hartree_energy_const.value(), 0.0);

    // Test that atomic constants are accessible
    EXPECT_DOUBLE_EQ(pkr::units::hartree_energy.value(), pkr::units::details::hartree_energy<double>());
}

// Test particle physics constants
TEST_F(ConstantsTest, ParticleConstantsWork)
{
    // Test muon mass
    pkr::units::kilogram_t<double> muon_mass_const{pkr::units::details::muon_mass<double>()};
    EXPECT_GT(muon_mass_const.value(), 0.0);

    // Test deuteron mass
    pkr::units::kilogram_t<double> deuteron_mass_const{pkr::units::details::deuteron_mass<double>()};
    EXPECT_GT(deuteron_mass_const.value(), 0.0);
}

// Test electromagnetic constants
TEST_F(ConstantsTest, ElectromagneticConstantsWork)
{
    // Test vacuum impedance
    EXPECT_GT(pkr::units::vacuum_impedance.value(), 0.0);

    // Test Josephson constant
    EXPECT_GT(pkr::units::josephson_constant.value(), 0.0);

    // Test von Klitzing constant
    EXPECT_GT(pkr::units::von_klitzing_constant.value(), 0.0);
}

// Test nuclear constants
TEST_F(ConstantsTest, NuclearConstantsWork)
{
    // Test classical electron radius
    pkr::units::meter_t<double> electron_radius{pkr::units::details::classical_electron_radius<double>()};
    EXPECT_GT(electron_radius.value(), 0.0);

    // Test Thomson cross section
    pkr::units::square_meter_t<double> thomson_cross_section_const{pkr::units::details::thomson_cross_section<double>()};
    EXPECT_GT(thomson_cross_section_const.value(), 0.0);
}

// Test conversion constants
TEST_F(ConstantsTest, ConversionConstantsWork)
{
    // Test electron volt
    EXPECT_DOUBLE_EQ(pkr::units::electron_volt, 1.602176634e-19);

    // Test conversion factors
    EXPECT_GT(pkr::units::ev_in_hz, 0.0);
    EXPECT_GT(pkr::units::ev_in_inverse_meter, 0.0);
}

// Test that constants maintain precision
TEST_F(ConstantsTest, ConstantsPrecision)
{
    // Test that constants have sufficient precision for calculations
    double fine_structure = pkr::units::fine_structure_constant;
    EXPECT_NEAR(fine_structure, 7.2973525643e-3, 1e-12);

    // Test that very small constants maintain precision
    double electron_mass_val = pkr::units::details::electron_mass<double>();
    EXPECT_NEAR(electron_mass_val, 9.1093837139e-31, 1e-40);
}

// Test compile-time usage
TEST_F(ConstantsTest, CompileTimeUsage)
{
    // Test that constants can be used in constexpr contexts
    constexpr double c = *pkr::units::speed_of_light;
    constexpr double h = pkr::units::planck_constant;
    constexpr double e = pkr::units::elementary_charge;

    // These should compile and work
    constexpr double hc = h * c;
    constexpr double ec = e * c;
    constexpr double alpha = pkr::units::fine_structure_constant;

    EXPECT_GT(hc, 0.0);
    EXPECT_GT(ec, 0.0);
    EXPECT_GT(alpha, 0.0);
}

} // namespace test
