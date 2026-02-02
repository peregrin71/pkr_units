#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/units/derived/mechanical/force.h>

namespace PKR_UNITS_NAMESPACE
{

// CGS force unit
// Dyne = 10^-5 newton
struct dyne_t final : public details::unit_t<double, std::ratio<1, 100000>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 100000>, force_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"dyne"};

    [[maybe_unused]] static constexpr std::string_view symbol{"dyn"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dyn"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dyn"};
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 100000>, force_dimension>
{
    using type = dyne_t;
};

} // namespace PKR_UNITS_NAMESPACE
