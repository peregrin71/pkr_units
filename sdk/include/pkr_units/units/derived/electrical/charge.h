#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// Electric charge dimension: A·s
inline constexpr dimension_t electric_charge_dimension{0, 0, 1, 1, 0, 0, 0, 0};

// Electric charge units (Coulomb and derived)
struct coulomb_t final : public details::unit_t<double, std::ratio<1, 1>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"coulomb"};
    static constexpr std::string_view symbol{"C"};
    static constexpr std::wstring_view w_symbol{L"C"};
    static constexpr std::u8string_view u8_symbol{u8"C"};
};

struct kilocoulomb_t final : public details::unit_t<double, std::ratio<1000, 1>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilocoulomb"};
    static constexpr std::string_view symbol{"kC"};
    static constexpr std::wstring_view w_symbol{L"kC"};
    static constexpr std::u8string_view u8_symbol{u8"kC"};
};

struct millicoulomb_t final : public details::unit_t<double, std::ratio<1, 1000>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millicoulomb"};
    static constexpr std::string_view symbol{"mC"};
    static constexpr std::wstring_view w_symbol{L"mC"};
    static constexpr std::u8string_view u8_symbol{u8"mC"};
};

struct microcoulomb_t final : public details::unit_t<double, std::ratio<1, 1000000>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microcoulomb"};
    static constexpr std::string_view symbol{"uC"};
    static constexpr std::wstring_view w_symbol{L"\u00b5C"};
    static constexpr std::u8string_view u8_symbol{u8"\u00b5C"};
};

struct nanocoulomb_t final : public details::unit_t<double, std::ratio<1, 1000000000>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanocoulomb"};
    static constexpr std::string_view symbol{"nC"};
    static constexpr std::wstring_view w_symbol{L"nC"};
    static constexpr std::u8string_view u8_symbol{u8"nC"};
};

struct picocoulomb_t final : public details::unit_t<double, std::ratio<1, 1000000000000>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000000>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"picocoulomb"};
    static constexpr std::string_view symbol{"pC"};
    static constexpr std::wstring_view w_symbol{L"pC"};
    static constexpr std::u8string_view u8_symbol{u8"pC"};
};

// ============================================================================
// Most derived unit type specializations for electric charge units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, electric_charge_dimension>
{
    using type = coulomb_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000, 1>, electric_charge_dimension>
{
    using type = kilocoulomb_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, electric_charge_dimension>
{
    using type = millicoulomb_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, electric_charge_dimension>
{
    using type = microcoulomb_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000>, electric_charge_dimension>
{
    using type = nanocoulomb_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000000>, electric_charge_dimension>
{
    using type = picocoulomb_t;
};

} // namespace PKR_UNITS_NAMESPACE
