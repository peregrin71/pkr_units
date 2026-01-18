#pragma once

#include <pkr_units/impl/details/si_unit.h>
#include "../../../../impl/common/dimension.h"
#include "../../../namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Conductance dimension: S = A²·s³·kg⁻¹·m⁻²
inline constexpr dimension_t conductance_dimension{.length = -2, .mass = -1, .time = 3, .current = 2};

// Strong type for siemens (SI base unit)
struct siemens final : public unit_t<double, std::ratio<1, 1>, conductance_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, conductance_dimension>;
    using _base::_base;
    constexpr std::string_view name{"siemens"};
    constexpr std::string_view symbol{"S"};
    constexpr std::wstring_view w_symbol{L"S"};
    constexpr std::u8string_view u8_symbol{u8"S"};
};

// Strong type for millisiemens
struct millisiemens final : public unit_t<double, std::ratio<1, 1000>, conductance_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, conductance_dimension>;
    using _base::_base;
    constexpr std::string_view name{"millisiemens"};
    constexpr std::string_view symbol{"mS"};
    constexpr std::wstring_view w_symbol{L"mS"};
    constexpr std::u8string_view u8_symbol{u8"mS"};
};

// Strong type for microsiemens
struct microsiemens final : public unit_t<double, std::ratio<1, 1000000>, conductance_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, conductance_dimension>;
    using _base::_base;
    constexpr std::string_view name{"microsiemens"};
    constexpr std::string_view symbol{"µS"};
    constexpr std::wstring_view w_symbol{L"µS"};
    constexpr std::u8string_view u8_symbol{u8"µS"};
};

} // PKR_UNITS_NAMESPACE


