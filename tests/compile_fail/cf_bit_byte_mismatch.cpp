#include <pkr_units/si_units.h>

int main()
{
    using namespace pkr::units;

    byte_t<double> b{1.0};
    bit_t<double> bits{8.0};

    // bytes and bits use different tags; addition should fail without an explicit cast
    auto x = b + bits; // expected compilation failure
    (void)x;
    return 0;
}
