#include <gtest/gtest.h>
#include <pkr_units/units/derived/mechanical/force.h>
#include <pkr_units/impl/cast/unit_cast.h>

using namespace ::testing;

class ForceCastTest : public Test
{
};

// ============================================================================
// Unit Conversion via unit_cast
// ============================================================================

TEST_F(ForceCastTest, cast_newton_to_kilonewton)
{
    pkr::units::newton_t<double> n{5000.0};
    auto kn = pkr::units::unit_cast<pkr::units::kilonewton_t<double>>(n);
    static_assert(std::is_same_v<decltype(kn), pkr::units::kilonewton_t<double>>);
    ASSERT_DOUBLE_EQ(kn.value(), 5.0);
}

TEST_F(ForceCastTest, cast_kilonewton_to_newton)
{
    pkr::units::kilonewton_t<double> kn{2.5};
    auto n = pkr::units::unit_cast<pkr::units::newton_t<double>>(kn);
    static_assert(std::is_same_v<decltype(n), pkr::units::newton_t<double>>);
    ASSERT_DOUBLE_EQ(n.value(), 2500.0);
}

TEST_F(ForceCastTest, cast_newton_to_meganewton)
{
    pkr::units::newton_t<double> n{2000000.0};
    auto mn = pkr::units::unit_cast<pkr::units::meganewton_t<double>>(n);
    static_assert(std::is_same_v<decltype(mn), pkr::units::meganewton_t<double>>);
    ASSERT_DOUBLE_EQ(mn.value(), 2.0);
}

TEST_F(ForceCastTest, cast_meganewton_to_newton)
{
    pkr::units::meganewton_t<double> mn{2.0};
    auto n = pkr::units::unit_cast<pkr::units::newton_t<double>>(mn);
    static_assert(std::is_same_v<decltype(n), pkr::units::newton_t<double>>);
    ASSERT_DOUBLE_EQ(n.value(), 2000000.0);
}

TEST_F(ForceCastTest, cast_newton_to_millinewton)
{
    pkr::units::newton_t<double> n{5.0};
    auto mn = pkr::units::unit_cast<pkr::units::millinewton_t<double>>(n);
    static_assert(std::is_same_v<decltype(mn), pkr::units::millinewton_t<double>>);
    ASSERT_DOUBLE_EQ(mn.value(), 5000.0);
}

TEST_F(ForceCastTest, cast_millinewton_to_newton)
{
    pkr::units::millinewton_t<double> mn{5000.0};
    auto n = pkr::units::unit_cast<pkr::units::newton_t<double>>(mn);
    static_assert(std::is_same_v<decltype(n), pkr::units::newton_t<double>>);
    ASSERT_DOUBLE_EQ(n.value(), 5.0);
}

TEST_F(ForceCastTest, cast_newton_to_micronewton)
{
    pkr::units::newton_t<double> n{0.001};
    auto un = pkr::units::unit_cast<pkr::units::micronewton_t<double>>(n);
    static_assert(std::is_same_v<decltype(un), pkr::units::micronewton_t<double>>);
    ASSERT_DOUBLE_EQ(un.value(), 1000.0);
}

TEST_F(ForceCastTest, cast_micronewton_to_newton)
{
    pkr::units::micronewton_t<double> un{1000000.0};
    auto n = pkr::units::unit_cast<pkr::units::newton_t<double>>(un);
    static_assert(std::is_same_v<decltype(n), pkr::units::newton_t<double>>);
    ASSERT_DOUBLE_EQ(n.value(), 1.0);
}

TEST_F(ForceCastTest, cast_newton_to_nanonewton)
{
    pkr::units::newton_t<double> n{0.000000001};
    auto nn = pkr::units::unit_cast<pkr::units::nanonewton_t<double>>(n);
    static_assert(std::is_same_v<decltype(nn), pkr::units::nanonewton_t<double>>);
    ASSERT_DOUBLE_EQ(nn.value(), 1.0);
}

TEST_F(ForceCastTest, cast_nanonewton_to_newton)
{
    pkr::units::nanonewton_t<double> nn{1000000000.0};
    auto n = pkr::units::unit_cast<pkr::units::newton_t<double>>(nn);
    static_assert(std::is_same_v<decltype(n), pkr::units::newton_t<double>>);
    ASSERT_DOUBLE_EQ(n.value(), 1.0);
}

TEST_F(ForceCastTest, cast_kilonewton_to_millinewton)
{
    pkr::units::kilonewton_t<double> kn{0.005};
    auto mn = pkr::units::unit_cast<pkr::units::millinewton_t<double>>(kn);
    static_assert(std::is_same_v<decltype(mn), pkr::units::millinewton_t<double>>);
    ASSERT_DOUBLE_EQ(mn.value(), 5000.0);
}

TEST_F(ForceCastTest, cast_millinewton_to_kilonewton)
{
    pkr::units::millinewton_t<double> mn{5000.0};
    auto kn = pkr::units::unit_cast<pkr::units::kilonewton_t<double>>(mn);
    static_assert(std::is_same_v<decltype(kn), pkr::units::kilonewton_t<double>>);
    ASSERT_DOUBLE_EQ(kn.value(), 0.005);
}

// ============================================================================
// Edge Cases and Precision Tests
// ============================================================================

TEST_F(ForceCastTest, cast_zero_force)
{
    pkr::units::newton_t<double> n{0.0};
    auto kn = pkr::units::unit_cast<pkr::units::kilonewton_t<double>>(n);
    ASSERT_DOUBLE_EQ(kn.value(), 0.0);
}

TEST_F(ForceCastTest, cast_negative_force)
{
    pkr::units::newton_t<double> n{-100.0};
    auto kn = pkr::units::unit_cast<pkr::units::kilonewton_t<double>>(n);
    ASSERT_DOUBLE_EQ(kn.value(), -0.1);
}

TEST_F(ForceCastTest, cast_very_small_force)
{
    pkr::units::nanonewton_t<double> nn{1e-12};
    auto n = pkr::units::unit_cast<pkr::units::newton_t<double>>(nn);
    ASSERT_DOUBLE_EQ(n.value(), 1e-21);
}

TEST_F(ForceCastTest, cast_very_large_force)
{
    pkr::units::meganewton_t<double> mn{1e6};
    auto n = pkr::units::unit_cast<pkr::units::newton_t<double>>(mn);
    ASSERT_DOUBLE_EQ(n.value(), 1e12);
}

TEST_F(ForceCastTest, round_trip_conversion)
{
    pkr::units::newton_t<double> original{123.456};
    auto kn = pkr::units::unit_cast<pkr::units::kilonewton_t<double>>(original);
    auto back = pkr::units::unit_cast<pkr::units::newton_t<double>>(kn);
    ASSERT_DOUBLE_EQ(back.value(), original.value());
}
