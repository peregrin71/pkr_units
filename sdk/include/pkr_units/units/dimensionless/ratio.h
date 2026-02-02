#pragma once

#include <ratio>
#include <string_view>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{

// Dimensionless ratio (1.0 == 1:1)
struct ratio_t final : public details::unit_t<double, std::ratio<1, 1>, scalar_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, scalar_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"ratio"};

    [[maybe_unused]] static constexpr std::string_view symbol{"ratio"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ratio"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ratio"};
};

// Percentage (100% == 1.0 ratio)
struct percentage_t final : public details::unit_t<double, std::ratio<1, 100>, scalar_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 100>, scalar_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"percent"};

    [[maybe_unused]] static constexpr std::string_view symbol{"%"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"%"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"%"};
};

} // namespace PKR_UNITS_NAMESPACE
