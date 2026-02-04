#pragma once
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/unit_impl.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/dimension.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"

namespace PKR_UNITS_NAMESPACE
{
// Capacitance dimension
inline constexpr dimension_t capacitance_v{-2, -1, 4, 2, 0, 0, 0, 0};

// Capacitance units (Farad and derived)
template <is_unit_value_type_c T>
struct farad_t final : public details::unit_t<T, std::ratio<1, 1>, capacitance_v>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, capacitance_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"farad"};
    [[maybe_unused]] static constexpr std::string_view symbol{"F"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"F"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"F"};
};

template <is_unit_value_type_c T>
farad_t(T) -> farad_t<T>;

template <is_unit_value_type_c T>
struct millifarad_t final : public details::unit_t<T, std::ratio<1, 1000>, capacitance_v>
{
    using _base = details::unit_t<T, std::ratio<1, 1000>, capacitance_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"millifarad"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mF"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mF"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mF"};
};

template <is_unit_value_type_c T>
millifarad_t(T) -> millifarad_t<T>;

template <is_unit_value_type_c T>
struct microfarad_t final : public details::unit_t<T, std::ratio<1, 1000000>, capacitance_v>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000>, capacitance_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"microfarad"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uF"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5F"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5F"};
};

template <is_unit_value_type_c T>
microfarad_t(T) -> microfarad_t<T>;

template <is_unit_value_type_c T>
struct nanofarad_t final : public details::unit_t<T, std::ratio<1, 1000000000>, capacitance_v>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000000>, capacitance_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nanofarad"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nF"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nF"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nF"};
};

template <is_unit_value_type_c T>
nanofarad_t(T) -> nanofarad_t<T>;

template <is_unit_value_type_c T>
struct picofarad_t final : public details::unit_t<T, std::ratio<1, 1000000000000>, capacitance_v>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000000000>, capacitance_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"picofarad"};
    [[maybe_unused]] static constexpr std::string_view symbol{"pF"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pF"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pF"};
};

template <is_unit_value_type_c T>
picofarad_t(T) -> picofarad_t<T>;

// ============================================================================
// Most derived unit type specializations for capacitance units
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, capacitance_v>
{
    using type = farad_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000>, capacitance_v>
{
    using type = millifarad_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000>, capacitance_v>
{
    using type = microfarad_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000000>, capacitance_v>
{
    using type = nanofarad_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000000000>, capacitance_v>
{
    using type = picofarad_t<T>;
};

// Explicit double instantiations for ABI / UDL stability
template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, capacitance_v>
{
    using type = farad_t<double>;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, capacitance_v>
{
    using type = millifarad_t<double>;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, capacitance_v>
{
    using type = microfarad_t<double>;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000>, capacitance_v>
{
    using type = nanofarad_t<double>;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000000>, capacitance_v>
{
    using type = picofarad_t<double>;
};
} // namespace PKR_UNITS_NAMESPACE
