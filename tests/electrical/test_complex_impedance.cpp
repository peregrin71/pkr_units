#include <gtest/gtest.h>
#include <complex>
#include <pkr_units/si_units.h>

using namespace ::testing;

class ComplexImpedanceTest : public Test
{
};

// Basic multiplication: V = Z * I
TEST_F(ComplexImpedanceTest, BasicImpedanceMultiplication)
{
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{50.0, 30.0}};   // 50 + j30 ohm
    pkr::units::ampere_t<cplx> I{cplx{2.0, -1.0}}; // 2 - j1 A

    auto V = Z * I; // volt_t<cplx>

    // Expected: (50 + j30) * (2 - j1) = 130 + j10
    ASSERT_DOUBLE_EQ(std::real(V.value()), 130.0);
    ASSERT_DOUBLE_EQ(std::imag(V.value()), 10.0);

    // Complex power S = V * conj(I) => real power = 250 W
    pkr::units::watt_t<cplx> S = V * pkr::units::ampere_t<cplx>(std::conj(I.value()));
    ASSERT_DOUBLE_EQ(std::real(S.value()), 250.0);
}

// More realistic scenario: voltage divider with complex impedance and compute real power
TEST_F(ComplexImpedanceTest, VoltageDividerAndPower)
{
    using cplx = std::complex<double>;

    pkr::units::volt_t<cplx> V_in{cplx{10.0, 0.0}}; // 10 V (real)
    pkr::units::ohm_t<cplx> Z1{cplx{0.0, 100.0}};   // j100
    pkr::units::ohm_t<cplx> Z2{cplx{100.0, 0.0}};   // 100 (resistor)

    // Current I = V_in / (Z1 + Z2)
    auto Z_total = Z1 + Z2;  // ohm_t<cplx>
    auto I = V_in / Z_total; // ampere_t<cplx>

    // Voltage across Z2: V_out = I * Z2
    auto V_out = I * Z2; // volt_t<cplx>

    // Expect V_out = 5 - j5 (calculated analytically)
    ASSERT_NEAR(std::real(V_out.value()), 5.0, 1e-12);
    ASSERT_NEAR(std::imag(V_out.value()), -5.0, 1e-12);

    // Real power dissipated in Z2 = Re(V_out * conj(I)) = 0.5 W
    pkr::units::watt_t<cplx> S2 = V_out * pkr::units::ampere_t<cplx>(std::conj(I.value()));
    ASSERT_NEAR(std::real(S2.value()), 0.5, 1e-12);
}
