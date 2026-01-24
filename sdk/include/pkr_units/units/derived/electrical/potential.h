#pragma once

#include <pkr_units/impl/unit_impl.h>
#include "../../../../../impl/dimension.h"
#include "../../../namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Electric potential dimension
inline constexpr dimension_t electric_potential_dimension{2, 1, -3, -1, 0, 0, 0, 0};

// Strong type for volt (SI base unit)
struct volt final : public unit_t<double, std::ratio<1, 1>, electric_potential_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, electric_potential_dimension>;
    using _base::_base;
    constexpr std::string_view name{"volt"};
    constexpr std::string_view symbol{"V"};
    constexpr std::wstring_view w_symbol{L"V"};
    constexpr std::u8string_view u8_symbol{u8"V"};
};

// Strong type for kilovolt
struct kilovolt final : public unit_t<double, std::ratio<1000, 1>, electric_potential_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, electric_potential_dimension>;
    using _base::_base;
    constexpr std::string_view name{"kilovolt"};
    constexpr std::string_view symbol{"kV"};
    constexpr std::wstring_view w_symbol{L"kV"};
    constexpr std::u8string_view u8_symbol{u8"kV"};
};

// Strong type for megavolt
struct megavolt final : public unit_t<double, std::ratio<1000000, 1>, electric_potential_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, electric_potential_dimension>;
    using _base::_base;
    constexpr std::string_view name{"megavolt"};
    constexpr std::string_view symbol{"MV"};
    constexpr std::wstring_view w_symbol{L"MV"};
    constexpr std::u8string_view u8_symbol{u8"MV"};
};

// Strong type for millivolt
struct millivolt final : public unit_t<double, std::ratio<1, 1000>, electric_potential_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, electric_potential_dimension>;
    using _base::_base;
    constexpr std::string_view name{"millivolt"};
    constexpr std::string_view symbol{"mV"};
    constexpr std::wstring_view w_symbol{L"mV"};
    constexpr std::u8string_view u8_symbol{u8"mV"};
};

// Strong type for microvolt
struct microvolt final : public unit_t<double, std::ratio<1, 1000000>, electric_potential_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, electric_potential_dimension>;
    using _base::_base;
    constexpr std::string_view name{"microvolt"};
    constexpr std::string_view symbol{"µV"};
    constexpr std::wstring_view w_symbol{L"µV"};
    constexpr std::u8string_view u8_symbol{u8"µV"};
};

} // PKR_UNITS_NAMESPACE








