#pragma once

#include <string_view>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/length_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Strong type for meter (SI base unit)
struct meter_t final : public details::unit_t<double, std::ratio<1, 1>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"meter"};

    [[maybe_unused]] static constexpr std::string_view symbol{"m"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"m"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"m"};
};

// Metric length prefixes (strong types)
struct attometer_t final : public details::unit_t<double, std::atto, length_dimension>
{
    using _base = details::unit_t<double, std::atto, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"attometer"};

    [[maybe_unused]] static constexpr std::string_view symbol{"am"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"am"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"am"};
};

struct femtometer_t final : public details::unit_t<double, std::femto, length_dimension>
{
    using _base = details::unit_t<double, std::femto, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"femtometer"};

    [[maybe_unused]] static constexpr std::string_view symbol{"fm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"fm"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"fm"};
};

struct picometer_t final : public details::unit_t<double, std::pico, length_dimension>
{
    using _base = details::unit_t<double, std::pico, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"picometer"};

    [[maybe_unused]] static constexpr std::string_view symbol{"pm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pm"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pm"};
};

struct nanometer_t final : public details::unit_t<double, std::nano, length_dimension>
{
    using _base = details::unit_t<double, std::nano, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"nanometer"};

    [[maybe_unused]] static constexpr std::string_view symbol{"nm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nm"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nm"};
};

struct micrometer_t final : public details::unit_t<double, std::micro, length_dimension>
{
    using _base = details::unit_t<double, std::micro, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"micrometer"};

    [[maybe_unused]] static constexpr std::string_view symbol{"um"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5m"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5m"};
};

struct millimeter_t final : public details::unit_t<double, std::milli, length_dimension>
{
    using _base = details::unit_t<double, std::milli, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"millimeter"};

    [[maybe_unused]] static constexpr std::string_view symbol{"mm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mm"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mm"};
};

struct centimeter_t final : public details::unit_t<double, std::centi, length_dimension>
{
    using _base = details::unit_t<double, std::centi, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"centimeter"};

    [[maybe_unused]] static constexpr std::string_view symbol{"cm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cm"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cm"};
};

struct decimeter_t final : public details::unit_t<double, std::deci, length_dimension>
{
    using _base = details::unit_t<double, std::deci, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"decimeter"};

    [[maybe_unused]] static constexpr std::string_view symbol{"dm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dm"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dm"};
};

struct decameter_t final : public details::unit_t<double, std::deca, length_dimension>
{
    using _base = details::unit_t<double, std::deca, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"decameter"};

    [[maybe_unused]] static constexpr std::string_view symbol{"dam"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dam"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dam"};
};

struct hectometer_t final : public details::unit_t<double, std::hecto, length_dimension>
{
    using _base = details::unit_t<double, std::hecto, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"hectometer"};

    [[maybe_unused]] static constexpr std::string_view symbol{"hm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"hm"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"hm"};
};

struct kilometer_t final : public details::unit_t<double, std::kilo, length_dimension>
{
    using _base = details::unit_t<double, std::kilo, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilometer"};

    [[maybe_unused]] static constexpr std::string_view symbol{"km"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"km"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"km"};
};

struct megameter_t final : public details::unit_t<double, std::mega, length_dimension>
{
    using _base = details::unit_t<double, std::mega, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megameter"};

    [[maybe_unused]] static constexpr std::string_view symbol{"Mm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Mm"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Mm"};
};

struct gigameter_t final : public details::unit_t<double, std::giga, length_dimension>
{
    using _base = details::unit_t<double, std::giga, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gigameter"};

    [[maybe_unused]] static constexpr std::string_view symbol{"Gm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Gm"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Gm"};
};

struct terameter_t final : public details::unit_t<double, std::tera, length_dimension>
{
    using _base = details::unit_t<double, std::tera, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"terameter"};

    [[maybe_unused]] static constexpr std::string_view symbol{"Tm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Tm"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Tm"};
};

struct petameter_t final : public details::unit_t<double, std::peta, length_dimension>
{
    using _base = details::unit_t<double, std::peta, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"petameter"};

    [[maybe_unused]] static constexpr std::string_view symbol{"Pm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Pm"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Pm"};
};

struct exameter_t final : public details::unit_t<double, std::exa, length_dimension>
{
    using _base = details::unit_t<double, std::exa, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"exameter"};

    [[maybe_unused]] static constexpr std::string_view symbol{"Em"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Em"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Em"};
};

// ============================================================================
// Most derived unit type specializations for length units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, length_dimension>
{
    using type = meter_t;
};

template <>
struct details::derived_unit_type_t<double, std::atto, length_dimension>
{
    using type = attometer_t;
};

template <>
struct details::derived_unit_type_t<double, std::femto, length_dimension>
{
    using type = femtometer_t;
};

template <>
struct details::derived_unit_type_t<double, std::pico, length_dimension>
{
    using type = picometer_t;
};

template <>
struct details::derived_unit_type_t<double, std::nano, length_dimension>
{
    using type = nanometer_t;
};

template <>
struct details::derived_unit_type_t<double, std::micro, length_dimension>
{
    using type = micrometer_t;
};

template <>
struct details::derived_unit_type_t<double, std::milli, length_dimension>
{
    using type = millimeter_t;
};

template <>
struct details::derived_unit_type_t<double, std::centi, length_dimension>
{
    using type = centimeter_t;
};

template <>
struct details::derived_unit_type_t<double, std::deci, length_dimension>
{
    using type = decimeter_t;
};

template <>
struct details::derived_unit_type_t<double, std::deca, length_dimension>
{
    using type = decameter_t;
};

template <>
struct details::derived_unit_type_t<double, std::hecto, length_dimension>
{
    using type = hectometer_t;
};

template <>
struct details::derived_unit_type_t<double, std::kilo, length_dimension>
{
    using type = kilometer_t;
};

template <>
struct details::derived_unit_type_t<double, std::mega, length_dimension>
{
    using type = megameter_t;
};

template <>
struct details::derived_unit_type_t<double, std::giga, length_dimension>
{
    using type = gigameter_t;
};

template <>
struct details::derived_unit_type_t<double, std::tera, length_dimension>
{
    using type = terameter_t;
};

template <>
struct details::derived_unit_type_t<double, std::peta, length_dimension>
{
    using type = petameter_t;
};

template <>
struct details::derived_unit_type_t<double, std::exa, length_dimension>
{
    using type = exameter_t;
};

} // namespace PKR_UNITS_NAMESPACE
