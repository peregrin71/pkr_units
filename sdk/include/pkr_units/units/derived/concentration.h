#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/concentration_decl.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{

// Molar concentration units (amount of substance per volume)

// Base unit: mole per cubic meter (mol/m^3)
struct mole_per_cubic_meter_concentration_t final : public details::unit_t<double, std::ratio<1, 1>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, molar_concentration_v>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"mole_per_cubic_meter_concentration"};

    [[maybe_unused]] static constexpr std::string_view symbol{"mol/m^3"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mol·m⁻³"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mol·m⁻³"};
};

struct mole_per_liter_concentration_t final : public details::unit_t<double, std::ratio<1000, 1>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, molar_concentration_v>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"mole_per_liter_concentration"};

    [[maybe_unused]] static constexpr std::string_view symbol{"mol/L"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mol·L⁻¹"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mol·L⁻¹"};
};

struct molar_concentration_t final : public details::unit_t<double, std::ratio<1000, 1>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, molar_concentration_v>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"molar_concentration"};

    [[maybe_unused]] static constexpr std::string_view symbol{"M"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"M"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"M"};
};

struct millimolar_concentration_t final : public details::unit_t<double, std::ratio<1, 1>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, molar_concentration_v>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"millimolar_concentration"};

    [[maybe_unused]] static constexpr std::string_view symbol{"mM"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mM"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mM"};
};

struct micromolar_concentration_t final : public details::unit_t<double, std::ratio<1, 1000>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, molar_concentration_v>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"micromolar_concentration"};

    [[maybe_unused]] static constexpr std::string_view symbol{"uM"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5M"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5M"};
};

struct nanomolar_concentration_t final : public details::unit_t<double, std::ratio<1, 1000000>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, molar_concentration_v>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"nanomolar_concentration"};

    [[maybe_unused]] static constexpr std::string_view symbol{"nM"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nM"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nM"};
};

struct picomolar_concentration_t final : public details::unit_t<double, std::ratio<1, 1000000000>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, molar_concentration_v>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"picomolar_concentration"};

    [[maybe_unused]] static constexpr std::string_view symbol{"pM"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pM"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pM"};
};

struct mole_per_cubic_centimeter_concentration_t final : public details::unit_t<double, std::ratio<1000000, 1>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, molar_concentration_v>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"mole_per_cubic_centimeter_concentration"};

    [[maybe_unused]] static constexpr std::string_view symbol{"mol/cm^3"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mol·cm⁻³"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mol·cm⁻³"};
};

struct mole_per_milliliter_concentration_t final : public details::unit_t<double, std::ratio<1000000, 1>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, molar_concentration_v>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"mole_per_milliliter_concentration"};

    [[maybe_unused]] static constexpr std::string_view symbol{"mol/mL"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mol·mL⁻¹"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mol·mL⁻¹"};
};

// Osmolarity units (moles of osmotically active particles per liter)
struct osmole_per_liter_concentration_t final : public details::unit_t<double, std::ratio<1000, 1>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, molar_concentration_v>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"osmole_per_liter_concentration"};

    [[maybe_unused]] static constexpr std::string_view symbol{"Osm/L"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Osm·L⁻¹"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Osm·L⁻¹"};
};

struct milliosmole_per_liter_concentration_t final : public details::unit_t<double, std::ratio<1, 1>, molar_concentration_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, molar_concentration_v>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"milliosmole_per_liter_concentration"};

    [[maybe_unused]] static constexpr std::string_view symbol{"mOsm/L"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mOsm·L⁻¹"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mOsm·L⁻¹"};
};

// ============================================================================
// Most derived unit type specializations for concentration units
// ============================================================================

// Molar concentration units
template <>
struct details::derived_unit_type_t<double, std::ratio<1000, 1>, molar_concentration_v>
{
    using type = mole_per_liter_concentration_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, molar_concentration_v>
{
    using type = millimolar_concentration_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, molar_concentration_v>
{
    using type = micromolar_concentration_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, molar_concentration_v>
{
    using type = nanomolar_concentration_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000, 1>, molar_concentration_v>
{
    using type = mole_per_cubic_centimeter_concentration_t;
};

} // namespace PKR_UNITS_NAMESPACE
