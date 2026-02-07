#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/unit_t.h>

namespace PKR_UNITS_NAMESPACE
{
// Strong type for kilogram (SI base unit for mass)
// NOTE: Kilogram is the base SI unit, not gram (unlike length where meter is base)
template <is_unit_value_type_c T>
struct kilogram_t final : public details::unit_t<T, std::ratio<1, 1>, mass_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilogram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kg"};
};

template <is_unit_value_type_c T>
kilogram_t(T) -> kilogram_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == mass_dimension)
kilogram_t(const U&) -> kilogram_t<typename details::is_pkr_unit<U>::value_type>;

// Metric mass prefixes (applied relative to kilogram)
// All mass units are defined relative to kilogram (ratio 1/1) as the base
// NOTE: attogram (10^-21) and femtogram (10^-18) exceed std::ratio limits
// and are omitted. The smallest representable is picogram (10^-15).
template <is_unit_value_type_c T>
struct picogram_t final : public details::unit_t<T, std::femto, mass_dimension>
{
    using _base = details::unit_t<T, std::femto, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"picogram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"pg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pg"};
};

template <is_unit_value_type_c T>
picogram_t(T) -> picogram_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == mass_dimension)
picogram_t(const U&) -> picogram_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct nanogram_t final : public details::unit_t<T, std::pico, mass_dimension>
{
    using _base = details::unit_t<T, std::pico, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nanogram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ng"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ng"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ng"};
};

template <is_unit_value_type_c T>
nanogram_t(T) -> nanogram_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == mass_dimension)
nanogram_t(const U&) -> nanogram_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct microgram_t final : public details::unit_t<T, std::nano, mass_dimension>
{
    using _base = details::unit_t<T, std::nano, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"microgram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ug"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5g"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5g"};
};

template <is_unit_value_type_c T>
microgram_t(T) -> microgram_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == mass_dimension)
microgram_t(const U&) -> microgram_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct milligram_t final : public details::unit_t<T, std::micro, mass_dimension>
{
    using _base = details::unit_t<T, std::micro, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"milligram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mg"};
};

template <is_unit_value_type_c T>
milligram_t(T) -> milligram_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == mass_dimension)
milligram_t(const U&) -> milligram_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct centigram_t final : public details::unit_t<T, std::ratio<1, 100000>, mass_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 100000>, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"centigram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cg"};
};

template <is_unit_value_type_c T>
centigram_t(T) -> centigram_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == mass_dimension)
centigram_t(const U&) -> centigram_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct decigram_t final : public details::unit_t<T, std::ratio<1, 10000>, mass_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 10000>, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"decigram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dg"};
};

template <is_unit_value_type_c T>
decigram_t(T) -> decigram_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == mass_dimension)
decigram_t(const U&) -> decigram_t<typename details::is_pkr_unit<U>::value_type>;

// gram is 1/1000 of kilogram
template <is_unit_value_type_c T>
struct gram_t final : public details::unit_t<T, std::milli, mass_dimension>
{
    using _base = details::unit_t<T, std::milli, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"g"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"g"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"g"};
};

template <is_unit_value_type_c T>
gram_t(T) -> gram_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == mass_dimension)
gram_t(const U&) -> gram_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct decagram_t final : public details::unit_t<T, std::centi, mass_dimension>
{
    using _base = details::unit_t<T, std::centi, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"decagram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dag"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dag"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dag"};
};

template <is_unit_value_type_c T>
decagram_t(T) -> decagram_t<T>;

template <is_unit_value_type_c T>
struct hectogram_t final : public details::unit_t<T, std::deci, mass_dimension>
{
    using _base = details::unit_t<T, std::deci, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"hectogram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"hg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"hg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"hg"};
};

template <is_unit_value_type_c T>
hectogram_t(T) -> hectogram_t<T>;

// Larger mass units
template <is_unit_value_type_c T>
struct gigagram_t final : public details::unit_t<T, std::mega, mass_dimension>
{
    using _base = details::unit_t<T, std::mega, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gigagram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Gg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Gg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Gg"};
};

template <is_unit_value_type_c T>
gigagram_t(T) -> gigagram_t<T>;

template <is_unit_value_type_c T>
struct teragram_t final : public details::unit_t<T, std::giga, mass_dimension>
{
    using _base = details::unit_t<T, std::giga, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"teragram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Tg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Tg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Tg"};
};

template <is_unit_value_type_c T>
teragram_t(T) -> teragram_t<T>;

template <is_unit_value_type_c T>
struct petagram_t final : public details::unit_t<T, std::tera, mass_dimension>
{
    using _base = details::unit_t<T, std::tera, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"petagram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Pg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Pg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Pg"};
};

template <is_unit_value_type_c T>
petagram_t(T) -> petagram_t<T>;

template <is_unit_value_type_c T>
struct exagram_t final : public details::unit_t<T, std::peta, mass_dimension>
{
    using _base = details::unit_t<T, std::peta, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"exagram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Eg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Eg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Eg"};
};

template <is_unit_value_type_c T>
exagram_t(T) -> exagram_t<T>;

// Common mass units
template <is_unit_value_type_c T>
struct metric_ton_t final : public details::unit_t<T, std::kilo, mass_dimension>
{
    using _base = details::unit_t<T, std::kilo, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"metric ton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"t"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"t"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"t"};
};

template <is_unit_value_type_c T>
metric_ton_t(T) -> metric_ton_t<T>;

// ============================================================================
// Most derived unit type specializations for mass units
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, mass_dimension>
{
    using type = kilogram_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::femto, mass_dimension>
{
    using type = picogram_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::pico, mass_dimension>
{
    using type = nanogram_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::nano, mass_dimension>
{
    using type = microgram_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::micro, mass_dimension>
{
    using type = milligram_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 100000>, mass_dimension>
{
    using type = centigram_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 10000>, mass_dimension>
{
    using type = decigram_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::milli, mass_dimension>
{
    using type = gram_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::centi, mass_dimension>
{
    using type = decagram_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::deci, mass_dimension>
{
    using type = hectogram_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::kilo, mass_dimension>
{
    using type = metric_ton_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::mega, mass_dimension>
{
    using type = gigagram_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::giga, mass_dimension>
{
    using type = teragram_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::tera, mass_dimension>
{
    using type = petagram_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::peta, mass_dimension>
{
    using type = exagram_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
