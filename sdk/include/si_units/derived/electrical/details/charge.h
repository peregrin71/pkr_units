#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/impl/details/dimension.h>
#include "../../../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Electric charge dimension: A·s
inline constexpr dimension_t electric_charge_dimension{.current = 1, .time = 1};

// Strong type for coulomb (SI base unit)
struct coulomb final : public unit_t<double, std::ratio<1, 1>, electric_charge_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, electric_charge_dimension>;
    using _base::_base;
    constexpr std::string_view name{"coulomb"};
    constexpr std::string_view symbol{"C"};
    constexpr std::wstring_view w_symbol{L"C"};
    constexpr std::u8string_view u8_symbol{u8"C"};
};

// Strong type for kilocoulomb
struct kilocoulomb final : public unit_t<double, std::ratio<1000, 1>, electric_charge_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, electric_charge_dimension>;
    using _base::_base;
    constexpr std::string_view name{"kilocoulomb"};
    constexpr std::string_view symbol{"kC"};
    constexpr std::wstring_view w_symbol{L"kC"};
    constexpr std::u8string_view u8_symbol{u8"kC"};
};

// Strong type for millicoulomb
struct millicoulomb final : public unit_t<double, std::ratio<1, 1000>, electric_charge_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, electric_charge_dimension>;
    using _base::_base;
    constexpr std::string_view name{"millicoulomb"};
    constexpr std::string_view symbol{"mC"};
    constexpr std::wstring_view w_symbol{L"mC"};
    constexpr std::u8string_view u8_symbol{u8"mC"};
};

// Strong type for microcoulomb
struct microcoulomb final : public unit_t<double, std::ratio<1, 1000000>, electric_charge_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, electric_charge_dimension>;
    using _base::_base;
    constexpr std::string_view name{"microcoulomb"};
    constexpr std::string_view symbol{"µC"};
    constexpr std::wstring_view w_symbol{L"µC"};
    constexpr std::u8string_view u8_symbol{u8"µC"};
};

// Strong type for nanocoulomb
struct nanocoulomb final : public unit_t<double, std::ratio<1, 1000000000>, electric_charge_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, electric_charge_dimension>;
    using _base::_base;
    constexpr std::string_view name{"nanocoulomb"};
    constexpr std::string_view symbol{"nC"};
    constexpr std::wstring_view w_symbol{L"nC"};
    constexpr std::u8string_view u8_symbol{u8"nC"};
};

// Strong type for picocoulomb
struct picocoulomb final : public unit_t<double, std::ratio<1, 1000000000000>, electric_charge_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000000>, electric_charge_dimension>;
    using _base::_base;
    constexpr std::string_view name{"picocoulomb"};
    constexpr std::string_view symbol{"pC"};
    constexpr std::wstring_view w_symbol{L"pC"};
    constexpr std::u8string_view u8_symbol{u8"pC"};
};

} // PKR_SI_NAMESPACE


