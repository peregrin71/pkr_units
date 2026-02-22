#include <gtest/gtest.h>
#include <pkr_units/units/computer_science/bits.h>
#include <pkr_units/units/computer_science/bytes.h>
#include <pkr_units/units/computer_science/flop.h>
#include <pkr_units/units/computer_science/neural.h>
#include <pkr_units/impl/cast/unit_cast.h>

using namespace pkr::units;

// qualification required in test bodies due to macro scopes

TEST(BandwidthTest, bits_and_bytes_per_second)
{
    bit_per_second_t<double> bps{8.0};
    auto Bps = unit_cast<byte_per_second_t<double>>(bps);
    EXPECT_EQ(Bps.value(), 1.0);
    // back-conversion
    auto bps2 = unit_cast<bit_per_second_t<double>>(Bps);
    EXPECT_EQ(bps2.value(), 8.0);
}

TEST(FlopRateTest, conversion)
{
    pkr::units::megaflop_per_second_t<double> mf{1.0};
    auto f = pkr::units::unit_cast<pkr::units::flop_per_second_t<double>>(mf);
    EXPECT_EQ(f.value(), 1'000'000);
}

TEST(NeuralRateTest, conversion)
{
    pkr::units::meganeural_op_per_second_t<double> mn{2.0};
    auto n = pkr::units::unit_cast<pkr::units::neural_op_per_second_t<double>>(mn);
    EXPECT_EQ(n.value(), 2'000'000);
}
