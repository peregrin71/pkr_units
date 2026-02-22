#include <pkr_units/si_units.h>

int main()
{
    using namespace pkr::units;

    // Direct use of unit_t to exercise the diagnostic constructor we added
    pkr::units::unit_t<double, std::ratio<1, 1>, length_dimension> a{1.0};
    pkr::units::unit_t<double, std::ratio<1, 1>, time_dimension> b{1.0};

    // Should trigger the unit_t diagnostic: cannot construct from different-dimension unit
    auto c = pkr::units::unit_t<double, std::ratio<1, 1>, length_dimension>(b);
    (void)c;
    return 0;
}
