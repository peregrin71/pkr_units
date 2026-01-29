#include <gtest/gtest.h>
#include <format>
#include <type_traits>
#include <pkr_units/si_units.h>
#include <pkr_units/cgs_units.h>
#include <pkr_units/si_units_formatting.h>

class ViscosityTest : public ::testing::Test
{
};

TEST_F(ViscosityTest, dynamic_viscosity_dimension)
{
    pkr::units::pascal_second_t mu{1.0};
    using dimension = typename std::decay_t<decltype(mu)>::dimension_type;
    static_assert(dimension::value == pkr::units::dynamic_viscosity_dimension);
    ASSERT_TRUE(true);
}

TEST_F(ViscosityTest, kinematic_viscosity_dimension)
{
    pkr::units::square_meter_per_second_t nu{1.0};
    using dimension = typename std::decay_t<decltype(nu)>::dimension_type;
    static_assert(dimension::value == pkr::units::kinematic_viscosity_dimension);
    ASSERT_TRUE(true);
}

TEST_F(ViscosityTest, pascal_second_to_poise)
{
    pkr::units::pascal_second_t mu{1.0};
    auto p = pkr::units::unit_cast<pkr::units::poise_t>(mu);
    EXPECT_DOUBLE_EQ(p.value(), 10.0);
}

TEST_F(ViscosityTest, poise_to_pascal_second)
{
    pkr::units::poise_t p{1.0};
    auto mu = pkr::units::unit_cast<pkr::units::pascal_second_t>(p);
    EXPECT_DOUBLE_EQ(mu.value(), 0.1);
}

TEST_F(ViscosityTest, square_meter_per_second_to_stokes)
{
    pkr::units::square_meter_per_second_t nu{1.0};
    auto st = pkr::units::unit_cast<pkr::units::stokes_t>(nu);
    EXPECT_DOUBLE_EQ(st.value(), 10000.0);
}

TEST_F(ViscosityTest, stokes_to_square_meter_per_second)
{
    pkr::units::stokes_t st{1.0};
    auto nu = pkr::units::unit_cast<pkr::units::square_meter_per_second_t>(st);
    EXPECT_DOUBLE_EQ(nu.value(), 0.0001);
}

TEST_F(ViscosityTest, pascal_second_formatting)
{
    pkr::units::pascal_second_t mu{1.5};
    std::string result = std::format("{}", mu);
    EXPECT_EQ(result, "1.5 Pa*s");
}

TEST_F(ViscosityTest, square_meter_per_second_formatting)
{
    pkr::units::square_meter_per_second_t nu{0.25};
    std::string result = std::format("{}", nu);
    EXPECT_EQ(result, "0.25 m^2/s");
}
