#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/length_decl.h>

namespace PKR_UNITS_NAMESPACE
{
// Astronomical units
template <is_unit_value_type_c T>
struct micron_t final : public details::unit_t<T, std::micro, length_dimension>
{
    using _base = details::unit_t<T, std::micro, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"micron"};
    [[maybe_unused]] static constexpr std::string_view symbol{"um"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5m"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5m"};
};

template <is_unit_value_type_c T>
micron_t(T) -> micron_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
micron_t(const U&) -> micron_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct angstrom_t final : public details::unit_t<T, std::ratio<1, 10000000000>, length_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 10000000000>, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"angstrom"};
    [[maybe_unused]] static constexpr std::string_view symbol{"A"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00C5"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00C5"};
};

template <is_unit_value_type_c T>
angstrom_t(T) -> angstrom_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
angstrom_t(const U&) -> angstrom_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct au_t final : public details::unit_t<T, std::ratio<149597870700, 1>, length_dimension>
{
    using _base = details::unit_t<T, std::ratio<149597870700, 1>, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"astronomical_unit"};
    [[maybe_unused]] static constexpr std::string_view symbol{"au"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"au"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"au"};
};

template <is_unit_value_type_c T>
au_t(T) -> au_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
au_t(const U&) -> au_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct light_year_t final : public details::unit_t<T, std::ratio<94607304725808000, 1>, length_dimension>
{
    using _base = details::unit_t<T, std::ratio<94607304725808000, 1>, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"light_year"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ly"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ly"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ly"};
};

template <is_unit_value_type_c T>
light_year_t(T) -> light_year_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
light_year_t(const U&) -> light_year_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct parsec_t final : public details::unit_t<T, std::ratio<30856775814913673, 1>, length_dimension>
{
    using _base = details::unit_t<T, std::ratio<30856775814913673, 1>, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"parsec"};
    [[maybe_unused]] static constexpr std::string_view symbol{"pc"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pc"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pc"};
};

template <is_unit_value_type_c T>
parsec_t(T) -> parsec_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
parsec_t(const U&) -> parsec_t<typename details::is_pkr_unit<U>::value_type>;
} // namespace PKR_UNITS_NAMESPACE
