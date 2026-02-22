#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>

namespace PKR_UNITS_NAMESPACE
{
// Strong type for ampere (SI base unit)
template <is_unit_value_type_c T>
struct ampere_t final : public unit_t<T, std::ratio<1, 1>, current_dimension>
{
    using _base = unit_t<T, std::ratio<1, 1>, current_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"ampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"A"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"A"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"A"};
};

template <is_unit_value_type_c T>
ampere_t(T) -> ampere_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == current_dimension)
ampere_t(const U&) -> ampere_t<typename details::is_pkr_unit<U>::value_type>;

// Metric current prefixes (strong types)
template <is_unit_value_type_c T>
struct attoampere_t final : public unit_t<T, std::atto, current_dimension>
{
    using _base = unit_t<T, std::atto, current_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"attoampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"aA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"aA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"aA"};
};

template <is_unit_value_type_c T>
attoampere_t(T) -> attoampere_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == current_dimension)
attoampere_t(const U&) -> attoampere_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct femtoampere_t final : public unit_t<T, std::femto, current_dimension>
{
    using _base = unit_t<T, std::femto, current_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"femtoampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"fA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"fA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"fA"};
};

template <is_unit_value_type_c T>
femtoampere_t(T) -> femtoampere_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == current_dimension)
femtoampere_t(const U&) -> femtoampere_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct deciampere_t final : public unit_t<T, std::deci, current_dimension>
{
    using _base = unit_t<T, std::deci, current_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"deciampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dA"};
};

template <is_unit_value_type_c T>
deciampere_t(T) -> deciampere_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == current_dimension)
deciampere_t(const U&) -> deciampere_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct decaampere_t final : public unit_t<T, std::deca, current_dimension>
{
    using _base = unit_t<T, std::deca, current_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"decaampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"daA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"daA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"daA"};
};

template <is_unit_value_type_c T>
decaampere_t(T) -> decaampere_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == current_dimension)
decaampere_t(const U&) -> decaampere_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct hectoampere_t final : public unit_t<T, std::hecto, current_dimension>
{
    using _base = unit_t<T, std::hecto, current_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"hectoampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"hA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"hA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"hA"};
};

template <is_unit_value_type_c T>
hectoampere_t(T) -> hectoampere_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == current_dimension)
hectoampere_t(const U&) -> hectoampere_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct kiloampere_t final : public unit_t<T, std::kilo, current_dimension>
{
    using _base = unit_t<T, std::kilo, current_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kiloampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kA"};
};

template <is_unit_value_type_c T>
kiloampere_t(T) -> kiloampere_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == current_dimension)
kiloampere_t(const U&) -> kiloampere_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct megaampere_t final : public unit_t<T, std::mega, current_dimension>
{
    using _base = unit_t<T, std::mega, current_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"megaampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MA"};
};

template <is_unit_value_type_c T>
megaampere_t(T) -> megaampere_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == current_dimension)
megaampere_t(const U&) -> megaampere_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct gigaampere_t final : public unit_t<T, std::giga, current_dimension>
{
    using _base = unit_t<T, std::giga, current_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gigaampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"GA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"GA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"GA"};
};

template <is_unit_value_type_c T>
gigaampere_t(T) -> gigaampere_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == current_dimension)
gigaampere_t(const U&) -> gigaampere_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct teraampere_t final : public unit_t<T, std::tera, current_dimension>
{
    using _base = unit_t<T, std::tera, current_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"teraampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"TA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"TA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"TA"};
};

template <is_unit_value_type_c T>
teraampere_t(T) -> teraampere_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == current_dimension)
teraampere_t(const U&) -> teraampere_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct petaampere_t final : public unit_t<T, std::peta, current_dimension>
{
    using _base = unit_t<T, std::peta, current_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"petaampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"PA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"PA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"PA"};
};

template <is_unit_value_type_c T>
petaampere_t(T) -> petaampere_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == current_dimension)
petaampere_t(const U&) -> petaampere_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct exaampere_t final : public unit_t<T, std::exa, current_dimension>
{
    using _base = unit_t<T, std::exa, current_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"exaampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"EA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"EA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"EA"};
};

template <is_unit_value_type_c T>
exaampere_t(T) -> exaampere_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == current_dimension)
exaampere_t(const U&) -> exaampere_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct picoampere_t final : public unit_t<T, std::pico, current_dimension>
{
    using _base = unit_t<T, std::pico, current_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"picoampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"pA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pA"};
};

template <is_unit_value_type_c T>
picoampere_t(T) -> picoampere_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == current_dimension)
picoampere_t(const U&) -> picoampere_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct nanoampere_t final : public unit_t<T, std::nano, current_dimension>
{
    using _base = unit_t<T, std::nano, current_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nanoampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nA"};
};

template <is_unit_value_type_c T>
nanoampere_t(T) -> nanoampere_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == current_dimension)
nanoampere_t(const U&) -> nanoampere_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct microampere_t final : public unit_t<T, std::micro, current_dimension>
{
    using _base = unit_t<T, std::micro, current_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"microampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5A"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5A"};
};

template <is_unit_value_type_c T>
microampere_t(T) -> microampere_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == current_dimension)
microampere_t(const U&) -> microampere_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct milliampere_t final : public unit_t<T, std::milli, current_dimension>
{
    using _base = unit_t<T, std::milli, current_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"milliampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mA"};
};

template <is_unit_value_type_c T>
milliampere_t(T) -> milliampere_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == current_dimension)
milliampere_t(const U&) -> milliampere_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct centiampere_t final : public unit_t<T, std::centi, current_dimension>
{
    using _base = unit_t<T, std::centi, current_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"centiampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cA"};
};

template <is_unit_value_type_c T>
centiampere_t(T) -> centiampere_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == current_dimension)
centiampere_t(const U&) -> centiampere_t<typename details::is_pkr_unit<U>::value_type>;

// ============================================================================
// Most derived unit type specializations for current units
// ============================================================================
template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1, 1>, current_dimension>
{
    using type = ampere_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::atto, current_dimension>
{
    using type = attoampere_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::femto, current_dimension>
{
    using type = femtoampere_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::pico, current_dimension>
{
    using type = picoampere_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::nano, current_dimension>
{
    using type = nanoampere_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::micro, current_dimension>
{
    using type = microampere_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::milli, current_dimension>
{
    using type = milliampere_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::centi, current_dimension>
{
    using type = centiampere_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::deci, current_dimension>
{
    using type = deciampere_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::deca, current_dimension>
{
    using type = decaampere_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::hecto, current_dimension>
{
    using type = hectoampere_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::kilo, current_dimension>
{
    using type = kiloampere_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::mega, current_dimension>
{
    using type = megaampere_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::giga, current_dimension>
{
    using type = gigaampere_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::tera, current_dimension>
{
    using type = teraampere_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::peta, current_dimension>
{
    using type = petaampere_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::exa, current_dimension>
{
    using type = exaampere_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
