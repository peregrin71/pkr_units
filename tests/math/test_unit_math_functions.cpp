#include <gtest/gtest.h>
#include <pkr_units/units/math/unit_math.h>
#include <pkr_units/si_units.h>
#include <numbers>

namespace test
{

using namespace ::testing;

class UnitMathTest : public Test
{
};

TEST_F(UnitMathTest, square_and_cube)
{
    pkr::units::meter_t<double> m{5.0};
    auto s = pkr::units::square(m);
    ASSERT_DOUBLE_EQ(s.value(), 25.0);
    using s_dim = decltype(s)::dimension;
    static_assert(s_dim::value.length == 2, "square dims");

    auto c = pkr::units::cube(m);
    ASSERT_DOUBLE_EQ(c.value(), 125.0);
    using c_dim = decltype(c)::dimension;
    static_assert(c_dim::value.length == 3, "cube dims");
}

TEST_F(UnitMathTest, pow_integer_exponent)
{
    pkr::units::meter_t<double> m{2.0};

    // Test positive exponents
    auto p0 = pkr::units::pow<0>(m);
    ASSERT_DOUBLE_EQ(p0.value(), 1.0);

    auto p2 = pkr::units::pow<2>(m);
    ASSERT_DOUBLE_EQ(p2.value(), 4.0);
    using p2_dim = decltype(p2)::dimension;
    static_assert(p2_dim::value.length == 2, "pow 2 dims");

    auto p3 = pkr::units::pow<3>(m);
    ASSERT_DOUBLE_EQ(p3.value(), 8.0);
    using p3_dim = decltype(p3)::dimension;
    static_assert(p3_dim::value.length == 3, "pow 3 dims");

    auto p4 = pkr::units::pow<4>(m);
    ASSERT_DOUBLE_EQ(p4.value(), 16.0);
    using p4_dim = decltype(p4)::dimension;
    static_assert(p4_dim::value.length == 4, "pow 4 dims");

    // Test negative exponents
    auto p_neg1 = pkr::units::pow<-1>(m);
    ASSERT_DOUBLE_EQ(p_neg1.value(), 0.5);
    using p_neg1_dim = decltype(p_neg1)::dimension;
    static_assert(p_neg1_dim::value.length == -1, "pow -1 dims");

    auto p_neg2 = pkr::units::pow<-2>(m);
    ASSERT_DOUBLE_EQ(p_neg2.value(), 0.25);
    using p_neg2_dim = decltype(p_neg2)::dimension;
    static_assert(p_neg2_dim::value.length == -2, "pow -2 dims");
}

TEST_F(UnitMathTest, pow_integer_exponent_non_unit_ratio)
{
    pkr::units::kilometer_t<double> km{3.0};

    auto p0 = pkr::units::pow<0>(km);
    ASSERT_DOUBLE_EQ(p0.value(), 1.0);
    using p0_dim = decltype(p0)::dimension;
    static_assert(p0_dim::value.length == 0, "pow 0 dims");

    auto p2 = pkr::units::pow<2>(km);
    ASSERT_DOUBLE_EQ(p2.value(), 9.0);
    using p2_dim = decltype(p2)::dimension;
    static_assert(p2_dim::value.length == 2, "pow 2 dims");
}

TEST_F(UnitMathTest, sqrt_of_area)
{
    auto length = pkr::units::meter_t<double>{4.0};
    auto area = length * length;
    auto root = pkr::units::sqrt(area);
    ASSERT_DOUBLE_EQ(root.value(), 4.0);
    using r_dim = decltype(root)::dimension;
    static_assert(r_dim::value.length == 1, "sqrt dims");
}

TEST_F(UnitMathTest, sqrt_throws_on_negative_value)
{
    using base_length_t = pkr::units::details::unit_t<double, std::ratio<1, 1>, pkr::units::length_dimension>;
    base_length_t length{-4.0};
    EXPECT_THROW(pkr::units::sqrt(length), std::invalid_argument);
}

TEST_F(UnitMathTest, log_and_exp_dimensionless)
{
    pkr::units::scalar_t<double> value{2.0};
    auto logged = pkr::units::log(value);
    auto exponent = pkr::units::exp(value);

    ASSERT_NEAR(logged.value(), std::log(2.0), 1e-12);
    ASSERT_NEAR(exponent.value(), std::exp(2.0), 1e-12);
}

TEST_F(UnitMathTest, trigonometric_functions)
{
    pkr::units::radian_t<double> angle{0.0};

    // Test sin
    auto s = pkr::units::sin(angle);
    ASSERT_DOUBLE_EQ(s.value(), 0.0);
    // Should return a dimensionless scalar
    static_assert(std::is_same_v<decltype(s), pkr::units::scalar_t<double>>, "sin returns scalar");

    // Test cos
    auto c = pkr::units::cos(angle);
    ASSERT_DOUBLE_EQ(c.value(), 1.0);
    static_assert(std::is_same_v<decltype(c), pkr::units::scalar_t<double>>, "cos returns scalar");

    // Test tan
    auto t = pkr::units::tan(angle);
    ASSERT_DOUBLE_EQ(t.value(), 0.0);
    static_assert(std::is_same_v<decltype(t), pkr::units::scalar_t<double>>, "tan returns scalar");

    // Test with pi/2 radians
    pkr::units::radian_t<double> angle_pi_2{std::numbers::pi / 2.0};
    auto sin_pi_2 = pkr::units::sin(angle_pi_2);
    ASSERT_NEAR(sin_pi_2.value(), 1.0, 1e-10);

    auto cos_pi_2 = pkr::units::cos(angle_pi_2);
    ASSERT_NEAR(cos_pi_2.value(), 0.0, 1e-10);
}

} // namespace test
