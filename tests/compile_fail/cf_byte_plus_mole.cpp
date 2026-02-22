#include <pkr_units/si_units.h>

int main()
{
    using namespace pkr::units;

    byte_t<double> b{1.0};
    mole_t<double> m{1.0};

    // mixing tagged `byte_t` (byte_tag) with untagged `mole_t` must NOT compile
    auto x = b + m; // expected compilation failure
    (void)x;
    return 0;
}
