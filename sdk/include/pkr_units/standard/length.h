#pragma once

#include "../impl/namespace_config.h"
#include "../impl/common/unit.h"
#include "../impl/common/length_def.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Strong type for meter (SI base unit)
struct meter_t final : public details::unit_t<double, std::ratio<1, 1>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"meter"};
    static constexpr std::string_view symbol{"m"};
    static constexpr std::wstring_view w_symbol{L"m"};
    static constexpr std::u8string_view u8_symbol{u8"m"};
};

// Metric length prefixes (strong types)
struct attometer_t final : public details::unit_t<double, std::atto, length_dimension>
{
    using _base = details::unit_t<double, std::atto, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"attometer"};
    static constexpr std::string_view symbol{"am"};
    static constexpr std::wstring_view w_symbol{L"am"};
    static constexpr std::u8string_view u8_symbol{u8"am"};
};

struct femtometer_t final : public details::unit_t<double, std::femto, length_dimension>
{
    using _base = details::unit_t<double, std::femto, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"femtometer"};
    static constexpr std::string_view symbol{"fm"};
    static constexpr std::wstring_view w_symbol{L"fm"};
    static constexpr std::u8string_view u8_symbol{u8"fm"};
};

struct picometer_t final : public details::unit_t<double, std::pico, length_dimension>
{
    using _base = details::unit_t<double, std::pico, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"picometer"};
    static constexpr std::string_view symbol{"pm"};
    static constexpr std::wstring_view w_symbol{L"pm"};
    static constexpr std::u8string_view u8_symbol{u8"pm"};
};

struct nanometer_t final : public details::unit_t<double, std::nano, length_dimension>
{
    using _base = details::unit_t<double, std::nano, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanometer"};
    static constexpr std::string_view symbol{"nm"};
    static constexpr std::wstring_view w_symbol{L"nm"};
    static constexpr std::u8string_view u8_symbol{u8"nm"};
};

struct micrometer_t final : public details::unit_t<double, std::micro, length_dimension>
{
    using _base = details::unit_t<double, std::micro, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"micrometer"};
    static constexpr std::string_view symbol{"um"};
    static constexpr std::wstring_view w_symbol{L"µm"};
    static constexpr std::u8string_view u8_symbol{u8"µm"};
};

struct millimeter_t final : public details::unit_t<double, std::milli, length_dimension>
{
    using _base = details::unit_t<double, std::milli, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millimeter"};
    static constexpr std::string_view symbol{"mm"};
    static constexpr std::wstring_view w_symbol{L"mm"};
    static constexpr std::u8string_view u8_symbol{u8"mm"};
};

struct centimeter_t final : public details::unit_t<double, std::centi, length_dimension>
{
    using _base = details::unit_t<double, std::centi, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"centimeter"};
    static constexpr std::string_view symbol{"cm"};
    static constexpr std::wstring_view w_symbol{L"cm"};
    static constexpr std::u8string_view u8_symbol{u8"cm"};
};

struct decimeter_t final : public details::unit_t<double, std::deci, length_dimension>
{
    using _base = details::unit_t<double, std::deci, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decimeter"};
    static constexpr std::string_view symbol{"dm"};
    static constexpr std::wstring_view w_symbol{L"dm"};
    static constexpr std::u8string_view u8_symbol{u8"dm"};
};

struct decameter_t final : public details::unit_t<double, std::deca, length_dimension>
{
    using _base = details::unit_t<double, std::deca, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decameter"};
    static constexpr std::string_view symbol{"dam"};
    static constexpr std::wstring_view w_symbol{L"dam"};
    static constexpr std::u8string_view u8_symbol{u8"dam"};
};

struct hectometer_t final : public details::unit_t<double, std::hecto, length_dimension>
{
    using _base = details::unit_t<double, std::hecto, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hectometer"};
    static constexpr std::string_view symbol{"hm"};
    static constexpr std::wstring_view w_symbol{L"hm"};
    static constexpr std::u8string_view u8_symbol{u8"hm"};
};

struct kilometer_t final : public details::unit_t<double, std::kilo, length_dimension>
{
    using _base = details::unit_t<double, std::kilo, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilometer"};
    static constexpr std::string_view symbol{"km"};
    static constexpr std::wstring_view w_symbol{L"km"};
    static constexpr std::u8string_view u8_symbol{u8"km"};
};

struct megameter_t final : public details::unit_t<double, std::mega, length_dimension>
{
    using _base = details::unit_t<double, std::mega, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megameter"};
    static constexpr std::string_view symbol{"Mm"};
    static constexpr std::wstring_view w_symbol{L"Mm"};
    static constexpr std::u8string_view u8_symbol{u8"Mm"};
};

struct gigameter_t final : public details::unit_t<double, std::giga, length_dimension>
{
    using _base = details::unit_t<double, std::giga, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gigameter"};
    static constexpr std::string_view symbol{"Gm"};
    static constexpr std::wstring_view w_symbol{L"Gm"};
    static constexpr std::u8string_view u8_symbol{u8"Gm"};
};

struct terameter_t final : public details::unit_t<double, std::tera, length_dimension>
{
    using _base = details::unit_t<double, std::tera, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"terameter"};
    static constexpr std::string_view symbol{"Tm"};
    static constexpr std::wstring_view w_symbol{L"Tm"};
    static constexpr std::u8string_view u8_symbol{u8"Tm"};
};

struct petameter_t final : public details::unit_t<double, std::peta, length_dimension>
{
    using _base = details::unit_t<double, std::peta, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"petameter"};
    static constexpr std::string_view symbol{"Pm"};
    static constexpr std::wstring_view w_symbol{L"Pm"};
    static constexpr std::u8string_view u8_symbol{u8"Pm"};
};

struct exameter_t final : public details::unit_t<double, std::exa, length_dimension>
{
    using _base = details::unit_t<double, std::exa, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"exameter"};
    static constexpr std::string_view symbol{"Em"};
    static constexpr std::wstring_view w_symbol{L"Em"};
    static constexpr std::u8string_view u8_symbol{u8"Em"};
};

// ============================================================================
// Most derived unit type specializations for length units
// ============================================================================

template<>
struct details::most_derived_unit_type<double, std::ratio<1, 1>, length_dimension>
{
    using type = meter_t;
};

template<>
struct details::most_derived_unit_type<double, std::atto, length_dimension>
{
    using type = attometer_t;
};

template<>
struct details::most_derived_unit_type<double, std::femto, length_dimension>
{
    using type = femtometer_t;
};

template<>
struct details::most_derived_unit_type<double, std::pico, length_dimension>
{
    using type = picometer_t;
};

template<>
struct details::most_derived_unit_type<double, std::nano, length_dimension>
{
    using type = nanometer_t;
};

template<>
struct details::most_derived_unit_type<double, std::micro, length_dimension>
{
    using type = micrometer_t;
};

template<>
struct details::most_derived_unit_type<double, std::milli, length_dimension>
{
    using type = millimeter_t;
};

template<>
struct details::most_derived_unit_type<double, std::centi, length_dimension>
{
    using type = centimeter_t;
};

template<>
struct details::most_derived_unit_type<double, std::deci, length_dimension>
{
    using type = decimeter_t;
};

template<>
struct details::most_derived_unit_type<double, std::deca, length_dimension>
{
    using type = decameter_t;
};

template<>
struct details::most_derived_unit_type<double, std::hecto, length_dimension>
{
    using type = hectometer_t;
};

template<>
struct details::most_derived_unit_type<double, std::kilo, length_dimension>
{
    using type = kilometer_t;
};

template<>
struct details::most_derived_unit_type<double, std::mega, length_dimension>
{
    using type = megameter_t;
};

template<>
struct details::most_derived_unit_type<double, std::giga, length_dimension>
{
    using type = gigameter_t;
};

template<>
struct details::most_derived_unit_type<double, std::tera, length_dimension>
{
    using type = terameter_t;
};

template<>
struct details::most_derived_unit_type<double, std::peta, length_dimension>
{
    using type = petameter_t;
};

template<>
struct details::most_derived_unit_type<double, std::exa, length_dimension>
{
    using type = exameter_t;
};

}  // namespace PKR_UNITS_NAMESPACE