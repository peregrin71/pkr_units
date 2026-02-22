#include <pkr_units/si_units.h>

int main()
{
    using namespace pkr::units;
    meter_t<double> distance(1.0);
    second_t<double> time(1.0);

    // should fail with our concise diagnostic from unit_t_operators.h
    auto value = distance + time;
    (void)value;
    return 0;
}
