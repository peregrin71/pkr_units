#pragma once

#include "../../impl/namespace_config.h"
#include "../../impl/unit_impl.h"
#include "../../impl/decls/temperature_decl.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Strong type for kelvin (SI base unit)
struct kelvin_t final : public details::unit_t<double, std::ratio<1, 1>, temperature_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kelvin"};
    static constexpr std::string_view symbol{"K"};
    static constexpr std::wstring_view w_symbol{L"K"};
    static constexpr std::u8string_view u8_symbol{u8"K"};
};

// Metric temperature prefixes (strong types)
struct millikelvin_t final : public details::unit_t<double, std::milli, temperature_dimension>
{
    using _base = details::unit_t<double, std::milli, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millikelvin"};
    static constexpr std::string_view symbol{"mK"};
    static constexpr std::wstring_view w_symbol{L"mK"};
    static constexpr std::u8string_view u8_symbol{u8"mK"};
};

struct microkelvin_t final : public details::unit_t<double, std::micro, temperature_dimension>
{
    using _base = details::unit_t<double, std::micro, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microkelvin"};
    static constexpr std::string_view symbol{"uK"};
    static constexpr std::wstring_view w_symbol{L"µK"};
    static constexpr std::u8string_view u8_symbol{u8"µK"};
};

struct nanokelvin_t final : public details::unit_t<double, std::nano, temperature_dimension>
{
    using _base = details::unit_t<double, std::nano, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanokelvin"};
    static constexpr std::string_view symbol{"nK"};
    static constexpr std::wstring_view w_symbol{L"nK"};
    static constexpr std::u8string_view u8_symbol{u8"nK"};
};

struct kilokelvin_t final : public details::unit_t<double, std::kilo, temperature_dimension>
{
    using _base = details::unit_t<double, std::kilo, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilokelvin"};
    static constexpr std::string_view symbol{"kK"};
    static constexpr std::wstring_view w_symbol{L"kK"};
    static constexpr std::u8string_view u8_symbol{u8"kK"};
};

// ============================================================================
// Most derived unit type specializations for temperature units
// ============================================================================

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1>, temperature_dimension>
{
    using type = kelvin_t;
};

template<>
struct details::named_unit_type_t<double, std::milli, temperature_dimension>
{
    using type = millikelvin_t;
};

template<>
struct details::named_unit_type_t<double, std::micro, temperature_dimension>
{
    using type = microkelvin_t;
};

template<>
struct details::named_unit_type_t<double, std::nano, temperature_dimension>
{
    using type = nanokelvin_t;
};

template<>
struct details::named_unit_type_t<double, std::kilo, temperature_dimension>
{
    using type = kilokelvin_t;
};

}  // namespace PKR_UNITS_NAMESPACE





