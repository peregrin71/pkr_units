#include <gtest/gtest.h>
#include <ratio>
#include <type_traits>
#include <pkr_units/si_units.h>
#include <pkr_units/impl/cast/unit_pow.h>

namespace test
{

using namespace ::testing;

class UnitPowTest : public Test
{
};

TEST_F(UnitPowTest, constexpr_pow_handles_zero_and_positive)
{
    volatile intmax_t base = 2;
    volatile unsigned int exp = 3;
    EXPECT_EQ(pkr::units::constexpr_pow(base, 0U), 1);
    EXPECT_EQ(pkr::units::constexpr_pow(base, exp), 8);
    EXPECT_EQ(pkr::units::constexpr_pow(3, 2U), 9);
}

TEST_F(UnitPowTest, power_of_ratio_and_dimension)
{
    using squared = pkr::units::power_of_t<pkr::units::kilometer_t<double>, 2>;
    using neg_squared = pkr::units::power_of_t<pkr::units::kilometer_t<double>, -2>;
    using squared_traits = pkr::units::details::is_pkr_unit<squared>;
    using neg_traits = pkr::units::details::is_pkr_unit<neg_squared>;

    static_assert(std::ratio_equal_v<typename squared_traits::ratio_type, std::ratio<1000000, 1>>);
    static_assert(std::ratio_equal_v<typename neg_traits::ratio_type, std::ratio<1, 1000000>>);
    static_assert(squared_traits::value_dimension.length == 2);
    static_assert(neg_traits::value_dimension.length == -2);
    static_assert(squared_traits::value_dimension.time == 0);

    EXPECT_TRUE((pkr::units::details::is_pkr_unit<pkr::units::power_of<pkr::units::second_t<double>, 2>>::value));
}

} // namespace test
