#include <gtest/gtest.h>
#include <pkr_units/units/computer_science/neural.h>
#include <pkr_units/units/computer_science/flop.h>

using namespace ::testing;
using namespace pkr::units;

TEST(ComputerScienceUnits, neural_op_and_flop_are_distinct)
{
    static_assert(!std::is_same_v<neural_op_t<double>, flop_t<double>>);
    neural_op_t<double> n{100.0};
    (void)n; // silence unused-variable warning
    meganeural_op_t<double> mn{1.0};

    // meganeural -> canonical should be 1e6 neural ops
    auto canonical = mn.to_si();
    ASSERT_DOUBLE_EQ(canonical.value(), 1e6);
}
