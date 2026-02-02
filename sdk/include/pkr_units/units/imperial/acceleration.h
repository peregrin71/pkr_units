#pragma once
#include <string_view>

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/acceleration_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Imperial acceleration units
struct feet_per_second_squared_t final : public details::unit_t<double, std::ratio<3048, 10000>, acceleration_v>
{
    using _base = details::unit_t<double, std::ratio<3048, 10000>, acceleration_v>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"feet per second squared"};

    [[maybe_unused]] static constexpr std::string_view symbol{"ft/s^2"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ft\u00b7s\u207b\u00b2"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ft\u00b7s\u207b\u00b2"};
};

} // namespace PKR_UNITS_NAMESPACE
