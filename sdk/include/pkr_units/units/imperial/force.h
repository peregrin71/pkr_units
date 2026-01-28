#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/units/derived/mechanical/force.h>

namespace PKR_UNITS_NAMESPACE
{

// Imperial force units
struct poundal_t final : public details::unit_t<double, std::ratio<45359237, 1000000000>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<45359237, 1000000000>, force_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"poundal"};
    static constexpr std::string_view symbol{"pdl"};
    static constexpr std::wstring_view w_symbol{L"pdl"};
    static constexpr std::u8string_view u8_symbol{u8"pdl"};
};

struct pound_force_t final : public details::unit_t<double, std::ratio<4448222, 1000000>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<4448222, 1000000>, force_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"pound_force"};
    static constexpr std::string_view symbol{"lbf"};
    static constexpr std::wstring_view w_symbol{L"lbf"};
    static constexpr std::u8string_view u8_symbol{u8"lbf"};
};

} // namespace PKR_UNITS_NAMESPACE
