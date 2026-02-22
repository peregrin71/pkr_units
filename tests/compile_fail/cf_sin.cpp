#include <pkr_units/si_units.h>

int main()
{
    using namespace pkr::units;
    meter_t<double> m(1.0);

    // should fail with concise sin() diagnostic (requires angle unit)
    auto v = sin(m);
    (void)v;
    return 0;
}
