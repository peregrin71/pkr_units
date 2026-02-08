#pragma once
#include <string_view>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>

namespace PKR_UNITS_NAMESPACE
{
// Strong type for meter (SI base unit)
template <is_unit_value_type_c T>
struct meter_t final : public details::unit_t<T, std::ratio<1, 1>, length_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"meter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"m"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"m"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"m"};
};

template <is_unit_value_type_c T>
meter_t(T) -> meter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
meter_t(const U&) -> meter_t<typename details::is_pkr_unit<U>::value_type>;

// Metric length prefixes (strong types)
template <is_unit_value_type_c T>
struct attometer_t final : public details::unit_t<T, std::atto, length_dimension>
{
    using _base = details::unit_t<T, std::atto, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"attometer"};
    [[maybe_unused]] static constexpr std::string_view symbol{"am"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"am"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"am"};
};

template <is_unit_value_type_c T>
attometer_t(T) -> attometer_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
attometer_t(const U&) -> attometer_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct femtometer_t final : public details::unit_t<T, std::femto, length_dimension>
{
    using _base = details::unit_t<T, std::femto, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"femtometer"};
    [[maybe_unused]] static constexpr std::string_view symbol{"fm"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"fm"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"fm"};
};

template <is_unit_value_type_c T>
femtometer_t(T) -> femtometer_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
femtometer_t(const U&) -> femtometer_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct picometer_t final : public details::unit_t<T, std::pico, length_dimension>
{
    using _base = details::unit_t<T, std::pico, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"picometer"};
    [[maybe_unused]] static constexpr std::string_view symbol{"pm"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pm"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pm"};
};

template <is_unit_value_type_c T>
picometer_t(T) -> picometer_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
picometer_t(const U&) -> picometer_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct nanometer_t final : public details::unit_t<T, std::nano, length_dimension>
{
    using _base = details::unit_t<T, std::nano, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nanometer"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nm"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nm"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nm"};
};

template <is_unit_value_type_c T>
nanometer_t(T) -> nanometer_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
nanometer_t(const U&) -> nanometer_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct micrometer_t final : public details::unit_t<T, std::micro, length_dimension>
{
    using _base = details::unit_t<T, std::micro, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"micrometer"};
    [[maybe_unused]] static constexpr std::string_view symbol{"um"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5m"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5m"};
};

template <is_unit_value_type_c T>
micrometer_t(T) -> micrometer_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
micrometer_t(const U&) -> micrometer_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct millimeter_t final : public details::unit_t<T, std::milli, length_dimension>
{
    using _base = details::unit_t<T, std::milli, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"millimeter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mm"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mm"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mm"};
};

template <is_unit_value_type_c T>
millimeter_t(T) -> millimeter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
millimeter_t(const U&) -> millimeter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct centimeter_t final : public details::unit_t<T, std::centi, length_dimension>
{
    using _base = details::unit_t<T, std::centi, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"centimeter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cm"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cm"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cm"};
};

template <is_unit_value_type_c T>
centimeter_t(T) -> centimeter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
centimeter_t(const U&) -> centimeter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct decimeter_t final : public details::unit_t<T, std::deci, length_dimension>
{
    using _base = details::unit_t<T, std::deci, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"decimeter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dm"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dm"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dm"};
};

template <is_unit_value_type_c T>
decimeter_t(T) -> decimeter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
decimeter_t(const U&) -> decimeter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct decameter_t final : public details::unit_t<T, std::deca, length_dimension>
{
    using _base = details::unit_t<T, std::deca, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"decameter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dam"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dam"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dam"};
};

template <is_unit_value_type_c T>
decameter_t(T) -> decameter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
decameter_t(const U&) -> decameter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct hectometer_t final : public details::unit_t<T, std::hecto, length_dimension>
{
    using _base = details::unit_t<T, std::hecto, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"hectometer"};
    [[maybe_unused]] static constexpr std::string_view symbol{"hm"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"hm"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"hm"};
};

template <is_unit_value_type_c T>
hectometer_t(T) -> hectometer_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
hectometer_t(const U&) -> hectometer_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct kilometer_t final : public details::unit_t<T, std::kilo, length_dimension>
{
    using _base = details::unit_t<T, std::kilo, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilometer"};
    [[maybe_unused]] static constexpr std::string_view symbol{"km"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"km"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"km"};
};

template <is_unit_value_type_c T>
kilometer_t(T) -> kilometer_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
kilometer_t(const U&) -> kilometer_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct megameter_t final : public details::unit_t<T, std::mega, length_dimension>
{
    using _base = details::unit_t<T, std::mega, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"megameter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Mm"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Mm"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Mm"};
};

template <is_unit_value_type_c T>
megameter_t(T) -> megameter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
megameter_t(const U&) -> megameter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct gigameter_t final : public details::unit_t<T, std::giga, length_dimension>
{
    using _base = details::unit_t<T, std::giga, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gigameter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Gm"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Gm"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Gm"};
};

template <is_unit_value_type_c T>
gigameter_t(T) -> gigameter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
gigameter_t(const U&) -> gigameter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct terameter_t final : public details::unit_t<T, std::tera, length_dimension>
{
    using _base = details::unit_t<T, std::tera, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"terameter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Tm"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Tm"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Tm"};
};

template <is_unit_value_type_c T>
terameter_t(T) -> terameter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
terameter_t(const U&) -> terameter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct petameter_t final : public details::unit_t<T, std::peta, length_dimension>
{
    using _base = details::unit_t<T, std::peta, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"petameter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Pm"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Pm"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Pm"};
};

template <is_unit_value_type_c T>
petameter_t(T) -> petameter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
petameter_t(const U&) -> petameter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct exameter_t final : public details::unit_t<T, std::exa, length_dimension>
{
    using _base = details::unit_t<T, std::exa, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"exameter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Em"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Em"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Em"};
};

template <is_unit_value_type_c T>
exameter_t(T) -> exameter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
exameter_t(const U&) -> exameter_t<typename details::is_pkr_unit<U>::value_type>;

// ============================================================================
// Derived unit type specializations for length units
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, length_dimension>
{
    using type = meter_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::atto, length_dimension>
{
    using type = attometer_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::femto, length_dimension>
{
    using type = femtometer_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::pico, length_dimension>
{
    using type = picometer_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::nano, length_dimension>
{
    using type = nanometer_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::micro, length_dimension>
{
    using type = micrometer_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::milli, length_dimension>
{
    using type = millimeter_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::centi, length_dimension>
{
    using type = centimeter_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::deci, length_dimension>
{
    using type = decimeter_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::deca, length_dimension>
{
    using type = decameter_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::hecto, length_dimension>
{
    using type = hectometer_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::kilo, length_dimension>
{
    using type = kilometer_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::mega, length_dimension>
{
    using type = megameter_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::giga, length_dimension>
{
    using type = gigameter_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::tera, length_dimension>
{
    using type = terameter_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::peta, length_dimension>
{
    using type = petameter_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::exa, length_dimension>
{
    using type = exameter_t<T>;
};

} // namespace PKR_UNITS_NAMESPACE
