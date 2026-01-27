#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// Electric charge dimension: A·s
inline constexpr dimension_t electric_charge_dimension{0, 0, 1, 1, 0, 0, 0, 0};

// Strong type for coulomb (SI base unit)
struct coulomb final : public details::unit_t<double, std::ratio<1, 1>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, electric_charge_dimension>;
    using _base::_base;
    const std::string_view name{"coulomb"};
    const std::string_view symbol{"C"};
    const std::wstring_view w_symbol{L"C"};
    const std::u8string_view u8_symbol{u8"C"};
};

// Strong type for kilocoulomb
struct kilocoulomb final : public details::unit_t<double, std::ratio<1000, 1>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, electric_charge_dimension>;
    using _base::_base;
    const std::string_view name{"kilocoulomb"};
    const std::string_view symbol{"kC"};
    const std::wstring_view w_symbol{L"kC"};
    const std::u8string_view u8_symbol{u8"kC"};
};

// Strong type for millicoulomb
struct millicoulomb final : public details::unit_t<double, std::ratio<1, 1000>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, electric_charge_dimension>;
    using _base::_base;
    const std::string_view name{"millicoulomb"};
    const std::string_view symbol{"mC"};
    const std::wstring_view w_symbol{L"mC"};
    const std::u8string_view u8_symbol{u8"mC"};
};

// Strong type for microcoulomb
struct microcoulomb final : public details::unit_t<double, std::ratio<1, 1000000>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, electric_charge_dimension>;
    using _base::_base;
    const std::string_view name{"microcoulomb"};
    const std::string_view symbol{"µC"};
    const std::wstring_view w_symbol{L"µC"};
    const std::u8string_view u8_symbol{u8"µC"};
};

// Strong type for nanocoulomb
struct nanocoulomb final : public details::unit_t<double, std::ratio<1, 1000000000>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, electric_charge_dimension>;
    using _base::_base;
    const std::string_view name{"nanocoulomb"};
    const std::string_view symbol{"nC"};
    const std::wstring_view w_symbol{L"nC"};
    const std::u8string_view u8_symbol{u8"nC"};
};

// Strong type for picocoulomb
struct picocoulomb final : public details::unit_t<double, std::ratio<1, 1000000000000>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000000>, electric_charge_dimension>;
    using _base::_base;
    const std::string_view name{"picocoulomb"};
    const std::string_view symbol{"pC"};
    const std::wstring_view w_symbol{L"pC"};
    const std::u8string_view u8_symbol{u8"pC"};
};

} // namespace PKR_UNITS_NAMESPACE
