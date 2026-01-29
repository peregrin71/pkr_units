#include <gtest/gtest.h>
#include <format>
#include <type_traits>
#include <pkr_units/impl/cast/unit_cast.h>
#include <pkr_units/impl/formatting/unit_formatter.h>
#include <pkr_units/units/derived/magnetic_flux.h>
#include <pkr_units/units/magnetic/gauss.h>

using namespace ::testing;

class MagneticFluxDensityTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(MagneticFluxDensityTest, gauss_construction)
{
    pkr::units::gauss_t g{2500.0};
    ASSERT_DOUBLE_EQ(g.value(), 2500.0);
}

TEST_F(MagneticFluxDensityTest, gauss_dimension)
{
    pkr::units::gauss_t g{1.0};
    using dimension = typename std::decay_t<decltype(g)>::dimension_type;
    static_assert(dimension::value == pkr::units::magnetic_flux_density_dimension);
    ASSERT_TRUE(true);
}

// ============================================================================
// Unit Conversion via unit_cast
// ============================================================================

TEST_F(MagneticFluxDensityTest, tesla_to_gauss)
{
    pkr::units::tesla_t t{1.0};
    auto g = pkr::units::unit_cast<pkr::units::gauss_t>(t);
    ASSERT_DOUBLE_EQ(g.value(), 10000.0);
}

TEST_F(MagneticFluxDensityTest, gauss_to_tesla)
{
    pkr::units::gauss_t g{5000.0};
    auto t = pkr::units::unit_cast<pkr::units::tesla_t>(g);
    ASSERT_DOUBLE_EQ(t.value(), 0.5);
}

TEST_F(MagneticFluxDensityTest, gauss_to_microtesla)
{
    pkr::units::gauss_t g{1.0};
    auto ut = pkr::units::unit_cast<pkr::units::microtesla_t>(g);
    ASSERT_DOUBLE_EQ(ut.value(), 100.0);
}

// ============================================================================
// Formatting Tests
// ============================================================================

TEST_F(MagneticFluxDensityTest, gauss_formatting)
{
    pkr::units::gauss_t g{2.0};
    std::string result = std::format("{}", g);
    EXPECT_EQ(result, "2 G");
}

TEST_F(MagneticFluxDensityTest, gauss_wide_formatting)
{
    pkr::units::gauss_t g{2.0};
    std::wstring result = std::format(L"{}", g);
    EXPECT_EQ(result, L"2 G");
}
