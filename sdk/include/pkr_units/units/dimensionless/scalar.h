#pragma once

#include <string_view>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/unit_t_decl.h>

namespace PKR_UNITS_NAMESPACE
{
struct scalar_t final : public details::unit_t<double, std::ratio<1>, scalar_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, scalar_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"scalar"};
    [[maybe_unused]] static constexpr std::string_view symbol{""};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L""};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8""};
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, scalar_dimension>
{
    using type = scalar_t;
};

} // namespace PKR_UNITS_NAMESPACE
