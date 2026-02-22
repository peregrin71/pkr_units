#include <pkr_units/si_units.h>

int main()
{
    using namespace pkr::units;

    // Constructing a meter from a second should trigger concise meter_t diagnostic
    second_t<double> s{1.0};
    meter_t<double> m{s}; // expected failure: "meter_t: expected a length unit"
    (void)m;
    return 0;
}
