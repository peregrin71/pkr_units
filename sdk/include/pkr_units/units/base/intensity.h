#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/intensity_decl.h>

PKR_UNITS_BEGIN_NAMESPACE
{

// Strong type for candela (SI base unit)
struct candela_t final : public details::unit_t<double, std::ratio<1, 1>, intensity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"candela"};
    static constexpr std::string_view symbol{"cd"};
    static constexpr std::wstring_view w_symbol{L"cd"};
    static constexpr std::u8string_view u8_symbol{u8"cd"};
};

// Metric intensity prefixes (strong types)
struct millicandela_t final : public details::unit_t<double, std::milli, intensity_dimension>
{
    using _base = details::unit_t<double, std::milli, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millicandela"};
    static constexpr std::string_view symbol{"mcd"};
    static constexpr std::wstring_view w_symbol{L"mcd"};
    static constexpr std::u8string_view u8_symbol{u8"mcd"};
};

struct microcandela_t final : public details::unit_t<double, std::micro, intensity_dimension>
{
    using _base = details::unit_t<double, std::micro, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microcandela"};
    static constexpr std::string_view symbol{"ucd"};
    static constexpr std::wstring_view w_symbol{L"µcd"};
    static constexpr std::u8string_view u8_symbol{u8"µcd"};
};

struct nanocandela_t final : public details::unit_t<double, std::nano, intensity_dimension>
{
    using _base = details::unit_t<double, std::nano, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanocandela"};
    static constexpr std::string_view symbol{"ncd"};
    static constexpr std::wstring_view w_symbol{L"ncd"};
    static constexpr std::u8string_view u8_symbol{u8"ncd"};
};

struct kilocandela_t final : public details::unit_t<double, std::kilo, intensity_dimension>
{
    using _base = details::unit_t<double, std::kilo, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilocandela"};
    static constexpr std::string_view symbol{"kcd"};
    static constexpr std::wstring_view w_symbol{L"kcd"};
    static constexpr std::u8string_view u8_symbol{u8"kcd"};
};

// ============================================================================
// Most derived unit type specializations for intensity units
// ============================================================================

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1>, intensity_dimension>
{
    using type = candela_t;
};

template<>
struct details::named_unit_type_t<double, std::milli, intensity_dimension>
{
    using type = millicandela_t;
};

template<>
struct details::named_unit_type_t<double, std::micro, intensity_dimension>
{
    using type = microcandela_t;
};

template<>
struct details::named_unit_type_t<double, std::nano, intensity_dimension>
{
    using type = nanocandela_t;
};

template<>
struct details::named_unit_type_t<double, std::kilo, intensity_dimension>
{
    using type = kilocandela_t;
};

}  // namespace PKR_UNITS_NAMESPACE






