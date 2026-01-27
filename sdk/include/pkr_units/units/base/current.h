#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/current_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Strong type for ampere (SI base unit)
struct ampere_t final : public details::unit_t<double, std::ratio<1, 1>, current_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"ampere"};
    static constexpr std::string_view symbol{"A"};
    static constexpr std::wstring_view w_symbol{L"A"};
    static constexpr std::u8string_view u8_symbol{u8"A"};
};

// Metric current prefixes (strong types)
struct milliampere_t final : public details::unit_t<double, std::milli, current_dimension>
{
    using _base = details::unit_t<double, std::milli, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"milliampere"};
    static constexpr std::string_view symbol{"mA"};
    static constexpr std::wstring_view w_symbol{L"mA"};
    static constexpr std::u8string_view u8_symbol{u8"mA"};
};

struct microampere_t final : public details::unit_t<double, std::micro, current_dimension>
{
    using _base = details::unit_t<double, std::micro, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microampere"};
    static constexpr std::string_view symbol{"uA"};
    static constexpr std::wstring_view w_symbol{L"µA"};
    static constexpr std::u8string_view u8_symbol{u8"µA"};
};

struct nanoampere_t final : public details::unit_t<double, std::nano, current_dimension>
{
    using _base = details::unit_t<double, std::nano, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanoampere"};
    static constexpr std::string_view symbol{"nA"};
    static constexpr std::wstring_view w_symbol{L"nA"};
    static constexpr std::u8string_view u8_symbol{u8"nA"};
};

struct kiloampere_t final : public details::unit_t<double, std::kilo, current_dimension>
{
    using _base = details::unit_t<double, std::kilo, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kiloampere"};
    static constexpr std::string_view symbol{"kA"};
    static constexpr std::wstring_view w_symbol{L"kA"};
    static constexpr std::u8string_view u8_symbol{u8"kA"};
};

// ============================================================================
// Most derived unit type specializations for current units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, current_dimension>
{
    using type = ampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::milli, current_dimension>
{
    using type = milliampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::micro, current_dimension>
{
    using type = microampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::nano, current_dimension>
{
    using type = nanoampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::kilo, current_dimension>
{
    using type = kiloampere_t;
};

} // namespace PKR_UNITS_NAMESPACE
