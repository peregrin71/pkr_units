#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/temperature_decl.h>

namespace PKR_UNITS_NAMESPACE
{
// Strong type for kelvin (SI base unit)
template <is_unit_value_type_c T>
struct kelvin_t final : public details::unit_t<T, std::ratio<1, 1>, temperature_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, temperature_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"K"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"K"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"K"};
};

template <is_unit_value_type_c T>
kelvin_t(T) -> kelvin_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == temperature_dimension)
kelvin_t(const U&) -> kelvin_t<typename details::is_pkr_unit<U>::value_type>;

// Metric temperature prefixes (strong types)
template <is_unit_value_type_c T>
struct attokelvin_t final : public details::unit_t<T, std::atto, temperature_dimension>
{
    using _base = details::unit_t<T, std::atto, temperature_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"attokelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"aK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"aK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"aK"};
};

template <is_unit_value_type_c T>
attokelvin_t(T) -> attokelvin_t<T>;

template <is_unit_value_type_c T>
struct femtokelvin_t final : public details::unit_t<T, std::femto, temperature_dimension>
{
    using _base = details::unit_t<T, std::femto, temperature_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"femtokelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"fK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"fK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"fK"};
};

template <is_unit_value_type_c T>
femtokelvin_t(T) -> femtokelvin_t<T>;

template <is_unit_value_type_c T>
struct picokelvin_t final : public details::unit_t<T, std::pico, temperature_dimension>
{
    using _base = details::unit_t<T, std::pico, temperature_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"picokelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"pK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pK"};
};

template <is_unit_value_type_c T>
picokelvin_t(T) -> picokelvin_t<T>;

template <is_unit_value_type_c T>
struct nanokelvin_t final : public details::unit_t<T, std::nano, temperature_dimension>
{
    using _base = details::unit_t<T, std::nano, temperature_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nanokelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nK"};
};

template <is_unit_value_type_c T>
nanokelvin_t(T) -> nanokelvin_t<T>;

template <is_unit_value_type_c T>
struct microkelvin_t final : public details::unit_t<T, std::micro, temperature_dimension>
{
    using _base = details::unit_t<T, std::micro, temperature_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"microkelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5K"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5K"};
};

template <is_unit_value_type_c T>
microkelvin_t(T) -> microkelvin_t<T>;

template <is_unit_value_type_c T>
struct millikelvin_t final : public details::unit_t<T, std::milli, temperature_dimension>
{
    using _base = details::unit_t<T, std::milli, temperature_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"millikelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mK"};
};

template <is_unit_value_type_c T>
millikelvin_t(T) -> millikelvin_t<T>;

template <is_unit_value_type_c T>
struct centikelvin_t final : public details::unit_t<T, std::centi, temperature_dimension>
{
    using _base = details::unit_t<T, std::centi, temperature_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"centikelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cK"};
};

template <is_unit_value_type_c T>
centikelvin_t(T) -> centikelvin_t<T>;

template <is_unit_value_type_c T>
struct decikelvin_t final : public details::unit_t<T, std::deci, temperature_dimension>
{
    using _base = details::unit_t<T, std::deci, temperature_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"decikelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dK"};
};

template <is_unit_value_type_c T>
decikelvin_t(T) -> decikelvin_t<T>;

template <is_unit_value_type_c T>
struct decakelvin_t final : public details::unit_t<T, std::deca, temperature_dimension>
{
    using _base = details::unit_t<T, std::deca, temperature_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"decakelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"daK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"daK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"daK"};
};

template <is_unit_value_type_c T>
decakelvin_t(T) -> decakelvin_t<T>;

template <is_unit_value_type_c T>
struct hectokelvin_t final : public details::unit_t<T, std::hecto, temperature_dimension>
{
    using _base = details::unit_t<T, std::hecto, temperature_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"hectokelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"hK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"hK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"hK"};
};

template <is_unit_value_type_c T>
hectokelvin_t(T) -> hectokelvin_t<T>;

template <is_unit_value_type_c T>
struct kilokelvin_t final : public details::unit_t<T, std::kilo, temperature_dimension>
{
    using _base = details::unit_t<T, std::kilo, temperature_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilokelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kK"};
};

template <is_unit_value_type_c T>
kilokelvin_t(T) -> kilokelvin_t<T>;

template <is_unit_value_type_c T>
struct megakelvin_t final : public details::unit_t<T, std::mega, temperature_dimension>
{
    using _base = details::unit_t<T, std::mega, temperature_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"megakelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MK"};
};

template <is_unit_value_type_c T>
megakelvin_t(T) -> megakelvin_t<T>;

template <is_unit_value_type_c T>
struct gigakelvin_t final : public details::unit_t<T, std::giga, temperature_dimension>
{
    using _base = details::unit_t<T, std::giga, temperature_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gigakelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"GK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"GK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"GK"};
};

template <is_unit_value_type_c T>
gigakelvin_t(T) -> gigakelvin_t<T>;

template <is_unit_value_type_c T>
struct terakelvin_t final : public details::unit_t<T, std::tera, temperature_dimension>
{
    using _base = details::unit_t<T, std::tera, temperature_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"terakelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"TK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"TK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"TK"};
};

template <is_unit_value_type_c T>
terakelvin_t(T) -> terakelvin_t<T>;

template <is_unit_value_type_c T>
struct petakelvin_t final : public details::unit_t<T, std::peta, temperature_dimension>
{
    using _base = details::unit_t<T, std::peta, temperature_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"petakelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"PK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"PK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"PK"};
};

template <is_unit_value_type_c T>
petakelvin_t(T) -> petakelvin_t<T>;

template <is_unit_value_type_c T>
struct exakelvin_t final : public details::unit_t<T, std::exa, temperature_dimension>
{
    using _base = details::unit_t<T, std::exa, temperature_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"exakelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"EK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"EK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"EK"};
};

template <is_unit_value_type_c T>
exakelvin_t(T) -> exakelvin_t<T>;

// ============================================================================
// Most derived unit type specializations for temperature units
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, temperature_dimension>
{
    using type = kelvin_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::atto, temperature_dimension>
{
    using type = attokelvin_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::femto, temperature_dimension>
{
    using type = femtokelvin_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::pico, temperature_dimension>
{
    using type = picokelvin_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::nano, temperature_dimension>
{
    using type = nanokelvin_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::micro, temperature_dimension>
{
    using type = microkelvin_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::milli, temperature_dimension>
{
    using type = millikelvin_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::centi, temperature_dimension>
{
    using type = centikelvin_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::deci, temperature_dimension>
{
    using type = decikelvin_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::deca, temperature_dimension>
{
    using type = decakelvin_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::hecto, temperature_dimension>
{
    using type = hectokelvin_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::kilo, temperature_dimension>
{
    using type = kilokelvin_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::mega, temperature_dimension>
{
    using type = megakelvin_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::giga, temperature_dimension>
{
    using type = gigakelvin_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::tera, temperature_dimension>
{
    using type = terakelvin_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::peta, temperature_dimension>
{
    using type = petakelvin_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::exa, temperature_dimension>
{
    using type = exakelvin_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
