#include <gtest/gtest.h>
#include <format>
#include <type_traits>
#include <pkr_units/cgs_units.h>
#include <pkr_units/format/cgs.h>
#include <pkr_units/si_units.h>

class CgsUnitsTest : public ::testing::Test
{
};

namespace
{
struct ampere_per_meter_t final : public pkr::units::unit_t<double, std::ratio<1, 1>, pkr::units::magnetic_field_strength_dimension>
{
    using _base = pkr::units::unit_t<double, std::ratio<1, 1>, pkr::units::magnetic_field_strength_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"ampere_per_meter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"A/m"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"A\u00B7m\u207B\u00B9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"A\u00B7m\u207B\u00B9"};
};
} // namespace

TEST_F(CgsUnitsTest, dyne_to_newton)
{
    pkr::units::dyne_t<double> d{1.0};
    auto n = pkr::units::unit_cast<pkr::units::newton_t<double>>(d);
    EXPECT_DOUBLE_EQ(n.value(), 1e-5);
}

TEST_F(CgsUnitsTest, erg_to_joule)
{
    pkr::units::erg_t<double> e{1.0};
    auto j = pkr::units::unit_cast<pkr::units::joule_t<double>>(e);
    EXPECT_DOUBLE_EQ(j.value(), 1e-7);
}

TEST_F(CgsUnitsTest, barye_to_pascal)
{
    pkr::units::barye_t<double> b{1.0};
    auto p = pkr::units::unit_cast<pkr::units::pascal_t<double>>(b);
    EXPECT_DOUBLE_EQ(p.value(), 0.1);
}

TEST_F(CgsUnitsTest, gal_to_meter_per_second_squared)
{
    pkr::units::gal_t<double> g{1.0};
    auto a = pkr::units::unit_cast<pkr::units::meter_per_second_squared_t<double>>(g);
    EXPECT_DOUBLE_EQ(a.value(), 0.01);
}

TEST_F(CgsUnitsTest, maxwell_to_weber)
{
    pkr::units::maxwell_t<double> mx{1.0};
    auto w = pkr::units::unit_cast<pkr::units::weber_t<double>>(mx);
    EXPECT_DOUBLE_EQ(w.value(), 1e-8);
}

TEST_F(CgsUnitsTest, statcoulomb_to_coulomb)
{
    pkr::units::statcoulomb_t<double> sc{1.0};
    auto c = pkr::units::unit_cast<pkr::units::coulomb_t<double>>(sc);
    EXPECT_NEAR(c.value(), 1.0 / 2997924580.0, 1e-15);
}

TEST_F(CgsUnitsTest, oersted_dimension)
{
    pkr::units::oersted_t<double> h{1.0};
    using dimension = typename std::decay_t<decltype(h)>::dimension_type;
    static_assert(dimension::value == pkr::units::magnetic_field_strength_dimension);
    ASSERT_TRUE(true);
}

TEST_F(CgsUnitsTest, oersted_to_ampere_per_meter)
{
    pkr::units::oersted_t<double> h{1.0};
    auto a_per_m = pkr::units::unit_cast<ampere_per_meter_t>(h);
    EXPECT_NEAR(a_per_m.value(), 79.5774715459477, 1e-10);
}

TEST_F(CgsUnitsTest, cgs_formatting)
{
    EXPECT_EQ(std::format("{}", pkr::units::dyne_t<double>{2.0}), "2 dyn");
    EXPECT_EQ(std::format("{}", pkr::units::erg_t<double>{3.0}), "3 erg");
    EXPECT_EQ(std::format("{}", pkr::units::barye_t<double>{4.0}), "4 Ba");
    EXPECT_EQ(std::format("{}", pkr::units::gal_t<double>{5.0}), "5 Gal");
    EXPECT_EQ(std::format("{}", pkr::units::maxwell_t<double>{6.0}), "6 Mx");
    EXPECT_EQ(std::format("{}", pkr::units::poise_t<double>{7.0}), "7 P");
    EXPECT_EQ(std::format("{}", pkr::units::stokes_t<double>{8.0}), "8 St");
    EXPECT_EQ(std::format("{}", pkr::units::statcoulomb_t<double>{9.0}), "9 statC");
    EXPECT_EQ(std::format("{}", pkr::units::oersted_t<double>{10.0}), "10 Oe");
}
