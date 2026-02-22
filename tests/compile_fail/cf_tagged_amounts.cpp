#include <pkr_units/si_units.h>

int main()
{
    using namespace pkr::units;

    // different non-void tags (byte vs flop) must NOT be addable
    byte_t<double> b{1.0};
    flop_t<double> f{1.0};

    auto x = b + f; // should fail to compile
    (void)x;
    return 0;
}
