#pragma once
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/unit_impl.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/decls/concentration_decl.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/dimension.h"

namespace PKR_UNITS_NAMESPACE
{
// Molar concentration units (amount of substance per volume)
// Base unit: mole per cubic meter (mol/m^3)
template <is_unit_value_type_c T>
struct mole_per_cubic_meter_concentration_t final : public details::unit_t<T, std::ratio<1, 1>, molar_concentration_v>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, molar_concentration_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"mole_per_cubic_meter_concentration"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mol/m^3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mol\u00B7m\u207B\u00B3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mol\u00B7m\u207B\u00B3"};
};

template <is_unit_value_type_c T>
mole_per_cubic_meter_concentration_t(T) -> mole_per_cubic_meter_concentration_t<T>;

template <is_unit_value_type_c T>
struct mole_per_liter_concentration_t final : public details::unit_t<T, std::ratio<1000, 1>, molar_concentration_v>
{
    using _base = details::unit_t<T, std::ratio<1000, 1>, molar_concentration_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"mole_per_liter_concentration"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mol/L"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mol\u00B7L\u207B\u00B9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mol\u00B7L\u207B\u00B9"};
};

template <is_unit_value_type_c T>
mole_per_liter_concentration_t(T) -> mole_per_liter_concentration_t<T>;

template <is_unit_value_type_c T>
struct molar_concentration_t final : public details::unit_t<T, std::ratio<1000, 1>, molar_concentration_v>
{
    using _base = details::unit_t<T, std::ratio<1000, 1>, molar_concentration_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"molar_concentration"};
    [[maybe_unused]] static constexpr std::string_view symbol{"M"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"M"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"M"};
};

template <is_unit_value_type_c T>
molar_concentration_t(T) -> molar_concentration_t<T>;

template <is_unit_value_type_c T>
struct millimolar_concentration_t final : public details::unit_t<T, std::ratio<1, 1>, molar_concentration_v>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, molar_concentration_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"millimolar_concentration"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mM"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mM"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mM"};
};

template <is_unit_value_type_c T>
millimolar_concentration_t(T) -> millimolar_concentration_t<T>;

template <is_unit_value_type_c T>
struct micromolar_concentration_t final : public details::unit_t<T, std::ratio<1, 1000>, molar_concentration_v>
{
    using _base = details::unit_t<T, std::ratio<1, 1000>, molar_concentration_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"micromolar_concentration"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uM"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5M"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5M"};
};

template <is_unit_value_type_c T>
micromolar_concentration_t(T) -> micromolar_concentration_t<T>;

template <is_unit_value_type_c T>
struct nanomolar_concentration_t final : public details::unit_t<T, std::ratio<1, 1000000>, molar_concentration_v>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000>, molar_concentration_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nanomolar_concentration"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nM"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nM"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nM"};
};

template <is_unit_value_type_c T>
nanomolar_concentration_t(T) -> nanomolar_concentration_t<T>;

template <is_unit_value_type_c T>
struct picomolar_concentration_t final : public details::unit_t<T, std::ratio<1, 1000000000>, molar_concentration_v>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000000>, molar_concentration_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"picomolar_concentration"};
    [[maybe_unused]] static constexpr std::string_view symbol{"pM"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pM"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pM"};
};

template <is_unit_value_type_c T>
picomolar_concentration_t(T) -> picomolar_concentration_t<T>;

template <is_unit_value_type_c T>
struct mole_per_cubic_centimeter_concentration_t final : public details::unit_t<T, std::ratio<1000000, 1>, molar_concentration_v>
{
    using _base = details::unit_t<T, std::ratio<1000000, 1>, molar_concentration_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"mole_per_cubic_centimeter_concentration"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mol/cm^3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mol\u00B7cm\u207B\u00B3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mol\u00B7cm\u207B\u00B3"};
};

template <is_unit_value_type_c T>
mole_per_cubic_centimeter_concentration_t(T) -> mole_per_cubic_centimeter_concentration_t<T>;

template <is_unit_value_type_c T>
struct mole_per_milliliter_concentration_t final : public details::unit_t<T, std::ratio<1000000, 1>, molar_concentration_v>
{
    using _base = details::unit_t<T, std::ratio<1000000, 1>, molar_concentration_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"mole_per_milliliter_concentration"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mol/mL"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mol\u00B7mL\u207B\u00B9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mol\u00B7mL\u207B\u00B9"};
};

template <is_unit_value_type_c T>
mole_per_milliliter_concentration_t(T) -> mole_per_milliliter_concentration_t<T>;

// Osmolarity units (moles of osmotically active particles per liter)
template <is_unit_value_type_c T>
struct osmole_per_liter_concentration_t final : public details::unit_t<T, std::ratio<1000, 1>, molar_concentration_v>
{
    using _base = details::unit_t<T, std::ratio<1000, 1>, molar_concentration_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"osmole_per_liter_concentration"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Osm/L"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Osm\u00B7L\u207B\u00B9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Osm\u00B7L\u207B\u00B9"};
};

template <is_unit_value_type_c T>
osmole_per_liter_concentration_t(T) -> osmole_per_liter_concentration_t<T>;

template <is_unit_value_type_c T>
struct milliosmole_per_liter_concentration_t final : public details::unit_t<T, std::ratio<1, 1>, molar_concentration_v>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, molar_concentration_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"milliosmole_per_liter_concentration"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mOsm/L"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mOsm\u00B7L\u207B\u00B9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mOsm\u00B7L\u207B\u00B9"};
};

template <is_unit_value_type_c T>
milliosmole_per_liter_concentration_t(T) -> milliosmole_per_liter_concentration_t<T>;

// ============================================================================
// Most derived unit type specializations for concentration units
// ============================================================================
// Molar concentration units (templated mapping)
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000, 1>, molar_concentration_v>
{
    using type = mole_per_liter_concentration_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, molar_concentration_v>
{
    using type = millimolar_concentration_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000>, molar_concentration_v>
{
    using type = micromolar_concentration_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000>, molar_concentration_v>
{
    using type = nanomolar_concentration_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000000, 1>, molar_concentration_v>
{
    using type = mole_per_cubic_centimeter_concentration_t<T>;
};

// Explicit double instantiations
template <>
struct details::derived_unit_type_t<double, std::ratio<1000, 1>, molar_concentration_v>
{
    using type = mole_per_liter_concentration_t<double>;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, molar_concentration_v>
{
    using type = millimolar_concentration_t<double>;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, molar_concentration_v>
{
    using type = micromolar_concentration_t<double>;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, molar_concentration_v>
{
    using type = nanomolar_concentration_t<double>;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000, 1>, molar_concentration_v>
{
    using type = mole_per_cubic_centimeter_concentration_t<double>;
};
} // namespace PKR_UNITS_NAMESPACE
