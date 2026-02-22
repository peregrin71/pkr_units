#include <gtest/gtest.h>
// only computer-science units are needed for these tests
#include <pkr_units/units/computer_science/bytes.h>
#include <pkr_units/units/computer_science/bits.h>
#include <pkr_units/impl/cast/unit_cast.h>

using namespace ::testing;
using namespace pkr::units;

TEST(ComputerScienceUnits, bit_byte_conversion)
{
    byte_t<double> one_byte{1.0};
    bit_t<double> eight_bits{8.0};

    // bits and bytes carry distinct tags and therefore cannot be compared
    // directly.  conversions must use `unit_cast`.
    ASSERT_TRUE(one_byte == unit_cast<byte_t<double>>(eight_bits));
}

TEST(ComputerScienceUnits, kibibyte_and_kilobyte_equal)
{
    kibibyte_t<double> kib{1.0};
    kilobyte_t<double> k{1.0};

    // bytes use binary scaling by convention in this library: 1 kB == 1 KiB == 1024 B
    ASSERT_TRUE(kib == k);
    // canonical value of 1 kB (and 1 KiB) should be 1024 bytes
    auto canonical = kib.to_si(); // returns `byte_t` canonical
    ASSERT_DOUBLE_EQ(canonical.value(), 1024.0);
}

TEST(ComputerScienceUnits, kilobit_and_megabit_decimal_scaling)
{
    kilobit_t<double> kb{1.0};
    // explicit cast to bytes so tag mismatch is resolved by the user
    auto kb_bytes = unit_cast<byte_t<double>>(kb);
    ASSERT_DOUBLE_EQ(kb_bytes.value(), 125.0); // 1000 bits = 125 bytes

    megabit_t<double> mb{1.0};
    auto mb_bytes = unit_cast<byte_t<double>>(mb);
    ASSERT_DOUBLE_EQ(mb_bytes.value(), 125000.0); // 1,000,000 bits = 125000 bytes
}

TEST(ComputerScienceUnits, metric_vs_binary_bytes)
{
    megabyte_t<double> mbyte{1.0};
    mebibyte_t<double> mib{1.0};

    // not equal: 1 MB = 1e6 bytes, 1 MiB = 1048576 bytes
    ASSERT_NE(mbyte, mib);
    ASSERT_DOUBLE_EQ(mbyte.to_si().value(), 1'000'000.0);
    ASSERT_DOUBLE_EQ(mib.to_si().value(), 1048576.0);
}
