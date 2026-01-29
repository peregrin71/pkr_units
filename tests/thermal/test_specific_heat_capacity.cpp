#include <gtest/gtest.h>
#include <format>
#include <pkr_units/units/derived/thermal/specific_heat_capacity.h>
#include <pkr_units/si_formatting.h>

using namespace ::testing;

class SpecificHeatCapacityTest : public Test
{
};

TEST_F(SpecificHeatCapacityTest, specific_heat_capacity_construction)
{
    pkr::units::specific_heat_capacity_t c{900.0};
    ASSERT_DOUBLE_EQ(c.value(), 900.0);
}

TEST_F(SpecificHeatCapacityTest, specific_heat_capacity_dimension)
{
    pkr::units::specific_heat_capacity_t c{1.0};
    using dimension = typename std::decay_t<decltype(c)>::dimension_type;
    static_assert(dimension::value == pkr::units::specific_heat_capacity_dimension);
    ASSERT_TRUE(true);
}

TEST_F(SpecificHeatCapacityTest, specific_heat_capacity_formatting)
{
    pkr::units::specific_heat_capacity_t c{1.5};
    std::string result = std::format("{}", c);
    EXPECT_EQ(result, "1.5 J/(kg*K)");
}

TEST_F(SpecificHeatCapacityTest, specific_heat_capacity_wide_formatting)
{
    pkr::units::specific_heat_capacity_t c{1.5};
    std::wstring result = std::format(L"{}", c);
    EXPECT_EQ(result, L"1.5 J·kg⁻¹·K⁻¹");
}
