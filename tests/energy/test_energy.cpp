#include <gtest/gtest.h>
#include <pkr_units/units/derived/mechanical/energy.h>

using namespace ::testing;

class EnergyTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(EnergyTest, joule_construction)
{
    pkr::units::joule energy{1000.0};
    ASSERT_DOUBLE_EQ(energy.value(), 1000.0);
}

TEST_F(EnergyTest, joule_dereference_operator)
{
    pkr::units::joule energy{1000.0};
    ASSERT_DOUBLE_EQ(*energy, 1000.0);
}

TEST_F(EnergyTest, joule_zero_value)
{
    pkr::units::joule energy{0.0};
    ASSERT_DOUBLE_EQ(energy.value(), 0.0);
}

TEST_F(EnergyTest, joule_negative_value)
{
    pkr::units::joule energy{-500.0};
    ASSERT_DOUBLE_EQ(energy.value(), -500.0);
}

TEST_F(EnergyTest, kilojoule_construction)
{
    pkr::units::kilojoule energy{5.0};
    ASSERT_DOUBLE_EQ(energy.value(), 5.0);
}

TEST_F(EnergyTest, megajoule_construction)
{
    pkr::units::megajoule energy{2.0};
    ASSERT_DOUBLE_EQ(energy.value(), 2.0);
}

TEST_F(EnergyTest, gigajoule_construction)
{
    pkr::units::gigajoule energy{1.5};
    ASSERT_DOUBLE_EQ(energy.value(), 1.5);
}

TEST_F(EnergyTest, millijoule_construction)
{
    pkr::units::millijoule energy{500000.0};
    ASSERT_DOUBLE_EQ(energy.value(), 500000.0);
}

TEST_F(EnergyTest, microjoule_construction)
{
    pkr::units::microjoule energy{1000000000.0};
    ASSERT_DOUBLE_EQ(energy.value(), 1000000000.0);
}

TEST_F(EnergyTest, calorie_construction)
{
    pkr::units::calorie energy{100.0};
    ASSERT_DOUBLE_EQ(energy.value(), 100.0);
}

TEST_F(EnergyTest, kilocalorie_construction)
{
    pkr::units::kilocalorie energy{0.5};
    ASSERT_DOUBLE_EQ(energy.value(), 0.5);
}

TEST_F(EnergyTest, watthour_construction)
{
    pkr::units::watthour energy{100.0};
    ASSERT_DOUBLE_EQ(energy.value(), 100.0);
}

TEST_F(EnergyTest, kilowatthour_construction)
{
    pkr::units::kilowatthour energy{10.0};
    ASSERT_DOUBLE_EQ(energy.value(), 10.0);
}

TEST_F(EnergyTest, electronvolt_construction)
{
    pkr::units::electronvolt energy{1e20};
    ASSERT_DOUBLE_EQ(energy.value(), 1e20);
}

TEST_F(EnergyTest, kiloelectronvolt_construction)
{
    pkr::units::kiloelectronvolt energy{1e17};
    ASSERT_DOUBLE_EQ(energy.value(), 1e17);
}

TEST_F(EnergyTest, megaelectronvolt_construction)
{
    pkr::units::megaelectronvolt energy{1e14};
    ASSERT_DOUBLE_EQ(energy.value(), 1e14);
}

TEST_F(EnergyTest, gigaelectronvolt_construction)
{
    pkr::units::gigaelectronvolt energy{1e11};
    ASSERT_DOUBLE_EQ(energy.value(), 1e11);
}

TEST_F(EnergyTest, copy_constructor)
{
    pkr::units::joule energy1{1000.0};
    pkr::units::joule energy2{energy1};
    ASSERT_DOUBLE_EQ(energy2.value(), 1000.0);
}

TEST_F(EnergyTest, move_constructor)
{
    pkr::units::joule energy1{1000.0};
    pkr::units::joule energy2{std::move(energy1)};
    ASSERT_DOUBLE_EQ(energy2.value(), 1000.0);
}

TEST_F(EnergyTest, copy_assignment)
{
    pkr::units::joule energy1{1000.0};
    pkr::units::joule energy2{0.0};
    energy2 = energy1;
    ASSERT_DOUBLE_EQ(energy2.value(), 1000.0);
}

TEST_F(EnergyTest, move_assignment)
{
    pkr::units::joule energy1{1000.0};
    pkr::units::joule energy2{0.0};
    energy2 = std::move(energy1);
    ASSERT_DOUBLE_EQ(energy2.value(), 1000.0);
}

TEST_F(EnergyTest, energy_has_correct_dimension)
{
    pkr::units::joule energy{1.0};
    using dimension = typename std::decay_t<decltype(energy)>::dimension_type;
    static_assert(std::is_same_v<dimension, pkr::units::energy_dimension>);
    ASSERT_TRUE(true); // Compile-time check
}

TEST_F(EnergyTest, very_small_values)
{
    pkr::units::electronvolt energy{1e-20};
    ASSERT_DOUBLE_EQ(energy.value(), 1e-20);
}

TEST_F(EnergyTest, very_large_values)
{
    pkr::units::gigajoule energy{1e9};
    ASSERT_DOUBLE_EQ(energy.value(), 1e9);
}