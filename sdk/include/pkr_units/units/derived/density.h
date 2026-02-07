#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{
// Density units (mass per volume)
// Base unit: kilogram per cubic meter (kg/mÂ³)
template <is_unit_value_type_c T>
struct kilogram_per_cubic_meter_t final : public details::unit_t<T, std::ratio<1, 1>, density_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilogram per cubic meter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kg/m^3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kg\u00B7m\u207B\u00B3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kg\u00B7m\u207B\u00B3"};
};

template <is_unit_value_type_c T>
kilogram_per_cubic_meter_t(T) -> kilogram_per_cubic_meter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == density_dimension)
kilogram_per_cubic_meter_t(const U&) -> kilogram_per_cubic_meter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct gram_per_cubic_meter_t final : public details::unit_t<T, std::ratio<1, 1000>, density_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000>, density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gram_per_cubic_meter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"g/m^3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"g\u00B7m\u207B\u00B3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"g\u00B7m\u207B\u00B3"};
};

template <is_unit_value_type_c T>
gram_per_cubic_meter_t(T) -> gram_per_cubic_meter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == density_dimension)
gram_per_cubic_meter_t(const U&) -> gram_per_cubic_meter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct gram_per_cubic_centimeter_t final : public details::unit_t<T, std::ratio<1000000, 1>, density_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000000, 1>, density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gram_per_cubic_centimeter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"g/cm^3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"g\u00B7cm\u207B\u00B3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"g\u00B7cm\u207B\u00B3"};
};

template <is_unit_value_type_c T>
gram_per_cubic_centimeter_t(T) -> gram_per_cubic_centimeter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == density_dimension)
gram_per_cubic_centimeter_t(const U&) -> gram_per_cubic_centimeter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct gram_per_milliliter_t final : public details::unit_t<T, std::ratio<1000000, 1>, density_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000000, 1>, density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gram_per_milliliter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"g/mL"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"g\u00B7mL\u207B\u00B9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"g\u00B7mL\u207B\u00B9"};
};

template <is_unit_value_type_c T>
gram_per_milliliter_t(T) -> gram_per_milliliter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == density_dimension)
gram_per_milliliter_t(const U&) -> gram_per_milliliter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct kilogram_per_liter_t final : public details::unit_t<T, std::ratio<1000, 1>, density_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000, 1>, density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilogram_per_liter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kg/L"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kg\u00B7L\u207B\u00B9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kg\u00B7L\u207B\u00B9"};
};

template <is_unit_value_type_c T>
kilogram_per_liter_t(T) -> kilogram_per_liter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == density_dimension)
kilogram_per_liter_t(const U&) -> kilogram_per_liter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct gram_per_liter_t final : public details::unit_t<T, std::ratio<1, 1>, density_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gram_per_liter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"g/L"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"g\u00B7L\u207B\u00B9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"g\u00B7L\u207B\u00B9"};
};

template <is_unit_value_type_c T>
gram_per_liter_t(T) -> gram_per_liter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == density_dimension)
gram_per_liter_t(const U&) -> gram_per_liter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct milligram_per_cubic_centimeter_t final : public details::unit_t<T, std::ratio<1000, 1>, density_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000, 1>, density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"milligram_per_cubic_centimeter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mg/cm^3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mg\u00B7cm\u207B\u00B3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mg\u00B7cm\u207B\u00B3"};
};

template <is_unit_value_type_c T>
milligram_per_cubic_centimeter_t(T) -> milligram_per_cubic_centimeter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == density_dimension)
milligram_per_cubic_centimeter_t(const U&) -> milligram_per_cubic_centimeter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct milligram_per_milliliter_t final : public details::unit_t<T, std::ratio<1000, 1>, density_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000, 1>, density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"milligram_per_milliliter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mg/mL"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mg\u00B7mL\u207B\u00B9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mg\u00B7mL\u207B\u00B9"};
};

template <is_unit_value_type_c T>
milligram_per_milliliter_t(T) -> milligram_per_milliliter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == density_dimension)
milligram_per_milliliter_t(const U&) -> milligram_per_milliliter_t<typename details::is_pkr_unit<U>::value_type>;

// Other common density units
template <is_unit_value_type_c T>
struct ton_per_cubic_meter_t final : public details::unit_t<T, std::ratio<1000000, 1>, density_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000000, 1>, density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"ton_per_cubic_meter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"t/m^3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"t\u00B7m\u207B\u00B3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"t\u00B7m\u207B\u00B3"};
};

template <is_unit_value_type_c T>
ton_per_cubic_meter_t(T) -> ton_per_cubic_meter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == density_dimension)
ton_per_cubic_meter_t(const U&) -> ton_per_cubic_meter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct atomic_mass_unit_per_cubic_angstrom_t final : public details::unit_t<T, std::ratio<166054, 1>, density_dimension>
{
    using _base = details::unit_t<T, std::ratio<166054, 1>, density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"atomic_mass_unit_per_cubic_angstrom"};
    [[maybe_unused]] static constexpr std::string_view symbol{"u/A^3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"u\u00B7\u00C5\u207B\u00B3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"u\u00B7\u00C5\u207B\u00B3"};
};

template <is_unit_value_type_c T>
atomic_mass_unit_per_cubic_angstrom_t(T) -> atomic_mass_unit_per_cubic_angstrom_t<T>;

// ============================================================================
// Most derived unit type specializations for density units
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, density_dimension>
{
    using type = kilogram_per_cubic_meter_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000>, density_dimension>
{
    using type = gram_per_cubic_meter_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000000, 1>, density_dimension>
{
    using type = gram_per_cubic_centimeter_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000, 1>, density_dimension>
{
    using type = kilogram_per_liter_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<166054, 1>, density_dimension>
{
    using type = atomic_mass_unit_per_cubic_angstrom_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
