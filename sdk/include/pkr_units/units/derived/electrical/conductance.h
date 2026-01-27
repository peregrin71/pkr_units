#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// Conductance dimension: S = A²·s³·kg⁻¹·m⁻²
inline constexpr dimension_t conductance_dimension{.length = -2, .mass = -1, .time = 3, .current = 2};

// Strong type for siemens (SI base unit)
struct siemens final : public details::unit_t<double, std::ratio<1, 1>, conductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, conductance_dimension>;
    using _base::_base;
    const std::string_view name{"siemens"};
    const std::string_view symbol{"S"};
    const std::wstring_view w_symbol{L"S"};
    const std::u8string_view u8_symbol{u8"S"};
};

// Strong type for millisiemens
struct millisiemens final : public details::unit_t<double, std::ratio<1, 1000>, conductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, conductance_dimension>;
    using _base::_base;
    const std::string_view name{"millisiemens"};
    const std::string_view symbol{"mS"};
    const std::wstring_view w_symbol{L"mS"};
    const std::u8string_view u8_symbol{u8"mS"};
};

// Strong type for microsiemens
struct microsiemens final : public details::unit_t<double, std::ratio<1, 1000000>, conductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, conductance_dimension>;
    using _base::_base;
    const std::string_view name{"microsiemens"};
    const std::string_view symbol{"µS"};
    const std::wstring_view w_symbol{L"µS"};
    const std::u8string_view u8_symbol{u8"µS"};
};

} // namespace PKR_UNITS_NAMESPACE
