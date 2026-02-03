#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/units/derived/mechanical/pressure.h>

namespace PKR_UNITS_NAMESPACE
{
// CGS pressure unit
// Barye (Ba) = 0.1 pascal
template <is_unit_value_type_c T>
struct barye_t final : public details::unit_t<T, std::ratio<1, 10>, pressure_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 10>, pressure_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"barye"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Ba"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Ba"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Ba"};
};

template <is_unit_value_type_c T>
barye_t(T) -> barye_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == pressure_dimension)
barye_t(const U&) -> barye_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 10>, pressure_dimension>
{
    using type = barye_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
