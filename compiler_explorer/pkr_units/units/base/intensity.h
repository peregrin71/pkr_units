#pragma once
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/unit_impl.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/decls/intensity_decl.h"

namespace PKR_UNITS_NAMESPACE
{
// Strong type for candela (SI base unit)
template <is_unit_value_type_c T>
struct candela_t final : public details::unit_t<T, std::ratio<1, 1>, intensity_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, intensity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"candela"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cd"};
};

template <is_unit_value_type_c T>
candela_t(T) -> candela_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == intensity_dimension)
candela_t(const U&) -> candela_t<typename details::is_pkr_unit<U>::value_type>;

// Metric intensity prefixes (strong types)
template <is_unit_value_type_c T>
struct attocandela_t final : public details::unit_t<T, std::atto, intensity_dimension>
{
    using _base = details::unit_t<T, std::atto, intensity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"attocandela"};
    [[maybe_unused]] static constexpr std::string_view symbol{"acd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"acd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"acd"};
};

template <is_unit_value_type_c T>
attocandela_t(T) -> attocandela_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == intensity_dimension)
attocandela_t(const U&) -> attocandela_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct femtocandela_t final : public details::unit_t<T, std::femto, intensity_dimension>
{
    using _base = details::unit_t<T, std::femto, intensity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"femtocandela"};
    [[maybe_unused]] static constexpr std::string_view symbol{"fcd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"fcd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"fcd"};
};

template <is_unit_value_type_c T>
femtocandela_t(T) -> femtocandela_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == intensity_dimension)
femtocandela_t(const U&) -> femtocandela_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct picocandela_t final : public details::unit_t<T, std::pico, intensity_dimension>
{
    using _base = details::unit_t<T, std::pico, intensity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"picocandela"};
    [[maybe_unused]] static constexpr std::string_view symbol{"pcd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pcd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pcd"};
};

template <is_unit_value_type_c T>
picocandela_t(T) -> picocandela_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == intensity_dimension)
picocandela_t(const U&) -> picocandela_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct nanocandela_t final : public details::unit_t<T, std::nano, intensity_dimension>
{
    using _base = details::unit_t<T, std::nano, intensity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nanocandela"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ncd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ncd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ncd"};
};

template <is_unit_value_type_c T>
nanocandela_t(T) -> nanocandela_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == intensity_dimension)
nanocandela_t(const U&) -> nanocandela_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct microcandela_t final : public details::unit_t<T, std::micro, intensity_dimension>
{
    using _base = details::unit_t<T, std::micro, intensity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"microcandela"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ucd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5cd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5cd"};
};

template <is_unit_value_type_c T>
microcandela_t(T) -> microcandela_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == intensity_dimension)
microcandela_t(const U&) -> microcandela_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct millicandela_t final : public details::unit_t<T, std::milli, intensity_dimension>
{
    using _base = details::unit_t<T, std::milli, intensity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"millicandela"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mcd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mcd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mcd"};
};

template <is_unit_value_type_c T>
millicandela_t(T) -> millicandela_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == intensity_dimension)
millicandela_t(const U&) -> millicandela_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct centicandela_t final : public details::unit_t<T, std::centi, intensity_dimension>
{
    using _base = details::unit_t<T, std::centi, intensity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"centicandela"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ccd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ccd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ccd"};
};

template <is_unit_value_type_c T>
centicandela_t(T) -> centicandela_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == intensity_dimension)
centicandela_t(const U&) -> centicandela_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct decicandela_t final : public details::unit_t<T, std::deci, intensity_dimension>
{
    using _base = details::unit_t<T, std::deci, intensity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"decicandela"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dcd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dcd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dcd"};
};

template <is_unit_value_type_c T>
decicandela_t(T) -> decicandela_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == intensity_dimension)
decicandela_t(const U&) -> decicandela_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct decacandela_t final : public details::unit_t<T, std::deca, intensity_dimension>
{
    using _base = details::unit_t<T, std::deca, intensity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"decacandela"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dacd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dacd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dacd"};
};

template <is_unit_value_type_c T>
decacandela_t(T) -> decacandela_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == intensity_dimension)
decacandela_t(const U&) -> decacandela_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct hectocandela_t final : public details::unit_t<T, std::hecto, intensity_dimension>
{
    using _base = details::unit_t<T, std::hecto, intensity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"hectocandela"};
    [[maybe_unused]] static constexpr std::string_view symbol{"hcd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"hcd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"hcd"};
};

template <is_unit_value_type_c T>
hectocandela_t(T) -> hectocandela_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == intensity_dimension)
hectocandela_t(const U&) -> hectocandela_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct kilocandela_t final : public details::unit_t<T, std::kilo, intensity_dimension>
{
    using _base = details::unit_t<T, std::kilo, intensity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilocandela"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kcd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kcd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kcd"};
};

template <is_unit_value_type_c T>
kilocandela_t(T) -> kilocandela_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == intensity_dimension)
kilocandela_t(const U&) -> kilocandela_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct megacandela_t final : public details::unit_t<T, std::mega, intensity_dimension>
{
    using _base = details::unit_t<T, std::mega, intensity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"megacandela"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Mcd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Mcd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Mcd"};
};

template <is_unit_value_type_c T>
megacandela_t(T) -> megacandela_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == intensity_dimension)
megacandela_t(const U&) -> megacandela_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct gigacandela_t final : public details::unit_t<T, std::giga, intensity_dimension>
{
    using _base = details::unit_t<T, std::giga, intensity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gigacandela"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Gcd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Gcd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Gcd"};
};

template <is_unit_value_type_c T>
gigacandela_t(T) -> gigacandela_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == intensity_dimension)
gigacandela_t(const U&) -> gigacandela_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct teracandela_t final : public details::unit_t<T, std::tera, intensity_dimension>
{
    using _base = details::unit_t<T, std::tera, intensity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"teracandela"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Tcd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Tcd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Tcd"};
};

template <is_unit_value_type_c T>
teracandela_t(T) -> teracandela_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == intensity_dimension)
teracandela_t(const U&) -> teracandela_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct petacandela_t final : public details::unit_t<T, std::peta, intensity_dimension>
{
    using _base = details::unit_t<T, std::peta, intensity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"petacandela"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Pcd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Pcd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Pcd"};
};

template <is_unit_value_type_c T>
petacandela_t(T) -> petacandela_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == intensity_dimension)
petacandela_t(const U&) -> petacandela_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct exacandela_t final : public details::unit_t<T, std::exa, intensity_dimension>
{
    using _base = details::unit_t<T, std::exa, intensity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"exacandela"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Ecd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Ecd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Ecd"};
};

template <is_unit_value_type_c T>
exacandela_t(T) -> exacandela_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == intensity_dimension)
exacandela_t(const U&) -> exacandela_t<typename details::is_pkr_unit<U>::value_type>;

// ============================================================================
// Most derived unit type specializations for intensity units
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, intensity_dimension>
{
    using type = candela_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::atto, intensity_dimension>
{
    using type = attocandela_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::femto, intensity_dimension>
{
    using type = femtocandela_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::pico, intensity_dimension>
{
    using type = picocandela_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::nano, intensity_dimension>
{
    using type = nanocandela_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::micro, intensity_dimension>
{
    using type = microcandela_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::milli, intensity_dimension>
{
    using type = millicandela_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::centi, intensity_dimension>
{
    using type = centicandela_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::deci, intensity_dimension>
{
    using type = decicandela_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::deca, intensity_dimension>
{
    using type = decacandela_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::hecto, intensity_dimension>
{
    using type = hectocandela_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::kilo, intensity_dimension>
{
    using type = kilocandela_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::mega, intensity_dimension>
{
    using type = megacandela_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::giga, intensity_dimension>
{
    using type = gigacandela_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::tera, intensity_dimension>
{
    using type = teracandela_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::peta, intensity_dimension>
{
    using type = petacandela_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::exa, intensity_dimension>
{
    using type = exacandela_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
