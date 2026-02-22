#include <pkr_units/si_units.h>

int main()
{
    using namespace pkr::units;
    meter_t<double> m(4.0);

    // should fail with concise sqrt() diagnostic (meter has odd exponent)
    auto v = sqrt(m);
    (void)v;
    return 0;
}
