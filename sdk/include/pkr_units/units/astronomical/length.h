#pragma once

#include "../../impl/namespace_config.h"
#include "../../impl/decls/length_decl.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Astronomical units
struct micron_t final : public details::unit_t<double, std::micro, length_dimension>
{
    using _base = details::unit_t<double, std::micro, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"micron"};
    static constexpr std::string_view symbol{"um"};
    static constexpr std::wstring_view w_symbol{L"µm"};
    static constexpr std::u8string_view u8_symbol{u8"µm"};
};

struct angstrom_t final : public details::unit_t<double, std::ratio<1, 10000000000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 10000000000>, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"angstrom"};
    static constexpr std::string_view symbol{"A"};
    static constexpr std::wstring_view w_symbol{L"Å"};
    static constexpr std::u8string_view u8_symbol{u8"Å"};
};

struct au_t final : public details::unit_t<double, std::ratio<149597870700, 1>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<149597870700, 1>, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"astronomical_unit"};
    static constexpr std::string_view symbol{"au"};
    static constexpr std::wstring_view w_symbol{L"au"};
    static constexpr std::u8string_view u8_symbol{u8"au"};
};

struct light_year_t final : public details::unit_t<double, std::ratio<94607304725808000, 1>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<94607304725808000, 1>, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"light_year"};
    static constexpr std::string_view symbol{"ly"};
    static constexpr std::wstring_view w_symbol{L"ly"};
    static constexpr std::u8string_view u8_symbol{u8"ly"};
};

struct parsec_t final : public details::unit_t<double, std::ratio<30856775814913673, 1>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<30856775814913673, 1>, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"parsec"};
    static constexpr std::string_view symbol{"pc"};
    static constexpr std::wstring_view w_symbol{L"pc"};
    static constexpr std::u8string_view u8_symbol{u8"pc"};
};

} // PKR_UNITS_NAMESPACE








