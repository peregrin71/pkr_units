#pragma once
#include <string_view>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/amount_decl.h>
namespace PKR_UNITS_NAMESPACE
{
// Strong type for mole (SI base unit)
template <is_unit_value_type_c T>
struct mole_t final : public details::unit_t<T, std::ratio<1, 1>, amount_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, amount_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"mole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mol"};
};

template <is_unit_value_type_c T>
mole_t(T) -> mole_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == amount_dimension)
mole_t(const U&) -> mole_t<typename details::is_pkr_unit<U>::value_type>; 

// Metric amount prefixes (strong types)
template <is_unit_value_type_c T>
struct attomole_t final : public details::unit_t<T, std::atto, amount_dimension>
{
    using _base = details::unit_t<T, std::atto, amount_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"attomole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"amol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"amol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"amol"};
};

template <is_unit_value_type_c T>
attomole_t(T) -> attomole_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == amount_dimension)
attomole_t(const U&) -> attomole_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct femtomole_t final : public details::unit_t<T, std::femto, amount_dimension>
{
    using _base = details::unit_t<T, std::femto, amount_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"femtomole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"fmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"fmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"fmol"};
};

template <is_unit_value_type_c T>
femtomole_t(T) -> femtomole_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == amount_dimension)
femtomole_t(const U&) -> femtomole_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct picomole_t final : public details::unit_t<T, std::pico, amount_dimension>
{
    using _base = details::unit_t<T, std::pico, amount_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"picomole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"pmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pmol"};
};

template <is_unit_value_type_c T>
picomole_t(T) -> picomole_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == amount_dimension)
picomole_t(const U&) -> picomole_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct nanomole_t final : public details::unit_t<T, std::nano, amount_dimension>
{
    using _base = details::unit_t<T, std::nano, amount_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nanomole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nmol"};
};

template <is_unit_value_type_c T>
nanomole_t(T) -> nanomole_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == amount_dimension)
nanomole_t(const U&) -> nanomole_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct micromole_t final : public details::unit_t<T, std::micro, amount_dimension>
{
    using _base = details::unit_t<T, std::micro, amount_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"micromole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"umol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5mol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5mol"};
};

template <is_unit_value_type_c T>
micromole_t(T) -> micromole_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == amount_dimension)
micromole_t(const U&) -> micromole_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct millimole_t final : public details::unit_t<T, std::milli, amount_dimension>
{
    using _base = details::unit_t<T, std::milli, amount_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"millimole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mmol"};
};

template <is_unit_value_type_c T>
millimole_t(T) -> millimole_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == amount_dimension)
millimole_t(const U&) -> millimole_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct centimole_t final : public details::unit_t<T, std::centi, amount_dimension>
{
    using _base = details::unit_t<T, std::centi, amount_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"centimole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cmol"};
};

template <is_unit_value_type_c T>
centimole_t(T) -> centimole_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == amount_dimension)
centimole_t(const U&) -> centimole_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct decimole_t final : public details::unit_t<T, std::deci, amount_dimension>
{
    using _base = details::unit_t<T, std::deci, amount_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"decimole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dmol"};
};

template <is_unit_value_type_c T>
decimole_t(T) -> decimole_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == amount_dimension)
decimole_t(const U&) -> decimole_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct decamole_t final : public details::unit_t<T, std::deca, amount_dimension>
{
    using _base = details::unit_t<T, std::deca, amount_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"decamole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"damol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"damol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"damol"};
};

template <is_unit_value_type_c T>
decamole_t(T) -> decamole_t<T>; 

template <is_unit_value_type_c T>
struct hectomole_t final : public details::unit_t<T, std::hecto, amount_dimension>
{
    using _base = details::unit_t<T, std::hecto, amount_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"hectomole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"hmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"hmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"hmol"};
};

template <is_unit_value_type_c T>
hectomole_t(T) -> hectomole_t<T>; 

template <is_unit_value_type_c T>
struct kilomole_t final : public details::unit_t<T, std::kilo, amount_dimension>
{
    using _base = details::unit_t<T, std::kilo, amount_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilomole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kmol"};
};

template <is_unit_value_type_c T>
kilomole_t(T) -> kilomole_t<T>; 

template <is_unit_value_type_c T>
struct megamole_t final : public details::unit_t<T, std::mega, amount_dimension>
{
    using _base = details::unit_t<T, std::mega, amount_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"megamole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Mmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Mmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Mmol"};
};

template <is_unit_value_type_c T>
megamole_t(T) -> megamole_t<T>; 

template <is_unit_value_type_c T>
struct gigamole_t final : public details::unit_t<T, std::giga, amount_dimension>
{
    using _base = details::unit_t<T, std::giga, amount_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gigamole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Gmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Gmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Gmol"};
};

template <is_unit_value_type_c T>
gigamole_t(T) -> gigamole_t<T>; 

template <is_unit_value_type_c T>
struct teramole_t final : public details::unit_t<T, std::tera, amount_dimension>
{
    using _base = details::unit_t<T, std::tera, amount_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"teramole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Tmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Tmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Tmol"};
};

template <is_unit_value_type_c T>
teramole_t(T) -> teramole_t<T>; 

template <is_unit_value_type_c T>
struct petamole_t final : public details::unit_t<T, std::peta, amount_dimension>
{
    using _base = details::unit_t<T, std::peta, amount_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"petamole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Pmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Pmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Pmol"};
};

template <is_unit_value_type_c T>
petamole_t(T) -> petamole_t<T>; 

template <is_unit_value_type_c T>
struct examole_t final : public details::unit_t<T, std::exa, amount_dimension>
{
    using _base = details::unit_t<T, std::exa, amount_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"examole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Emol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Emol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Emol"};
};

template <is_unit_value_type_c T>
examole_t(T) -> examole_t<T>; 

// ============================================================================
// Most derived unit type specializations for amount units
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, amount_dimension>
{
    using type = mole_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::atto, amount_dimension>
{
    using type = attomole_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::femto, amount_dimension>
{
    using type = femtomole_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::pico, amount_dimension>
{
    using type = picomole_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::nano, amount_dimension>
{
    using type = nanomole_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::micro, amount_dimension>
{
    using type = micromole_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::milli, amount_dimension>
{
    using type = millimole_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::centi, amount_dimension>
{
    using type = centimole_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::deci, amount_dimension>
{
    using type = decimole_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::deca, amount_dimension>
{
    using type = decamole_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::hecto, amount_dimension>
{
    using type = hectomole_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::kilo, amount_dimension>
{
    using type = kilomole_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::mega, amount_dimension>
{
    using type = megamole_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::giga, amount_dimension>
{
    using type = gigamole_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::tera, amount_dimension>
{
    using type = teramole_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::peta, amount_dimension>
{
    using type = petamole_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::exa, amount_dimension>
{
    using type = examole_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
