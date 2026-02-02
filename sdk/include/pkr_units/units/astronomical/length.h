#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/length_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Astronomical units
struct micron_t final : public details::unit_t<double, std::micro, length_dimension>
{
    using _base = details::unit_t<double, std::micro, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"micron"};
    [[maybe_unused]] static constexpr std::string_view symbol{"um"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5m"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5m"};
};

struct angstrom_t final : public details::unit_t<double, std::ratio<1, 10000000000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 10000000000>, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"angstrom"};
    [[maybe_unused]] static constexpr std::string_view symbol{"A"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Å"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Å"};
};

struct au_t final : public details::unit_t<double, std::ratio<149597870700, 1>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<149597870700, 1>, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"astronomical_unit"};
    [[maybe_unused]] static constexpr std::string_view symbol{"au"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"au"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"au"};
};

struct light_year_t final : public details::unit_t<double, std::ratio<94607304725808000, 1>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<94607304725808000, 1>, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"light_year"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ly"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ly"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ly"};
};

struct parsec_t final : public details::unit_t<double, std::ratio<30856775814913673, 1>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<30856775814913673, 1>, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"parsec"};
    [[maybe_unused]] static constexpr std::string_view symbol{"pc"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pc"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pc"};
};

} // namespace PKR_UNITS_NAMESPACE
