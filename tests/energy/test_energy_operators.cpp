#include <gtest/gtest.h>
#include <pkr_units/units/derived/mechanical/energy.h>

using namespace ::testing;

class EnergyOperatorsTest : public Test
{
};

// ============================================================================
// Arithmetic Operations Tests
// ============================================================================

TEST_F(EnergyOperatorsTest, add_energies)
{
    pkr::units::joule_t<double> energy1{500.0};
    pkr::units::joule_t<double> energy2{300.0};
    auto result = energy1 + energy2;
    ASSERT_DOUBLE_EQ(result.value(), 800.0);
}

TEST_F(EnergyOperatorsTest, subtract_energies)
{
    pkr::units::joule_t<double> energy1{1000.0};
    pkr::units::joule_t<double> energy2{300.0};
    auto result = energy1 - energy2;
    ASSERT_DOUBLE_EQ(result.value(), 700.0);
}

TEST_F(EnergyOperatorsTest, multiply_energy_by_scalar)
{
    pkr::units::joule_t<double> energy{500.0};
    auto result = energy * 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 1000.0);
}

TEST_F(EnergyOperatorsTest, divide_energy_by_scalar)
{
    pkr::units::joule_t<double> energy{1000.0};
    auto result = energy / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(EnergyOperatorsTest, multiply_energy_by_zero)
{
    pkr::units::joule_t<double> energy{500.0};
    auto result = energy * 0.0;
    ASSERT_DOUBLE_EQ(result.value(), 0.0);
}

TEST_F(EnergyOperatorsTest, multiply_energy_by_fraction)
{
    pkr::units::joule_t<double> energy{1000.0};
    auto result = energy * 0.5;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(EnergyOperatorsTest, equal_energies)
{
    pkr::units::joule_t<double> energy1{1000.0};
    pkr::units::joule_t<double> energy2{1000.0};
    ASSERT_TRUE(energy1 == energy2);
}

TEST_F(EnergyOperatorsTest, not_equal_energies)
{
    pkr::units::joule_t<double> energy1{1000.0};
    pkr::units::joule_t<double> energy2{500.0};
    ASSERT_TRUE(energy1 != energy2);
}

TEST_F(EnergyOperatorsTest, less_than_energies)
{
    pkr::units::joule_t<double> energy1{500.0};
    pkr::units::joule_t<double> energy2{1000.0};
    ASSERT_TRUE(energy1 < energy2);
}

TEST_F(EnergyOperatorsTest, less_than_or_equal_energies)
{
    pkr::units::joule_t<double> energy1{500.0};
    pkr::units::joule_t<double> energy2{500.0};
    ASSERT_TRUE(energy1 <= energy2);
    pkr::units::joule_t<double> energy3{300.0};
    ASSERT_TRUE(energy3 <= energy1);
}

TEST_F(EnergyOperatorsTest, greater_than_energies)
{
    pkr::units::joule_t<double> energy1{1000.0};
    pkr::units::joule_t<double> energy2{500.0};
    ASSERT_TRUE(energy1 > energy2);
}

TEST_F(EnergyOperatorsTest, greater_than_or_equal_energies)
{
    pkr::units::joule_t<double> energy1{500.0};
    pkr::units::joule_t<double> energy2{500.0};
    ASSERT_TRUE(energy1 >= energy2);
    pkr::units::joule_t<double> energy3{700.0};
    ASSERT_TRUE(energy3 >= energy1);
}

TEST_F(EnergyOperatorsTest, constexpr_energy_addition)
{
    constexpr pkr::units::joule_t<double> energy1{500.0};
    constexpr pkr::units::joule_t<double> energy2{300.0};
    constexpr auto result = energy1 + energy2;
    static_assert(result.value() == 800.0);
    ASSERT_DOUBLE_EQ(result.value(), 800.0);
}

TEST_F(EnergyOperatorsTest, constexpr_energy_multiplication_and_division)
{
    constexpr pkr::units::joule_t<double> energy{1000.0};
    constexpr auto result = energy * 2.0 / 4.0;
    static_assert(result.value() == 500.0);
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(EnergyOperatorsTest, scalar_rhs_multiply_energy)
{
    pkr::units::joule_t<double> energy{500.0};
    auto result = 2.0 * energy;
    ASSERT_DOUBLE_EQ(result.value(), 1000.0);
}

TEST_F(EnergyOperatorsTest, scalar_rhs_divide_energy)
{
    pkr::units::joule_t<double> energy{1000.0};
    auto result = 2000.0 / energy;
    // This should result in 1/energy (per joule)
    ASSERT_DOUBLE_EQ(result.value(), 2.0);
}

TEST_F(EnergyOperatorsTest, add_to)
{
    pkr::units::joule_t<double> energy{500.0};
    energy += pkr::units::joule_t<double>{300.0};
    ASSERT_DOUBLE_EQ(energy.value(), 800.0);
}

TEST_F(EnergyOperatorsTest, constexpr_add_to)
{
    constexpr pkr::units::joule_t<double> energy1{500.0};
    constexpr pkr::units::joule_t<double> energy2{300.0};
    constexpr auto result = energy1 + energy2;
    static_assert(result.value() == 800.0);
    ASSERT_DOUBLE_EQ(result.value(), 800.0);
}
