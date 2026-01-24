#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/concentration_decl.h>
#include <pkr_units/impl/dimension.h>

PKR_UNITS_BEGIN_NAMESPACE
{

// Molar concentration quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using molar_concentration_unit_t = details::unit_t<type_t, ratio_t, molar_concentration_v>;

// Molar concentration units (amount of substance per volume)

// Base unit: mole per cubic meter (mol/m³)
struct mole_per_cubic_meter_concentration_t final : public details::unit_t<double, std::ratio<1, 1>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"mole_per_cubic_meter_concentration"};
    static constexpr std::string_view symbol{"mol/m^3"};
    static constexpr std::wstring_view w_symbol{L"mol/m³"};
    static constexpr std::u8string_view u8_symbol{u8"mol/m³"};
};

struct mole_per_liter_concentration_t final : public details::unit_t<double, std::ratio<1000, 1>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"mole_per_liter_concentration"};
    static constexpr std::string_view symbol{"mol/L"};
    static constexpr std::wstring_view w_symbol{L"mol/L"};
    static constexpr std::u8string_view u8_symbol{u8"mol/L"};
};

struct molar_concentration_t final : public details::unit_t<double, std::ratio<1000, 1>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"molar_concentration"};
    static constexpr std::string_view symbol{"M"};
    static constexpr std::wstring_view w_symbol{L"M"};
    static constexpr std::u8string_view u8_symbol{u8"M"};
};

struct millimolar_concentration_t final : public details::unit_t<double, std::ratio<1, 1>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"millimolar_concentration"};
    static constexpr std::string_view symbol{"mM"};
    static constexpr std::wstring_view w_symbol{L"mM"};
    static constexpr std::u8string_view u8_symbol{u8"mM"};
};

struct micromolar_concentration_t final : public details::unit_t<double, std::ratio<1, 1000>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"micromolar_concentration"};
    static constexpr std::string_view symbol{"uM"};
    static constexpr std::wstring_view w_symbol{L"µM"};
    static constexpr std::u8string_view u8_symbol{u8"µM"};
};

struct nanomolar_concentration_t final : public details::unit_t<double, std::ratio<1, 1000000>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"nanomolar_concentration"};
    static constexpr std::string_view symbol{"nM"};
    static constexpr std::wstring_view w_symbol{L"nM"};
    static constexpr std::u8string_view u8_symbol{u8"nM"};
};

struct picomolar_concentration_t final : public details::unit_t<double, std::ratio<1, 1000000000>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"picomolar_concentration"};
    static constexpr std::string_view symbol{"pM"};
    static constexpr std::wstring_view w_symbol{L"pM"};
    static constexpr std::u8string_view u8_symbol{u8"pM"};
};

struct mole_per_cubic_centimeter_concentration_t final : public details::unit_t<double, std::ratio<1000000, 1>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"mole_per_cubic_centimeter_concentration"};
    static constexpr std::string_view symbol{"mol/cm^3"};
    static constexpr std::wstring_view w_symbol{L"mol/cm³"};
    static constexpr std::u8string_view u8_symbol{u8"mol/cm³"};
};

struct mole_per_milliliter_concentration_t final : public details::unit_t<double, std::ratio<1000000, 1>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"mole_per_milliliter_concentration"};
    static constexpr std::string_view symbol{"mol/mL"};
    static constexpr std::wstring_view w_symbol{L"mol/mL"};
    static constexpr std::u8string_view u8_symbol{u8"mol/mL"};
};

// Osmolarity units (moles of osmotically active particles per liter)
struct osmole_per_liter_concentration_t final : public details::unit_t<double, std::ratio<1000, 1>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"osmole_per_liter_concentration"};
    static constexpr std::string_view symbol{"Osm/L"};
    static constexpr std::wstring_view w_symbol{L"Osm/L"};
    static constexpr std::u8string_view u8_symbol{u8"Osm/L"};
};

struct milliosmole_per_liter_concentration_t final : public details::unit_t<double, std::ratio<1, 1>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"milliosmole_per_liter_concentration"};
    static constexpr std::string_view symbol{"mOsm/L"};
    static constexpr std::wstring_view w_symbol{L"mOsm/L"};
    static constexpr std::u8string_view u8_symbol{u8"mOsm/L"};
};

// ============================================================================
// Most derived unit type specializations for concentration units
// ============================================================================

// Molar concentration units
template<>
struct details::named_unit_type_t<double, std::ratio<1000, 1>, molar_concentration_v>
{
    using type = mole_per_liter_concentration_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1>, molar_concentration_v>
{
    using type = millimolar_concentration_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000>, molar_concentration_v>
{
    using type = micromolar_concentration_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000>, molar_concentration_v>
{
    using type = nanomolar_concentration_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000000, 1>, molar_concentration_v>
{
    using type = mole_per_cubic_centimeter_concentration_t;
};

} // PKR_UNITS_NAMESPACE















