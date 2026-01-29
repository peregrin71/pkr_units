#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/acceleration_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// CGS acceleration unit (formatting-friendly, not a derived-unit mapping)
// Gal (cm/s^2) = 0.01 m/s^2
struct gal_t final : public details::unit_t<double, std::ratio<1, 100>, acceleration_v>
{
    using _base = details::unit_t<double, std::ratio<1, 100>, acceleration_v>;
    using _base::_base;
    static constexpr std::string_view name{"gal"};
    static constexpr std::string_view symbol{"Gal"};
    static constexpr std::wstring_view w_symbol{L"Gal"};
    static constexpr std::u8string_view u8_symbol{u8"Gal"};
};

} // namespace PKR_UNITS_NAMESPACE
