#include <gtest/gtest.h>
#include <pkr_units/units/computer_science/flop.h>

using namespace ::testing;
using namespace pkr::units;

TEST(ComputerScienceUnits, megaflop_scaling)
{
    megaflop_t<double> mflop{1.0};
    auto canonical = mflop.to_si(); // canonical is `flop_t` stored value in FLOPs
    ASSERT_DOUBLE_EQ(canonical.value(), 1e6);
}
