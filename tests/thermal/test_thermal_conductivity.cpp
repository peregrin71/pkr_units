#include <gtest/gtest.h>
#include <format>
#include <pkr_units/units/derived/thermal/thermal_conductivity.h>
#include <pkr_units/format/si.h>

using namespace ::testing;

class ThermalConductivityTest : public Test
{
};

TEST_F(ThermalConductivityTest, thermal_conductivity_construction)
{
    pkr::units::thermal_conductivity_t<double> k{0.6};
    ASSERT_DOUBLE_EQ(k.value(), 0.6);
}

TEST_F(ThermalConductivityTest, thermal_conductivity_dimension)
{
    pkr::units::thermal_conductivity_t<double> k{1.0};
    using dimension = typename std::decay_t<decltype(k)>::dimension_type;
    static_assert(dimension::value == pkr::units::thermal_conductivity_dimension);
    ASSERT_TRUE(true);
}

TEST_F(ThermalConductivityTest, thermal_conductivity_formatting)
{
    pkr::units::thermal_conductivity_t<double> k{3.0};
    std::string result = std::format("{}", k);
    EXPECT_EQ(result, "3 W/(m*K)");
}

TEST_F(ThermalConductivityTest, thermal_conductivity_wide_formatting)
{
    pkr::units::thermal_conductivity_t<double> k{3.0};
    std::wstring result = std::format(L"{}", k);
    EXPECT_EQ(result, L"3 W\xB7m\u207B\xB9\xB7K\u207B\xB9");
}
